/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "STK_interface.h"
#include "PWM_interface.h"
#include "ADC_interface.h"
#include "SPI_interface.h"
#include "USART_interface.h"

/* HAL */

#include "TFT_interface.h"
#include "TFT_config.h"
#include "VOLT_Interface.h"
#include "ESP_interface.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************
 *    This functions used to initialize the system module
 ************************************************************************************/
void WallBoxChargerInit(void);


u8  *apiKey     = (u8*) "WM07MFYYRM94MDY8"   ;
u8  *ssid       = (u8*) "WE_B9B903"       ;
u8  *pass       = (u8*) "k1816891XY@"      ;
u8  *server     = (u8*) "api.thingspeak.com";
u8 *URL_withGET = (u8*) "GET https://api.thingspeak.com/update?api_key=WM07MFYYRM94MDY8&field1=3";

float  volt;
u8 temp = 6  ;
u8 current=10 ;
s8 buff[16]; /* String to hold the ascii result */

u8 Str[2]={'o' , 'k'} ;

sUART_Config_t UART_Config_1;
sUART_Config_t UART_Config_2;

sADC_Config_t adc_info ;

void main (void)
{

	    WallBoxChargerInit();

        while(1){

			volt = VOLT_f32ReadValue();

        	USART_voidReceiveStringSynch(USART_2 ,(u8*) Str);


        	if(Str[0] == 'o'  &&  Str[1]=='k')
        	{

   			 PWM_voidUpdate(PWM_TIMER1,Channel_1,50);

			 volt = VOLT_f32ReadValue();

			 if(volt >= (float)4.0 && volt <=(float) 6.9)
			 {
				 // close switch that means that car is in charging state
	        	 GPIO_voidsetPinValue (PORTB  , PIN1 , HIGH);

			 }


        	}

        	TFT_voidFillDisplay(TFT_YELLOW );
        	TFT_voidPrintText((s8*)"VOLT:=" , 10 , 20 , 1 , TFT_BLUE , TFT_YELLOW );
        	itoa((int)volt, buff ,10); /* 10 for decimal */
        	TFT_voidPrintText(buff ,        100 , 20 , 1 , TFT_RED , TFT_YELLOW );
       	    ESP8266_VoidSendHttpReq( (u8*)apiKey , (u8*)buff ,(u8*) "73" ,(u8*) "field3" );

        	 if(volt >= (float)4.0 && volt <=(float) 6.9)
        	 {
     			TFT_voidPrintText((s8*)"State = Charging" , 10 , 40 , 1 , TFT_BLUE , TFT_YELLOW );
    			ESP8266_VoidSendHttpReq( (u8*)apiKey , (u8*)"1" ,(u8*) "73" ,(u8*) "field2" );

        	 }
        	 else
        	 {
     			TFT_voidPrintText((s8*)"State =Not_Charging" , 10 , 40 , 1 , TFT_BLUE , TFT_YELLOW );
    			ESP8266_VoidSendHttpReq( (u8*)apiKey , (u8*)"0" ,(u8*) "73" ,(u8*) "field2" );

        	 }


        	 TFT_voidPrintText((s8*)"Current:=" , 10 , 80 , 1 , TFT_BLUE , TFT_YELLOW );
        	 itoa(current,buff,10); /* 10 for decimal */
        	 TFT_voidPrintText(buff       , 100 , 80 , 1 , TFT_RED , TFT_YELLOW );
 			 ESP8266_VoidSendHttpReq( (u8*)apiKey , (u8*)buff ,(u8*) "73" ,(u8*) "field4" );
        	 TFT_voidPrintText((s8*)"Temp="    , 10 , 120 , 1 , TFT_BLUE , TFT_YELLOW );
        	 itoa(temp,buff,10); /* 10 for decimal */
        	 TFT_voidPrintText(buff      , 100 , 120 , 1 , TFT_RED , TFT_YELLOW );
 			 ESP8266_VoidSendHttpReq( (u8*)apiKey , (u8*)buff ,(u8*) "73" ,(u8*) "field4" );


        }
    	}


void WallBoxChargerInit(void)
{

    RCC_voidInitSysClock();

    UART_Config_1.USART_Num = USART_1;
    UART_Config_1.UART_Status = USART_Enable;
    UART_Config_1.BaudRate = BAUD_115200;
    UART_Config_1.Parity = No_Parity;
    UART_Config_1.DataDirection = Transmit_Recieve;

    /*Usart2 BUS configuration parameters */

    UART_Config_2.USART_Num = USART_2;
    UART_Config_2.UART_Status = USART_Enable;
    UART_Config_2.BaudRate = BAUD_9600;
    UART_Config_2.Parity = No_Parity;
    UART_Config_2.DataDirection = Transmit_Recieve;

	 /* master - idle high - write first - msb - 8bit format - sw m slave ,full duplex ,
				f/2 / disable ISR*/
	SPI_config_t SPI1_config = { 1 , 1 , 1 , 0 , 0 , 1, 0 ,0 ,0 };

   	/*ADC configuration parameters */
    adc_info.ADC_Num =ADC1 ;
    adc_info.ADC_Prescaller = 0 ;
    adc_info.V_Refrance  = V_Internal;

    /*****************************************************
  		    * FRQ(pwm)=FRQclk /(prescaler+1) * (ARR+1)
  		    * 1000 HZ   = 8000000 / (200)* (40 )
    *******************************************************/

    sPWM_Confg_t PWM_Confg;
  	PWM_Confg.AutoReloadReg=39;
  	PWM_Confg.Prescaler=199;
  	PWM_Confg.TimerSelect=PWM_TIMER1;
    PWM_Confg.CCR1_Status=CCR_ENABLE;
  	PWM_Confg.CCR2_Status=CCR_ENABLE;
  	PWM_Confg.CCR3_Status=CCR_ENABLE;
  	PWM_Confg.CCR4_Status=CCR_ENABLE;

/* Enable the clock for all Perepherals */
	RCC_voidEnableClock(RCC_APB2 , IOPA_PERIPHERAL); // enable clock for portA
	RCC_voidEnableClock(RCC_APB2 , IOPB_PERIPHERAL); //enable clock for portB
	RCC_voidEnableClock(RCC_APB2 , ADC1_PERIPHERAL); // enable clock for ADC
	RCC_voidEnableClock(RCC_APB2,  USART1_PERIPHERAL); /* USART1 */
	RCC_voidEnableClock(RCC_APB1,  USART2_PERIPHERAL); /* USART2 */
	RCC_voidEnableClock(RCC_APB2 , SPI1_PERIPHERAL); // SPI CLOCK



	/* Configure pins for ADC */
	GPIO_voidSetPinMode(PORTA , PIN0 , GPIO_INPUT_ANALOG ); //ADC CHANNEL0

	/*Configure switch pin */
	GPIO_voidSetPinMode(PORTB , PIN1 , GPIO_OUTPUT_2MHZ_PP ); //SWITCH PIN B1

	/*Configure PWM pin */
	GPIO_voidSetPinMode(PORTA , PIN8 , GPIO_OUTPUT_2MHZ_AFPP); //PWM channel 1

	/*USART1 pins  configuration*/
	GPIO_voidSetPinMode(PORTA , PIN2 , GPIO_OUTPUT_2MHZ_AFPP); /* TX PP */
	GPIO_voidSetPinMode(PORTA , PIN3 , GPIO_INPUT_FLOATING);  /* Rx Input Floating */

	/*USART2 pins  configuration*/
	GPIO_voidSetPinMode(PORTA , PIN9 , GPIO_OUTPUT_2MHZ_AFPP); /* TX PP */
	GPIO_voidSetPinMode(PORTA , PIN10 , GPIO_INPUT_FLOATING);  /* Rx Input Floating */

	/* Configure pins for SPI */

	GPIO_voidSetPinMode(PORTA , PIN7 , GPIO_OUTPUT_10MHZ_AFPP); //MOSI
	GPIO_voidSetPinMode(PORTA , PIN6 , GPIO_INPUT_FLOATING); //MISO
	GPIO_voidSetPinMode(PORTA , PIN5 , GPIO_OUTPUT_10MHZ_AFPP); //SCK


    /*Init ADC */
	ADC_voidInit(&adc_info);

    /*Init USART */
	USART_voidInit(&UART_Config_1);
	USART_voidInit(&UART_Config_2);


	/*init SPI */
	SPI_u8ConfigureCh(SPI1 , &SPI1_config );

	/* Initialize STK */
	MSTK_voidInit();

	/*initialize PWM */
	PWM_voidInit(&PWM_Confg);


	ESP_u8Init();
	ESP_u8ConnectAP(ssid , pass);
	MSTK_voidSetBusyWait( 1000 ); // wait 1 ms
	ESP_u8ConnectServer ((u8*) "api.thingspeak.com"   );

	/* Initialize TFT */
	TFT_voidInit();
	TFT_voidDisplayImage(image);
	// delay 2 minutes
	for(int i=0 ; i<30 ; i++){ MSTK_voidSetBusyWait(1000000);  }

}



