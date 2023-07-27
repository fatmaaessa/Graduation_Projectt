/********************************************************************************************/
/* 	AUTHOR  		: islam atef Mohamed 													*/
/* 	VERSION 		:	  V1.0 																*/
/* 	DATE    		:  1/2023 																*/
/*	Description  	:  This is the Program file For the TIMER Peripheral                    */
/*                                       at ARM-CORTEX m4						            */
/********************************************************************************************/

#include 	"../LIB/BIT_MATH.h"
#include 	"../LIB/STD_Types.h"

#include "../Inc/TIM_private.h"
#include "../Inc/TIM_config.h"
#include "../Inc/TIM_interface.h"


/* Notes*/

/* (1) The UEV event can be disabled by software by setting the UDIS bit in the TIMx_CR1
register. This is to avoid updating the shadow registers while writing new values in the
preload registers. Then no update event occurs until the UDIS bit has been written to 0. */

/* (2) if the URS bit (update request selection) in TIMx_CR1 register is set,
setting the UG bit generates an update event UEV but without setting the UIF flag,
This is to avoid generating both update and capture interrupts 
when clearing the counter on the capture event. */


/**************************************************----------General Functions----------*********************************************************/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_General_Config : in this Function we just Configure the Counting mode and the clock.
/// @param timx                    : the general Timer handler struct.
/// @return the Function state.
TIM_FUN_STATE   MCAL_TIM_General_Config(TIM_HANDLER   *timx)
{
    // Check parameters.
    if (timx ->TIMx == NULL){ return TIM_ERROR;}
    // Disable the Peripheral.
    CLR_BIT(timx ->TIMx ->CR1, CR1_CEN);

    // Configure the Counting Type.
    if (timx ->Count_M != Center_Aligned)
    {
        CLR_BIT(timx ->TIMx ->CR1 , CR1_CMS_0 | CR1_CMS_1);
        CLR_BIT(timx ->TIMx ->CR1 , CR1_DIR);
        __WRITE_BIT_(timx ->TIMx ->CR1 ,CR1_DIR ,timx ->Count_M);
    }
    else
    {
        CLR_BIT(timx ->TIMx ->CR1 , CR1_CMS_0 | CR1_CMS_1);
        __WRITE_BIT_(timx ->TIMx ->CR1 ,CR1_CMS_0 ,1);
    }

    // clock Configuration.
    /*--------First---------Internal_clk ---> (SMS=000) Configuration.--------------------------------*/
    // clear the Slave Selection First to configure the other Options.
    CLR_BIT(timx ->TIMx ->SMCR, SMCR_SMS_0 | SMCR_SMS_1 | SMCR_SMS_2);
    // clear External Clock Enable bit (ECE.)
    CLR_BIT(timx ->TIMx ->SMCR, SMCR_ECE);

    switch (timx ->Peri_Clock)
    {
        case    External_clk_m1:
        {
            // 1- Channel Mapping terminals
            if (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_1)
            {
                __WRITE_BIT_(timx ->TIMx ->CCMR1, CCMR1_CC1S_0 , 0b01); // 01: CC1 channel is configured as input, IC1 is mapped on TI1
            }
            else if (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_2)
            {
                __WRITE_BIT_(timx ->TIMx ->CCMR1, CCMR1_CC2S_0 , 0b01); // 01: CC2 channel is configured as input, IC2 is mapped on TI2
            }

            // 2- select the Channel Filter.
            if (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_1)
            {
                // clear the Filter bits.
                CLR_BIT(timx ->TIMx ->CCMR1, CCMR1_IC1F_0 | CCMR1_IC1F_1 | CCMR1_IC1F_2 | CCMR1_IC1F_3 );
                // write the Filter bits' value.
                __WRITE_BIT_(timx ->TIMx ->CCMR1, CCMR1_IC1F_0 , timx ->ext_clk_m1_config ->ch_filter);
            }
            else if (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_2)
            {
                // clear the Filter bits.
                CLR_BIT(timx ->TIMx ->CCMR1, CCMR1_IC2F_0 | CCMR1_IC2F_1 | CCMR1_IC2F_2 | CCMR1_IC2F_3 );
                // write the Filter bits' value.
                __WRITE_BIT_(timx ->TIMx ->CCMR1, CCMR1_IC2F_0 , timx ->ext_clk_m1_config ->ch_filter);
            }

            // 3- select the Channel prescaler.
            if (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_1)
            {
                // clear the prescaler bits.
                CLR_BIT(timx ->TIMx ->CCMR1, CCMR1_IC1PSC_0 | CCMR1_IC1PSC_1 );
                // write the prescaler bits' value.
                __WRITE_BIT_(timx ->TIMx ->CCMR1, CCMR1_IC1PSC_0 , timx ->ext_clk_m1_config ->ch_prescaler);
            }
            else if (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_2)
            {
                // clear the Filter bits.
                CLR_BIT(timx ->TIMx ->CCMR1, CCMR1_IC2PSC_0 | CCMR1_IC2PSC_1  );
                // write the Filter bits' value.
                __WRITE_BIT_(timx ->TIMx ->CCMR1, CCMR1_IC2PSC_0 , timx ->ext_clk_m1_config ->ch_prescaler);
            }

            // 4- select the Channel Trigger signal Polarity : configure (CCxNP)/(CCxP) bits in {CCER} register.
            CLR_BIT(timx ->TIMx ->CCER, CCER_CC1P | CCER_CC1NP );

            switch ( timx ->ext_clk_m1_config ->ch_polarity)
            {
            case non_inverted_rising_edge   :
                // CC1P =0;
                CLR_BIT(timx ->TIMx ->CCER, CCER_CC1P);
                // CC1NP =0;
                CLR_BIT(timx ->TIMx ->CCER, CCER_CC1NP);
                break;

            case inverted_falling_edge      :
                // CC1P =0;
                CLR_BIT(timx ->TIMx ->CCER, CCER_CC1P);
                // CC1NP =0;
                SET_BIT(timx ->TIMx ->CCER, CCER_CC1NP);
                break;

            case non_inverted_both_edge     :
                // CC1P =0;
                SET_BIT(timx ->TIMx ->CCER, CCER_CC1P);
                // CC1NP =0;
                SET_BIT(timx ->TIMx ->CCER, CCER_CC1NP);
                break;
            }

            // 5- Enable the Channel.
            if (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_1)
            {
                SET_BIT(timx ->TIMx ->CCER , CCER_CC1E );
            }
            else if (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_2)
            {
                SET_BIT(timx ->TIMx ->CCER , CCER_CC2E );
            }

            // 6- select the slave_mode.
            __WRITE_BIT_(timx ->TIMx ->SMCR, SMCR_SMS_0, External_Clock_Mode1);

            // 7- select the  (External_Trigger_input) as the Trigger source.
            if ( (timx ->ext_clk_m1_config ->trigger_Selection != Filtered_Timer_Input_1) || \
                 (timx ->ext_clk_m1_config ->trigger_Selection != Filtered_Timer_Input_2)     )
            {
                return TIM_ERROR;
            }
            __WRITE_BIT_(timx ->TIMx ->SMCR , SMCR_TS_0 , (timx ->ext_clk_m1_config ->trigger_Selection) );
            break;
        }
        case    External_clk_m2:
        {
            // 1- select the External clock Polarity.
            CLR_BIT(timx ->TIMx ->SMCR, SMCR_ETP );
            __WRITE_BIT_(timx ->TIMx ->SMCR, SMCR_ETP , timx ->ext_clk_m2_config ->trigger_Polarity);

            // 2- select the External clock prescaler.
            CLR_BIT(timx ->TIMx ->SMCR, SMCR_ETPS_0 | SMCR_ETPS_1 );
            __WRITE_BIT_(timx ->TIMx ->SMCR, SMCR_ETPS_0 , timx ->ext_clk_m2_config ->prescaler_Type);

            // 3- select the External clock Filter.
            CLR_BIT(timx ->TIMx ->SMCR, SMCR_ETF_0 | SMCR_ETF_1 | SMCR_ETF_2 | SMCR_ETF_3 );
            __WRITE_BIT_(timx ->TIMx ->SMCR, SMCR_ETPS_0 , timx ->ext_clk_m2_config ->trigger_Filter);

            // 4- select the  (External_Trigger_input) as the Trigger source.
            __WRITE_BIT_(timx ->TIMx ->SMCR, SMCR_TS_0, External_Trigger_input);

            // 5- select the slave_mode.
            if (timx ->ext_clk_m2_config ->slave_mode == External_Clock_Mode1)
            {
                return TIM_ERROR;
            }
            __WRITE_BIT_(timx ->TIMx ->SMCR, SMCR_SMS_0, timx ->ext_clk_m2_config ->slave_mode );

            // 5- Here we just Enable the (ECE) bit at the {SMCR} register, to select the [ETRF] as the trigger source .
            SET_BIT(timx ->TIMx ->SMCR, SMCR_ECE);

            break;
        }
        default :   //Internal_clk ---> (SMS=000).
            /*  DO Nothing Additional */
            break;
    }

    // Auto_Reload Configuration.
    //---------------------------------configure the preload Option of the Peripheral :
    CLR_BIT(timx ->TIMx ->CR1, CR1_ARPE);
    __WRITE_BIT_(timx ->TIMx ->CR1 ,CR1_ARPE ,timx ->preload_State);
    //---------------------------------write the Reload value in the {ARR} register :
    if ( timx ->Reload_V )
    {
        timx ->TIMx ->ARR = timx ->Reload_V;
    }else
    {
        timx ->TIMx ->ARR = _AUTO_RELOAD_MAX_;
    }

    // Initial Prescaler Configuration.
    //---------------------------------write the prescaler value in the {PSC} register if it exists:
    if ( timx ->prescaler_V )
    {
        timx ->TIMx ->PSC = timx ->prescaler_V;
    }else
    {
        timx ->TIMx ->PSC = 0x0000;
    }

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Prescaler   : this function is responsible for loading the Prescaler value in the {PSC} register . 
/// @param timx                 : the general Timer handler struct.
/// @param prescaler_value      : the Prescaler value.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Prescaler(TIM_HANDLER   *timx, u16 prescaler_value)
{   
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    // Check the Type of the clock source.
    if ( (timx ->Peri_Clock == External_clk_m1) || (timx ->Peri_Clock == External_clk_m2) )
    {
        return TIM_CLK_ERROR;
    }
    
    // store the new prescaler value in the prescaler variable in the TIM_HANDLER.
    timx ->prescaler_V = prescaler_value;

    // write the prescaler value in the {PSC} register.
    timx ->TIMx ->PSC = timx ->prescaler_V;

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Reload_Value : this function is responsible for loading the AUTO_RELOAD value in the {ARR} register in Normal mode.
/// @param timx                  : the general Timer handler struct.
/// @param reload_value          : the Auto_Reload value.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Reload_Value(TIM_HANDLER   *timx, u16 reload_value)
{   
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    // store the new Reload value in the Reload variable in the TIM_HANDLER.
    timx ->Reload_V = reload_value;

    // write the Reload value in the {ARR} register.
    timx ->TIMx ->ARR = timx ->Reload_V;

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
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
TIM_FUN_STATE   MCAL_TIM_RepetitionCounter(TIM_HANDLER   *timx, u8 repetition_value)
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    // store the new Reload value in the Reload variable in the TIM_HANDLER.
    timx ->Repetition_V = repetition_value;

    // write the Reload value in the {ARR} register.
    timx ->TIMx ->RCR = timx ->Repetition_V;

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_START_peri  : this Function is used to Start the Counter.
/// @param timx                  : the general Timer handler struct.
/// @return     Function State. 
TIM_FUN_STATE   MCAL_TIM_START_peri(TIM_HANDLER   *timx)
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    // write the prescaler value in the {PSC} register.
    timx ->TIMx ->PSC = timx ->prescaler_V;

    // write the Reload value in the {ARR} register.
    timx ->TIMx ->ARR = timx ->Reload_V;

    // Enable the Peripheral.
    SET_BIT(timx ->TIMx ->CR1, CR1_CEN);

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_STOP_peri   : this Function is used to Stop the Counter.
/// @param timx                 : the general Timer handler struct.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_STOP_peri(TIM_HANDLER   *timx)
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    // Disable the Peripheral.
    CLR_BIT(timx ->TIMx ->CR1, CR1_CEN);

    // write the prescaler value in the {PSC} register.
    timx ->TIMx ->PSC = 0;

    // write the Reload value in the {ARR} register.
    timx ->TIMx ->ARR = 0;

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_CH_Enable   : this function Enable the Channel in Capture or in Output Compare Mode.
/// @param timx             : the general Timer handler struct.
/// @param ch_Num           : the channel number in the peripheral.
/// @return       the remaining time.
TIM_FUN_STATE   MCAL_CH_Enable(TIM_HANDLER   *timx , CHANNEL_NUM  ch_Num )
{
    // check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }
    // Enable the Channel.
    SET_BIT(timx ->TIMx ->CCER , ((ch_Num-1)*2) );
    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_CH_Enable   : this function Disable the Channel in Capture or in Output Compare Mode.
/// @param timx             : the general Timer handler struct.
/// @param ch_Num           : the channel number in the peripheral.
/// @return       the remaining time.
TIM_FUN_STATE   MCAL_CH_Disable(TIM_HANDLER   *timx , CHANNEL_NUM  ch_Num )
{
    // check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }
    // Disable the channel.
    CLR_BIT(timx ->TIMx ->CCER , ((ch_Num-1)*2) );
    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/************************************************************************************************************************************************/






/****************************************************----------Base Functions----------**********************************************************/
#if			_BASE_FUNCTIONS_	 	== 	stTRUE
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/// @brief MCAL_TIM_Elapsed_Time : this function is used to return the elapsed time of the counter. 
/// @param timx                  : the general Timer handler struct.
/// @return         the Elapsed time value.
u32   MCAL_TIM_Elapsed_Time(TIM_HANDLER   *timx )
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    u32 Elapsed_Time ;

    if (timx ->Count_M != Center_Aligned)
    {
        Elapsed_Time = GET_BIT(timx ->TIMx ->CR1 , CR1_DIR)? ((timx ->Reload_V) -(timx ->TIMx ->CNT)):(timx ->TIMx ->CNT);
        return Elapsed_Time;
    }
    else
    {
        Elapsed_Time = GET_BIT(timx ->TIMx ->CR1 , CR1_DIR)? (timx ->TIMx ->CNT):((timx ->TIMx ->CNT)+(timx ->Reload_V));
        return Elapsed_Time;
    }
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/// @brief MCAL_TIM_Remain_Time  : this function is used to return the remaining time of the counter.
/// @param timx                  : the general Timer handler struct.
/// @return             the remaining time.
u32   MCAL_TIM_Remain_Time(TIM_HANDLER   *timx )
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    u32 Remain_Time;
    if (timx ->Count_M != Center_Aligned)
    {
        Remain_Time = GET_BIT(timx ->TIMx ->CR1 , CR1_DIR)? (timx ->TIMx ->CNT):((timx ->Reload_V) -(timx ->TIMx ->CNT));
        return Remain_Time;
    }
    else
    {
        Remain_Time = GET_BIT(timx ->TIMx ->CR1 , CR1_DIR)? ( ( (timx ->Reload_V)-(timx ->TIMx ->CNT) )+(timx ->Reload_V)) : ((timx ->Reload_V)-(timx ->TIMx ->CNT));
        return Remain_Time;
    }
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
#endif
/************************************************************************************************************************************************/



/* CC2S[1:0] bit-field defines the direction of the channel (input/output) as well as the used input. */

/*****************************************----------Capture/Compare Input Functions----------****************************************************/
#if			_CC_INPUT_FUNCTIONS_	 	== 	stTRUE
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Capture_Input_Config : this function is used to configure a channel as A Capture PWM channel.
/// @param timx                          : the general Timer handler struct.
/// @param ch_capture_config             : the Configuration struct that will be used.
/// @param ch_Num                        : the Channel Number.
/// @return         the Function state.
TIM_FUN_STATE   MCAL_TIM_Capture_Input_Config(TIM_HANDLER  *timx , TIM_CH_INPUT_CONFIG *ch_capture_config , CHANNEL_NUM ch_Num )
{
   
    // check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    // check clock source.
    if (timx ->Peri_Clock == External_clk_m1) 
    {   
        if (   ((ch_Num == channel_1) && (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_1)) \
            || ((ch_Num == channel_2) && (timx ->ext_clk_m1_config ->trigger_Selection == Filtered_Timer_Input_2)) )
        {
            return TIM_CLK_ERROR; 
        }
    }

    u8  local_var = ch_Num; 

    // configure the channel as Capture input channel.
    if( ch_Num < 3)
    {
        // 1- adjust the channel number to suitable the other register configuration
        local_var -=1; 

        // 2- select the channel trigger (CCxS)bits :

        // Clear the CCnS bits.
        CLR_BIT(timx ->TIMx -> CCMR1 , (CCMR1_CC1S_0 +(local_var * 8))) ;
        CLR_BIT(timx ->TIMx -> CCMR1 , (CCMR1_CC1S_1 +(local_var * 8))) ;
     
        // check if there is a mismatch with the clock mode.
        if ( (ch_capture_config ->ch_input_mode == INPUT_CH_ICn_ON_TRC) && (timx ->Peri_Clock != Internal_clk))
        {
            return TIM_CLK_ERROR;
        }

        // 3- Select the Channel capture input Mode.
        __WRITE_BIT_(timx ->TIMx -> CCMR1 , (CCMR1_CC1S_0 +(local_var * 8)) , ch_capture_config ->ch_input_mode);

        // 4- select the Channel Filter :

        // clear the filter bits (ICxF_0),(ICxF_1),(ICxF_2),and (ICxF_3).
        CLR_BIT(timx ->TIMx -> CCMR1 , (CCMR1_IC1F_0 +(local_var * 8)) | (CCMR1_IC1F_1 +((local_var * 8))) );
        CLR_BIT(timx ->TIMx -> CCMR1 , (CCMR1_IC1F_2 +(local_var * 8)) | (CCMR1_IC1F_3 +((local_var * 8))) );
        // Select the Channel Mode.
        __WRITE_BIT_(timx ->TIMx -> CCMR1 , (CCMR1_IC1F_0 +(local_var * 8)) , ch_capture_config -> ch_filter);


        // 5- select the Channel prescaler :

        // clear the prescaler bits.
        CLR_BIT(timx ->TIMx ->CCMR1, (CCMR1_IC1PSC_0 +(local_var * 8)) | (CCMR1_IC1PSC_1 +(local_var * 8)) );
        // write the prescaler bits' value.
        __WRITE_BIT_(timx ->TIMx ->CCMR1, (CCMR1_IC1PSC_0 +(local_var * 8)) , ch_capture_config ->ch_prescaler);
    }
    else
    {
        // 2- adjust the channel number to suitable the other register configuration
        local_var -=3;

        // 2- select the channel trigger (CCxS)bits :

        // Clear the CCnS bits.
        CLR_BIT(timx ->TIMx -> CCMR2 , (CCMR2_CC3S_0 +(local_var * 8)) | (CCMR2_CC3S_1 +((local_var * 8)) ));

        // check if there is a mismatch with the clock mode.
        if ( (ch_capture_config ->ch_input_mode == INPUT_CH_ICn_ON_TRC) && (timx ->Peri_Clock != Internal_clk))
        {
            return TIM_CLK_ERROR;
        }

        // 3- Select the Channel capture input Mode
        __WRITE_BIT_(timx ->TIMx -> CCMR1 , (CCMR2_CC3S_0 +(local_var * 8)) , ch_capture_config ->ch_input_mode);


        // 4- select the Channel Filter :

        // clear the filter bits (ICxF_0),(ICxF_1),(ICxF_2),and (ICxF_3).
        CLR_BIT(timx ->TIMx -> CCMR1 , (CCMR2_IC3F_0 +(local_var * 8)) | (CCMR2_IC3F_1 +((local_var * 8))) );
        CLR_BIT(timx ->TIMx -> CCMR1 , (CCMR2_IC3F_2 +(local_var * 8)) | (CCMR2_IC3F_3 +((local_var * 8))) );
        // Select the Channel Mode.
        __WRITE_BIT_(timx ->TIMx -> CCMR2 , (CCMR2_IC3F_0 +(local_var * 8)) , ch_capture_config -> ch_filter);

        // 5- select the Channel prescaler :

        // clear the prescaler bits.
        CLR_BIT(timx ->TIMx ->CCMR2, (CCMR2_IC3PSC_0 +(local_var * 8)) | (CCMR2_IC3PSC_1 +(local_var * 8)) );
        // write the prescaler bits' value.
        __WRITE_BIT_(timx ->TIMx ->CCMR2, (CCMR2_IC3PSC_0 +(local_var * 8)) , ch_capture_config ->ch_prescaler); 
    }

    // 6- select the Channel Trigger signal Polarity : configure (CCxNP)/(CCxP) bits in {CCER} register :
    // clear the polarity bits.
    CLR_BIT(timx ->TIMx ->CCER, CCER_CC1P+(ch_Num * 4) | CCER_CC1NP+(ch_Num * 4));
    switch ( ch_capture_config ->ch_polarity)
    {
    case non_inverted_rising_edge   :
        // CCxNP =0;
        CLR_BIT(timx ->TIMx ->CCER, CCER_CC1NP+(ch_Num * 4));
        // CCxP =0;
        CLR_BIT(timx ->TIMx ->CCER, CCER_CC1P+(ch_Num * 4));
        break;
    case inverted_falling_edge      :
        // CCxNP =0;
        CLR_BIT(timx ->TIMx ->CCER, CCER_CC1NP+(ch_Num * 4));
        // CCxP =1;
        SET_BIT(timx ->TIMx ->CCER, CCER_CC1P+(ch_Num * 4));
        break;
    case non_inverted_both_edge     :
        // CCxNP =1;
        SET_BIT(timx ->TIMx ->CCER, CCER_CC1NP+(ch_Num * 4));
        // CCxP =1;
        SET_BIT(timx ->TIMx ->CCER, CCER_CC1P+(ch_Num * 4));
        break;
    }

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
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
TIM_FUN_STATE   MCAL_TIM_Capture_PWM_Config(TIM_HANDLER  *timx , TIM_CAPTURE_PWM_CONFIG *capture_pwm_config )
{
    //  Stop the Peripheral.
    MCAL_TIM_STOP_peri(timx);

    // check clock source.
    if (timx ->Peri_Clock == External_clk_m1) 
    {   
        return TIM_CLK_ERROR; 
    }

    // 1- Select the active input for TIMx_CCR1, Select the active input for TIMx_CCR2 : (TI1 selected) or (TI2 selected).
    //                                TIMx_CCR3, Select the active input for TIMx_CCR4 : (TI3 selected) or (TI4 selected)
    switch (capture_pwm_config ->pin_number)
    {
    case TI1:
        // clear CCxS bits :
        CLR_BIT(timx ->TIMx ->CCMR1 , CCMR1_CC1S_0 | CCMR1_CC1S_1);
        CLR_BIT(timx ->TIMx ->CCMR1 , CCMR1_CC2S_0 | CCMR1_CC2S_1);
        // select the active input :
        __WRITE_BIT_(timx ->TIMx ->CCMR1 , CCMR1_CC1S_0 ,01); // CC1 channel is configured as input, IC1 is mapped on TI1
        __WRITE_BIT_(timx ->TIMx ->CCMR1 , CCMR1_CC2S_0 ,10); // CC2 channel is configured as input, IC2 is mapped on TI1
        break;
    
    case TI2:
        // clear CCxS bits.
        CLR_BIT(timx ->TIMx ->CCMR1 , CCMR1_CC1S_0 | CCMR1_CC1S_1);
        CLR_BIT(timx ->TIMx ->CCMR1 , CCMR1_CC2S_0 | CCMR1_CC2S_1);
        // select the active input :
        __WRITE_BIT_(timx ->TIMx ->CCMR1 , CCMR1_CC1S_0 ,10); // CC1 channel is configured as input, IC1 is mapped on TI2
        __WRITE_BIT_(timx ->TIMx ->CCMR1 , CCMR1_CC2S_0 ,01); // CC2 channel is configured as input, IC2 is mapped on TI2

        break;
    // case TI3:
    //     // clear CCxS bits.
    //     CLR_BIT(timx ->TIMx ->CCMR2 , CCMR2_CC3S_0 | CCMR2_CC3S_1);
    //     CLR_BIT(timx ->TIMx ->CCMR2 , CCMR2_CC4S_0 | CCMR2_CC4S_1);
    //     // select the active input :
    //     __WRITE_BIT_(timx ->TIMx ->CCMR2 , CCMR2_CC3S_0 ,01); // CC3 channel is configured as input, IC3 is mapped on TI3
    //     __WRITE_BIT_(timx ->TIMx ->CCMR2 , CCMR2_CC4S_0 ,10); // CC4 channel is configured as input, IC4 is mapped on TI3
    //     break;

    // case TI4:
    //    // clear CCxS bits.
    //     CLR_BIT(timx ->TIMx ->CCMR2 , CCMR2_CC3S_0 | CCMR2_CC3S_1);
    //     CLR_BIT(timx ->TIMx ->CCMR2 , CCMR2_CC4S_0 | CCMR2_CC4S_1);
    //     // select the active input :
    //     __WRITE_BIT_(timx ->TIMx ->CCMR2 , CCMR2_CC3S_0 ,10); // CC3 channel is configured as input, IC3 is mapped on TI4
    //     __WRITE_BIT_(timx ->TIMx ->CCMR2 , CCMR2_CC4S_0 ,01); // CC4 channel is configured as input, IC4 is mapped on TI4
    //     break;

    }

    // 2- select the Channel Trigger signal Polarity : configure (CCxNP)/(CCxP) bits in {CCER} register :
    // clear the polarity bits.
    u8 local_buffer = capture_pwm_config ->pin_number ;
    for (u8 i = 0; i < 2; i++)
    {
        CLR_BIT(timx ->TIMx ->CCER, CCER_CC1P+((local_buffer) * 4) | CCER_CC1NP+((local_buffer) * 4));
        switch ( capture_pwm_config ->ch_polarity)
        {
        case non_inverted_rising_edge   :
            // CCxNP =0;
            CLR_BIT(timx ->TIMx ->CCER, CCER_CC1NP+((local_buffer) * 4));
            // CCxP =0;
            CLR_BIT(timx ->TIMx ->CCER, CCER_CC1P+((local_buffer) * 4));
            break;
        case inverted_falling_edge      :
            // CCxNP =0;
            CLR_BIT(timx ->TIMx ->CCER, CCER_CC1NP+((local_buffer) * 4));
            // CCxP =1;
            SET_BIT(timx ->TIMx ->CCER, CCER_CC1P+((local_buffer) * 4));
            break;
        case non_inverted_both_edge     :
            // CCxNP =0;
            SET_BIT(timx ->TIMx ->CCER, CCER_CC1NP+((local_buffer ) * 4));
            // CCxP =0;
            SET_BIT(timx ->TIMx ->CCER, CCER_CC1P+(local_buffer ) * 4);
            break;
        }

        if ( ((capture_pwm_config ->pin_number % 2) == 0) && (capture_pwm_config ->pin_number != 0 ) )
        {
               local_buffer --;
        }else{ local_buffer ++; }
    }
    // Select the valid trigger input: write the TS bits  in the (TIMx_SMCR) register : to [101] (TI1FP1 selected) or [110] (TI2FP2 selected).
    (capture_pwm_config ->pin_number == 0)? (__WRITE_BIT_(timx ->TIMx ->SMCR,SMCR_TS_0, 101)) : (__WRITE_BIT_(timx ->TIMx ->SMCR,SMCR_TS_0, 110));

    // Configure the slave mode controller in reset mode : write the SMS bits to 100 in the (TIMx_SMCR) register
     CLR_BIT(timx ->TIMx ->SMCR, SMCR_SMS_0 | SMCR_SMS_1);
    __WRITE_BIT_(timx ->TIMx ->SMCR,SMCR_SMS_0, 100);

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Elapsed_Time : this function is used to return the Channel Capture value. 
/// @param timx                  : the general Timer handler struct.
/// @param ch_Num                : the Channel Number.
/// @return         the Channel Capture value.
u32   MCAL_TIM_Capture_Value(TIM_HANDLER *timx , CHANNEL_NUM ch_Num )
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    u32 capture_v;
    switch (ch_Num)
    {
    case channel_1:
        {
            if (timx ->Count_M != Center_Aligned)
            {
                capture_v = GET_BIT(timx ->TIMx ->CR1 , CR1_DIR)? ((timx ->TIMx ->CCR1) + (timx ->Reload_V)) : (timx ->TIMx ->CCR1);
                return capture_v;
            }
            else
            {
                capture_v =  timx ->TIMx ->CCR1 ;
                return capture_v;
            }
            break;
        }
    case channel_2:
        {   
            if (timx ->Count_M != Center_Aligned)
            {
                capture_v = GET_BIT(timx ->TIMx ->CR1 , CR1_DIR)? ((timx ->TIMx ->CCR2) + (timx ->Reload_V)) : (timx ->TIMx ->CCR2);
                return capture_v;
            }
            else
            {
                capture_v =  timx ->TIMx ->CCR2 ;
                return capture_v;
            }
            break;
        }
    case channel_3:
        {
            if (timx ->Count_M != Center_Aligned)
            {
                capture_v = GET_BIT(timx ->TIMx ->CR1 , CR1_DIR)? ((timx ->TIMx ->CCR3) + (timx ->Reload_V)) : (timx ->TIMx ->CCR3);
                return capture_v;
            }
            else
            {
                capture_v =  timx ->TIMx ->CCR3 ;
                return capture_v;
            }
            break;
        }
    case channel_4:
        {
            if (timx ->Count_M != Center_Aligned)
            {
                capture_v = GET_BIT(timx ->TIMx ->CR1 , CR1_DIR)? ((timx ->TIMx ->CCR4) + (timx ->Reload_V)) : (timx ->TIMx ->CCR4);
                return capture_v;
            }
            else
            {
                capture_v =  timx ->TIMx ->CCR4 ;
                return capture_v;
            }
            break;
        }
    }
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Elapsed_Time : this function is used to return the Channel Capture value. 
/// @param timx                  : the general Timer handler struct.
/// @param timer_input           : the input terminal that the signal is applied on.
/// @param return_values         : the struct that will store the values.
/// @return         the Function state.
TIM_FUN_STATE   MCAL_TIM_PWM_Input_Values(TIM_HANDLER *timx , CH_PWM_INPUT_PIN timer_input , TIM_CAPTURE_PWM_VALUES *return_values )
{   
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    return_values ->duty_cycle_V = timx ->TIMx ->CCR2;
    return_values ->period_V = timx ->TIMx ->CCR1;
    
    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
#endif
/************************************************************************************************************************************************/


/****************************************----------Capture/Compare Output Functions----------****************************************************/
#if			_CC_OUTPUT_FUNCTIONS_	 	== 	stTRUE
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
#endif
/************************************************************************************************************************************************/


/*****************************************----------Timer PWM Output Functions----------*********************************************************/
#if			_PWM_OUTPUT_FUNCTIONS_	 	== 	stTRUE
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
#endif
/************************************************************************************************************************************************/


/********************************************----------Timer Interrupt Functions----------*******************************************************/
#if			_TIMER_INTERRUPT_FUNCTIONS_	 == 	stTRUE
/*----------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------Timers Interrupt CallBack Functions---------------------------------------------------*/
static void (* TIM1_BRK_TIM9_handler) (void) = NULL ;
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
static void (* TIM1_UP_TIM10_handler) (void) = NULL ;
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
static void (* TIM1_TRG_COM_TIM11_handler) (void) = NULL ;
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
static void (* TIM1_CC_handler) (void) = NULL ;
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
static void (* TIM2_handler) (void) = NULL ;
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
static void (* TIM3_handler) (void) = NULL ;
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
static void (* TIM4_handler) (void) = NULL ;
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
static void (* TIM5_handler) (void) = NULL ;
/*----------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Interrupt_CallBack  : this Function is used to set CallBack Functions to there Handler Functions.
/// @param timx                         : the general Timer handler struct.
/// @param ptFunction                   : pointer to the Function that will be executed inside the handler.
/// @param interrupt_type               : the Type of the interrupt that the will execute the function.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Interrupt_CallBack(TIM_HANDLER   *timx , TIM_INTERRUPT_TYPE interrupt_type , void (*ptFunction)(void) )
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }

    // pass the interrupt function to the suitable Handler.
    switch ((u32)timx ->TIMx)
    {
    case (u32)TIM1_R:
        {   
            switch (interrupt_type)
            {
            case    Break_interrupt     :
                TIM1_BRK_TIM9_handler = *ptFunction;
                break;
            
            case    Update_interrupt    :
                TIM1_UP_TIM10_handler = *ptFunction;
                break;

            case    Trigger_interrupt   :
                TIM1_TRG_COM_TIM11_handler = *ptFunction;
                break;

            case    COM_interrupt   :
                TIM1_TRG_COM_TIM11_handler = *ptFunction;
                break;

            default:
                TIM1_CC_handler = *ptFunction;
                break;
            }
        };

    case (u32)TIM2_R:
        {
            TIM2_handler = *ptFunction;
            break;
        }

    case (u32)TIM3_R:
        {
            TIM3_handler = *ptFunction;
            break;
        }

    case (u32)TIM4_R:
        {
            TIM4_handler = *ptFunction;
            break;
        }

    case (u32)TIM5_R:
        {
            TIM5_handler = *ptFunction;
            break;
        }
        
    case (u32)TIM9_R:
        {
            TIM1_BRK_TIM9_handler = *ptFunction;
            break;
        }

    case (u32)TIM10_R:
        {
            TIM1_UP_TIM10_handler = *ptFunction;
            break;
        }

    case (u32)TIM11_R:
        {
            TIM1_TRG_COM_TIM11_handler = *ptFunction;
            break;
        }
    };
    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
/// @brief MCAL_TIM_Interrupt_Enable    : this function is used to Enable the interrupt.
/// @param timx                         : the general Timer handler struct.
/// @param interrupt_type               : the Type of the interrupt that the will be Enabled.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Interrupt_Enable(TIM_HANDLER   *timx , TIM_INTERRUPT_TYPE interrupt_type)
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }
    
    //Enable the interrupt.
    SET_BIT(timx ->TIMx ->DIER , interrupt_type);

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/// @brief MCAL_TIM_Interrupt_Disable   : this function is used to Disable the interrupt.
/// @param timx                         : the general Timer handler struct.
/// @param interrupt_type               : the Type of the interrupt that the will be Disabled.
/// @return     Function State.
TIM_FUN_STATE   MCAL_TIM_Interrupt_Disable(TIM_HANDLER   *timx , TIM_INTERRUPT_TYPE interrupt_type)
{
    // Check parameters.
    if(timx ->TIMx == NULL){ return TIM_ERROR ; }
    
    //Enable the interrupt.
    CLR_BIT(timx ->TIMx ->DIER , interrupt_type);

    return TIM_OK;
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------Timers Interrupt Handlers---------------------------------------------------------------*/
/*
**      TIM1_BRK_TIM9       //TIM1 Break interrupt and TIM9 global interrupt
**      TIM1_UP_TIM10       //TIM1 Update interrupt and TIM10 global interrupt
**      TIM1_TRG_COM_TIM11  //TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
**      TIM1_CC             //TIM1 Capture Compare interrupt
**      TIM2                //TIM2 global interrupt
**      TIM3                //TIM3 global interrupt
**      TIM4                //TIM4 global interrupt 
**      TIM5                //TIM5 global interrupt
*/
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void TIM1_BRK_TIM9_IRQHandler(void)
{
    TIM1_BRK_TIM9_handler();
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void TIM1_UP_TIM10_IRQHandler(void)
{
    TIM1_UP_TIM10_handler();
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
    TIM1_TRG_COM_TIM11_handler();
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void TIM1_CC_IRQHandler(void)
{
    TIM1_CC_handler();
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void TIM2_IRQHandler(void)
{
    TIM2_handler();
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void TIM3_IRQHandler(void)
{
    TIM3_handler();
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void TIM4_IRQHandler(void)
{
    TIM4_handler();
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
void TIM5_IRQHandler(void)
{
    TIM5_handler();
}
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
#endif
/************************************************************************************************************************************************/
