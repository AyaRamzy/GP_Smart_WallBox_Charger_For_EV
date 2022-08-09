/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/

#ifndef TFT_CONFIG_H_
#define TFT_CONFIG_H_


/* Write pin in pair port,pin */
#define    TFT_A0_PIN      PORTB , 4   // output pin
#define    TFT_RST_PIN     PORTB , 3   // reset pin

/* Write pin in pair port,pin */
#define    TFT_SLAVE_PIN   PORTA,3   // slave select pin

/* Configure TFT size */
#define    TFT_MAX_X       127
#define    TFT_MAX_Y       159





#endif /* TFT_CONFIG_H_ */
