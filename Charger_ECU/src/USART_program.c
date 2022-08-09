
/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/



/******************************************************************************
                              Includes
*******************************************************************************/
// Include libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// Include files
#include "RCC_interface.h"
#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"

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

static void (*UART_Fptr[3]) (void)= {0};

/******************************************************************************
* Static Function Prototypes
*******************************************************************************/


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
void USART_voidInit(sUART_Config_t *UART_Config) {

	/* Page 798  in register discripion */
	UARTx[UART_Config->USART_Num]->BRR = UART_Config->BaudRate;

	/* Data Direction setup */
	if (UART_Config->DataDirection == Transmition)
		SET_BIT(UARTx[UART_Config->USART_Num]->CR1, 3); /* TX Enable */
	else if (UART_Config->DataDirection == Recieving)
		SET_BIT(UARTx[UART_Config->USART_Num]->CR1, 2); /* RX Enable */
	else {
		SET_BIT(UARTx[UART_Config->USART_Num]->CR1, 3); /* TX Enable */
		SET_BIT(UARTx[UART_Config->USART_Num]->CR1, 2); /* RX Enable */
	}


	/* Parity Configuration */
	if (UART_Config->Parity == No_Parity){
		CLEAR_BIT(UARTx[UART_Config->USART_Num] -> CR1 , 10);
        CLEAR_BIT(UARTx[UART_Config->USART_Num] -> CR1 , 9);

	}
    else if (UART_Config->Parity == Even_Parity){
        SET_BIT(UARTx[UART_Config->USART_Num] -> CR1 , 10);
        CLEAR_BIT(UARTx[UART_Config->USART_Num] -> CR1 , 9);

    }else if (UART_Config->Parity == Odd_Parity)
    {   SET_BIT(UARTx[UART_Config->USART_Num] -> CR1 , 10);
        SET_BIT(UARTx[UART_Config->USART_Num] -> CR1 , 9);
    }

	UARTx[UART_Config->USART_Num]->SR = 0; /* Clear Status Reg*/

	if (UART_Config->UART_Status == USART_Enable){
	   SET_BIT(UARTx[UART_Config->USART_Num]->CR1, 13); /* USART Enable */

	}else
		CLEAR_BIT(UARTx[UART_Config->USART_Num]->CR1, 13); /* USART Enable */


}

void USART_voidSendCharSynch(eUSART_Num_t USART_Number, u8 copy_u8Char) {

	UARTx[USART_Number]->DR = copy_u8Char; /* Add Data to the DATA reg */
	while ((GIT_BIT( UARTx[USART_Number] -> SR, 6) == 0)); /* Wait for Transmtion complite */


}

void USART_voidSendStringSynch(eUSART_Num_t USART_Number, u8 * Pu8Char) {

	for (u8 i = 0; Pu8Char[i] != 0; i++) {
		USART_voidSendCharSynch( USART_Number, Pu8Char[i]);
	}

}

u8 USART_u8ReceiveCharSynch(eUSART_Num_t USART_Number) {


	while (GIT_BIT( UARTx[USART_Number]-> SR , 5) == 0);
	return UARTx[USART_Number]->DR;	/* Casting to u8 */

}

void USART_voidReceiveStringSynch(eUSART_Num_t USART_Number, u8 * Pu8String) {


	u8 i = 0;
	Pu8String[i] = USART_u8ReceiveCharSynch(USART_Number);
	while (Pu8String[i] != '\n') {
		i++;
		Pu8String[i] = USART_u8ReceiveCharSynch(USART_Number);
	}
	Pu8String[i] = '\0';
}

/**********************/
void USART_voidNewLine(eUSART_Num_t USART_Number) {

	USART_voidSendCharSynch( USART_Number , 10);		/* new line  */
	USART_voidSendCharSynch( USART_Number , 13);		/* cr */
}

void USART_voidSendStringSynchSum(eUSART_Num_t USART_Number,u8 *text) {

	u16 sum = 0;
	for (u8 counter = 0; text[counter] != '\0'; counter++) {
		sum += text[counter];
		USART_voidSendCharSynch( USART_Number , text[counter]);
	}
	USART_voidSendCharSynch( USART_Number , 0xff); /* separate between text and sum  */
	/*  Send The Sum */
	USART_voidSendCharSynch( USART_Number , (u8) sum);
	USART_voidSendCharSynch( USART_Number , (u8) (sum << 8));

}

u8 USART_u8ReceiveStringSynchSum(eUSART_Num_t USART_Number , u8 *text) {

	u16 sum_received, sum = 0;
	u8 Frist_Part_Sum, Secound_Part_Sum , counter =0 ;
	text[counter] = USART_u8ReceiveCharSynch( USART_Number );
	for ( ; text[counter] !=0xff; counter++) {
		text[counter] = USART_u8ReceiveCharSynch( USART_Number );
		sum += text[counter]; /*Sum of received data*/
	}
	Frist_Part_Sum = USART_u8ReceiveCharSynch( USART_Number);	/* Least byte from the resever */
	Secound_Part_Sum = USART_u8ReceiveCharSynch( USART_Number);
	sum_received = (u8)Secound_Part_Sum<<8 | (u8)Frist_Part_Sum;

	if (sum_received == sum) {
		return 1; /* return 1 if the data was valid */
	} else {
		return 0;
	}

}

void USART_voidSendIntSynch(eUSART_Num_t USART_Number,u16 number) {

    s8 i = 0;u8 arr[10];

    while (number != 0) {
        arr[i++] = (number % 10) + '0';
        number = number / 10;
    }
    i--;
    while (i >= 0) {
        USART_voidSendCharSynch(USART_Number,arr[i]);i--;
    }

}

u8 USART_u8Receive(eUSART_Num_t USART_Number,u8* Copy_u8Data)
{
	u8 Local_u8Result = 1;

	if ( (GIT_BIT((UARTx[USART_Number]->SR), 5)) == 1 )
	{
		*Copy_u8Data = UARTx[USART_Number]->DR;
	}
	else
	{
		Local_u8Result = 0;
	}

	return (Local_u8Result);
}
/* ******* DMA enable or disable ******* */
void USART_voidDMAEnableTransming(eUSART_Num_t USART_Number){
	SET_BIT(UARTx[USART_Number] -> CR3 , 7);
}
void USART_voidDMADisableTransming(eUSART_Num_t USART_Number){
	CLEAR_BIT(UARTx[USART_Number] -> CR3 , 7);
}
void USART_voidDMAEnableReceiving(eUSART_Num_t USART_Number){
	//SET_BIT(UARTx[USART_Number] -> CR1 , 4);
	SET_BIT(UARTx[USART_Number] -> CR3 , 6);
}
void USART_voidDMADisableReceiving(eUSART_Num_t USART_Number){
	CLEAR_BIT(UARTx[USART_Number] -> CR3 , 6);
}
/* ********TX , RX Interrupts enable or disable ******** */
/**
 * @brief   Enable Receiving interrupt
 * @param   void
 * @return  void
 */
void USART_voidRXInterruptEnable(eUSART_Num_t USART_Number) {
	SET_BIT(UARTx[USART_Number] -> CR1 , 5);
}

void USART_voidRXIdleInterruptEnable(eUSART_Num_t USART_Number) {
	SET_BIT(UARTx[USART_Number] -> CR1 , 4);
}
/**
 * @brief   Disable Receiving interrupt
 * @param   void
 * @return  void
 */
void USART_voidRXInterruptDisable(eUSART_Num_t USART_Number) {
	CLEAR_BIT(UARTx[USART_Number] -> CR1 , 5);
}
void USART_voidRXIdleInterruptDisable(eUSART_Num_t USART_Number) {
	CLEAR_BIT(UARTx[USART_Number] -> CR1 , 4);
}
/**
 * @brief   Enable Transmiting interrupt
 * @param   void
 * @return  void
 */
void USART_voidTXInterruptEnable(eUSART_Num_t USART_Number) {
	SET_BIT(UARTx[USART_Number] -> CR1 , 7);
}
/**
 * @brief   Disable Transmiting interrupt
 * @param   void
 * @return  void
 */
void USART_voidTXInterruptDisable(eUSART_Num_t USART_Number) {
	CLEAR_BIT(UARTx[USART_Number] -> CR1 , 7);
}

/************** Set Call Back Functions ***************/
/**
 * @brief   Send the function that you want excute to ISR when receive
 * @param   LocalFptr     Pointer to the function (its name)
 * @return  void
 */
void USART_voidSetCallBack(eUSART_Num_t USART_Number,void (*LocalFptr)(void)) {

	UART_Fptr[USART_Number] = LocalFptr;
}


void USART1_IRQHandler(void){
	if (UART_Fptr[0] != 0) {
		UART_Fptr[0]();
	}
	CLEAR_BIT(UARTx[0] -> SR , 5);
	CLEAR_BIT(UARTx[0] -> SR , 6);
	CLEAR_BIT(UARTx[0] -> SR , 7);
	if(GIT_BIT(UARTx[0] -> SR , 4)){
		//Check the idle flag , clear it by clear the flag then read the DR
		CLEAR_BIT(UARTx[0] -> SR , 4);
	(void)UARTx[0] ->DR;
	}

}

void USART2_IRQHandler(void){

	if (UART_Fptr[1] != 0) {
		UART_Fptr[1]();
	}
}

void USART3_IRQHandler(void){
	if (UART_Fptr[2] != 0) {
		UART_Fptr[2]();
	}
}

















