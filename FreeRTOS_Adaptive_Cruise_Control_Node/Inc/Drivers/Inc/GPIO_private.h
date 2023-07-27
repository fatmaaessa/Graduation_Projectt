/*********************************************/
/*********************************************/
/*********  Author: graduation_project  ******/
/*********  Layer: MCAL                 ******/
/*********  SWC: GPIO                   ******/
/*********  Version: 1.00               ******/
/*********************************************/
/*********************************************/


#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/*Definitions of GPIO_PORT'S ADDRESSES*/

#define GPIO_PORTA_BASE_ADDRESS   (u32)(0x40020000)
#define GPIO_PORTB_BASE_ADDRESS   (u32)(0x40020400)
#define GPIO_PORTC_BASE_ADDRESS   (u32)(0x40020800)

/*GPIO_REGISTER'S*/

typedef struct
{
	u32 MODER;            //GPIO Register To Configure The I/O Direction Mode.
	u32 OTYPER;           //GPIO Port Output Type Register To configure the output type of the I/O port.
	u32 OSPEEDR;          //GPIO port output speed Register To configure the I/O output speed.
	u32 PUPDR;            //GPIO port Register To configure the I/O pull-up or pull-down
	u32 IDR;              //GPIO port Register To contain the input value of the corresponding I/O port.
	u32 ODR;              //GPIO port Register To contain the output value of the corresponding I/O port.
	u32 BSRR;             //GPIO port bit set/reset register.
	u32 LCKR;             //GPIO port configuration lock register. 
	u32 AFRL;             //GPIO alternate function low register.
	u32 AFRH;             //GPIO alternate function high register.

}GPIO_RegMap_t;

#define GPIOA  ((volatile GPIO_RegMap_t*)(GPIO_PORTA_BASE_ADDRESS))
#define GPIOB  ((volatile GPIO_RegMap_t*)(GPIO_PORTB_BASE_ADDRESS))
#define GPIOC  ((volatile GPIO_RegMap_t*)(GPIO_PORTC_BASE_ADDRESS))


#endif
