/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/
 
/******************************************************************************
* Includes
*******************************************************************************/
// Include libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// Include files 
#include "RCC_interface.h"
#include "PWM_interface.h"
#include "PWM_config.h"
#include "PWM_private.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Static Function Prototypes
*******************************************************************************/
static u16 map(u8 x, u8 in_min, u8 in_max, u16 out_min, u16 out_max);

/******************************************************************************
* Function Definitions
*******************************************************************************/

/**
 * @fn               
 * @brief   		 
 * @param               		 
 * @return 			 
 * PRE-CONDITION     
 * POST-CONDITION     	  
 */

void PWM_voidInit(sPWM_Confg_t *PWM_Config)
{
	/* Enable clock */
	if (PWM_Config->TimerSelect ==PWM_TIMER1 )
		RCC_voidEnableClock(RCC_APB2 , TIM1_PERIPHERAL);
	else 
		RCC_voidEnableClock(RCC_APB2 , TIM8_PERIPHERAL );
	//TIMx[PWM_Config->TimerSelect]->
	/*Auto-reload preload enable*/
	SET_BIT(TIMx[PWM_Config->TimerSelect]->CR1,7);
	/* Set counter direction as up-counter */
	CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CR1,4);
	  /* Select master mode Compare */
	  /* Compare - OC1REF signal is used as trigger output (TRGO)  */
	SET_BIT(TIMx[PWM_Config->TimerSelect]->CR2,6);
	SET_BIT(TIMx[PWM_Config->TimerSelect]->SMCR ,7);
	
  /* Set timer Prescaler, bus clock = 90 MHz, fCK_PSC / (PSC[15:0] + 1)
   * CK_CNT = F / (PSC+1) -> FREQ Hz -> time base = 1/FREQ */
  TIMx[PWM_Config->TimerSelect]->PSC = PWM_Config->Prescaler;
  /* Set timer auto reload value to maximum */
  TIMx[PWM_Config->TimerSelect]->ARR = PWM_Config->AutoReloadReg;;
	  /* Set duty cycle */
  TIMx[PWM_Config->TimerSelect]->CCR1 = 0x00;
  
	for (u8 i=0;i<4;i++){
		if (i <2){
		/* Set Capture/Compare  as output */
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCMR1,(0+(i*8)));
		/* Set Capture/Compare  as output */
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCMR1,(1+(i*8)));
		/* Output Compare  preload enable */
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCMR1,(3+(i*8)));
		
		/* Select Output Compare 1 PWM mode 1
		* TIMx_CNT < TIMx_CCR1 -> Output Active
		* TIMx_CNT >= TIMx_CCR1 -> Output Inactive
		* 110: PWM mode 1 - In upcounting,
		* channel 1 is active as long as TIMx_CNT<TIMx_CCR1
		* else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as */

		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCMR1,(4+(i*8)));
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCMR1,(5+(i*8)));
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCMR1,(6+(i*8)));
		}else 
		{
		/* Set Capture/Compare  as output */
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCMR2,(0+((i-2)*8)));
		/* Set Capture/Compare  as output */
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCMR2,(1+((i-2)*8)));
		/* Output Compare  preload enable */
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCMR2,(3+((i-2)*8)));
		
		/* Select Output Compare  PWM mode 1
		* TIMx_CNT < TIMx_CCR1 -> Output Active
		* TIMx_CNT >= TIMx_CCR1 -> Output Inactive */
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCMR2,(4+((i-2)*8)));
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCMR2,(5+((i-2)*8)));
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCMR2,(6+((i-2)*8)));
		}
    }
		

	/* Select Capture/Compare 1 output polarity active high */
	CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCER,1);
	
	if (PWM_Config->CCR1_Status == CCR_ENABLE )
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCER,0); /* Enable Capture/Compare output */
    else 
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCER,0);
    
	if (PWM_Config->CCR2_Status == CCR_ENABLE )
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCER,4); /* Enable Capture/Compare output */
    else 
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCER,4);
  
  	if (PWM_Config->CCR3_Status == CCR_ENABLE )
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCER,8); /* Enable Capture/Compare output */
    else 
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCER,8);
  
  	if (PWM_Config->CCR4_Status == CCR_ENABLE )
		SET_BIT(TIMx[PWM_Config->TimerSelect]->CCER,12); /* Enable Capture/Compare output */
    else 
		CLEAR_BIT(TIMx[PWM_Config->TimerSelect]->CCER,12);
  
  
  /* Initialize all the registers */
  SET_BIT(TIMx[PWM_Config->TimerSelect]->EGR ,0);
  /* Enable timer main output */
  SET_BIT(TIMx[PWM_Config->TimerSelect]->BDTR ,15);
  /* Enable TIMx */
  SET_BIT(TIMx[PWM_Config->TimerSelect]->CR1,0); 
}

void PWM_voidUpdate(ePWM_TimerSelect_t Timer ,eCCR_Channel_t channel, u8 duty ){
	switch (channel){
		case Channel_1:
		TIMx[Timer]->CCR1=map(duty, 0, 100, 0, TIMx[Timer]->ARR);
		break ;
		case Channel_2:
		TIMx[Timer]->CCR2=map(duty, 0, 100, 0, TIMx[Timer]->ARR);
		break ;
		case Channel_3:
		TIMx[Timer]->CCR3=map(duty, 0, 100, 0, TIMx[Timer]->ARR);
		break ;
		case Channel_4:
		TIMx[Timer]->CCR4=map(duty, 0, 100, 0, TIMx[Timer]->ARR);
		break ;
	}
	
}

static u16 map(u8 x, u8 in_min, u8 in_max, u16 out_min, u16 out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
/*************** END OF FUNCTIONS *********************************************/
