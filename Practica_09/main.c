/*
===============================================================================
 Name        : Practica_09.c
 Author      : Juan Ignacio Avelar Miranda
 Version     : 1.0
 License     : Open Source (LGPL)
 Copyright   : Copyright (C)
 Description : Programa que hace un corrimiento de LEDs en un puerto.

 This is a free software and is opened for education, research and commercial developments under license policy of following terms:
 - This is a free software and there is NO WARRANTY.
 - No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 - Redistributions of source code must retain the above copyright notice.
===============================================================================
*/
//----------------------------------- Frecuencia del CPU --------------------------------------
#define F_CPU 16000000UL        		// El AVR trabajará a una velocidad de Reloj de 16MHz.
//----------------------------------- Librerías -----------------------------------------------
#include <avr/io.h>             		// Librería colocada automaticamente por el wizard de Atmel Studio
#include <util/delay.h>         		// Librería para retardo
//=================================== Programa Principal ======================================
int main(void)                  		// Función Principal que no devuelve nada.
{
	DDRD = 0b11111111;					// Configura los 8 pines como salida del puerto D.
	PORTD = 0b00000000;					// Limpiamos el puerto D
										//        7 6 5 4 3 2 1 0 bit
										//       -----------------
										// MSB<--|0|0|0|0|0|0|0|1|-->LSB
										//       -----------------
	while(1)                     		// Ciclo while infinito.
	{
		PORTD = 0b00000001;				// Asignamos el dato "MSB <--00000001--> LSB" en el puerto D.
		_delay_ms(50);
		while(PORTD<=0b01000000)    	// Ciclo while para generar el desplazamiento del dato de forma acendente.
		{
			PORTD = PORTD<<1;			// Operador de desplazamiento a la izquierda.
			_delay_ms(50);				// Retardo
		}
		while(PORTD>=0b00000100)    	// Ciclo while para generar el desplazamiento del dato de forma descendente.
		{
			PORTD= PORTD>>1;			// Operador de desplazamiento a la derecha.
			_delay_ms(50);				// Retardo
		}
	}
}
