/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/
 
#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

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
typedef enum 
{
	PWM_TIMER1,
	PWM_TIMER8
}ePWM_TimerSelect_t;

typedef enum 
{
	Channel_1,
	Channel_2,
	Channel_3,
	Channel_4
}eCCR_Channel_t;

typedef enum 
{
	CCR_DISABLE,
	CCR_ENABLE
}eCCR_Status_t;

typedef struct
{
	ePWM_TimerSelect_t TimerSelect ;
	u16 Prescaler;	/* fCK_PSC / (PSC[15:0] + 1)*/
	u16 AutoReloadReg;
	eCCR_Status_t CCR1_Status;
	eCCR_Status_t CCR2_Status;
	eCCR_Status_t CCR3_Status;
	eCCR_Status_t CCR4_Status;
}sPWM_Confg_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
/*Steps to Generate PWM
 * 1- Create a configuration struct
 * 2- Calculate The frequency by using the prescaler and autoreaload register
 * 3- Choose which timer will generate the PWM
 * 4- Choose the number of channels that will work
 * 5- Call PWM_voidInit(); to init the timer
 * 6- Init The GPIO that has the timer channel pins (Enable clock)
 * 7- Choose the pin mode as OUTPUT AF PP
 * 8- Call PWM_voidUpdate() for change the duty cycle of the pulse from 0% to 100%
 * EX:
     GPIO_voidInit(GPIOA);
     GPIO_voidSetPinDirection(PINA8,OUTPUT_SPEED_2MHZ_AFPP); CH 1 TMr1
  	 sPWM_Confg_t PWM_Confg;
	 PWM_Confg.AutoReloadReg=65500;
	 PWM_Confg.Prescaler=1;
	 PWM_Confg.TimerSelect=PWM_TIMER1;
	 PWM_Confg.CCR1_Status=CCR_ENABLE;
	 PWM_Confg.CCR2_Status=CCR_ENABLE;
	 PWM_Confg.CCR3_Status=CCR_ENABLE;
	 PWM_Confg.CCR4_Status=CCR_ENABLE;
	 PWM_voidInit(&PWM_Confg);
	 PWM_voidUpdate(PWM_TIMER1,Channel_1,x);

 */

void PWM_voidInit(sPWM_Confg_t *PWM_Config);
void PWM_voidUpdate(ePWM_TimerSelect_t Timer ,eCCR_Channel_t channel, u8 duty );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/
