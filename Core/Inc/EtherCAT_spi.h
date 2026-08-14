/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               TouchPanel.h
** Descriptions:            The TouchPanel application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef _TOUCHPANEL_H_
#define _TOUCHPANEL_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


  #define SPIx                           SPI2
  #define SPIx_CLK                       RCC_APB1Periph_SPI2
  #define SPIx_CLK_INIT                  RCC_APB1PeriphClockCmd

  #define SPIx_SCK_PIN                   GPIO_Pin_13
  #define SPIx_SCK_GPIO_PORT             GPIOB
  #define SPIx_SCK_GPIO_CLK              RCC_APB2Periph_GPIOB

  #define SPIx_MISO_PIN                  GPIO_Pin_14
  #define SPIx_MISO_GPIO_PORT            GPIOB
  #define SPIx_MISO_GPIO_CLK             RCC_APB2Periph_GPIOB

  #define SPIx_MOSI_PIN                  GPIO_Pin_15
  #define SPIx_MOSI_GPIO_PORT            GPIOB
  #define SPIx_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOB

#define DESELECT_SPI 		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  //GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define SELECT_SPI 			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  //GPIO_ResetBits(GPIOE,GPIO_Pin_2)


#define CSLOW()      SELECT_SPI
#define CSHIGH()     DESELECT_SPI

#define SPIWriteByte SPIWrite
#define SPIReadByte() SPIRead()



	// *****************************************************************************
	// *****************************************************************************
	// Section: File Scope or Global Data Types
	// *****************************************************************************
	// *****************************************************************************
	#define CMD_SERIAL_READ 0x03
	#define CMD_FAST_READ 0x0B
	#define CMD_DUAL_OP_READ 0x3B
	#define CMD_DUAL_IO_READ 0xBB
	#define CMD_QUAD_OP_READ 0x6B
	#define CMD_QUAD_IO_READ 0xEB
	#define CMD_SERIAL_WRITE 0x02
	#define CMD_DUAL_DATA_WRITE 0x32
	#define CMD_DUAL_ADDR_DATA_WRITE 0xB2
	#define CMD_QUAD_DATA_WRITE 0x62
	#define CMD_QUAD_ADDR_DARA_WRITE 0xE2

	#define CMD_SERIAL_READ_DUMMY 0
	/* FCE1353 的 FAST READ 需要 3 个 dummy 字节（LAN9252 只需 1 个）。
	   实测：dummy 不足时，前几个读周期 MISO 保持高电平，读回 0xFF，
	   只有凑满 3 个 dummy 后才能读到有效数据 */
	#define CMD_FAST_READ_DUMMY 	3
	#define CMD_DUAL_OP_READ_DUMMY 1
	#define CMD_DUAL_IO_READ_DUMMY 2
	#define CMD_QUAD_OP_READ_DUMMY 1
	#define CMD_QUAD_IO_READ_DUMMY 4
	#define CMD_SERIAL_WRITE_DUMMY 0
	#define CMD_DUAL_DATA_WRITE_DUMMY 0
	#define CMD_DUAL_ADDR_DATA_WRITE_DUMMY 0
	#define CMD_QUAD_DATA_WRITE_DUMMY 0
	#define CMD_QUAD_ADDR_DARA_WRITE_DUMMY 0

	#define ESC_CSR_CMD_REG		0x304
	#define ESC_CSR_DATA_REG	0x300
	#define ESC_WRITE_BYTE 		0x80
	#define ESC_READ_BYTE 		0xC0
	#define ESC_CSR_BUSY		0x80


	/////////////////////////////////////////////////////////////////////////////////
	
	
typedef union
{
	uint32_t Val;
	uint8_t v[4];
	uint16_t w[2];
	struct
	{
		uint8_t LB;
		uint8_t HB;	
		uint8_t UB;
		uint8_t MB;
	}byte;
}UINT32_VAL;


typedef union
{
	uint16_t Val;
	struct
	{
		uint8_t LB;
		uint8_t HB;	
	}byte;
}UINT16_VAL;


///////////////////////////////////////////////////////////////////////////////////////




/* Private function prototypes -----------------------------------------------*/
uint8_t WR_CMD (uint8_t cmd);
void ADC_GPIO_Configuration(void);
void ADC_Configuration(void);
void Dac1_Init(void);
void NVIC_Configuration(void);
void TIM_Configuration(uint8_t period)	;
void EXTI1_Configuration(void);
void EXTI2_Configuration(void);
void EXTI0_Configuration(void);
void SPIReadDRegister(uint8_t *ReadBuffer, uint16_t Address, uint16_t Count);
void SPIWriteRegister( uint8_t *WriteBuffer, uint16_t Address, uint16_t Count);
uint32_t SPIReadDWord (uint16_t Address);
void SPIWriteDWord (uint16_t Address, uint32_t Val);
uint32_t SPIFastReadDWord (uint16_t Address);

void mem_test(void);
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


