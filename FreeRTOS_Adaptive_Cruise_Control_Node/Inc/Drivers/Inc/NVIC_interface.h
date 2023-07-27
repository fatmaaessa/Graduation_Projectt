/****************************
 *  NVIC_INTERFACE.h        *
 *  Created on: FEB 7, 2023 *
 *  Author: MANAR EMAD      *
 ****************************/
 
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#define GROUP_4BITS 0b011
#define GROUP_3BITS 0b100
#define GROUP_2BITS 0b101
#define GROUP_1BITS 0b110
#define GROUP_0BITS 0b111

/*System handler priority register 1 "SHPR1" */
#define PEND_SV -6
#define SYSTICK -5
/*System handler priority register 2 "SHPR2" */
#define SV_CALL -4
/*System handler priority register 3 "SHPR3" */
#define MEMORY_MANAGE -3
#define BUS_FAULT     -2
#define USAGE_FAULT   -1
/////////////////////////

#define WWDG 0
#define EXTI16 1
#define EXTI21 2
#define EXTI22 3
#define FLASH 4
#define RCC 5
#define ETI0 6
#define EXTI1 7
#define EXTI2 8
#define EXTI3 9
#define EXTI4 10
#define DMA1_STREAM0 11
#define DMA1_STREAM1 12
#define DMA1_STREAM2 13
#define DMA1_STREAM3 14
#define DMA1_STREAM4 15
#define DMA1_STREAM5 16
#define DMA1_STREAM6 17
#define ADC 18
#define EXTI9_5 23
#define TIM1_BRK_TIM9 24
#define TIM1_UP_TIM10 25
#define TIM1_TRG_COM_TIM11 26
#define TIM1_CC 27
#define TIM2 28
#define TIM3 29
#define TIM4 30
#define I2C1_EV 31
#define I2C1_ER 32
#define I2C2_EV 33
#define I2C2_ER 34
#define SPI1 35
#define SPI2 36
#define USART1 37
#define USART2 38
#define EXTI15_10 40
#define EXTI17 41
#define EXTI18 42
#define DMA1_STREAM7 47
#define SDIO 49
#define TIM5 50
#define SPI3 51
#define DMA2_STREAM0 56
#define DMA2_STREAM1 57
#define DMA2_STREAM2 58
#define DMA2_STREAM3 59
#define DMA2_STREAM4 60
#define OTG_FS 67
#define DMA2_STREAM5 68
#define DMA2_STREAM6 69
#define DMA2_STREAM7 70
#define USART6 71
#define I2C3_EV 72
#define I2C3_ER 73
#define FPU 81
#define SPI4 84
///////////////


#define GROUP_PRIORITY_0 0
#define GROUP_PRIORITY_1 1
#define GROUP_PRIORITY_2 2
#define GROUP_PRIORITY_3 3
#define GROUP_PRIORITY_4 4
#define GROUP_PRIORITY_5 5
#define GROUP_PRIORITY_6 6
#define GROUP_PRIORITY_7 7
#define GROUP_PRIORITY_8 8
#define GROUP_PRIORITY_9 9
#define GROUP_PRIORITY_10 10
#define GROUP_PRIORITY_11 11
#define GROUP_PRIORITY_12 12
#define GROUP_PRIORITY_13 13
#define GROUP_PRIORITY_14 14
#define GROUP_PRIORITY_15 15

#define SUB_PRIORITY_0 0
#define SUB_PRIORITY_1 1
#define SUB_PRIORITY_2 2
#define SUB_PRIORITY_3 3
#define SUB_PRIORITY_4 4
#define SUB_PRIORITY_5 5
#define SUB_PRIORITY_6 6
#define SUB_PRIORITY_7 7
#define SUB_PRIORITY_8 8
#define SUB_PRIORITY_9 9
#define SUB_PRIORITY_10 10
#define SUB_PRIORITY_11 11
#define SUB_PRIORITY_12 12
#define SUB_PRIORITY_13 13
#define SUB_PRIORITY_14 14
#define SUB_PRIORITY_15 15

/******************************************************************************/
/*Parameters: Interrupt ID              								      */
/*Desc:This Function Enables the INT of the peripheral in NVIC		          */
/******************************************************************************/
void MNVIC_VoidEnablePeripheral(u8 Copy_u8INTID);

/******************************************************************************/
/*Parameters: Interrupt ID              								      */
/*Desc:This Function Disables the INT of the peripheral in NVIC		          */
/******************************************************************************/
void MNVIC_VoidDisablePeripheral(u8 Copy_u8INTID);

/******************************************************************************/
/*Parameters: Interrupt ID                     								  */
/*Desc:This Function Sets pending flag of Peripheral        		          */
/******************************************************************************/
void MNVIC_VoidSetPending(u8 Copy_u8INTID);

/******************************************************************************/
/*Parameters: Interrupt ID                  								  */
/*Desc:This Function Clears pending flag of Peripheral        		          */
/******************************************************************************/
void MNVIC_VoidClearPending(u8 Copy_u8INTID);

/******************************************************************************/
/*Parameters: Interrupt ID              								      */
/*Desc:This Function returns state of active flag in NVIC     		          */
/******************************************************************************/
u8 MNVIC_u8GetActive(u8 Copy_u8INTID);

/******************************************************************************/
/*Parameters: Priority option                								  */
/*Desc:This Function Sets the group and the sub priority configurations       */
/******************************************************************************/
/*Options:- GROUP_4BITS - GROUP_3BITS - GROUP_2BITS - GROUP_1BITS - GROUP_0BITS
/******************************************************************************/
void MNVIC_voidSetPriorityConfig(u8 Copy_u8PriorityOption);

/******************************************************************************/
/*Parameters: Interrupt ID                  								  */
/*Desc:This Function Sets the group and the sub priority for required INT     */
/******************************************************************************/
/*
 * Options for Copy_u8GroupPriority:- GROUP_PRIORITY_0 ... GROUP_PRIORITY_15
 * Options for Copy_u8SubPriority  :- SUB_PRIORITY_0   ... SUB_PRIORITY_15
/******************************************************************************/
void MNVIC_VoidSetPriority(s8 Copy_s8INTID, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority);

#endif