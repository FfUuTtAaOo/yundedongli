/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <assert.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void uart_debug(const char *msg);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NTC_Pin GPIO_PIN_2
#define NTC_GPIO_Port GPIOA
#define SPI1_CS1_Pin GPIO_PIN_4
#define SPI1_CS1_GPIO_Port GPIOA
#define SPI1_CS2_Pin GPIO_PIN_0
#define SPI1_CS2_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define SYNC1_Pin GPIO_PIN_8
#define SYNC1_GPIO_Port GPIOA
#define SYNC1_EXTI_IRQn EXTI9_5_IRQn
#define SYNC0_Pin GPIO_PIN_9
#define SYNC0_GPIO_Port GPIOA
#define SYNC0_EXTI_IRQn EXTI9_5_IRQn
#define IRQ_Pin GPIO_PIN_10
#define IRQ_GPIO_Port GPIOA
#define IRQ_EXTI_IRQn EXTI15_10_IRQn

/* USER CODE BEGIN Private defines */
#define RS485_TX    { HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); HAL_Delay(10); }
#define RS485_RX    { HAL_Delay(10); HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); }

typedef union {
    float f32;
    uint32_t u32;
} floatuint_t;

#define U32_TO_U8(u32, u8, offset)  (u8) = (((u32) >> (offset)) & 0xFF)
#define UINT8_EQUAL(a, b) ((a) == (b))
#define U8_TO_U32_SAFE(u8_val, u32_val, index) \
  ({ \
    assert((index) < 4); \
    ((u32_val & ~(0xFFUL << ((index) * 8))) | (((uint32_t)(u8_val)) << ((index) * 8))); \
  })

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
