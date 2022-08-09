/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "USART_interface.h"
#include "DIO_interface.h"
#include "STK_interface.h"




#include "ESP_interface.h"
#include "ESP_confg.h"

static u8 ESP_Responce[15];


void ESP_u8Init()
 {
	 /* disable echo */
	USART_voidSendStringSynch(USART_1,(u8*)"ATE1\r\n");
	USART_voidReceiveStringSynch(USART_1,ESP_Responce);
	MSTK_voidSetBusyWait( 1000 ); // wait 1 ms
	USART_voidSendStringSynch(USART_1,(u8*)"ATE0\r\n");
	USART_voidReceiveStringSynch(USART_1,ESP_Responce);
	MSTK_voidSetBusyWait( 1000 ); // wait 1 ms
	 /* Wifi  mode */
	USART_voidSendStringSynch(USART_1,(u8*)"AT+CWMODE_CUR=3\r\n");
	USART_voidReceiveStringSynch(USART_1,ESP_Responce);
	MSTK_voidSetBusyWait( 1000 ); // wait 1 ms

 }

u8 ESP_u8ConnectAP(u8* SSIDName, u8* SSIDPass) {

	USART_voidSendStringSynch(USART_1,(u8*)(u8*)"AT+CWJAP_CUR=\"");
	USART_voidSendStringSynch(USART_1, SSIDName);
	USART_voidSendStringSynch(USART_1,(u8*)(u8*)"\",\"");
	USART_voidSendStringSynch(USART_1,SSIDPass);
	USART_voidSendStringSynch(USART_1,(u8*)"\"\r\n");
	USART_voidReceiveStringSynch(USART_1,ESP_Responce);
	return 1;

}



u8 ESP_u8ConnectServer(u8* ip) {

	USART_voidSendStringSynch(USART_1,(u8*)"AT+CIPSTART=\"TCP\",");
	USART_voidSendStringSynch(USART_1,(u8*)"\"");
	USART_voidSendStringSynch(USART_1,ip);
	USART_voidSendStringSynch(USART_1,(u8*)"\",80\r\n");
	USART_voidReceiveStringSynch(USART_1,ESP_Responce);
    return 1;
}


void ESP8266_VoidSendHttpReq( u8 * Copy_u8Key , u8  *Copy_u8Data , u8  *Copy_u8Length , u8 *field )
{
	USART_voidSendStringSynch(USART_1,(u8 *) "AT+CIPSEND=");

	USART_voidSendStringSynch(USART_1,(u8 *)Copy_u8Length);

	USART_voidSendStringSynch(USART_1, (u8 *) "\r\n");

	MSTK_voidSetBusyWait(100);

	USART_voidReceiveStringSynch(USART_1,ESP_Responce);

	USART_voidSendStringSynch(USART_1,(u8 *) "GET https://api.thingspeak.com/update?api_key=");

	USART_voidSendStringSynch(USART_1,(u8 *) Copy_u8Key);

	USART_voidSendStringSynch(USART_1,(u8 *) "&");

	USART_voidSendStringSynch(USART_1,(u8 *) field);

	USART_voidSendStringSynch(USART_1,(u8 *) "=");

	USART_voidSendStringSynch(USART_1,(u8 *)Copy_u8Data);

	USART_voidSendStringSynch(USART_1,(u8 *) "\r\n");

	MSTK_voidSetBusyWait(100);

	USART_voidReceiveStringSynch(USART_1,ESP_Responce);

}

