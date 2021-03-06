/*
===============================================================================
 Name        : Practica_08.c
 Author      : Juan Ignacio Avelar Miranda
 Version     : 1.0
 License     : Open Source (LGPL)
 Copyright   : Copyright (C)
 Description : Programa que prende y apaga un LED.

 This is a free software and is opened for education, research and commercial developments under license policy of following terms:
 - This is a free software and there is NO WARRANTY.
 - No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 - Redistributions of source code must retain the above copyright notice.
===============================================================================
*/

//----------------------------------- Frecuencia del CPU --------------------------------------
#define F_CPU 16000000UL			// El AVR trabajara a una velocidad de Reloj de 16MHz.

//----------------------------------- Librerías -----------------------------------------------
#include <avr/io.h>				// Librería colocada automaticamente por el wizard de Atmel Studio.
#include <util/delay.h>				// Librería para retardo.

//=================================== Programa Principal ======================================
int main(void)					// Función Principal.
{
	DDRB = 0b11111111;			// Configura los 8 pines como salida del puerto B.
	PORTB = 0b00000000;			// Limpiamos el puerto B.
	while (1)				// Ciclo while infinito.
    	{
		PORTB = 0b00100000;		// Mandamos un 1 en el pin PB5, los demas pines del puerto con 0
		_delay_ms(500);			// Retardo
		PORTB = 0b00000000;		// Mandamos un 0 cada uno de los pines del puerto B
		_delay_ms(500);			// Retardo
    }
}
