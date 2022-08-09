/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/*****************************************************/


#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

typedef enum {

	ESP_OK=0,
	ESP_READY,
	ESP_FAIL,
    ESP_NOCHANGE,
    ESP_LINKED,
    ESP_UNLINK,
	ESP_ERROR

}ESP_Status;

void ESP_u8Init();
u8 ESP_u8IsStarted(void) ;
u8 ESP_u8Restart(void);
u8 ESP_u8ConnectAP(u8* SSIDName, u8* SSIDPass) ;
u8 ESP_u8DisconnectAP();
u8 ESP_u8ConnectServer(u8* ip);
u8 ESP_u8Response();
void ESP_voidSendRequest(u8 *length,u8* URL_withGET);
void ESP8266_VoidSendHttpReq( u8 * Copy_u8Key , u8  *Copy_u8Data , u8  *Copy_u8Length , u8 *field );
u8 ESP_voidReciveRespnse(u8* Buffer);

#endif
