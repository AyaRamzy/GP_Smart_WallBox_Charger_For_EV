/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

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
	USART_1=0,
	USART_2,
	USART_3,
	USART_TOTAL_NUMBERS
}eUSART_Num_t;

typedef enum {
    USART_Disable,
	 USART_Enable

}eUART_Status_t;

typedef enum {
    BAUD_4800   = 0x683,
    BAUD_9600   = 0x341,
    BAUD_19200  = 0x1A1,
    BAUD_57600  = 0x8B,
    BAUD_115200 = 0x45
}eBaudRate_t;

typedef enum {
    No_Parity,
    Even_Parity,
    Odd_Parity
}eParity_t;


typedef enum {
    Transmition,
    Recieving,
    Transmit_Recieve
}eDataDirection_t;

typedef struct
{
	eUSART_Num_t 		USART_Num;
	eUART_Status_t		UART_Status;
	eBaudRate_t          BaudRate;
	eParity_t				Parity;
    eDataDirection_t     DataDirection;

}sUART_Config_t;
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
/*Steps to use USART module
 * 1- Init the GPIO that include your tx and rx pins
 * 2- Set the tx pin as OUTPUT AF PP
 * 3- Set the rx pin as input floating
 * 4- Create a struct to configure the UART settings
 * 5- Call USART_voidInit() to init , config the module and init the clock
 * 6- Start Send or receive
 * EX:
     GPIO_voidInit(GPIOA);
     GPIO_voidSetPinDirection(RX1,INPUT_FLOATING);
     GPIO_voidSetPinDirection(TX1,OUTPUT_SPEED_2MHZ_AFPP);
     USART_voidInit(&UART_Config);
 	 USART_voidSendCharSynch(USART_1, 'A');

 */
void USART_voidInit(sUART_Config_t *UART_Config);

void USART_voidSendCharSynch(eUSART_Num_t USART_Number, u8 copy_u8Char);

u8   USART_u8ReceiveCharSynch(eUSART_Num_t USART_Number) ;

void USART_voidSendStringSynch(eUSART_Num_t USART_Number, u8 * Pu8Char);

void USART_voidReceiveStringSynch(eUSART_Num_t USART_Number, u8 * Pu8String);

void USART_voidNewLine(eUSART_Num_t USART_Number) ;

void USART_voidSendStringSynchSum(eUSART_Num_t USART_Number,u8 *text);

u8   USART_u8ReceiveStringSynchSum(eUSART_Num_t USART_Number , u8 *text) ;

//void USART_voidSendIntSynch(eUSART_Num_t USART_Number,u16 number)

u8   USART_u8Receive(eUSART_Num_t USART_Number,u8* Copy_u8Data);

void USART_voidRXInterruptEnable(eUSART_Num_t USART_Number);
void USART_voidRXInterruptDisable(eUSART_Num_t USART_Number);
void USART_voidTXInterruptEnable(eUSART_Num_t USART_Number);
void USART_voidTXInterruptDisable(eUSART_Num_t USART_Number);
void USART_voidRXIdleInterruptDisable(eUSART_Num_t USART_Number) ;
void USART_voidRXIdleInterruptEnable(eUSART_Num_t USART_Number);
void USART_voidSetCallBack(eUSART_Num_t USART_Number,void (*LocalFptr)(void));

void USART_voidDMAEnableTransming(eUSART_Num_t USART_Number);
void USART_voidDMADisableTransming(eUSART_Num_t USART_Number);
void USART_voidDMAEnableReceiving(eUSART_Num_t USART_Number);
void USART_voidDMADisableReceiving(eUSART_Num_t USART_Number);
#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/

