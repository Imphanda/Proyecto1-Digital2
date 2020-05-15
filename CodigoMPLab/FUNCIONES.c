/*
 * File:   FUNCIONES.c
 * Author: Daniel Hengstenberg
 *
 * Created on 11 de marzo de 2020, 11:25 PM
 */

#define _XTAL_FREQ 4000000
#include "LIBRERIAS.h"

#define data        PORTB               // DATA
#define LCD_RD7     PORTBbits.RB7       // D7
#define LCD_RD6     PORTBbits.RB6       // D6
#define LCD_RD5     PORTBbits.RB5       // D5
#define LCD_RD4     PORTBbits.RB4       // D4
#define LCD_RD3     PORTBbits.RB3       // D3   
#define LCD_RD2     PORTBbits.RB2       // D2
#define LCD_RD1     PORTBbits.RB1       // D1
#define LCD_RD0     PORTBbits.RB0       // D0
#define LCD_EN      PORTDbits.RD7       // EN
#define LCD_RS      PORTDbits.RD6       // RS


void Lcd_Init(void){
    __delay_ms(20);
    Lcd_Cmd (0x30);
    __delay_ms(5);
    Lcd_Cmd (0x30);
    __delay_us(100);
    Lcd_Cmd (0x30);
    __delay_us(100);
    Lcd_Cmd (0x38);
    __delay_us(60);
    Lcd_Cmd (0x08);
    __delay_us(60);
    Lcd_Cmd (0x01);
    __delay_ms(5);
    Lcd_Cmd (0x06);
    __delay_us(60);
    Lcd_Cmd (0x0C);     
    __delay_us(60);
    

}


void Lcd_Cmd(int variable){
    LCD_RS = 0;
    __delay_ms(5);
    LCD_EN = 1;
    data = variable;
    __delay_ms(5);
    LCD_EN = 0;
    __delay_ms(5);
    

}


void Lcd_Clear(void){
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x01);
    __delay_ms(5);
}



void Lcd_Set_Cursor(int a, int b)
{
    int d;
	if(a == 1)
	{
        d = 0x80 + b - 1;
		Lcd_Cmd(d);
	}
	else if(a == 2)
	{
		d = 0xC0 + b - 1;
		Lcd_Cmd(d);
	}
}


void Lcd_Write_Char(char a)
{   
    LCD_RS = 1;
    // LCD_Port(caracter);
    data = a;
    LCD_EN = 1;
    __delay_us(40);
    LCD_EN = 0;
}

void Lcd_Write_String(char *a)
{
    int n;
    for(n = 0; a[n] != '\0'; n++){
        Lcd_Write_Char(a[n]);
    }
}