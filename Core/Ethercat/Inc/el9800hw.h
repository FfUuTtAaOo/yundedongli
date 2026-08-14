/**
 * \addtogroup EL9800_HW EL9800 Platform (Serial ESC Access)
 * @{
 */

/**
\file el9800hw.h
\author EthercatSSC@beckhoff.com
\brief Defines to access the EL9800 specific periphery and ESC (via SPI)

\version 5.01

<br>Changes to version - :<br>
V5.01 : Start file change log
 */

#ifndef _EL9800HW_H_
#define _EL9800HW_H_


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include  "esc.h"

//#include <p24Hxxxx.h>
#include "stm32f4xx.h"
#include "system.h"
/*-----------------------------------------------------------------------------------------
------
------    Defines and Types
------
-----------------------------------------------------------------------------------------*/
#define ESC_RD                    0x02 /**< \brief Indicates a read access to ESC or EEPROM*/
#define ESC_WR                    0x04 /**< \brief Indicates a write access to ESC or EEPROM.*/


/*---------------------------------------------
-    Microcontroller definitions
-----------------------------------------------*/


#define SWITCH_1              PEin(0)
#define SWITCH_2              PEin(1)
#define SWITCH_3              PEin(2)
#define SWITCH_4              PEin(3)
#define SWITCH_5              PEin(4)
#define SWITCH_6              PEin(5)
#define SWITCH_7              PEin(6)
#define SWITCH_8              PEin(7)
#define SWITCH_9              PEin(8)
#define SWITCH_10             PEin(9)
#define SWITCH_11             PEin(10)
#define SWITCH_12             PEin(11)
#define SWITCH_13             PEin(12)
#define SWITCH_14             PEin(13)
#define SWITCH_15             PEin(14)
#define SWITCH_16             PEin(15)
	
#define LED_1                 PDout(0)
#define LED_2                 PDout(1)
#define LED_3                 PDout(2)
#define LED_4                 PDout(3)
#define LED_5                 PDout(4)
#define LED_6                 PDout(5)
#define LED_7                 PDout(6)
#define LED_8                 PDout(7)
#define LED_9                 PDout(8)
#define LED_10                PDout(9)
#define LED_11                PDout(10)
#define LED_12                PDout(11)
#define LED_13                PDout(12)
#define LED_14                PDout(13)
#define LED_15                PDout(14)
#define LED_16                PDout(15)

///////////////////////////////////////////////////////////////////////////////
#define FCE135x_BYTE_ORDER_REG		0x64
#define FCE135x_CSR_INT_CONF		0x54
#define FCE135x_CSR_INT_EN			0x5C
#define FCE135x_CSR_INT_STS			0x58
#define FCE135x_POWER_MGMT_CTL		0x84

//9252 HW DEFINES
#define ECAT_REG_BASE_ADDR              0x0300

#define ESC_PDI_CONFIG_OFFSET			0x150 

#define CSR_DATA_REG_OFFSET             0x00
#define CSR_CMD_REG_OFFSET              0x04
#define PRAM_READ_ADDR_LEN_OFFSET       0x08
#define PRAM_READ_CMD_OFFSET            0x0c
#define PRAM_WRITE_ADDR_LEN_OFFSET      0x10
#define PRAM_WRITE_CMD_OFFSET           0x14

#define PRAM_SPACE_AVBL_COUNT_MASK      0x1f
#define IS_PRAM_SPACE_AVBL_MASK         0x01


#define CSR_DATA_REG                    ECAT_REG_BASE_ADDR+CSR_DATA_REG_OFFSET
#define CSR_CMD_REG                     ECAT_REG_BASE_ADDR+CSR_CMD_REG_OFFSET
#define PRAM_READ_ADDR_LEN_REG          ECAT_REG_BASE_ADDR+PRAM_READ_ADDR_LEN_OFFSET
#define PRAM_READ_CMD_REG               ECAT_REG_BASE_ADDR+PRAM_READ_CMD_OFFSET
#define PRAM_WRITE_ADDR_LEN_REG         ECAT_REG_BASE_ADDR+PRAM_WRITE_ADDR_LEN_OFFSET
#define PRAM_WRITE_CMD_REG              ECAT_REG_BASE_ADDR+PRAM_WRITE_CMD_OFFSET

#define PRAM_READ_FIFO_REG              0x04
#define PRAM_WRITE_FIFO_REG             0x20

#define HBI_INDEXED_DATA0_REG           0x04
#define HBI_INDEXED_DATA1_REG           0x0c
#define HBI_INDEXED_DATA2_REG           0x14

#define HBI_INDEXED_INDEX0_REG          0x00
#define HBI_INDEXED_INDEX1_REG          0x08
#define HBI_INDEXED_INDEX2_REG          0x10

#define HBI_INDEXED_PRAM_READ_WRITE_FIFO    0x18

#define PRAM_RW_ABORT_MASK      (1U << 30)
#define PRAM_RW_BUSY_32B        (1U << 31)
#define PRAM_RW_BUSY_8B         (1U << 7)
#define PRAM_SET_READ           (1U << 6)
#define PRAM_SET_WRITE          0



/*---------------------------------------------
-    hardware timer settings
-----------------------------------------------*/

#define ECAT_TIMER_INC_P_MS                2000 //72000   	//0x271 /**< \brief 625 ticks per ms*/

extern 	uint16_t adcValue;
extern 	uint16_t dacValue;
extern 	uint16_t adcx;
/*---------------------------------------------
-    Interrupt and Timer defines
-----------------------------------------------*/

#ifndef DISABLE_ESC_INT
#define    DISABLE_ESC_INT()           NVIC_DisableIRQ(EXTI15_10_IRQn)		// IRQ=PA10(EXTI10), 属于 EXTI15_10_IRQn; {(_INT1IE)=0;} /**< \brief Disable interrupt source INT1*/
#endif
#ifndef ENABLE_ESC_INT
#define    ENABLE_ESC_INT()           HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); // IRQ=PA10(EXTI10); NVIC_EnableIRQ(EXTI15_10_IRQn)			// {(_INT1IE)=1;} /**< \brief Enable interrupt source INT1*/
#endif

#ifndef HW_GetTimer
#define HW_GetTimer()       		TIM2->CNT		//(SysTick->LOAD - 	SysTick->VAL) //			// ((UINT16)(TMR7)) /**< \brief Access to the hardware timer*/
#endif

#ifndef HW_ClearTimer
#define HW_ClearTimer()         ((TIM2->CNT)=0); //(SysTick->VAL = SysTick->LOAD)// //{(TMR7) = 0;} /**< \brief Clear the hardware timer*/
#endif




#define HW_EscReadByte(ByteValue,Address)	HW_EscRead(((MEM_ADDR *)&(ByteValue)),((UINT16)(Address)),1) 
#define HW_EscReadWord(WordValue, Address) HW_EscRead(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief 16Bit ESC read access*/
#define HW_EscReadDWord(DWordValue, Address) HW_EscRead(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief 32Bit ESC read access*/
#define HW_EscReadMbxMem(pData,Address,Len) HW_EscRead(((MEM_ADDR *)(pData)),((UINT16)(Address)),(Len)) /**< \brief The mailbox data is stored in the local uC memory therefore the default read function is used.*/

#define HW_EscReadByteIsr(ByteValue,Address)	HW_EscReadIsr(((MEM_ADDR *)&(ByteValue)),((UINT16)(Address)),1) 
#define HW_EscReadWordIsr(WordValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief Interrupt specific 16Bit ESC read access*/
#define HW_EscReadDWordIsr(DWordValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief Interrupt specific 32Bit ESC read access*/

#define HW_EscWriteByte(WordValue, Address) HW_EscWrite(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),1)
#define HW_EscWriteWord(WordValue, Address) HW_EscWrite(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief 16Bit ESC write access*/
#define HW_EscWriteDWord(DWordValue, Address) HW_EscWrite(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief 32Bit ESC write access*/
#define HW_EscWriteMbxMem(pData,Address,Len) HW_EscWrite(((MEM_ADDR *)(pData)),((UINT16)(Address)),(Len)) /**< \brief The mailbox data is stored in the local uC memory therefore the default write function is used.*/

#define HW_EscWriteWordIsr(WordValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief Interrupt specific 16Bit ESC write access*/
#define HW_EscWriteDWordIsr(DWordValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief Interrupt specific 32Bit ESC write access*/

#endif //_EL9800HW_H_


#if _EL9800HW_
    #define PROTO
#else
    #define PROTO extern
#endif


/*-----------------------------------------------------------------------------------------
------
------    Global variables
------
-----------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------
------
------    Global functions
------
-----------------------------------------------------------------------------------------*/
PROTO UINT8 ethercat_hw_init(void);
PROTO void HW_Release(void);
PROTO UINT16 HW_GetALEventRegister(void);

PROTO UINT16 HW_GetALEventRegister_Isr(void);

PROTO void HW_ResetALEventMask(UINT16 intMask);
PROTO void HW_SetALEventMask(UINT16 intMask);
PROTO void HW_SetLed(UINT8 RunLed,UINT8 ErrLed);

PROTO void HW_EscRead( MEM_ADDR * pData, UINT16 Address, UINT16 Len );
PROTO void HW_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

PROTO void HW_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

PROTO void HW_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

PROTO void HW_DisableSyncManChannel(UINT8 channel);
PROTO void HW_EnableSyncManChannel(UINT8 channel);
PROTO TSYNCMAN ESCMEM *HW_GetSyncMan(UINT8 channel);

/*---------------------------------------------
-    ESC Access macros
-----------------------------------------------*/
#if _EL9800HW_

#endif //#if _EL9800HW_
#undef    PROTO
/** @}*/
