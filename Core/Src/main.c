/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "calibration.h"
#include "filter.h"
#include "lha7668-8.h"
#include "self_test.h"
#include "rs485_cmd.h"
#include "sensor_types.h"
#include "flash_storage.h"
#include "at24c04.h"
#include "six_component_force.h"
#include "applInterface.h"
#include "ecat_def.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static volatile uint32_t g_tick_ms = 0;

/* Shared global state (declared in sensor_types.h) */
volatile sensor_data_t   g_sensor;
volatile system_state_t  g_sys;
config_t                 g_config = {
    .sn         = "HS-01234567",
    .fw_version = 0x0100,
};
decouple_matrix_t        g_matrix;

uint8_t output_interface = 0;
uint8_t ether_flag = 1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define ADC_DATA_BUFF_LEN       64
#define ADC_CHANNEL_NUM         6
#define KILOGRAM_TO_NEWTON      9.8

static uint8_t adc_data_int_count = 0;
static uint8_t adc_data_usr_count = 0;
static uint32_t adc_data_buff[ADC_DATA_BUFF_LEN][6] = { 0 };


static float adc_data_calculate(uint8_t index)
{
    return (float)((int32_t)adc_data_buff[adc_data_usr_count][index] - 0x800000) * (1.0f / 8388608.0f) * 2500;
}

float matrix[6][6] = { {0.298418, -0.211604, -0.529767, -0.012232, -0.178473, 0.211071 },
                        {0.004134, 0.211038, -0.006878, 0.007002, -0.001183, -0.001670 },
                        {0.006217, -0.000427, 0.558141, 0.003760, -0.004378, -0.142885 },
                        {-0.000174, -0.000562, 0.001114, 0.001136, 0.000010, -0.000292 },
                        {-0.000243, -0.000483, -0.003015, -0.000066, -0.001470, 0.001025 },
                        {0.000317, -0.000204, -0.000423, -0.000031, -0.000158, 0.001769 }};

static void adc_data_proc(float data[6])
{
    // int i = 0;
    // if (g_sys.data_format == 0) {
    //     for (i = 0; i < ADC_CHANNEL_NUM; i++) {
    //         g_sensor.force[i] = data[i];
    //     }
    // } else if (g_sys.data_format == 1) {
    //     g_sensor.force[0] = matrix[0][0] * data[0] / KILOGRAM_TO_NEWTON + matrix[0][1] * data[1] / KILOGRAM_TO_NEWTON +
    //                 matrix[0][2] * data[2] / KILOGRAM_TO_NEWTON + matrix[0][3] * data[3] / KILOGRAM_TO_NEWTON +
    //                 matrix[0][4] * data[4] / KILOGRAM_TO_NEWTON + matrix[0][5] * data[5] / KILOGRAM_TO_NEWTON;

    //     g_sensor.force[1] = matrix[1][0] * data[0] / KILOGRAM_TO_NEWTON + matrix[1][1] * data[1] / KILOGRAM_TO_NEWTON +
    //                 matrix[1][2] * data[2] / KILOGRAM_TO_NEWTON + matrix[1][3] * data[3] / KILOGRAM_TO_NEWTON +
    //                 matrix[1][4] * data[4] / KILOGRAM_TO_NEWTON + matrix[1][5] * data[5] / KILOGRAM_TO_NEWTON;

    //     g_sensor.force[2] = matrix[2][0] * data[0] / KILOGRAM_TO_NEWTON + matrix[2][1] * data[1] / KILOGRAM_TO_NEWTON +
    //                 matrix[2][2] * data[2] / KILOGRAM_TO_NEWTON + matrix[2][3] * data[3] / KILOGRAM_TO_NEWTON +
    //                 matrix[2][4] * data[4] / KILOGRAM_TO_NEWTON + matrix[2][5] * data[5] / KILOGRAM_TO_NEWTON;

    //     g_sensor.force[3] = matrix[3][0] * data[0] / KILOGRAM_TO_NEWTON + matrix[3][1] * data[1] / KILOGRAM_TO_NEWTON +
    //                 matrix[3][2] * data[2] / KILOGRAM_TO_NEWTON + matrix[3][3] * data[3] / KILOGRAM_TO_NEWTON +
    //                 matrix[3][4] * data[4] / KILOGRAM_TO_NEWTON + matrix[3][5] * data[5] / KILOGRAM_TO_NEWTON;

    //     g_sensor.force[4] = matrix[4][0] * data[0] / KILOGRAM_TO_NEWTON + matrix[4][1] * data[1] / KILOGRAM_TO_NEWTON +
    //                 matrix[4][2] * data[2] / KILOGRAM_TO_NEWTON + matrix[4][3] * data[3] / KILOGRAM_TO_NEWTON +
    //                 matrix[4][4] * data[4] / KILOGRAM_TO_NEWTON + matrix[4][5] * data[5] / KILOGRAM_TO_NEWTON;

    //     g_sensor.force[5] = matrix[5][0] * data[0] / KILOGRAM_TO_NEWTON + matrix[5][1] * data[1] / KILOGRAM_TO_NEWTON +
    //                 matrix[5][2] * data[2] / KILOGRAM_TO_NEWTON + matrix[5][3] * data[3] / KILOGRAM_TO_NEWTON +
    //                 matrix[5][4] * data[4] / KILOGRAM_TO_NEWTON + matrix[5][5] * data[5] / KILOGRAM_TO_NEWTON;
    // } else if (g_sys.data_format == 2) {
    //     g_sensor.force[0] = matrix[0][0] * data[0] + matrix[0][1] * data[1] +
    //                 matrix[0][2] * data[2] + matrix[0][3] * data[3] +
    //                 matrix[0][4] * data[4] + matrix[0][5] * data[5];

    //     g_sensor.force[1] = matrix[1][0] * data[0] + matrix[1][1] * data[1] +
    //                 matrix[1][2] * data[2] + matrix[1][3] * data[3] +
    //                 matrix[1][4] * data[4] + matrix[1][5] * data[5];

    //     g_sensor.force[2] = matrix[2][0] * data[0] + matrix[2][1] * data[1] +
    //                 matrix[2][2] * data[2] + matrix[2][3] * data[3] +
    //                 matrix[2][4] * data[4] + matrix[2][5] * data[5];

    //     g_sensor.force[3] = matrix[3][0] * data[0] + matrix[3][1] * data[1] +
    //                 matrix[3][2] * data[2] + matrix[3][3] * data[3] +
    //                 matrix[3][4] * data[4] + matrix[3][5] * data[5];

    //     g_sensor.force[4] = matrix[4][0] * data[0] + matrix[4][1] * data[1] +
    //                 matrix[4][2] * data[2] + matrix[4][3] * data[3] +
    //                 matrix[4][4] * data[4] + matrix[4][5] * data[5];

    //     g_sensor.force[5] = matrix[5][0] * data[0] + matrix[5][1] * data[1] +
    //                 matrix[5][2] * data[2] + matrix[5][3] * data[3] +
    //                 matrix[5][4] * data[4] + matrix[5][5] * data[5];
    // }
    int i = 0;
    if (g_sys.data_format == 0) {
        for (i = 0; i < ADC_CHANNEL_NUM; i++) {
            g_sensor.force[i] = data[i];
        }
    } else if (g_sys.data_format == 1) {
        g_sensor.force[0] = g_matrix.m[0][0] * data[0] / KILOGRAM_TO_NEWTON + g_matrix.m[0][1] * data[1] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[0][2] * data[2] / KILOGRAM_TO_NEWTON + g_matrix.m[0][3] * data[3] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[0][4] * data[4] / KILOGRAM_TO_NEWTON + g_matrix.m[0][5] * data[5] / KILOGRAM_TO_NEWTON;

        g_sensor.force[1] = g_matrix.m[1][0] * data[0] / KILOGRAM_TO_NEWTON + g_matrix.m[1][1] * data[1] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[1][2] * data[2] / KILOGRAM_TO_NEWTON + g_matrix.m[1][3] * data[3] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[1][4] * data[4] / KILOGRAM_TO_NEWTON + g_matrix.m[1][5] * data[5] / KILOGRAM_TO_NEWTON;

        g_sensor.force[2] = g_matrix.m[2][0] * data[0] / KILOGRAM_TO_NEWTON + g_matrix.m[2][1] * data[1] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[2][2] * data[2] / KILOGRAM_TO_NEWTON + g_matrix.m[2][3] * data[3] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[2][4] * data[4] / KILOGRAM_TO_NEWTON + g_matrix.m[2][5] * data[5] / KILOGRAM_TO_NEWTON;

        g_sensor.force[3] = g_matrix.m[3][0] * data[0] / KILOGRAM_TO_NEWTON + g_matrix.m[3][1] * data[1] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[3][2] * data[2] / KILOGRAM_TO_NEWTON + g_matrix.m[3][3] * data[3] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[3][4] * data[4] / KILOGRAM_TO_NEWTON + g_matrix.m[3][5] * data[5] / KILOGRAM_TO_NEWTON;

        g_sensor.force[4] = g_matrix.m[4][0] * data[0] / KILOGRAM_TO_NEWTON + g_matrix.m[4][1] * data[1] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[4][2] * data[2] / KILOGRAM_TO_NEWTON + g_matrix.m[4][3] * data[3] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[4][4] * data[4] / KILOGRAM_TO_NEWTON + g_matrix.m[4][5] * data[5] / KILOGRAM_TO_NEWTON;

        g_sensor.force[5] = g_matrix.m[5][0] * data[0] / KILOGRAM_TO_NEWTON + g_matrix.m[5][1] * data[1] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[5][2] * data[2] / KILOGRAM_TO_NEWTON + g_matrix.m[5][3] * data[3] / KILOGRAM_TO_NEWTON +
                    g_matrix.m[5][4] * data[4] / KILOGRAM_TO_NEWTON + g_matrix.m[5][5] * data[5] / KILOGRAM_TO_NEWTON;
    } else if (g_sys.data_format == 2) {
        g_sensor.force[0] = g_matrix.m[0][0] * data[0] + g_matrix.m[0][1] * data[1] +
                    g_matrix.m[0][2] * data[2] + g_matrix.m[0][3] * data[3] +
                    g_matrix.m[0][4] * data[4] + g_matrix.m[0][5] * data[5];

        g_sensor.force[1] = g_matrix.m[1][0] * data[0] + g_matrix.m[1][1] * data[1] +
                    g_matrix.m[1][2] * data[2] + g_matrix.m[1][3] * data[3] +
                    g_matrix.m[1][4] * data[4] + g_matrix.m[1][5] * data[5];

        g_sensor.force[2] = g_matrix.m[2][0] * data[0] + g_matrix.m[2][1] * data[1] +
                    g_matrix.m[2][2] * data[2] + g_matrix.m[2][3] * data[3] +
                    g_matrix.m[2][4] * data[4] + g_matrix.m[2][5] * data[5];

        g_sensor.force[3] = g_matrix.m[3][0] * data[0] + g_matrix.m[3][1] * data[1] +
                    g_matrix.m[3][2] * data[2] + g_matrix.m[3][3] * data[3] +
                    g_matrix.m[3][4] * data[4] + g_matrix.m[3][5] * data[5];

        g_sensor.force[4] = g_matrix.m[4][0] * data[0] + g_matrix.m[4][1] * data[1] +
                    g_matrix.m[4][2] * data[2] + g_matrix.m[4][3] * data[3] +
                    g_matrix.m[4][4] * data[4] + g_matrix.m[4][5] * data[5];

        g_sensor.force[5] = g_matrix.m[5][0] * data[0] + g_matrix.m[5][1] * data[1] +
                    g_matrix.m[5][2] * data[2] + g_matrix.m[5][3] * data[3] +
                    g_matrix.m[5][4] * data[4] + g_matrix.m[5][5] * data[5];
    }

    for (i = 0; i < ADC_CHANNEL_NUM; i++) {
        g_sensor.force[i] = FloatFilter_UpdateChannel(i, g_sensor.force[i]);
    }
}

void uart_debug(const char *msg)
{
    RS485_TX;
    HAL_UART_Transmit(&huart1, (const uint8_t *)msg, (uint16_t)strlen(msg), 100);
    RS485_RX;
}

/* Interrupt function callback -----------------------------------------------*/
void USART1_IRQHandler(void)
{
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE)) {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        if (huart1.hdmarx) {
            uint16_t rem = (uint16_t)__HAL_DMA_GET_COUNTER(huart1.hdmarx);
            rs485_rx_idle_cb(rem);
        }
    }
    HAL_UART_IRQHandler(&huart1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2) {
        g_tick_ms++;

        if (g_tick_ms % 3 == 0) {
            uint32_t raw;
            /* 六个通道分别对应 FX FY FZ TX TY TZ。
               任一通道读取失败(超时)时跳过写入，该通道保留上一次自己的有效值，
               避免把其他通道(如 FX)的数据错填到 FY/FZ 上 */
            if (int_adcData(&raw) == 0)   { adc_data_buff[adc_data_int_count][0] = raw; }
            if (int_adcData(&raw) == 0)   { adc_data_buff[adc_data_int_count][1] = raw; }
            if (int_adcData(&raw) == 0)   { adc_data_buff[adc_data_int_count][2] = raw; }
            if (int_adcData_2(&raw) == 0) { adc_data_buff[adc_data_int_count][3] = raw; }
            if (int_adcData_2(&raw) == 0) { adc_data_buff[adc_data_int_count][4] = raw; }
            if (int_adcData_2(&raw) == 0) { adc_data_buff[adc_data_int_count][5] = raw; }
            adc_data_int_count++;
            if (adc_data_int_count >= 64) {
                adc_data_int_count = 0;
            }
        }
    }
}

/* ---- Continuous RS485 data send state ---- */
static uint32_t g_last_rs485_send_ms;

void send_string(uint8_t *str, uint16_t len)
{
    RS485_TX;
    HAL_UART_Transmit(&huart1, (uint8_t *)str, len, 500);
    RS485_RX;
}

uint8_t hex_buf_send[256] = { 0 };
uint8_t mb_buf_send[33] = { 0 };

#define HEX_BUF_SEND_OFFSET 1

static void rs485_send_continuous(void)
{
    uint32_t interval = (g_sys.freq_mode == 0) ? 2U : 1U;  /* 500Hz or 1kHz */
    if ((g_tick_ms - g_last_rs485_send_ms) >= interval) {
        g_last_rs485_send_ms = g_tick_ms;

        if (g_sys.debug_mode == 0) {
            if (output_interface == 1) {
                /* Build data frame: AA 55 00 [SEQ4B] [6×float32] 0D 0A */
                // uint32_t seq = g_sys.frame_seq++;
                hex_buf_send[0] = RS485_CMD_CONT_DATA;
                // hex_buf_send[1] = (uint8_t)(seq);
                // hex_buf_send[2] = (uint8_t)(seq >> 8);
                // hex_buf_send[3] = (uint8_t)(seq >> 16);
                // hex_buf_send[4] = (uint8_t)(seq >> 24);
                for (int i = 0; i < 6; i++) {
                    float f = g_sensor.force[i];   /* read volatile once */
                    uint32_t u; memcpy(&u, &f, 4);
                    hex_buf_send[HEX_BUF_SEND_OFFSET + i * 4 + 0] = (uint8_t)(u);
                    hex_buf_send[HEX_BUF_SEND_OFFSET + i * 4 + 1] = (uint8_t)(u >> 8);
                    hex_buf_send[HEX_BUF_SEND_OFFSET + i * 4 + 2] = (uint8_t)(u >> 16);
                    hex_buf_send[HEX_BUF_SEND_OFFSET + i * 4 + 3] = (uint8_t)(u >> 24);
                }

                rs485_send_raw(hex_buf_send, 24 + HEX_BUF_SEND_OFFSET);
            }
        } else if (g_sys.debug_mode == 1) {
            for (int i = 0; i < 6; i++) {
                float f = g_sensor.force[i];   /* read volatile once */
                uint32_t u; memcpy(&u, &f, 4);
                hex_buf_send[i * 4 + 0] = (uint8_t)(u);
                hex_buf_send[i * 4 + 1] = (uint8_t)(u >> 8);
                hex_buf_send[i * 4 + 2] = (uint8_t)(u >> 16);
                hex_buf_send[i * 4 + 3] = (uint8_t)(u >> 24);
            }
            hex_buf_send[24] = 0x00;
            hex_buf_send[25] = 0x00;
            hex_buf_send[26] = 0x80;
            hex_buf_send[27] = 0x7F;
            just_float_send_raw(hex_buf_send, 28);
        }
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

    flash_load_all();

    calib_init();
    uart_debug("Data Transformation Layer Init OK\r\n");
    FloatFilter_Init();
    uart_debug("FloatFilter Init OK\r\n");

    HAL_GPIO_WritePin(GPIOA, SPI1_CS1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SPI1_CS2_Pin, GPIO_PIN_SET);

    lha7668_init(ADC_SAMPLING_RATE_3);
    uart_debug("LHA7668 OK\r\n");

    uart_debug("--- RS485 self-test ---\r\n");
    rs485_init(&huart1, rs485_cmd_dispatch);
    uint32_t st_rs485 = self_test_rs485();
    uart_debug(st_rs485 == ST_ERR_NONE ? "RS485 OK (USART+DMA)\r\n" : "RS485 FAIL\r\n");

    if (ethercat_hw_init() != 0)
    {
        uart_debug("EtherCAT SPI FAILED (BYTE_ORDER 0x64)\r\n");
    }
    else
    {
        uart_debug("EtherCAT SPI OK\r\n");
        MainInit();
        uart_debug("EtherCAT Init OK\r\n");
    }

    g_sys.data_format = 2;
    HAL_TIM_Base_Start_IT(&htim2);   /* Start 1kHz timer */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
        if (ether_flag == 1) {
            MainLoop();
        }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        // static uint32_t last_beat = 0;
        // /* ---- Heartbeat ---- */
        // if ((g_tick_ms - last_beat) >= 3000) {
        //     uart_debug(".\r\n");
        //     last_beat = g_tick_ms;
        // }

        {
            float adc_tmp[ADC_CHANNEL_NUM] = { 0 };

            if (adc_data_usr_count != adc_data_int_count) {
                adc_data_usr_count = adc_data_int_count;
                for (uint8_t i = 0; i < ADC_CHANNEL_NUM; i++) {
                    adc_tmp[i] = adc_data_calculate(i);

                    if (g_sys.zero_calib_busy == 0) {
                        adc_tmp[i] -= g_sensor.force_zero[i];
                    }
                }

                if (g_sys.zero_calib_busy == 1) {
                    calib_zero_cale(adc_tmp);
                }

                adc_data_proc(adc_tmp);
            }
        }

        if (calib_zero_is_done()) {
            g_sys.zero_calib_busy = 0;
            calib_zero_over();
            flash_save_zero();
            uart_debug("Zero calib done — saved to Flash\r\n");
        }

        if (g_sys.send_mode == 1) {
            rs485_send_continuous();
        } else {
            g_last_rs485_send_ms = g_tick_ms;   /* reset timer on stop */
        }

        rs485_process();
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
