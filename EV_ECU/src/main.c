/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "STK_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*==============================================================================================*/


sUART_Config_t UART_Config;

void main(void)
{

	    UART_Config.USART_Num = USART_2;
	    UART_Config.UART_Status = USART_Enable;
	    UART_Config.BaudRate = BAUD_9600;
	    UART_Config.Parity = No_Parity;
	    UART_Config.DataDirection = Transmit_Recieve;

	    RCC_voidInitSysClock();
		RCC_voidEnableClock(RCC_APB1,USART2_PERIPHERAL); /* USART2 */
		RCC_voidEnableClock(RCC_APB2 , IOPA_PERIPHERAL);  /* PortA  */
		RCC_voidEnableClock(RCC_APB2 , IOPB_PERIPHERAL);  /* PortB  */


		GPIO_voidSetPinMode(PORTA , PIN2 , GPIO_OUTPUT_2MHZ_AFPP); /* TX PP */
		GPIO_voidSetPinMode(PORTA , PIN3 , GPIO_INPUT_FLOATING);/* RC Input Floating */
		GPIO_voidSetPinMode(PORTB , PIN0 , GPIO_OUTPUT_2MHZ_PP); //SWITCH PIN B0


		USART_voidInit(&UART_Config);

		MSTK_voidInit();



		while(1){
			 /*
			              * close switch
			              * send signal to charger
			              * */
			        	// open switch

			     	    GPIO_voidsetPinValue (PORTB  , PIN0 , HIGH);
			     	    USART_voidSendStringSynch(USART_2, "ok");
		}

}
