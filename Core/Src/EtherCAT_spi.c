/****************************************Copyright (c)****************************************************
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               .c
** Descriptions:           SPI2 hardware driver
**
**--------------------------------------------------------------------------------------------------------
** Created by:             	 lyd
** Created date:            2015-05-01
** Version:                 		v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "EtherCAT_spi.h"
#include "ecat_def.h"
#include "el9800hw.h"
#include <stdio.h>

EXTI_HandleTypeDef hext0;
void EXTI0_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	EXTI_ConfigTypeDef EXTI_Config = { 0 };

	// 1. 配置PB0为输入模式
	__HAL_RCC_GPIOA_CLK_ENABLE();  // 使能GPIOA时钟
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;  // 下降沿触发中断
	GPIO_InitStruct.Pull = GPIO_NOPULL;           // 无上拉下拉
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// 2. 配置EXTI中断
	EXTI_Config.Line = EXTI_LINE_10;
	EXTI_Config.Mode = EXTI_MODE_INTERRUPT;
	EXTI_Config.Trigger = EXTI_TRIGGER_FALLING;
	EXTI_Config.GPIOSel = EXTI_GPIOA;
	HAL_EXTI_SetConfigLine(&hext0, &EXTI_Config);

	// 3. 清除中断标志位
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);

	// 4. 配置NVIC
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);  // 优先级1, 子优先级0
//	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

EXTI_HandleTypeDef hext1;
void EXTI1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	EXTI_ConfigTypeDef EXTI_Config = { 0 };

	// 1. 配置PB0为输入模式
	__HAL_RCC_GPIOA_CLK_ENABLE();  // 使能GPIOA时钟
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;  // 下降沿触发中断
	GPIO_InitStruct.Pull = GPIO_NOPULL;           // 无上拉下拉
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// 2. 配置EXTI中断
	EXTI_Config.Line = EXTI_LINE_9;
	EXTI_Config.Mode = EXTI_MODE_INTERRUPT;
	EXTI_Config.Trigger = EXTI_TRIGGER_FALLING;
	EXTI_Config.GPIOSel = EXTI_GPIOA;
	HAL_EXTI_SetConfigLine(&hext1, &EXTI_Config);

	// 3. 清除中断标志位
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);

	// 4. 配置NVIC
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 1);  // 优先级1, 子优先级1
//	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

EXTI_HandleTypeDef hext2;
void EXTI2_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	EXTI_ConfigTypeDef EXTI_Config = { 0 };

	// 1. 配置PB0为输入模式
	__HAL_RCC_GPIOA_CLK_ENABLE();  // 使能GPIOA时钟
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;  // 下降沿触发中断
	GPIO_InitStruct.Pull = GPIO_NOPULL;           // 无上拉下拉
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// 2. 配置EXTI中断
	EXTI_Config.Line = EXTI_LINE_8;
	EXTI_Config.Mode = EXTI_MODE_INTERRUPT;
	EXTI_Config.Trigger = EXTI_TRIGGER_FALLING;
	EXTI_Config.GPIOSel = EXTI_GPIOA;
	HAL_EXTI_SetConfigLine(&hext2, &EXTI_Config);

	// 3. 清除中断标志位
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);

	// 4. 配置NVIC
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 2);  // 优先级1, 子优先级2
//	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

/* SPI DMA 相关定义 */
#define SPI_TX_DMA_BUF_SIZE     (3 + MAX_PD_INPUT_SIZE)   /* 命令(1) + 地址(2) + 最大数据长度 */

/* DMA 双缓冲区 */
static volatile uint8_t active_dma_buf = 0;   /* 当前用于填充的缓冲区索引 */
static volatile uint8_t dma_busy = 0;         /* DMA 传输中标志 */

extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_tx;

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	CSHIGH();           /* 拉高片选，结束 SPI 帧 */
	dma_busy = 0;       /* 清除忙碌标志 */
}

/*******************************************************************************
* Function Name  : WR_CMD
* Description    : Read and Wire data to ET1100 
* Input          : - cmd: the data send to ET1100
* Output         : none
* Return         : temp: the data read from ET1100
* Attention      : None
*******************************************************************************/
uint8_t WR_CMD (uint8_t cmd)
{
//	SPI2->DR = cmd;
//	while ((SPI2->SR & SPI_FLAG_RXNE) == 0x00);
//	return SPI2->DR;
	uint8_t rx = 0;
	HAL_SPI_TransmitReceive(&hspi2, &cmd, &rx, 1U, HAL_MAX_DELAY);
	return rx;
}

/*******************************************************************************
* Function Name  : SPIWrite
* Description    : Wire byte data to FCE1353
* Input          : - data: the data send to ET1100
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIWrite(UINT8 data)
{
	WR_CMD(data);
}

/*******************************************************************************
* Function Name  : SPIRead
* Description    : read byte data from FCE1353
* Input          : none
* Output         : none
* Return         : data: read from FCE1353
* Attention		 : None
*******************************************************************************/
UINT8 SPIRead(void)
{
    UINT8 data;
    data = WR_CMD(0);
    return (data);
}

/*******************************************************************************
* Function Name  : SPIReadDWord
* Description    : read word data from FCE1353
* Input          : Address��the addreoss to be read from FCE1353
* Output         : none
* Return         : data: word data from FCE1353
* Attention		 : None
*******************************************************************************/
uint32_t SPIReadDWord (uint16_t Address)
{
	UINT32_VAL dwResult;
	UINT16_VAL wAddr;

	wAddr.Val  = Address;
	//Assert CS line
	CSLOW();
	//Write Command
	SPIWriteByte(CMD_SERIAL_READ);
	//Write Address
	SPIWriteByte(wAddr.byte.HB);
	SPIWriteByte(wAddr.byte.LB);

	//Read Bytes
	dwResult.byte.LB = SPIReadByte();
	dwResult.byte.HB = SPIReadByte();
	dwResult.byte.UB = SPIReadByte();
	dwResult.byte.MB = SPIReadByte();
	//De-Assert CS line
	CSHIGH();

	return dwResult.Val;
}

uint32_t SPIFastReadDWord (uint16_t Address)
{
	UINT32_VAL dwResult;
	UINT16_VAL wAddr;

	wAddr.Val  = Address;
	//Assert CS line
	CSLOW();
	//Write Command
	SPIWriteByte(CMD_FAST_READ);
	//Write Address
	SPIWriteByte(wAddr.byte.HB);
	SPIWriteByte(wAddr.byte.LB);

	//Dummy Byte
	SPIWriteByte(CMD_FAST_READ_DUMMY);
	SPIReadByte();
	//Read Bytes
	dwResult.byte.LB = SPIReadByte();
	dwResult.byte.HB = SPIReadByte();
	dwResult.byte.UB = SPIReadByte();
	dwResult.byte.MB = SPIReadByte();
	//De-Assert CS line
	CSHIGH();

	return dwResult.Val;
}

/*******************************************************************************
* Function Name  : SPISendAddr
* Description    : write address to FCE1353
* Input          : Address��the address write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPISendAddr (uint16_t Address)
{
    UINT16_VAL wAddr;

    wAddr.Val  = Address;
    //Write Address
    SPIWriteByte(wAddr.byte.HB);
    SPIWriteByte(wAddr.byte.LB);
}

/*******************************************************************************
* Function Name  : SPIReadBurstMode
* Description    : Read word from FCE1353 in burst mode
* Input          : none
* Output         : none
* Return         : word data from FCE1353
* Attention		 : None
*******************************************************************************/
UINT32 SPIReadBurstMode ()
{
    UINT32_VAL dwResult;
    //Read Bytes
    dwResult.byte.LB = SPIReadByte();
    dwResult.byte.HB = SPIReadByte();
    dwResult.byte.UB = SPIReadByte();
    dwResult.byte.MB = SPIReadByte();
    
    return dwResult.Val;
}

/*******************************************************************************
* Function Name  : SPIWriteBurstMode
* Description    : write data to FCE1353 in burst mode
* Input          : val��the data write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIWriteBurstMode (uint32_t Val)
{
    UINT32_VAL dwData;
    dwData.Val = Val;
    
    //Write Bytes
    SPIWriteByte(dwData.byte.LB);
    SPIWriteByte(dwData.byte.HB);
    SPIWriteByte(dwData.byte.UB);
    SPIWriteByte(dwData.byte.MB);
}
/*******************************************************************************
* Function Name  : SPIWriteDWord
* Description    : write Word FCE1353 in 
* Input          : Address the address write to FCE1353
										val��the data write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIWriteDWord (uint16_t Address, uint32_t Val)
{
    UINT32_VAL dwData;
    UINT16_VAL wAddr;

    wAddr.Val  = Address;
    dwData.Val = Val;
    //Assert CS line
    CSLOW();
    //Write Command
    SPIWriteByte(CMD_SERIAL_WRITE);
    //Write Address
    SPIWriteByte(wAddr.byte.HB);
    SPIWriteByte(wAddr.byte.LB);
    //Write Bytes
    SPIWriteByte(dwData.byte.LB);
    SPIWriteByte(dwData.byte.HB);
    SPIWriteByte(dwData.byte.UB);
    SPIWriteByte(dwData.byte.MB);

    //De-Assert CS line
    CSHIGH();
}

/*******************************************************************************
* Function Name  : SPIReadRegUsingCSR
* Description    : Read data from FCE1353 use CSR
* Input          : ReadBuffer:data buf 
									 Address��the reg address write to FCE1353
										Count:the number write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIReadRegUsingCSR(uint8_t *ReadBuffer, uint16_t Address, uint8_t Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;
    UINT16_VAL wAddr;
    wAddr.Val = Address;

    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_READ_BYTE;

    SPIWriteDWord (ESC_CSR_CMD_REG, param32_1.Val);

    do
    {
        param32_1.Val = SPIReadDWord (ESC_CSR_CMD_REG);
		
    }while(param32_1.v[3] & ESC_CSR_BUSY);

    param32_1.Val = SPIReadDWord (ESC_CSR_DATA_REG);

    
    for(i=0;i<Count;i++)
         ReadBuffer[i] = param32_1.v[i];
   
    return;
}

/*******************************************************************************
* Function Name  : SPIWriteRegUsingCSR
* Description    : write data to FCE1353 use CSR
* Input          : ReadBuffer:data buf 
									 Address��the reg address write to FCE1353
										Count:the number write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIWriteRegUsingCSR( uint8_t *WriteBuffer, uint16_t Address, uint8_t Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;
    UINT16_VAL wAddr;

    for(i=0;i<Count;i++)
         param32_1.v[i] = WriteBuffer[i];

    SPIWriteDWord (ESC_CSR_DATA_REG, param32_1.Val);


    wAddr.Val = Address;

    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_WRITE_BYTE;

    SPIWriteDWord (0x304, param32_1.Val);
    do
    {
        param32_1.Val = SPIReadDWord (0x304);

    }while(param32_1.v[3] & ESC_CSR_BUSY);

    return;
}


/*******************************************************************************
* Function Name  : SPIReadPDRamRegister
* Description    : read data from FCE1353 pd ram
* Input          : ReadBuffer:data buf 
									 Address��the reg address write to FCE1353
										Count:the number write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIReadPDRamRegister(uint8_t *ReadBuffer, uint16_t Address, uint16_t Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0,nlength, nBytePosition;
    UINT8 nReadSpaceAvblCount;

//    /*Reset/Abort any previous commands.*/
    param32_1.Val = (unsigned long int)PRAM_RW_ABORT_MASK;                                                 

    SPIWriteDWord (PRAM_READ_CMD_REG, param32_1.Val);

    /*The host should not modify this field unless the PRAM Read Busy
    (PRAM_READ_BUSY) bit is a 0.*/
    do
    {

			param32_1.Val = SPIReadDWord (PRAM_READ_CMD_REG);

    }while((param32_1.v[3] & PRAM_RW_BUSY_8B));

    /*Write address and length in the EtherCAT Process RAM Read Address and
     * Length Register (ECAT_PRAM_RD_ADDR_LEN)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

    SPIWriteDWord (PRAM_READ_ADDR_LEN_REG, param32_1.Val);


    /*Set PRAM Read Busy (PRAM_READ_BUSY) bit(-EtherCAT Process RAM Read Command Register)
     *  to start read operatrion*/

    param32_1.Val = PRAM_RW_BUSY_32B; /*TODO:replace with #defines*/

    SPIWriteDWord (PRAM_READ_CMD_REG, param32_1.Val);

		

    /*Read PRAM Read Data Available (PRAM_READ_AVAIL) bit is set*/
    do
    {			
      //  param32_1.Val
			param32_1.Val = SPIReadDWord (PRAM_READ_CMD_REG);
		

    }while(!(param32_1.v[0] & IS_PRAM_SPACE_AVBL_MASK));

    nReadSpaceAvblCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;

    /*Fifo registers are aliased address. In indexed it will read indexed data reg 0x04, but it will point to reg 0
     In other modes read 0x04 FIFO register since all registers are aliased*/

    /*get the UINT8 lenth for first read*/
    //Auto increment is supported in SPIO
    param32_1.Val = SPIReadDWord (PRAM_READ_FIFO_REG);
    nReadSpaceAvblCount--;
    nBytePosition = (Address & 0x03);
    nlength = (4-nBytePosition) > Count ? Count:(4-nBytePosition);
    memcpy(ReadBuffer+i ,&param32_1.v[nBytePosition],nlength);
    Count-=nlength;
    i+=nlength;

    //Lets do it in auto increment mode
    CSLOW();

    //Write Command
    SPIWriteByte(CMD_FAST_READ);

    SPISendAddr(PRAM_READ_FIFO_REG);
    
    //Dummy Byte
    SPIWriteByte(CMD_FAST_READ_DUMMY);

    while(Count)
    {
        param32_1.Val = SPIReadBurstMode();

        nlength = Count > 4 ? 4: Count;
        memcpy((ReadBuffer+i) ,&param32_1,nlength);

        i+=nlength;
        Count-=nlength;
        nReadSpaceAvblCount --;
    }

    CSHIGH();

    return;
}
/*******************************************************************************
* Function Name  : SPIWritePDRamRegister
* Description    : write data from FCE1353 pd ram
* Input          : ReadBuffer:data buf 
									 Address��the reg address write to FCE1353
										Count:the number write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIWritePDRamRegister(uint8_t *WriteBuffer, uint16_t Address, uint16_t Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0,nlength, nBytePosition,nWrtSpcAvlCount;

//    /*Reset or Abort any previous commands.*/
    param32_1.Val = PRAM_RW_ABORT_MASK;                                                

    SPIWriteDWord (PRAM_WRITE_CMD_REG, param32_1.Val);

    /*Make sure there is no previous write is pending
    (PRAM Write Busy) bit is a 0 */
    do
    {			
        param32_1.Val = SPIReadDWord (PRAM_WRITE_CMD_REG);

    }while((param32_1.v[3] & PRAM_RW_BUSY_8B));

    /*Write Address and Length Register (ECAT_PRAM_WR_ADDR_LEN) with the
    starting UINT8 address and length)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

    SPIWriteDWord (PRAM_WRITE_ADDR_LEN_REG, param32_1.Val);

    /*write to the EtherCAT Process RAM Write Command Register (ECAT_PRAM_WR_CMD) with the  PRAM Write Busy
    (PRAM_WRITE_BUSY) bit set*/

    param32_1.Val = PRAM_RW_BUSY_32B; /*TODO:replace with #defines*/

    SPIWriteDWord (PRAM_WRITE_CMD_REG, param32_1.Val);
		

    /*Read PRAM write Data Available (PRAM_READ_AVAIL) bit is set*/
    do
    {	
       param32_1.Val = SPIReadDWord (PRAM_WRITE_CMD_REG);

    }while(!(param32_1.v[0] & IS_PRAM_SPACE_AVBL_MASK));

    /*Check write data available count*/
    nWrtSpcAvlCount = param32_1.v[1] & PRAM_SPACE_AVBL_COUNT_MASK;

    /*Write data to Write FIFO) */ 
    /*get the byte lenth for first read*/
    nBytePosition = (Address & 0x03);

    nlength = (4-nBytePosition) > Count ? Count:(4-nBytePosition);

    param32_1.Val = 0;
    memcpy(&param32_1.v[nBytePosition],WriteBuffer+i, nlength);

    SPIWriteDWord (PRAM_WRITE_FIFO_REG,param32_1.Val);

    nWrtSpcAvlCount--;
    Count-=nlength;
    i+=nlength;

    //Auto increment mode
    CSLOW();

    //Write Command
    SPIWriteByte(CMD_SERIAL_WRITE);

    SPISendAddr(PRAM_WRITE_FIFO_REG);

    while(Count)
    {
        nlength = Count > 4 ? 4: Count;
        param32_1.Val = 0;
        memcpy(&param32_1, (WriteBuffer+i), nlength);

        SPIWriteBurstMode (param32_1.Val);
        i+=nlength;
        Count-=nlength;
        nWrtSpcAvlCount--;
    }

    CSHIGH();
    return;
}


/*******************************************************************************
* Function Name  : SPIReadDRegister
* Description    : read reg from FCE1353 pd ram
* Input          : ReadBuffer:data buf 
									 Address��the reg address write to FCE1353
										Count:the number write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIReadDRegister(uint8_t *ReadBuffer, uint16_t Address, uint16_t Count)
{
    if (Address >= 0x1000)
    {
         SPIReadPDRamRegister(ReadBuffer, Address,Count);
    }
    else
    {
         SPIReadRegUsingCSR(ReadBuffer, Address,Count);
    }
}

/*******************************************************************************
* Function Name  : SPIWriteRegister
* Description    : write reg from FCE1353 pd ram
* Input          : ReadBuffer:data buf 
									 Address��the reg address write to FCE1353
										Count:the number write to FCE1353
* Output         : none
* Return         : none: 
* Attention		 : None
*******************************************************************************/
void SPIWriteRegister( uint8_t *WriteBuffer, uint16_t Address, uint16_t Count)
{
   
   if (Address >= 0x1000)
   {
		SPIWritePDRamRegister(WriteBuffer, Address,Count);
   }
   else
   {
		SPIWriteRegUsingCSR(WriteBuffer, Address,Count);
   }
    
}

unsigned long SPIReadDWord_test(unsigned short Address)
{
	UINT32_VAL dwResult;
	UINT16_VAL wAddr;

	wAddr.Val  = Address;
	//Assert CS line
	CSLOW();
	//Write Command
	SPIWriteByte(CMD_FAST_READ);
    //Write Address
	SPIWriteByte(wAddr.byte.HB);
	SPIWriteByte(wAddr.byte.LB);
			
	//Dummy Byte
	SPIWriteByte(CMD_FAST_READ_DUMMY);
    //Read Bytes
    dwResult.byte.LB = SPIReadByte();
    dwResult.byte.HB = SPIReadByte();
    dwResult.byte.UB = SPIReadByte();
    dwResult.byte.MB = SPIReadByte();
    //De-Assert CS line
		CSHIGH();
		return dwResult.Val;
}
/*
 * ��    ����FCE1353_ReadID
 * ��    �ܣ�CSR��������FCE1353��оƬID
 * ��ڲ�������
 * ���ڲ�����������оƬID
 */
unsigned long FCE1353_ReadID(void)
{
	UINT8 Temp[10] = {0,0,0,0,0,0,0,0,0,0};	  
	SPIReadRegUsingCSR(Temp, 0x0e02, 2);	    
	return (Temp[0] | ((uint32_t)Temp[1] << 8) | ((uint32_t)Temp[2] << 16) | ((uint32_t)Temp[3] << 24));
}   
/*
 * ��    ����mem_test
 * ��    �ܣ�����PDI�ӿ�
 * ��ڲ�������
 * ���ڲ�������
 */
void mem_test(void)
{
	unsigned long temp = 0;
	//------------------------------------��������ַ64H=87654321
	temp = SPIReadDWord_test(0x64);
	temp = SPIReadDWord_test(0x64);
//	printf(temp == 0x87654321 ? "\n\r  mem_test:PASSED! const = %x ":"\n\r  test:FAILED! const = %x ", (int)temp);
    
	if(temp != 0x87654321)
	{
//		printf("stop();");
		while(1);
	}
	
	//------------------------------------�������ַ0e02H=9252
	temp = FCE1353_ReadID();
	//temp = SPIReadDWord_test(0x50);
	//temp = SPIReadDWord_test(0x50);
//	printf(temp == 0x9252 ? "   ID = %x\n\r":"\n\r  test:FAILED! ID = %x\n\r", (int)temp);
	
	if(temp != 0x9252)
	{
//		printf("stop();");
		while(1);
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
