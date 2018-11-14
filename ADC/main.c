/*
===============================================================================
Name        : main.c
Author      : Juan Ignacio Avelar Miranda
Version     : 1.0
License	 : Open Source (LGPL)
Copyright   : Copyright (C)
Description : Programa que lee los datos del ADC y los imprime en un LCD16x2.


							   (Vin)*(1024)							  System Clock
			  Valor del ADC = --------------			Freq_conv = ----------------
								  (Vref)							   Preescaler


This is a free software and is opened for education, research and commercial developments under license policy of following terms:
- This is a free software and there is NO WARRANTY.
- No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
- Redistributions of source code must retain the above copyright notice.
===============================================================================
 */ 
//----------------------------------- Frecuencia del CPU --------------------------------------
#define F_CPU 16000000UL
//----------------------------------- Librerías Base ------------------------------------------
#include <avr/io.h>									// Librerías base para el microcontrolador
#include <util/delay.h>								// Librería para generar retardos
#include <stdio.h>									// Librería para manejar la función sprintf()
//----------------------------------- Librerías de drivers ------------------------------------
#include "GPIO.h"									// Librería para los puertos GPIO.
#include "HD44780.h"								// Librería para los pantalla LCD 16x2.
#include "ADC.h"									// Librería para ADC.

//=================================== Programa Principal ======================================
int main(void)
{
	uint16_t x,y;									// Variable de 16 bits entero sin signo para guardar las conversiones del ADC. 
	float Vx,Vy;									// Variable flotante para guardar la conversión a voltaje.
	char Mensaje1[16], Mensaje2[16];				// Arreglo de 16x1 para guardar la cadena a imprimir en la pantalla LCD.
	GPIO_Init();									// Función de configuración e inicialización de los GPIO.
	LCD_Init();										// Función de inicialización de la pantalla LCD.
    ADC_Init();										// Función de configuración e inicialización del ADC.

	//------------------------------- Ciclo Infinito ------------------------------------------
    while (1) 
    {	
		//--------------------------- Conversión del ADC0 -------------------------------------
		ADC_read(0);								// Función para seleccionar el canal del ADC y realizar la conversión.
		_delay_us(10);								// Retardo para retener el valor adquirido por el ADC.
		x = ADC;									// Guardamos el valor del ADC en la variable ADC_val.
		Vx = x*(5)/1023.0;							// Convierte a voltaje el valor del ADC.
		
		//--------------------------- Conversión del ADC0 -------------------------------------
		ADC_read(1);								// Función para seleccionar el canal del ADC y realizar la conversión.
		_delay_us(10);								// Retardo para retener el valor adquirido por el ADC.
		y = ADC;									// Guardamos el valor del ADC en la variable ADC_val.
		Vy = y*(5)/1023.0;							// Convierte a voltaje el valor del ADC.
		
		//--------------------------- Impresión en pantalla del resultado ---------------------
		sprintf(Mensaje1,"Voltaje = %.2f",Vx);		// Se imprime en memoria como caractér el resultado de la variable Volts.
		LCD_Gotoxy(0,0);
		LCD_Message(Mensaje1);						// Mandamos a imprimir en la LCD el arreglo Mensaje.
		_delay_ms(10);								// Retardo para alcanzar a visualizar el mensaje en la LCD.
		
		sprintf(Mensaje2,"Voltaje = %.2f",Vy);		// Se imprime en memoria como caractér el resultado de la variable Volts.
		LCD_Gotoxy(0,1);
		LCD_Message(Mensaje2);						// Mandamos a imprimir en la LCD el arreglo Mensaje.
		_delay_ms(10);								// Retardo para alcanzar a visualizar el mensaje en la LCD.
    }
	return 0;
}
//=================================== Fin del Programa ========================================