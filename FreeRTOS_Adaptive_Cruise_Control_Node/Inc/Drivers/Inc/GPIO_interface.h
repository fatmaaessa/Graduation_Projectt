/*********************************************/
/*********************************************/
/*********  Author: graduation_project *******/
/*********  Layer: MCAL              *********/
/*********  SWC: GPIO                *********/
/*********  Version: 1.00            *********/
/*********************************************/
/*********************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/*
 * Use these macros as port numbers
 * it used with all functions
*/
 
#define GPIO_PORTA         0
#define GPIO_PORTB         1
#define GPIO_PORTC         2


/*
 * Use these macros as pin numbers, with the following functions:
 * 															1- GPIO_u8SetPinDir
 * 															2- GPIO_u8SetPinVal
 * 															3- GPIO_u8GetPinVal
*/

#define PIN0          0
#define PIN1          1
#define PIN2          2
#define PIN3          3
#define PIN4          4
#define PIN5          5
#define PIN6          6
#define PIN7          7
#define PIN8          8
#define PIN9          9
#define PIN10         10
#define PIN11         11
#define PIN12         12
#define PIN13         13
#define PIN14         14
#define PIN15         15

#define INPUT         0
#define OUTPUT        1

#define LOW           0
#define HIGH          1

#define PORT_RANGE    3
#define PIN_RANGE     16

/* options for select GPIO Mode
    *Input
    *General purpose output mode
    *Alternate function mode
    *Analog mode
*/

#define INPUT         0
#define OUTPUT        1
#define AF            2
#define ANALOG        3

/******************************************************************************/

/* options for select Output type
	*push-pull -->PP
    *open-drain --> OD
*/

#define PP            0
#define OD            1

/******************************************************************************/


/* options for select speed
    *Low speed--->LS
    *Medium speed--->MS
    *High speed--->HS
    *Very high speed--->VHS
*/
#define LS           0
#define MS           1
#define HS           2
#define VHS          3

/******************************************************************************/

/* options 
    *pull-up/pull-down register
	*No pull-up, pull-down--->NPP
    *Pull-up---->PU
    *Pull-down---->PD
*/
#define NPP          0
#define PU           1
#define PD           2

/******************************************************************************/


#define GPIO_AF_0    0
#define GPIO_AF_1    1
#define GPIO_AF_2    2
#define GPIO_AF_3    3
#define GPIO_AF_4    4
#define GPIO_AF_5    5
#define GPIO_AF_6    6
#define GPIO_AF_7    7
#define GPIO_AF_8    8
#define GPIO_AF_9    9
#define GPIO_AF_10   10
#define GPIO_AF_11   11
#define GPIO_AF_12   12
#define GPIO_AF_13   13
#define GPIO_AF_14   14
#define GPIO_AF_15   15

/******************************************************************************/

typedef struct
{
    u8 PIN_MOD;
    u8 PIN_OT;
    u8 PIN_SPD;
    u8 PIN_PUPD;
    
}PIN_st;

/******************************************************************************/

//function to set pin direction
/*
 * description:
 * 				Use this function to set the pin direction.
 *
 * parameters:
 * 			 	1- (u8) port name    (PORTA, PORTB, PORTC)
 * 			 	2- (u8) pin  number  (PIN0, PIN1, ...., PIN15)
				3- 
*/
void GPIO_voidSetPinDirection (u8 Copy_u8PortName, u8 Copy_u8PinNumber, PIN_st*  Copy_psPinInfo);

/******************************************************************************/

//function to set AlternativeFunction
/*
 * description:
 * 				Use this function to set the AlternativeFunction.
 *
 * parameters:
 * 			 	1- (u8) port name    (PORTA, PORTB, PORTC)
 * 			 	2- (u8) pin  number  (PIN0, PIN1, ...., PIN15)
				3- (u8) AltFun
*/
void GPIO_voidSetAlternativeFunction(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8AltFun);

/******************************************************************************/
//function to set pin value
/*
 * description:
 * 				Use this function to set the pin value.
 *
 * parameters:
 * 			 	1- (u8) port number (PORTA, PORTB, PORTC, PORTD)
 * 			 	2- (u8) pin number  (PIN0, PIN1, ...., PIN7)
 *				3- (u8) value of the pin (HIGH, LOW)
*/
void GPIO_voidSetPinValue     (u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinValue);

/******************************************************************************/
//function to GetPinValue
/*
 * description:
 * 				Use this function to GetPinValue.
 *
 * parameters:
 * 			 	1- (u8) port name    (PORTA, PORTB, PORTC)
 * 			 	2- (u8) pin  number  (PIN0, PIN1, ...., PIN15)
				3- 
*/
u8   GPIO_u8GetPinValue       (u8 Copy_u8PortName, u8 Copy_u8PinNumber);

/******************************************************************************/
//function to GetPortValue
/*
 * description:
 * 				Use this function to GetPortValue.
 *
 * parameters:
 * 			 	1- (u8) port name    (PORTA, PORTB, PORTC)
*/
u8   GPIO_u8GetPortValue      (u8 Copy_u8PortName);





#endif
