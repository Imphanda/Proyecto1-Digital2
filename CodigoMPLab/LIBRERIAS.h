


#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
void Lcd_Init(void);
void Lcd_Cmd(int variable);
void Lcd_Write_String(char *a);
void Lcd_Write_Char(char a);
void Lcd_Set_Cursor(int a, int b);
void Lcd_Clear(void);
void INADC1(void);
void INADC2(void);


#endif	/* XC_HEADER_TEMPLATE_H */

