/**
 * STM32F411CE Blackpill - LED Blink with FreeRTOS
 *
 * Blinks the onboard LED (PC13) at 1 second interval using FreeRTOS task.
 */

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_PIN         GPIO_PIN_13
#define LED_GPIO_PORT   GPIOC

void SystemClock_Config(void);
static void GPIO_Init(void);
void Error_Handler(void);

/**
 * LED blink task
 */
static void LedBlinkTask(void *pvParameters)
{
    (void)pvParameters;

    while (1) {
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);  // LED ON (active low)
        vTaskDelay(pdMS_TO_TICKS(1000));

        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);    // LED OFF
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    // Initialize HAL
    HAL_Init();

    // Configure system clock
    SystemClock_Config();

    // Initialize GPIO
    GPIO_Init();

    // Create LED blink task
    xTaskCreate(
        LedBlinkTask,       // Task function
        "LedBlink",         // Task name
        128,                // Stack size (words)
        NULL,               // Parameters
        1,                  // Priority
        NULL                // Task handle
    );

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1) {
    }
}

/**
 * GPIO initialization
 */
static void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOC clock
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Configure PC13 as output
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    // Set initial state (LED OFF)
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
}

/**
 * System clock configuration
 * Using HSE (25MHz) with PLL to get 100MHz system clock
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Configure power regulator voltage scale
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // Configure HSE and PLL
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 200;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    // Configure system clock
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * Error handler
 */
void Error_Handler(void)
{
    __disable_irq();
    while (1) {
        // Stay here on error
    }
}

/**
 * HAL tick increment (called from SysTick handler in FreeRTOS port)
 */
void HAL_IncTick_Callback(void)
{
    HAL_IncTick();
}
