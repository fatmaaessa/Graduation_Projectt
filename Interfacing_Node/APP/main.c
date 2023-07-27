/*
 * main.c
 *
 *  Created on: Jun 25, 2023
 *      Author: musta
 */

#include "../LIB/STD_TYPES.h"

#include "../MCAL/USART_Driver_V1/USART_ErrorTypes.h"
#include "../MCAL/USART_Driver_V1/USART_Init.h"

#include "../HAL/LCD_Handler_V2/LCD_err.h"
#include "../HAL/LCD_Handler_V2/LCD_int.h"

#include "../MCAL/EXTI_Driver_V3/EXTI_int.h"
#include "../MCAL/DIO_V2/DIO_init.h"
#include "../HAL/IR_Remote_V2/IR_Interface.h"
#include "../HAL/LED_Handler_V1/LED_int.h"
#include "avr/delay.h"
#include "../HAL/MCP2515_driver_V2/MCP2515_Interface.h"
#include "../HAL/MCP2515_driver_V2/MP2515_Private.h"

static u8 USARTBuffer[10];
static u8 Usart_RxFlag = 0;

/*Definition Section */
u8  _Data_Msg_Lentgh_ = 3 ;
u32 CAN_Msg_ID        = 0x00000003 ;
static u32 Counter ;

#define APP_GO_FORWORD		(u16)3
#define APP_GO_BACKWORD		(u16)2
#define APP_GO_LEFT			(u16)14
#define APP_GO_RIGHT		(u16)26
#define APP_STOP_CAR		(u16)7

//Functions Prototypes
void APP_Recieve_Data_Usart(u8 data);
void APP_Recieve_Data_CAN(void);

//External Objects
extern u8 REC_Message[];

//Global Objects
static u8 Global_SignBuffer[3];
static u8 Global_SignFlag;


u8 CAN_Msg[] ={'Y'}   ;
u8 CAN_MESSAGE_1 []= {'I','f','#'	} ;
u8 CAN_MESSAGE_2 []= {'I','b', '#' } ;
u8 CAN_MESSAGE_3 []= {'I','l','#'  } ;
u8 CAN_MESSAGE_4 []= {'I','r','#' } ;
u8 CAN_MESSAGE_5 []= {'I','s', '#' } ;

int main(){

	u8 index = 0;

	LED_e arr[] = {LED_e_1};
	LED_vidInit(arr,1);



	//USART Configurations.
	USART_Config_t Local_Usart_STR = {.usart_charSize_slct = USART_CharcterSize_t_8,
			.usart_circuit_enable = USART_Enable_t_TXAndRXEnable,
			.usart_parity = USART_ParityMode_t_Disable,
			.usart_speed_slct = USART_Speed_t_NormalSpeed,
			.usart_stopBits_slct = USART_StopBitSlct_t_OneBit
	};

	//LCD Initialization.
	LCD_vidInit();
	IR_Init() ;



	//External Interrupt Configurations.
	EXTI_u8SetSource(EXTI_INT_0, EXTI_FALLING_EDGE);
	EXTI_voidSet_INT0_Cbf(APP_Recieve_Data_CAN);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();

	//CAN Initialization.
	HMCP2515_voidInitTransimiter() ;
	HMCP2515_voidRecievInit();


	LED_vidTurnOnLed(LED_e_1);
	_delay_ms(1000);
	LED_vidTurnOffLed(LED_e_1);

	//USART Initialization.
	USART_init(&Local_Usart_STR);
	USART_ReceiveData_interrupt(&APP_Recieve_Data_Usart);


	LCD_vidWriteChar('m');

	while(1)
	{
		index = 0;
		//		LCD_vidClear();
		//		LCD_vidSendInt(ir_signal);
		//		//IR Remote code
		switch(ir_signal)
		{
		case APP_GO_FORWORD://up
			//Send the direction to the adaptive node.
			HMCP2515_VidSendCAN_Msg(TXB0CTRL , CAN_Msg_ID , _Data_Msg_Lentgh_, CAN_MESSAGE_1);
			LCD_vidClear();
			LCD_vidSendInt(ir_signal);
			ir_signal =0;
			break;
		case APP_GO_RIGHT://right
			//Send the direction to the adaptive node.
			HMCP2515_VidSendCAN_Msg(TXB0CTRL, CAN_Msg_ID , _Data_Msg_Lentgh_ , CAN_MESSAGE_4);
			LCD_vidClear();
			LCD_vidSendInt(ir_signal);
			ir_signal =0;
			break;
		case APP_GO_LEFT://left
			//Send the direction to the adaptive node.
			HMCP2515_VidSendCAN_Msg(TXB0CTRL, CAN_Msg_ID, _Data_Msg_Lentgh_, CAN_MESSAGE_3);
			LCD_vidClear();
			LCD_vidSendInt(ir_signal);
			ir_signal =0;
			break;
		case APP_GO_BACKWORD://down
			//Send the direction to the adaptive node.
			HMCP2515_VidSendCAN_Msg(TXB0CTRL, CAN_Msg_ID, _Data_Msg_Lentgh_, CAN_MESSAGE_2);
			LCD_vidClear();
			LCD_vidSendInt(ir_signal);
			ir_signal =0;
			break;
		case APP_STOP_CAR://ok
			//Send the direction to the adaptive node.

			HMCP2515_VidSendCAN_Msg(TXB0CTRL, CAN_Msg_ID, _Data_Msg_Lentgh_, CAN_MESSAGE_5);
			ir_signal =0;
			break;
		}

		//Check if data is received using the can
		if(Global_SignFlag == 1)
		{
			//Check if the data is sign data received from the master node.
			if(Global_SignBuffer[0] == 'S')
			{
				switch(Global_SignBuffer[1]){
				case 's':
					Global_SignFlag =0 ;
					LCD_vidClear();
					LCD_u8Goto(1,1);
					LCD_vidSendString("Speed Sign");
					LCD_u8Goto(2,1);
					LCD_vidSendString("Speed : ");
					index = 2;
					while(Global_SignBuffer[index] != '#')
					{

						LCD_vidWriteChar(Global_SignBuffer[index]);
						index++;
					}
					break;
				case 'b':
					Global_SignFlag =0;
					LCD_vidClear();
					LCD_u8Goto(1,1);
					LCD_vidSendString("Bump");
					USART_SendData('y');

					break;
				case 'l':
					Global_SignFlag =0;
					LCD_vidClear();
					LCD_u8Goto(1,1);
					LCD_vidSendString("Turn Left");
					break;
				case 'r':
					Global_SignFlag=0;
					LCD_vidClear();
					LCD_u8Goto(1,1);
					LCD_vidSendString("Turn right");
					break;

				}
			}
			//Check if the data is speed data received from the adaptive node.
			else if(Global_SignBuffer[0] == 'V')
			{
				Global_SignFlag =0;
				LCD_vidClear();
				LCD_u8Goto(1,1);
				LCD_vidSendString("Speed = ");
				index  = 1;
				while(Global_SignBuffer[index] != '#')
				{
					LCD_vidWriteChar(Global_SignBuffer[index]);
					index++;
				}
			}

			//Global_SignFlag = 0;
		}

		if(Usart_RxFlag == 1)
		{
			LCD_vidClear();
			if(USARTBuffer[0] == 'B')
			{
				//Send Frame to the adaptive node by CAN
				HMCP2515_VidSendCAN_Msg(TXB0CTRL ,CAN_Msg_ID ,Counter,USARTBuffer) ;
				LCD_vidSendString(USARTBuffer);
			}
			else{
				LCD_vidClear();
				LCD_vidSendString("U:Wrong Frame");
			}
			Counter = 0;
			Usart_RxFlag = 0;
		}

	}

}


void APP_Recieve_Data_Usart(u8 data)
{

	LED_vidTurnOnLed(LED_e_1);
	_delay_ms(1000);
	LED_vidTurnOffLed(LED_e_1);
	_delay_ms(1000);

	if(data != '\n')
	{
		USARTBuffer[Counter] = data;

	}else{
		USARTBuffer[Counter] = '#';
		Usart_RxFlag = 1;
	}
	Counter++;


}

void APP_Recieve_Data_CAN(void)
{
	//Receive data from the Routing and the adaptive nodes.
	HMCP2515_voidRecieveMess(RXB0CTRL) ;
	//the routing node should send the sign.
	//the adaptive node should send the current speed.
	u8 _Data_Lentgh_Rec_ = REC_Message[5] ;
	//Store the received data into the SignBuffer.

	for( u8 Index =0 ; Index < _Data_Lentgh_Rec_ ; Index++)
	{
		Global_SignBuffer [Index]= REC_Message[6 + Index] ;
	}

	//Set the flag to indicate that data is received.
	Global_SignFlag = 1;
}
