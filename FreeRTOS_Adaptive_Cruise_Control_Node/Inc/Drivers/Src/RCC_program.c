/****************************
 *  RCC_PROGRAM.h           *
 *  Created on: FEB 5, 2023 *
 *  Author: MANAR EMAD      *
 ****************************/

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"


#include "../Inc/RCC_INTERFACE.h"
#include "../Inc/RCC_PRIVATE.h"
#include "../Inc/RCC_CONFIG.h"

void MRCC_voidSystemClkInit(void)
{
#if RCC_CLK_SECURITY_SYSTEM == ENABLE
    SET_BIT(RCC->CR, CSSON);

# elif RCC_CLK_SECURITY_SYSTEM == DISABLE
    CLR_BIT(RCC->CR, CSSON);

#endif

#if RCC_HSE_CLK_BYBASS == NO
    CLR_BIT(RCC->CR, HSEBYPASS);

# elif RCC_HSE_CLK_BYBASS == YES
    SET_BIT(RCC->CR, HSEBYPASS);

#endif

#if CLK_SOURCE == HSI

	// 1- Turn on HSI Clock
	SET_BIT(RCC->CR, HSION);
	// 2- Check HSI is Ready
	while (GET_BIT(RCC->CR, HSIRDY) == 0);
	// 3- Switch to HSI
	CLR_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);
	// 4- Turn off PLL
	CLR_BIT(RCC->CR, PLLON);
	// 5- Turn off HSE
	CLR_BIT(RCC->CR, HSEON);
	
#elif CLK_SOURCE == HSE

	// 1- Turn on HSE Clock
	SET_BIT(RCC->CR, HSEON);
	// 2- Check HSE is Ready
	while (GET_BIT(RCC->CR, HSERDY) == 0);
	// 3- Switch to HSE
	SET_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);
	// 4- Turn off PLL
	CLR_BIT(RCC->CR, PLLON);
	// 5- Turn off HSI
	CLR_BIT(RCC->CR, HSION);

#elif CLK_SOURCE == PLL

#if PLL_SOURCE == HSI
	// 1- Turn on HSI Clock
	SET_BIT(RCC->CR, HSION);
	// 2- Check HSI is Ready
	while (GET_BIT(RCC->CR, HSIRDY) == 0);
	// 3- Set PLL Source to HSI
	CLR_BIT(RCC->PLLCFGR, PLLSRC);
	// 4- Set PLLM Values
	RCC->PLLCFGR &= ~PLLM_MASK;
	RCC->PLLCFGR |= PLLM_VALUE;
	// 5- Set PLLN Values
	RCC->PLLCFGR &= ~PLLN_MASK;
	RCC->PLLCFGR |= (PLLN_VALUE << 6);
	// 6- Set PLLP Values
	RCC->PLLCFGR &= ~PLLP_MASK;
	RCC->PLLCFGR |= (PLLP_VALUE << 16);
	// 7- Set AHB Prescaler
	RCC->CFGR &= ~HPRE;
	RCC->CFGR |= AHB_PRESCALER << 4;

	// 8- Set APB1 Prescaler
	RCC->CFGR &= ~ PPRE1;
	RCC->CFGR |= APB1_PRESCALER << 10;

	// 9- Set APB2 Prescaler
	RCC->CFGR &= ~PPRE2;
	RCC->CFGR |= APB2_PRESCALER << 13;

	// 10- Turn on PLL Clock
	SET_BIT(RCC->CR, PLLON);

	// 11- Check HSI is Ready
	while (GET_BIT(RCC->CR, PLLRDY) == 0);

	// 12- Switch to PLL
	CLR_BIT(RCC->CFGR, SW0);
	SET_BIT(RCC->CFGR, SW1);

#elif PLL_SOURCE == HSE
	// 1- Turn on HSE Clock
	SET_BIT(RCC->CR, HSEON);
	// 2- Check HSE is Ready
	while (GET_BIT(RCC->CR, HSERDY) == 0);
	// 3- Set PLL Source to HSE
	SET_BIT(RCC->PLLCFGR, PLLSRC);
	// 4- Set PLLM Values
	RCC->PLLCFGR &= ~PLLM_MASK;
	RCC->PLLCFGR |= PLLM_VALUE;
	// 5- Set PLLN Values
	RCC->PLLCFGR &= ~PLLN_MASK;
	RCC->PLLCFGR |= (PLLN_VALUE << 6);
	// 6- Set PLLP Values
	RCC->PLLCFGR &= ~PLLP_MASK;
	RCC->PLLCFGR |= (PLLP_VALUE << 16);
	// 7- Set AHB Prescaler
	RCC->CFGR &= ~HPRE;
	RCC->CFGR |= AHB_PRESCALER << 4;

	// 8- Set APB1 Prescaler
	RCC->CFGR &= ~ PPRE1;
	RCC->CFGR |= APB1_PRESCALER << 10;

	// 9- Set APB2 Prescaler
	RCC->CFGR &= ~PPRE2;
	RCC->CFGR |= APB2_PRESCALER << 13;

	// 10- Turn on PLL Clock
	SET_BIT(RCC->CR, PLLON);

	// 11- Check HSI is Ready
	while (GET_BIT(RCC->CR, PLLRDY) == 0);

	// 12- Switch to PLL
	CLR_BIT(RCC->CFGR, SW0);
	SET_BIT(RCC->CFGR, SW1);
#else
#error Wrong Clock Configuration
#endif
#else
#error Wrong Clock Configuration
#endif	
}
void MRCC_voidPeripheralEnable(u8 copy_u8Bus, u8 copy_u8Peripheral)
{
	/* CHECK RANGE */
    if(copy_u8Peripheral < PeripheralRange && copy_u8Bus <= APB2)
    {
        switch(copy_u8Bus)
        {
        case AHB1 :
            SET_BIT(RCC->AHB1ENR, copy_u8Peripheral);
            break;
        case AHB2 :
            SET_BIT(RCC->AHB2ENR, copy_u8Peripheral);
            break;
        case APB1 :
            SET_BIT(RCC->APB1ENR, copy_u8Peripheral);
            break;
        case APB2 :
            SET_BIT(RCC->APB2ENR, copy_u8Peripheral);
            break;
        }
    }
    else
    {
        //out of range
    }
}

void MRCC_voidPeripheralDisable(u8 copy_u8Bus, u8 copy_u8Peripheral)
{
	/* CHECK RANGE */
    if(copy_u8Peripheral<PeripheralRange && copy_u8Bus <= APB2 ) 
	{
		switch(copy_u8Bus)
		{
		case AHB1:
			CLR_BIT(RCC->AHB1ENR, copy_u8Peripheral);
			break;
		case AHB2:
			CLR_BIT(RCC->AHB2ENR, copy_u8Peripheral);
			break;
		case APB1:
			CLR_BIT(RCC->APB1ENR, copy_u8Peripheral);
			break;
		case APB2:
			CLR_BIT(RCC->APB2ENR, copy_u8Peripheral);
			break;
		}
	}
	else
    {
        //out of range
    }
}

