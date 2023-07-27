/*
 * Main.c
 *
 *  Created on: Jun 20, 2023
 *      Author: musta
 */

#include "../LIB/STD_TYPES.h"

#include "../MCAL/EXTI_Driver_V2/EXTI_int.h"

#include "../HAL/MCP2515_driver/MP2515_Private.h"
#include "../HAL/MCP2515_driver/MCP2515_Interface.h"

#include "../HAL/LED_Handler_V1/LED_int.h"

#include "avr/interrupt.h"

//Function Prototype.
void RX_Distance(void);

//External Objects
extern u8 REC_Message[];

//Global Objects
// Data Length
u8 _Data_lentgh_ =     4;
//ID of Control Node
u32  _CAN_Msg_ID  =    0x00000003 ;
static u8 App_CANMsgBuffer [16] ;
volatile u8 App_CANMsgFlag =0 ;

static u8 Global_Turn_Left_[] =  {'r', 70  , 100, '#'} ;
static u8 Global_Turn_Right_[] =  {'r', 100 , 70 , '#'} ;
static u8 Global_Go_Straight__[] =  {'r', 100 , 100 , '#'} ;

void main()
{
	LED_e arr[] = {LED_e_1};
	LED_vidInit(&arr, 1);
	//EXTI Configurations.
	EXTI_voidSet_INT0_Cbf(&RX_Distance);
	EXTI_u8SetSource( EXTI_INT_0,EXTI_FALLING_EDGE);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();

	//CAN initialization.
	HMCP2515_voidRecievInit();
	HMCP2515_voidInitTransimiter();
	LED_vidTurnOnLed(LED_e_1);

	while(1)
	{
		if(App_CANMsgFlag == 1 ){
			if(App_CANMsgBuffer[0] ==  'L')
			{

				App_CANMsgFlag =0 ;
				//				Test
				//				_CAN_Msg_ID =0x00000005 ;
				//				HMCP2515_VidSendCAN_Msg(TXB0CTRL, _CAN_Msg_ID, _Data_lentgh_ , _Turn_Right2_);
				//				DIO_u8setPinVal(DIO_PORT_C ,DIO_PIN_2 ,DIO_HIGH);
				//				_delay_ms(1000) ;
				//				DIO_u8setPinVal(DIO_PORT_C ,DIO_PIN_2 ,DIO_LOW);
				//_delay_ms(1000) ;
				/*_____________*/

				/* Sending  speed of the left motor For Control Node  only */

				HMCP2515_VidSendCAN_Msg(TXB0CTRL, _CAN_Msg_ID , _Data_lentgh_ , Global_Turn_Left_);


			}
			else if(App_CANMsgBuffer[0] == 'R'){

				//Sending  speed of the _Right_ motor For Control Node  only
				App_CANMsgFlag =0 ;
				HMCP2515_VidSendCAN_Msg(TXB0CTRL, _CAN_Msg_ID, _Data_lentgh_ , Global_Turn_Right_);
				//				Test
				//				DIO_u8setPinVal(DIO_PORT_C ,DIO_PIN_2 ,DIO_HIGH);
				//				_delay_ms(1000) ;
				//				DIO_u8setPinVal(DIO_PORT_C ,DIO_PIN_2 ,DIO_LOW);
				//				_delay_ms(1000) ;
				//				DIO_u8setPinVal(DIO_PORT_C ,DIO_PIN_2 ,DIO_HIGH);
				//				_delay_ms(1000) ;
				//				DIO_u8setPinVal(DIO_PORT_C ,DIO_PIN_2 ,DIO_LOW);
				//				_delay_ms(1000) ;
				//				DIO_u8setPinVal(DIO_PORT_C ,DIO_PIN_2 ,DIO_HIGH);
				//				_delay_ms(1000) ;
				//				DIO_u8setPinVal(DIO_PORT_C ,DIO_PIN_2 ,DIO_LOW);
				//				_delay_ms(1000) ;

			}

		}
		else if(App_CANMsgBuffer[0] == 'C')
		{
			/*Any Code */
			App_CANMsgFlag =0 ;
			HMCP2515_VidSendCAN_Msg(TXB0CTRL, _CAN_Msg_ID, _Data_lentgh_ , Global_Go_Straight__);
		}
	}
}

void RX_Distance(void){

	/* ** RECEIVE CAN MESSAGE FROM  Master Node ** */
	HMCP2515_voidRecieveMess(RXB0CTRL);
	//Change Depend Sender
	u8 Data_Lentgh = REC_Message[5] ;
	for(u8 index =0 ;index < Data_Lentgh ; index++)
	{
		App_CANMsgBuffer[index] =  REC_Message[6 + index];
	}
	App_CANMsgFlag =1 ;

}
