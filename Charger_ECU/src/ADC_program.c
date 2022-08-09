/**
 * *************************************************************************
 *  @file      ADC_program.c
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)
 *  @version   v1.0
 *  @date      05/08/2021
 *  @brief     This file have the implementation of
 *
 *
 *  @note      This program is distributed in the hope  that it
 * 	           will be useful,but WITHOUT ANY WARRANTY; without
 *	           even the implied warranty of  MERCHANTABILITY or
 *	           FITNESS FOR A PARTICULAR PURPOSE.
 *
 * *************************************************************************
 */

/******************************************************************************
* Includes
*******************************************************************************/
// Include libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// Include files
#include "RCC_interface.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"

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
static void ADC_voidOn(eADC_Num_t ADC_Num);
static void ADC_voidOff(eADC_Num_t ADC_Num);
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
void ADC_voidInit(sADC_Config_t *ADC_Config){
	
	/* Enable Clock  */
	//RCC_voidEnableClock(APB2,(9+ (ADC_Config->ADC_Num)));
	/* ADC On  */
	SET_BIT(ADCx[ADC_Config->ADC_Num]->CR2,0);
	/* Enable the single conversation mode  */
	CLEAR_BIT (ADCx[ADC_Config->ADC_Num]->CR1,1) ;
	/* Enable Scan mode  */
		CLEAR_BIT (ADCx[ADC_Config->ADC_Num]->CR1,8) ;
	/* Discontinuous mode on regular channels Disabled*/
	CLEAR_BIT(ADCx[ADC_Config->ADC_Num]->CR1,11);
	/* Data alignment */
	CLEAR_BIT(ADCx[ADC_Config->ADC_Num]->CR2,11);
	/* Single conversion mode */
	CLEAR_BIT(ADCx[ADC_Config->ADC_Num]->CR2,1);
}

u16 ADC_u16Read(eADC_Num_t ADC_Num,u8 Channel)
{
	ADC_voidOn(ADC_Num);
	ADC_voidOn(ADC_Num);
	ADCx[ADC_Num]->SQR3 &=0XFFFFFFF0; /* Clear channel */
	ADCx[ADC_Num]->SQR3 |= Channel;
	/* Start conversion of regular channels */
	SET_BIT(ADCx[ADC_Num]->CR2,22);
	/* Wait till end of operation flag is set */
	while (GIT_BIT(ADCx[ADC_Num]->SR,1)==0);
	u16 Result =(u16)ADCx[ADC_Num]->DR;
	CLEAR_BIT(ADCx[ADC_Num]->SR,1);
	CLEAR_BIT(ADCx[ADC_Num]->SR,4);
	ADC_voidOff(ADC_Num);
	return Result;
}
static void ADC_voidOn(eADC_Num_t ADC_Num){
	/* Conversion starts when ADON bit is set for a second time by
	software after ADCx[ADC_Config->ADC_Num] power-up time (tSTAB) */
	SET_BIT(ADCx[ADC_Num]->CR2,0);
}

static void ADC_voidOff(eADC_Num_t ADC_Num){
	CLEAR_BIT(ADCx[ADC_Num]->CR2,0);
}

/*************** END OF FUNCTIONS *********************************************/
