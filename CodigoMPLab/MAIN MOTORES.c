/*
 * File:   MAIN MOTORES.c
 * Author: Daniel Hengstenberg
 *
 * Created on 11 de marzo de 2020, 02:53 PM
 */


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config WRT = OFF 


// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
 #include <stdio.h>
//#include "ADC.h"
#include "LIBRERIAS.h"
//#include "PWM.h"

#define _XTAL_FREQ 500000
#define rojas RA0
#define amarillas RA1
#define azules RA2

uint8_t z;
uint8_t i;
uint8_t grados;
int posicion;
int color;
uint8_t rojasod = 0;
uint8_t amarillasod = 0;
uint8_t azulesod = 0;
unsigned int dato = 0;
unsigned int DC2 = 32;
int banderaR = 0;
int banderaA = 0;
int banderaAM = 0;
int banderaS = 0;  
int banderaDC = 0;

void setup(void);

void servoRotate0() // grado 0 rojas 
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD0 = 1;
    __delay_us(800);
    RD0 = 0;
    __delay_us(19200);
  }
}

void servoRotate90() //90 azules 
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD0 = 1;
    __delay_us(1500);
    RD0 = 0;
    __delay_us(18500);
  }
}

void servoRotate180() //180 amarillas
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD0 = 1;
    __delay_us(2200);
    RD0 = 0;
    __delay_us(17800);
  }
}


void __interrupt() isr(void){
   if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            grados = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            grados = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = i;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }        
        PIR1bits.SSPIF = 0;    
    }   
}
 

void main(void) {
    setup();

    
    TRISCbits.TRISC1 = 0;
    OSCCONbits.IRCF2 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;       //config
    
    T2CON=  0b00000110;
    
    PR2 = 155;
    //TRISD = 0; // PORTD como salida
    PORTCbits.RC0 =1;
    int banderaR = 0;
    int banderaA = 0;
    int banderaAM = 0;
    
    if (PORTAbits.RA5 ==1 && banderaDC == 0){
        banderaDC=1;
        if (banderaDC == 1 ){
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 1;
            __delay_ms(2000);
            banderaDC = 0;
    }   
    }
    
    
    
    if(banderaDC == 0 ){
        PORTCbits.RC0 = 1;
        PORTCbits.RC1 = 1;
    }
    
    if (PORTAbits.RA1 == 1 && banderaR==0){
        banderaR = 1;               //
        if (banderaR==1){
            servoRotate0(); 
            banderaR=0;        
    }
    }
    
    if (PORTAbits.RA2 == 1 && banderaA ==0){
        banderaA = 1;               //
        if (banderaA==1){
            servoRotate90(); 
            banderaA=0;
    }
    }
    if (PORTAbits.RA3 ==1 && banderaAM ==0){
        banderaAM = 1;              
        if (banderaAM==1){
            servoRotate180();
            banderaAM=0;
    }
    }
    if (PORTAbits.RA4 == 1 && banderaS ==0){
        banderaS = 1;
        if (banderaS == 1){
        
            PORTB = 0b01110000;     //paso1
            __delay_ms(800);    
            PORTB = 0b00110000;     //paso2
            __delay_ms(800);
            PORTB = 0b10110000;     //paso3
            __delay_ms(800);
            PORTB = 0b10010000;     //paso4
            __delay_ms(800);
            PORTB = 0b11010000;     //paso5
            __delay_ms(800);
            PORTB = 0b11000000;     //paso6
            __delay_ms(800);
            PORTB = 0b11100000;     //paso7
            __delay_ms(800);
            PORTB = 0b01100000;     //paso8
            __delay_ms(800);    
            
            banderaS=0;
      
        }
      }
   

    return;    
}
//***************************
// Función de Inicialización
//***************************
void setup(void){
    //Configuración del OSC 500000
    OSCCONbits.IRCF2 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    //OSCCONbits.SCS = 1;
    
    PORTA = 0;
    TRISA = 1;
    PORTB = 0;
    TRISB = 0;
    PORTD = 0;
    TRISD = 0;
    PORTC = 0;
    TRISC = 0;
    ANSEL = 0;
    ANSELH = 0;
    
    
    
    //I2C_Slave_Init(0x40);   
}