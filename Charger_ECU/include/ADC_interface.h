/**
 * ***************************************************************
 *  @file      ADC_interface.h
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)
 *  @version   v1.0
 *  @date      05/08/2021
 *  @brief     [Write a brief of this file ]
 *
 *
 *  @note      This program is distributed in the hope  that it
 * 	           will be useful,but WITHOUT ANY WARRANTY; without
 *	           even the implied warranty of  MERCHANTABILITY or
 *	           FITNESS FOR A PARTICULAR PURPOSE.
 *
 * ***************************************************************
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef enum {
	V_Internal,
	V_External
}eV_Ref_t;
typedef enum {
	ADC1,
	ADC2
}eADC_Num_t;
typedef struct {
	eADC_Num_t ADC_Num;
	u16 ADC_Prescaller;/* Clock must not exceed 14 MHz, APB2 */
	eV_Ref_t V_Refrance; /*VREFINT are only available on the master ADC1 peripheral*/
}sADC_Config_t;
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
/*Steps to use ADC moudule
 * 1- Create a configuration struct
 * 2- Init the GPIO that has the channel you want to use (currently ADC1 is tested)
 * 3- Config the pin as input analog
 * 4- Call ADC_voidInit() for init the module and clock
 * 5- Call ADC_u16Read() to get the result from 0 to 4096
 * EX:
	 sADC_Config_t ADC_Config;
	 ADC_Config.ADC_Num=ADC1;

	 GPIO_voidInit(GPIOA);
	 GPIO_voidSetPinDirection(AN0,INPUT_ANLOG);
	  ADC_voidInit(&ADC_Config);
	 u16 x= ADC_u16Read(ADC1,9);
 */

void ADC_voidInit(sADC_Config_t *ADC_Config);
u16  ADC_u16Read(eADC_Num_t ADC_Num,u8 Channel);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/
