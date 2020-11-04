/*
===============================================================================
Name        : GPIO.h
Author      : Juan Ignacio Avelar Miranda
Version     : 1.0
License		: Open Source (LGPL)
Copyright   : Copyright (C)
Description : Librería para usar los GPIO.

This is a free software and is opened for education, research and commercial developments under license policy of following terms:
- This is a free software and there is NO WARRANTY.
- No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
- Redistributions of source code must retain the above copyright notice.
===============================================================================
*/
#ifndef GPIO_H_
#define GPIO_H_

//------------------------------------------------- Definiciones de Funciones -----------------------------------
#define OUTPUT_HIGH(port,bit) (port) |= (1 << (bit))	// Función para mandar un nivel ALTO en un GPIO.
														// ej. OUTPUT_HIGH(PORTB,0)	--> PB0=1
#define OUTPUT_LOW(port,bit) (port) &= ~(1 << (bit))	// Función para mandar un nivel BAJO en un GPIO.
														// ej. OUTPUT_LOW(PORTB,0)	--> PB0=0
#define PUSH_BUTTON(port,bit) (port & (1<<bit))			// Función para leer un nivel ALTO en un GPIO.
														// ej. PUSH_BUTTON(PINB,0)

//------------------------------------------------- Funciones ---------------------------------------------------
void GPIO_Init()										// Función configurar los GPIO
{
	DDRB = 0b00111111;									// Registro para configurar la dirección del GPIO.
	//DDRC = 0b11111111;								// 0 = entradas / 1 = salidas.
	//DDRD = 0b11111111;								// ej. DDRB = 0b11111111 --> PORTB como salida.
														// ej. DDRC = 0b00000000 --> PORTC como entrada.
	PORTB = 0;
	//PORTD = 0;
}

#endif
