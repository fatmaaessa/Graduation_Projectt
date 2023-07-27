/********************************************************************************************/
/* 	AUTHOR  		: islam atef Mohamed 													*/
/* 	VERSION 		:	  V1.0 																*/
/* 	DATE    		:  1/2023 																*/
/*	Description  	:  This is the Interface file For the TIMER Peripheral                  */
/*                                       at ARM-CORTEX m4						            */
/********************************************************************************************/
#ifndef		TIM_INTERFACE_H
#define		TIM_INTERFACE_H


/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/
/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/

/********************************************************************************************/
/*-------------------------------------Timer Register Struct--------------------------------*/
/********************************************************************************************/
typedef struct
{
   volatile u16 CR1         ;
            u16  RESERVED0  ;
  volatile  u16 CR2         ;
            u16  RESERVED1  ;
  volatile  u16 SMCR        ;
            u16  RESERVED2  ;
  volatile  u16 DIER        ;
            u16  RESERVED3  ;
  volatile  u16 SR          ;
            u16  RESERVED4  ;
  volatile  u16 EGR         ;
            u16  RESERVED5  ;
  volatile  u16 CCMR1       ;
            u16  RESERVED6  ;
  volatile  u16 CCMR2       ;
            u16  RESERVED7  ;
  volatile  u16 CCER        ;
            u16  RESERVED8  ;
  volatile  u16 CNT         ;
            u16  RESERVED9  ;
  volatile  u16 PSC         ;
            u16  RESERVED10 ;
  volatile  u16 ARR         ;
            u16  RESERVED11 ;
  volatile  u16 RCR         ;
            u16  RESERVED12 ;
  volatile  u16 CCR1        ;
            u16  RESERVED13 ;
  volatile  u16 CCR2        ;
            u16  RESERVED14 ;
  volatile  u16 CCR3        ;
            u16  RESERVED15 ;
  volatile  u16 CCR4        ;
            u16  RESERVED16 ;
  volatile  u16 BDTR        ;
            u16  RESERVED17 ;
  volatile  u16 DCR         ;
            u16  RESERVED18 ;
  volatile  u16 DMAR        ;
            u16  RESERVED19 ;

}TIM_Registers;
/*------------------------------------------------------------------------------------------*/

/*--------------------------------------Timers Base Addresses-------------------------------*/
#define     TIM1_BASE_ADDRESS   (u32)0x40010000
#define     TIM2_BASE_ADDRESS   (u32)0x40000000
#define     TIM3_BASE_ADDRESS   (u32)0x40000400
#define     TIM4_BASE_ADDRESS   (u32)0x40000800
#define     TIM5_BASE_ADDRESS   (u32)0x40000C00
#define     TIM9_BASE_ADDRESS   (u32)0x40014000
#define     TIM10_BASE_ADDRESS  (u32)0x40014400
#define     TIM11_BASE_ADDRESS  (u32)0x40014800
/*------------------------------------------------------------------------------------------*/
/********************************************************************************************/


/********************************************************************************************/
/*--------------(1)-------------------Timers' Registers struct------------------------------*/
/********************************************************************************************/
// The advanced-control timers (TIM1), a [16-bit] auto-reload counter.
#define     TIM1_R          ((TIM_Registers * )TIM1_BASE_ADDRESS)

// The general-purpose timers (TIM2 -> TIM5), [16-bit] or [32-bit] auto-reload counters.
#define     TIM2_R          ((TIM_Registers * )TIM2_BASE_ADDRESS)
#define     TIM3_R          ((TIM_Registers * )TIM3_BASE_ADDRESS)
#define     TIM4_R          ((TIM_Registers * )TIM4_BASE_ADDRESS)
#define     TIM5_R          ((TIM_Registers * )TIM5_BASE_ADDRESS)

// The general-purpose timers (TIM9 -> TIM11), a [16-bit] auto-reload counter.
#define     TIM9_R          ((TIM_Registers * )TIM9_BASE_ADDRESS)
#define     TIM10_R         ((TIM_Registers * )TIM10_BASE_ADDRESS)
#define     TIM11_R         ((TIM_Registers * )TIM11_BASE_ADDRESS)
/********************************************************************************************/

/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/
/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/



/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/
/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/

/********************************************************************************************/
/*-----------------------TIM1 Capture/Compare' Configuration--------------------------------*/
/********************************************************************************************/

//-------------------TIM Channels Options : 
typedef enum 
{
    channel_1  = 1,
    channel_2  = 2,
    channel_3  = 3,
    channel_4  = 4

}CHANNEL_NUM;


//--------------------(IC1PSC) Input capture channels' prescaler :
typedef enum
{
    capture_each_event        =   0b00,
    capture_every_2_event     =   0b01,
    capture_every_4_event     =   0b01,
    capture_every_8_event     =   0b11 

}TIM_CH_PRESCALER;


//-------------------Channel Capture Filter :
typedef enum
{
    INPUT_CAPTURE_No_Filter              =0b0000,      //sampling is done at fDTS
    INPUT_CAPTURE_SAMPLING_2_fCK_INT     =0b0001,
    INPUT_CAPTURE_SAMPLING_4_fCK_INT     =0b0010,
    INPUT_CAPTURE_SAMPLING_8_fCK_INT     =0b0011, 

    INPUT_CAPTURE_SAMPLING_6_fDTS_2      =0b0100,
    INPUT_CAPTURE_SAMPLING_8_fDTS_2      =0b0101,

    INPUT_CAPTURE_SAMPLING_6_fDTS_4      =0b0110,
    INPUT_CAPTURE_SAMPLING_8_fDTS_4      =0b0111,

    INPUT_CAPTURE_SAMPLING_6_fDTS_8      =0b1000,
    INPUT_CAPTURE_SAMPLING_8_fDTS_8      =0b1001,

    INPUT_CAPTURE_SAMPLING_5_fDTS_16     =0b1010,
    INPUT_CAPTURE_SAMPLING_6_fDTS_16     =0b1011,
    INPUT_CAPTURE_SAMPLING_8_fDTS_16     =0b1100,

    INPUT_CAPTURE_SAMPLING_5_fDTS_32     =0b1101,
    INPUT_CAPTURE_SAMPLING_6_fDTS_32     =0b1110,
    INPUT_CAPTURE_SAMPLING_8_fDTS_32     =0b1111

}TIM_CH_CAPTURE_FILTER;


//-------------------TIM Channel input Modes : 
typedef enum
{
    INPUT_CH_ICn_ON_TI1     =   0b01,
    INPUT_CH_ICn_ON_TI2     =   0b10,
    INPUT_CH_ICn_ON_TRC     =   0b11   // This mode is working only if an internal trigger input is selected through TS bit

}TIM_CH_INPUT_MODE;

//-------------------TIM Channel input Modes : 
typedef enum
{
    ch_active_on_match          =   0b001,
    ch_inactive_on_match        =   0b010,
    toggle                      =   0b011,  
    force_inactive_level        =   0b100,
    force_active_level          =   0b101,

}TIM_CH_OUTPUT_MODE;

//-------------------Output channel Type :
typedef enum
{
    PWM_mode_1                  =   0b110,
    PWM_mode_2                  =   0b111      

}TIM_CH_PWM_MODE;

//-------------------Center_Aligned Mode:
typedef enum
{
    Center_Aligned_Disable      =0,

    Center_Aligned_Mode1        =1,     /* The counter counts up and down alternatively. Output compare interrupt flags of 
                                        **   channels configured in output (CCxS=00 inTIMx_CCMRx register) are set only
                                        **               when the counter is counting down.                                     */

    Center_Aligned_Mode2        =2,     /* The counter counts up and down alternatively. Output compare interrupt flags of 
                                        **   channels configured in output (CCxS=00 inTIMx_CCMRx register) are set only
                                        **               when the counter is counting Up.                                       */

    Center_Aligned_Mode3        =3      /* The counter counts up and down alternatively. Output compare interrupt flags of 
                                        **   channels configured in output (CCxS=00 inTIMx_CCMRx register) are set
                                        **     both when the counter is counting up or down.                                    */
}CENTER_ALIGNED_M;

//--------------------Channel Input signal Polarity : (CCxNP)/(CCxP) bits in {CCER} register.
typedef enum
{
    non_inverted_rising_edge  =0b00,
    inverted_falling_edge     =0b01,
    non_inverted_both_edge    =0b11

}CH_INPUT_POLARITY;

//--------------------Channel Output signal Polarity : (CCxP) bit in {CCER} register.
typedef enum
{
    active_HIGH     =0,
    active_LOW      =1
}CH_OUTPUT_POLARITY;

//--------------------Channel PWM Input signal Pin :
typedef enum
{
    TI1     =0,
    TI2     =1,
    // TI3     =2,
    // TI4     =3

}CH_PWM_INPUT_PIN;

/********************************************************************************************/
/*-----------------------------TIM1 Base Configuration Options------------------------------*/
/********************************************************************************************/

/*----------------------------TIM General Configuration-------------------------------------*/
//-------------------------Counting Modes :
typedef enum
{
    Count_UP,           // 16-bit counter
    Count_DOWN,         // 16-bit counter       
    Center_Aligned      // 32-bit counter
}COUNTER_MODE;

//-------------------------Auto_Reload Preload :
typedef enum
{
    ARR_not_Buffered,           // do not use Shadow register.
    ARR_Buffered,               // do use Shadow register.       

}AUTOR_PRELOAD;

//-------------------------Clock Selection :
typedef enum
{
    Internal_clk,               // CK_INT.
    External_clk_m1,            // external input pin, there is "Trigger interrupt". 
    External_clk_m2,            // external trigger input ETR, there is No "Trigger interrupt", and there is no trigger_Selection or slave_mode Selection needed.

}CLOCK_SELECTION;

/****************************************************************************************************************************************************/
/* 
** (Note that) :- 
**              there is no big different between [External_clk_m1] and [External_clk_m2], except the exist of the Trigger interrupt in (Mode 1).
*/
/****************************************************************************************************************************************************/

/*----------------------TIM1 External Clock Configuration-----------------------------------*/
//---------------------------(ETPS) External trigger prescaler Options :
typedef enum
{
    Prescaler_OFF =0b00 , 
    ETRP_DIV_BY2  =0b01 , 
    ETRP_DIV_BY4  =0b10 , 
    ETRP_DIV_BY8  =0b11 

}EX_CLK_TRIG_PRESCALER;

//--------------------------External trigger Polarity :
typedef enum
{
    Non_Inverted =0b00 , 
    Inverted     =0b01 

}EX_TRIG_POLARITY;

//--------------------------External trigger Filter :
typedef enum
{
    EX_TRIG_No_Filter              =0b0000,      //sampling is done at fDTS
    EX_TRIG_SAMPLING_2_fCK_INT     =0b0001,
    EX_TRIG_SAMPLING_4_fCK_INT     =0b0010,
    EX_TRIG_SAMPLING_8_fCK_INT     =0b0011, 

    EX_TRIG_SAMPLING_6_fDTS_2      =0b0100,
    EX_TRIG_SAMPLING_8_fDTS_2      =0b0101,

    EX_TRIG_SAMPLING_6_fDTS_4      =0b0110,
    EX_TRIG_SAMPLING_8_fDTS_4      =0b0111,

    EX_TRIG_SAMPLING_6_fDTS_8      =0b1000,
    EX_TRIG_SAMPLING_8_fDTS_8      =0b1001,

    EX_TRIG_SAMPLING_5_fDTS_16     =0b1010,
    EX_TRIG_SAMPLING_6_fDTS_16     =0b1011,
    EX_TRIG_SAMPLING_8_fDTS_16     =0b1100,

    EX_TRIG_SAMPLING_5_fDTS_32     =0b1101,
    EX_TRIG_SAMPLING_6_fDTS_32     =0b1110,
    EX_TRIG_SAMPLING_8_fDTS_32     =0b1111,

}EX_TRIG_FILTER;

//--------------------Slave Mode Selection :
typedef enum
{
    Slave_Mode_disabled    =0b000,      
    Encode_Mode_1          =0b001,
    Encode_Mode_2          =0b010,
    Encode_Mode_3          =0b011, 
    Reset_Mode             =0b100,
    Gated_Mode             =0b101,
    Trigger_Mode           =0b110,
    External_Clock_Mode1   =0b111

}SLAVE_MODE_SELECTION;

//--------------------------External trigger Selection For (External_clk_m1) :
typedef enum
{
    Internal_Trigger_0          =0b000,     // (ITR0). 
    Internal_Trigger_1          =0b001,     // (ITR1).
    Internal_Trigger_2          =0b010,     // (ITR2).
    Internal_Trigger_3          =0b011,     // (ITR3).
    TI1_Edge_Detector           =0b100,     // (TI1F_ED) --> Also from channel 1.

    Filtered_Timer_Input_1      =0b101,     // (TI1FP1), from channel 1, ------> External_clk_m1.
    Filtered_Timer_Input_2      =0b110,     // (TI2FP2), from channel 2, ------> External_clk_m1.

    External_Trigger_input      =0b111      // (ETRF) --------> External_clk_m2.

}EX_TRIG_SELECTION;

/*-----------------------------------------------------------------------------------------*/
typedef struct 
{
    
    EX_TRIG_SELECTION           trigger_Selection;  /*              selects the trigger input to be used to synchronize the counter                  */

    TIM_CH_CAPTURE_FILTER       ch_filter;          /*               the Filter Configuration that the channel will use                              */

    TIM_CH_PRESCALER            ch_prescaler;       /* the ratio of the prescaler acting on input (ICn), The prescaler is reset as soon as CC1E=’0’  */

    CH_INPUT_POLARITY           ch_polarity;        /*                          the Channel polarity in Input Mode                                    */

}EXTERNAL_CLK_M1_CONFIG;

/*-----------------------------------------------------------------------------------------*/
typedef struct 
{
    EX_CLK_TRIG_PRESCALER       prescaler_Type;             /*           the Type of the prescaler of the External Clock        */
    EX_TRIG_POLARITY            trigger_Polarity;           /*  the Polarity of the External trigger in (External_clk_m2) Mode  */
    EX_TRIG_FILTER              trigger_Filter;             /*   the Filter of the External trigger in (External_clk_m2) Mode   */
    SLAVE_MODE_SELECTION        slave_mode;                 /*              the Slave Mode of the Timer Peripheral              */

}EXTERNAL_CLK_M2_CONFIG;
/********************************************************************************************/

/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/
/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/




/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/
/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/

/********************************************************************************************/
/*----------------------------TIM1 functions Status-----------------------------------------*/
/********************************************************************************************/
typedef enum
{
    TIM_OK,
    TIM_BUSY,
    TIM_CLK_ERROR,
    TIM_ERROR

}TIM_FUN_STATE;
/********************************************************************************************/

/********************************************************************************************/
/*-----------------------DataType used with Special functions-------------------------------*/
/********************************************************************************************/
//-------------------TIM Special Values :
#define     _AUTO_RELOAD_MAX_       (u16)0xFFFF
//-------------------TIMER Interrupt Types  : 
typedef enum 
{
    Update_interrupt            =0,     // "UIE" bit.
    CaptureCompare_1_interrupt  =1,     // "CC1IE" bit.
    CaptureCompare_2_interrupt  =2,     // "CC1IE" bit.
    CaptureCompare_3_interrupt  =3,     // "CC1IE" bit.
    CaptureCompare_4_interrupt  =4,     // "CC1IE" bit.
    COM_interrupt               =5,     // "COMIE" bit.
    Trigger_interrupt           =6,     // "TIE" bit.
    Break_interrupt             =7      // "BIE" bit.
}TIM_INTERRUPT_TYPE;
/*------------------------------------------------------------------------------------------*/
typedef struct 
{
    u16     duty_cycle_V;   /*  the Value of the time duty cycle of the applied PWM signal  */
    u16     period_V;       /*    the Value of the time period of the applied PWM signal    */

}TIM_CAPTURE_PWM_VALUES;

/********************************************************************************************/

/********************************************************************************************/
/*---------------------------TIM1 General Handler Struct------------------------------------*/
/********************************************************************************************/
typedef struct
{
	TIM_Registers            *TIMx;              /*          The Timer Peripheral that will be Used                  */

    COUNTER_MODE             Count_M;           /*          The type of counting that the Timer will Use            */

    u16                      prescaler_V;       /*          the value of the prescaler that the timer uses          */

    AUTOR_PRELOAD            preload_State;     /*          the State of the Auto Reload preload Option             */
    u16                      Reload_V;          /*          the value of the Auto_Reload that the timer uses        */

    u8                       Repetition_V;      /*          the Number of Repetition of the Timer/Counter           */

    CLOCK_SELECTION          Peri_Clock;        /*          the Type of clock that the Timer will use               */

    EXTERNAL_CLK_M1_CONFIG  *ext_clk_m1_config; /*      the Configuration of the External Clock in EXTERNAL_CLK_M1  */

    EXTERNAL_CLK_M2_CONFIG  *ext_clk_m2_config; /*      the Configuration of the External Clock in EXTERNAL_CLK_M2  */


}TIM_HANDLER;
/********************************************************************************************/

/********************************************************************************************/
/*------------------------Channel Input Config Struct---------------------------------------*/
/********************************************************************************************/
typedef struct
{

    TIM_CH_INPUT_MODE        ch_input_mode;   /*           the Operation Input Mode of the CH : [INPUT]                                        */

    TIM_CH_PRESCALER         ch_prescaler;    /* the ratio of the prescaler acting on input (ICn), The prescaler is reset as soon as CC1E=’0’  */

    TIM_CH_CAPTURE_FILTER    ch_filter;       /*               the Filter Configuration that the channel will use                              */

    CH_INPUT_POLARITY        ch_polarity;     /*                          the Channel polarity in Input Mode                                    */

}TIM_CH_INPUT_CONFIG;
/********************************************************************************************/

/********************************************************************************************/
/*------------------------Channel Input PWM Struct------------------------------------------*/
/********************************************************************************************/
typedef struct
{
    CH_PWM_INPUT_PIN         pin_number;      /*                the number of the Pin that the signal came from.                              */

    TIM_CH_INPUT_MODE        ch_input_mode;   /*           the Operation Input Mode of the CH : [INPUT]                                        */

    TIM_CH_PRESCALER         ch_prescaler;    /* the ratio of the prescaler acting on input (ICn), The prescaler is reset as soon as CC1E=’0’  */

    TIM_CH_CAPTURE_FILTER    ch_filter;       /*               the Filter Configuration that the channel will use                              */

    CH_INPUT_POLARITY        ch_polarity;     /*                          the Channel polarity in Input Mode                                    */

}TIM_CAPTURE_PWM_CONFIG;


/********************************************************************************************/
/*------------------------Channel Output Config Struct--------------------------------------*/
/********************************************************************************************/
typedef struct
{
    CHANNEL_NUM             ch_number;       /*                the number of the Channel in the peripheral.                                    */

    TIM_CH_OUTPUT_MODE     	ch_input_mode;   /*           the Operation Output Mode of the CH : [OUTPUT]                                       */

    TIM_CH_PRESCALER   		ch_prescaler;    /* the ratio of the prescaler acting on input (ICn), The prescaler is reset as soon as CC1E=’0’  */

    TIM_CH_CAPTURE_FILTER   ch_filter;       /*               the Filter Configuration that the channel will use                              */

    CENTER_ALIGNED_M       	Center_Al_M;     /*                                 the Mode of the Center_Aligned                                */

    CH_OUTPUT_POLARITY     	ch_polarity;     /*                               the Channel polarity in Output Mode                             */

}TIM_CH_OUTPUT_CONFIG;


/********************************************************************************************/
/*------------------------Channel Output PWM Config Struct----------------------------------*/
/********************************************************************************************/
typedef struct
{
    CHANNEL_NUM              ch_number;      /*                the number of the Channel in the peripheral.                                   */

    TIM_CH_PWM_MODE          ch_PWM_mode;     /*           the Operation Output Mode of the CH : [OUTPUT]                                      */

    TIM_CH_PRESCALER         ch_prescaler;    /* the ratio of the prescaler acting on input (ICn), The prescaler is reset as soon as CC1E=’0’  */

    TIM_CH_CAPTURE_FILTER    ch_filter;       /*               the Filter Configuration that the channel will use                              */

    CH_OUTPUT_POLARITY       ch_polarity;    /*                               the Channel polarity in Output Mode                             */

}TIM_CH_PWM_CONFIG;
/********************************************************************************************/

/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/
/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/




/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/
/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/


/********************************************************************************************/
/*-------------------------------Functions' Prototype---------------------------------------*/
/********************************************************************************************/

/*********************----------General Functions----------**********************************/
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Base_Config : in this Function we just Configure the Counting mode and the clock.
/// @param timx                 : the general Timer handler struct.
/// @return the Function state.
TIM_FUN_STATE   MCAL_TIM_General_Config(TIM_HANDLER   *timx);
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Prescaler   : this function is responsible for loading the Prescaler value in the {PSC} register . 
/// @param timx                 : the general Timer handler struct.
/// @param prescaler_value      : the Prescaler value.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Prescaler(TIM_HANDLER   *timx, u16 prescaler_value);
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Reload_Value : this function is responsible for loading the AUTO_RELOAD value in the {ARR} register in Normal mode.
/// @param timx                  : the general Timer handler struct.
/// @param reload_value          : the Auto_Reload value.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Reload_Value(TIM_HANDLER   *timx, u16 reload_value);
/*------------------------------------------------------------------------------------------*/

// The repetition counter is decremented:
// • At each counter overflow in upcounting mode,
// • At each counter underflow in downcounting mode,
// • At each counter overflow and at each counter underflow in center-aligned mode.
// These bits allow the user to set-up the update rate of the compare registers,
// as well as the update interrupt generation rate, if this interrupt is enable.
//  any write to the TIMx_RCR register is not taken in account until the next repetition update event.
// It means in PWM mode (REP+1) corresponds to:
// – the number of PWM periods in edge-aligned mode
// – the number of half PWM period in center-aligned mode

/// @brief MCAL_TIM_RepetitionCounter   : this function initiate the number of repetition of the counter.
/// @param timx                         : the general Timer handler struct.
/// @param Repetition_value             : the Number of Repetition.
/// @return             Function State. 
TIM_FUN_STATE   MCAL_TIM_RepetitionCounter(TIM_HANDLER   *timx, u8 repetition_value);
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_START_peri  : this Function is used to Start the Counter.
/// @param timx                  : the general Timer handler struct.
/// @return     Function State. 
TIM_FUN_STATE   MCAL_TIM_START_peri(TIM_HANDLER   *timx);
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_STOP_peri   : this Function is used to Stop the Counter.
/// @param timx                 : the general Timer handler struct.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_STOP_peri(TIM_HANDLER   *timx);
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_CH_Enable   : this function Enable the Channel in Capture or in Output Compare Mode.
/// @param timx             : the general Timer handler struct.
/// @param ch_Num           : the channel number in the peripheral.
/// @return       the remaining time.
TIM_FUN_STATE   MCAL_CH_Enable(TIM_HANDLER   *timx , CHANNEL_NUM  ch_Num );
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_CH_Enable   : this function Disable the Channel in Capture or in Output Compare Mode.
/// @param timx             : the general Timer handler struct.
/// @param ch_Num           : the channel number in the peripheral.
/// @return       the remaining time.
TIM_FUN_STATE   MCAL_CH_Disable(TIM_HANDLER   *timx , CHANNEL_NUM  ch_Num );
/*------------------------------------------------------------------------------------------*/

/********************************************************************************************/


/***********************----------Base Functions----------***********************************/
#if			_BASE_FUNCTIONS_	 	== 	stTRUE
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Elapsed_Time : this function is used to return the elapsed time of the counter. 
/// @param timx                  : the general Timer handler struct.
/// @return         the Elapsed time value.
u32   MCAL_TIM_Elapsed_Time(TIM_HANDLER   *timx );
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Remain_Time  : this function is used to return the remaining time of the counter.
/// @param timx                  : the general Timer handler struct.
/// @return             the remaining time.
u32   MCAL_TIM_Remain_Time(TIM_HANDLER   *timx );
/*------------------------------------------------------------------------------------------*/
#endif
/********************************************************************************************/


/******************----------Capture/Compare Input Functions----------***********************/
#if			_CC_INPUT_FUNCTIONS_	 	== 	stTRUE
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Capture_Input_Config : this function is used to configure a channel as A Capture input channel.
/// @param timx                          : the general Timer handler struct.
/// @param ch_capture_config             : the Configuration struct that will be used.
/// @param ch_Num                        : the Channel Number.
/// @return         the Function state.
TIM_FUN_STATE   MCAL_TIM_Capture_Input_Config(TIM_HANDLER   *timx , TIM_CH_INPUT_CONFIG *ch_capture_config , CHANNEL_NUM ch_Num );
/*------------------------------------------------------------------------------------------*/
// This mode is a particular case of input capture mode. The procedure is the same except:
// • Two ICx signals are mapped on the same TIx input.
// • These 2 ICx signals are active on edges with opposite polarity.
// • One of the two TIxFP signals is selected as trigger input and the slave mode controller
//  is configured in reset mode.
// For example :- user can measure the period (in TIMx_CCR1 register) and the duty cycle (in TIMx_CCR2 register) of the PWM applied on TI1
/// @brief MCAL_TIM_Capture_PWM_Config : this function is used to configure a channel as A Capture input channel.
/// @param timx                        : the general Timer handler struct.
/// @param capture_pwm_config          : the PWM capture input struct that has the configurations.
/// @return         the Function state.
TIM_FUN_STATE   MCAL_TIM_Capture_PWM_Config(TIM_HANDLER  *timx , TIM_CAPTURE_PWM_CONFIG *capture_pwm_config );
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Elapsed_Time : this function is used to return the Channel Capture value. 
/// @param timx                  : the general Timer handler struct.
/// @param ch_Num                : the Channel Number.
/// @return         the Channel Capture value.
u32   MCAL_TIM_Capture_Value(TIM_HANDLER   *timx , CHANNEL_NUM ch_Num );
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Elapsed_Time : this function is used to return the Channel Capture value. 
/// @param timx                  : the general Timer handler struct.
/// @param timer_input           : the input terminal that the signal is applied on.
/// @param return_values         : the struct that will store the values.
/// @return         the Function state.
TIM_FUN_STATE   MCAL_TIM_PWM_Input_Values(TIM_HANDLER *timx , CH_PWM_INPUT_PIN timer_input , TIM_CAPTURE_PWM_VALUES *return_values );
/*------------------------------------------------------------------------------------------*/
#endif
/********************************************************************************************/


/*****************----------Capture/Compare OUTput Functions----------***********************/
#if			_CC_OUTPUT_FUNCTIONS_	 	== 	stTRUE
/*------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------*/
#endif
/********************************************************************************************/


/***********************----------Timer PWM Functions----------******************************/
#if			_PWM_OUTPUT_FUNCTIONS_	 	== 	stTRUE
/*------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------*/
#endif
/********************************************************************************************/


/********************----------Timer Interrupt Functions----------***************************/
#if			_TIMER_INTERRUPT_FUNCTIONS_	 == 	stTRUE
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Interrupt_CallBack  : this Function is used to set CallBack Functions to there Handler Functions.
/// @param timx                         : the general Timer handler struct.
/// @param ptFunction                   : pointer to the Function that will be executed inside the handler.
/// @param interrupt_type               : the Type of the interrupt that the will execute the function.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Interrupt_CallBack(TIM_HANDLER   *timx , TIM_INTERRUPT_TYPE interrupt_type , void (*ptFunction)(void) );
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Interrupt_Enable    : this function is used to Enable the interrupt.
/// @param timx                         : the general Timer handler struct.
/// @param interrupt_type               : the Type of the interrupt that the will be Enabled.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Interrupt_Enable(TIM_HANDLER   *timx , TIM_INTERRUPT_TYPE interrupt_type);
/*------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Interrupt_Disable   : this function is used to Disable the interrupt.
/// @param timx                         : the general Timer handler struct.
/// @param interrupt_type               : the Type of the interrupt that the will be Disabled.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Interrupt_Disable(TIM_HANDLER   *timx , TIM_INTERRUPT_TYPE interrupt_type);
/*------------------------------------------------------------------------------------------*/
#endif
/********************************************************************************************/

/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/
/**************************************************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++******************************************/

#endif
