/*
 * LCD16x2.c
 *
 * Created: 10/05/2017 10:27:59 a.m.
 * Author : NV57H
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "gpio.h"
#include "HD44780.h"

int main(void)
{
	GPIO_Init();
	LCD_Init();
	LCD_Message("HOLA MUNDO");

	while(1)
	{
		
	}
}

