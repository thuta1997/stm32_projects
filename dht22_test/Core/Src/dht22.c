/*
 * dht22.c
 *
 *  Created on: Oct 20, 2026
 *      Author: Thu Ta
 */


#include "dht22.h"

/* DHT22 timing */
#define DHT22_START_LOW_US       1200U
#define DHT22_START_RELEASE_US     30U
#define DHT22_TIMEOUT_US          120U
#define DHT22_BIT_THRESHOLD_US     40U
#define DHT22_MIN_INTERVAL_MS    2000U

static TIM_HandleTypeDef *dht22_tim = NULL;
static uint32_t last_read_tick = 0U;
static uint8_t has_read_before = 0U;

/* TIM2 counter runs at 1 MHz: one count = one microsecond. */
static void delay_us(uint32_t us)
{
    uint32_t start = __HAL_TIM_GET_COUNTER(dht22_tim);

    while ((uint32_t)(__HAL_TIM_GET_COUNTER(dht22_tim) - start) < us)
    {
        /* Busy wait */
    }
}

/* Wait until DATA reaches the requested level, with timeout. */
static uint8_t wait_level(GPIO_TypeDef *GPIOx,
                          uint16_t GPIO_Pin,
                          GPIO_PinState level,
                          uint32_t timeout_us)
{
    uint32_t start = __HAL_TIM_GET_COUNTER(dht22_tim);

    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != level)
    {
        if ((uint32_t)(__HAL_TIM_GET_COUNTER(dht22_tim) - start)
            >= timeout_us)
        {
            return 0U;
        }
    }

    return 1U;
}

/* Set DATA as open-drain output. */
static void data_output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = GPIO_Pin;
    gpio.Mode = GPIO_MODE_OUTPUT_OD;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOx, &gpio);
}

/* Release DATA and read it as an input. */
static void data_input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef gpio = {0};

    gpio.Pin = GPIO_Pin;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOx, &gpio);
}

DHT22_Status_t DHT22_Init(TIM_HandleTypeDef *htim)
{
    RCC_ClkInitTypeDef clk_config = {0};
    uint32_t flash_latency = 0U;
    uint32_t pclk1;
    uint32_t timer_clock;
    uint32_t divider;

    if (htim == NULL || htim->Instance != TIM2)
    {
        return DHT22_ERROR_ARGUMENT;
    }

    __HAL_RCC_TIM2_CLK_ENABLE();

    /*
     * Derive the APB1 timer clock from the current clock configuration.
     * For STM32F446, APB1 timers run at 2 x PCLK1 when
     * the APB1 prescaler is greater than 1.
     */
    HAL_RCC_GetClockConfig(&clk_config, &flash_latency);
    pclk1 = HAL_RCC_GetPCLK1Freq();

    timer_clock = pclk1;

    if (clk_config.APB1CLKDivider != RCC_HCLK_DIV1)
    {
        timer_clock = pclk1 * 2U;
    }

    if ((timer_clock < 1000000U) ||
        ((timer_clock % 1000000U) != 0U))
    {
        return DHT22_ERROR_TIMER;
    }

    divider = timer_clock / 1000000U;

    htim->Instance = TIM2;
    htim->Init.Prescaler = divider - 1U;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.Period = 0xFFFFFFFFU;
    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(htim) != HAL_OK)
    {
        return DHT22_ERROR_TIMER;
    }

    __HAL_TIM_SET_COUNTER(htim, 0U);

    if (HAL_TIM_Base_Start(htim) != HAL_OK)
    {
        return DHT22_ERROR_TIMER;
    }

    dht22_tim = htim;
    last_read_tick = 0U;
    has_read_before = 0U;

    return DHT22_OK;
}

DHT22_Status_t DHT22_Read(GPIO_TypeDef *GPIOx,
                          uint16_t GPIO_Pin,
                          DHT22_Data_t *data)
{
    uint8_t raw[5] = {0};
    uint8_t bit;
    uint8_t i;
    uint32_t high_start;
    uint32_t high_width;
    uint16_t raw_humidity;
    uint16_t raw_temperature;
    uint8_t checksum;

    if ((dht22_tim == NULL) || (GPIOx == NULL) ||
        (GPIO_Pin == 0U) || (data == NULL))
    {
        return DHT22_ERROR_ARGUMENT;
    }

    /* Respect the DHT22 minimum sampling interval. */
    if (has_read_before != 0U)
    {
        uint32_t elapsed = HAL_GetTick() - last_read_tick;

        if (elapsed < DHT22_MIN_INTERVAL_MS)
        {
            HAL_Delay(DHT22_MIN_INTERVAL_MS - elapsed);
        }
    }

    /*
     * Host start signal:
     * Pull DATA low for at least 1 ms, then release it.
     */
    data_output(GPIOx, GPIO_Pin);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    delay_us(DHT22_START_LOW_US);

    /* Open-drain SET releases the line high. */
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
    delay_us(DHT22_START_RELEASE_US);
    data_input(GPIOx, GPIO_Pin);

    /* Sensor response: LOW, then HIGH, then LOW. */
    if (!wait_level(GPIOx, GPIO_Pin, GPIO_PIN_RESET,
                    DHT22_TIMEOUT_US))
    {
        goto timeout;
    }

    if (!wait_level(GPIOx, GPIO_Pin, GPIO_PIN_SET,
                    DHT22_TIMEOUT_US))
    {
        goto timeout;
    }

    if (!wait_level(GPIOx, GPIO_Pin, GPIO_PIN_RESET,
                    DHT22_TIMEOUT_US))
    {
        goto timeout;
    }

    /* Read 40 bits, MSB first. */
    for (i = 0U; i < 40U; i++)
    {
        /* Each data bit starts with a LOW pulse. */
        if (!wait_level(GPIOx, GPIO_Pin, GPIO_PIN_SET,
                        DHT22_TIMEOUT_US))
        {
            goto timeout;
        }

        high_start = __HAL_TIM_GET_COUNTER(dht22_tim);

        /* A falling edge ends the data bit's HIGH pulse. */
        if (!wait_level(GPIOx, GPIO_Pin, GPIO_PIN_RESET,
                        DHT22_TIMEOUT_US))
        {
            goto timeout;
        }

        high_width =
            (uint32_t)(__HAL_TIM_GET_COUNTER(dht22_tim) - high_start);

        bit = (high_width > DHT22_BIT_THRESHOLD_US) ? 1U : 0U;

        raw[i / 8U] <<= 1U;
        raw[i / 8U] |= bit;
    }

    /* Validate the 8-bit checksum. */
    checksum = (uint8_t)(raw[0] + raw[1] + raw[2] + raw[3]);

    if (checksum != raw[4])
    {
        return DHT22_ERROR_CHECKSUM;
    }

    /* Humidity is an unsigned 16-bit value in tenths of a percent. */
    raw_humidity = (uint16_t)(((uint16_t)raw[0] << 8U) | raw[1]);

    /* Temperature uses bit 15 as the sign bit. */
    raw_temperature =
        (uint16_t)(((uint16_t)raw[2] << 8U) | raw[3]);

    data->humidity = (float)raw_humidity / 10.0f;

    if ((raw_temperature & 0x8000U) != 0U)
    {
        /* Negative temperature: clear sign bit to obtain magnitude. */
        raw_temperature &= 0x7FFFU;
        data->temperature = -((float)raw_temperature / 10.0f);
    }
    else
    {
        data->temperature = (float)raw_temperature / 10.0f;
    }

    last_read_tick = HAL_GetTick();
    has_read_before = 1U;

    return DHT22_OK;

timeout:
    /* Leave the open-drain DATA line released. */
    data_output(GPIOx, GPIO_Pin);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

    return DHT22_ERROR_TIMEOUT;
}

