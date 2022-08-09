/*********************************************************/
/* Author      :  GP Team                                */
/* Date        : 28 JAN 2021                             */
/* Version     : V01                                     */
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_Interface.h"
#include "VOLT_Interface.h"
#include "VOLT_Config.h"



float VOLT_f32ReadValue (void)
{
	u16 Local_u16ReadValue = 0 ;
	float Local_f32ReadVolt =0.0;
	//Read ADC Value 
	Local_u16ReadValue = (u16 )ADC_u16Read(ADC1,0);
	//Calculate the voltage value from the ADC value
	Local_f32ReadVolt = ((float)(Local_u16ReadValue))*(3.3/4096)*((100000+100000)/100000) ;
	return Local_f32ReadVolt;
}
