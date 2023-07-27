
#include "../LIB/STD_TYPES.h"
#include "../MCAL/EXTI_Driver_V3/EXTI_int.h"
#include "../HAL/MCP2515_driver/MP2515_Private.h"
#include "../HAL/MCP2515_driver/MCP2515_Interface.h"
#include "../MCAL/USART_Driver_V1/USART_ErrorTypes.h"
#include "../MCAL/DIO_V2/DIO_init.h"
#include "../MCAL/USART_Driver_V1/USART_Init.h"

#include "../HAL/LCD_Handler_V2/LCD_err.h"
#include "../HAL/LCD_Handler_V2/LCD_int.h"

#include "../HAL/CarMotion/CarMotion.h"

#include "../HAL/LED_Handler_V1/LED_int.h"

#include "avr/delay.h"

#define APP_GO_FORWORD		(u16)3
#define APP_GO_BACKWORD		(u16)2
#define APP_GO_LEFT			(u16)14
#define APP_GO_RIGHT		(u16)26
#define APP_STOP_CAR		(u16)7

void RX_CanMsg(void);
//void Go_Forword(void);
//void Go_Backword(void);
//void Go_Left(void);
//void Go_Right(void);
//void Car_Stop(void);
//void Set_Speed(u8 Copy_u8SpeedValue);
void Rx_Data_CallBack_USART(u8 Speed);
static u32 ExtractDataFromFrame(u8 * Copy_Pu8String);

extern u8 REC_Message[16];
static u8 App_CANRecMessage[16];
static u8 Old_Speed = 90 ;
static u8 SpeedFrame[10];
static u8 USARTFrameReady = 0;
static u8 counter = 0;
volatile u8 Can_Flag =0 ;
int main()
{
	LED_e arr[] = {LED_e_1};
	LED_vidInit(arr, 1);

	SpeedFrame[0] = 'V';
	SpeedFrame[2] = '#';

	//USART Configurations.
	USART_Config_t Local_Usart_STR = {.usart_charSize_slct = USART_CharcterSize_t_8,
			.usart_circuit_enable = USART_Enable_t_TXAndRXEnable,
			.usart_parity = USART_ParityMode_t_Disable,
			.usart_speed_slct = USART_Speed_t_DoubleSpeed,
			.usart_stopBits_slct = USART_StopBitSlct_t_OneBit
	};

	u8 Local_u8CharCounter = 0;
	EXTI_u8SetSource(EXTI_INT_0, EXTI_FALLING_EDGE);
	EXTI_voidSet_INT0_Cbf(RX_CanMsg);
	EXTI_u8EnablePIE(EXTI_INT_0);
	EXTI_voidEnableGIE();

	USART_init(&Local_Usart_STR);
	USART_ReceiveData_interrupt(&Rx_Data_CallBack_USART);

	Car_Init();

	LCD_vidInit();

	HMCP2515_voidInitTransimiter();
	HMCP2515_voidRecievInit();
	LED_vidTurnOnLed(LED_e_1);

	//	DIO_u8setPinVal(DIO_PORT_A,DIO_PIN_6, DIO_HIGH);

	SpeedFrame[1] = Old_Speed;
	while(SpeedFrame[Local_u8CharCounter] != '#')
	{
		USART_SendData(SpeedFrame[Local_u8CharCounter]);
		Local_u8CharCounter++;

	}
	USART_SendData(SpeedFrame[Local_u8CharCounter]);

	while(1)
	{

		Local_u8CharCounter = 0;
		//		SpeedFrame[1] = Old_Speed;
		if(Can_Flag ==1 )
		{
			switch (App_CANRecMessage[0]) {
			case 'I':
				switch(App_CANRecMessage[1]){
				case 'f':
					Car_Go_Forword();
					//DIO_u8setPinVal(DIO_PORT_A ,DIO_PIN_1 ,DIO_HIGH);
					break;

				case 'b':
					Car_Go_Backword();
					//DIO_u8setPinVal(DIO_PORT_A ,DIO_PIN_2 ,DIO_HIGH);
					break;
				case 'l':
					Car_Go_Left();
					//DIO_u8setPinVal(DIO_PORT_A ,DIO_PIN_3 ,DIO_HIGH);
					break;
				case 'r':
					Car_Go_Right();
					//DIO_u8setPinVal(DIO_PORT_A ,DIO_PIN_4 ,DIO_HIGH);
					break;
				case 's':
					Car_Stop();
					//DIO_u8setPinVal(DIO_PORT_A ,DIO_PIN_5 ,DIO_HIGH);
					break;
				default:
					break;
				}
				break;
				case 'r':
					if(App_CANRecMessage[1] > App_CANRecMessage[2])
					{
						Car_Go_Right();
					}else if(App_CANRecMessage[1] < App_CANRecMessage[2])
					{
						Car_Go_Left();
					}else if(App_CANRecMessage[1] == App_CANRecMessage[2]){
						Car_Go_Forword();
					}
					break;
				case 'B':
					while(App_CANRecMessage[Local_u8CharCounter] != '#')
					{
						USART_SendData(App_CANRecMessage[Local_u8CharCounter]);
						Local_u8CharCounter++;
					}
					USART_SendData(App_CANRecMessage[Local_u8CharCounter]);
					break;

				default:
					break;
			}
			Can_Flag =0 ;
		}

		if(USARTFrameReady == 1)
		{
//			u32 Local_u32Speed = 0;
			if(SpeedFrame[0] == 'V')
			{

//				Local_u32Speed =ExtractDataFromFrame(&SpeedFrame);
				Car_Set_Speed(MOTOR_1, (u8)SpeedFrame[1]);
				Car_Set_Speed(MOTOR_2, (u8)SpeedFrame[1]);

				LCD_vidClear();
				LCD_vidSendInt(SpeedFrame[1]);
			}
			counter = 0;
			USARTFrameReady = 0;
		}
	}
}

void RX_CanMsg(void)
{
	HMCP2515_voidRecieveMess(RXB0CTRL) ;
	u8 i = 0;
	while(REC_Message[6+i] != '#')
	{
		App_CANRecMessage[i] = REC_Message[6+i] ;
		i++;
	}
	App_CANRecMessage[i] = REC_Message[6+i];
	Can_Flag =1 ;

}

void Rx_Data_CallBack_USART(u8 Copy_u8NewSpeed)
{

	if(Copy_u8NewSpeed != '#')
	{
		SpeedFrame[counter] = Copy_u8NewSpeed;
	}else{
		LED_vidTurnOnLed(LED_e_1);
		_delay_ms(200);
		LED_vidTurnOffLed(LED_e_1);
		_delay_ms(200);
		SpeedFrame[counter] = Copy_u8NewSpeed;
		USARTFrameReady = 1;
	}
	counter++;


	//	if(Copy_u8NewSpeed != Old_Speed)
	//	{
	//		Car_Set_Speed(MOTOR_1, Copy_u8NewSpeed);
	//		Car_Set_Speed(MOTOR_2, Copy_u8NewSpeed);
	//		Old_Speed = Copy_u8NewSpeed;
	//	}
	//	else{
	//
	//	}
}

static u32 ExtractDataFromFrame(u8 * Copy_Pu8String){

	u8 Local_u8Index = 1;
	u32 Local_u32Int_Speed = 0;
	while(Copy_Pu8String[Local_u8Index] != '#')
	{
		Local_u32Int_Speed *= 10;
		Local_u32Int_Speed += (Copy_Pu8String[Local_u8Index] - '0');
		Local_u8Index++;
	}
	Can_Flag =1;

	return Local_u32Int_Speed;
}
