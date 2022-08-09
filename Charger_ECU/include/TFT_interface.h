/*********************************************************/
/* Author      :  GP Team                                */
/* Date        :                                         */
/* Version     : V01                                     */
/*********************************************************/

#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_


/* Colours */

#define     TFT_BLACK        0x0000
#define     TFT_WHITE        0xffff
#define     TFT_RED          0xf800
#define     TFT_BLUE         0x39df
#define     TFT_YELLOW       0xffc0
#define     TFT_ORANGE       0xfd20
#define     TFT_PURPLE       0xf1df
#define     TFT_GREEN        0x1427

#define BLACK        0x0000
#define NAVY         0x000F
#define DARKGREEN    0x03E0
#define DARKCYAN     0x03EF
#define MAROON       0x7800
#define PURPLE       0x780F
#define OLIVE        0x7BE0
#define LIGHTGREY    0xC618
#define DARKGREY     0x7BEF
#define BLUE         0x001F
#define GREEN        0x07E0
#define CYAN         0x07FF
#define RED          0xF800
#define MAGENTA      0xF81F
#define YELLOW       0xFFE0
#define WHITE        0xFFFF
#define ORANGE       0xFD20
#define GREENYELLOW  0xAFE5
#define PINK         0xF81F


void TFT_voidInit (void);

void TFT_voidDisplayImage(const u16* copy_u16Image);

void TFT_voidDrawRectangle (u16 copy_u16X ,u16 copy_u16Y , u16 copy_u16Width , u16 copy_u16Hight , u16 copy_u16Color );

void TFT_voidFillDisplay (u16 copy_u16Colour);

void TFT_voidPrintChar(s8 copy_s8Char , u16 copy_u16X , u16 copy_u16Y, u8 copy_u8Size , u16 copy_u16Color, u16 copy_u16BackColor);

void TFT_voidPrintText(s8 *copy_s8Text , u16 copy_u16X , u16 copy_u16Y, u8 copy_u8Size , u16 copy_u16Color, u16 copy_u16BackColor);


#endif /* TFT_INTERFACE_H_ */
