/* ----------------------------------------------------------------------------------------------------
// RUTINAS DEL DRIVER HD44780-LCD 
//
// Rutinas:
// LCD_Init inicializa el controlador del LCD
// LCD_Cmd envía sends LCD controller command
// LCD_Char envía un caracter ascii al display
// LCD_Clear limpia el display LCD y el cursor se mueve a home
// LCD_Home el cursor se mueve a la posición home
// LCD_Goto mueve el cursor a la posición (x,y)
// LCD_Line mueve el cursor a la linea (x)
// LCD_Hex muestra un valor hexadecimal
// LCD_Integer muestra un valor entero
// LCD_Message muestra una cadena
//
// El modulo LCD requiere 6 pines I/O: delas cuales 2 son lineas de control (EN y RS) y 4 lineas de datos
// (D4, D5, D6, D7).
//
// ---------------------------------- Distribución de los pines del LCD -------------------------------
//		   ______________________________________________
//		 ||												 ||
//		 ||												 ||
//		 ||												 ||
//		 ||______________________________________________||
//		   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
// PINES   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
//       --------------------------------------------------
//		   G +5V G  RS RW E              D4 D5 D6 D7 +5V G
//
// PIN	  CONEXIÓN
//	1		GND
//	2		VCC
//	3		Contraste (Pot 10K GND y VCC)
//	4		RS dato (el pin en 1) o instrucción (comando LCD) (el pin en 0)
//	5		RW conectado a GND
//	6		E  enable
//	7		D0 No se conecta
//	8		D1 No se conecta
//	9		D2 No se conecta
//	10		D3 No se conecta
//	11		D4 Datos
//	12		D5 Datos
//	13		D6 Datos
//	14		D7 Datos
*/

#ifndef HD44780_H_
#define HD44780_H_

// -------------------------------- Definiciones básicas ----------------------------------------------
#define ClearBit(x,y) x &= ~(1<<y)				// equivalent to cbi(x,y)
#define SetBit(x,y)   x |= (1<<y)				// equivalent to sbi(x,y)

// -------------------------------- Librerias a Usar --------------------------------------------------
#include <stdlib.h>								// librería estandar

// -------------------------------- Definiciones Utiles -----------------------------------------------
typedef uint8_t byte;							// declaracion de entero para compatibilidad
typedef int8_t sbyte;							// con otros compiladores

// -------------------------------- Definiciones de configuración -------------------------------------
#define LCD_RS	0								// pin para LCD R/S
#define LCD_E	1								// pin para LCD ENABLE
#define DAT4	2								// pin para d4
#define DAT5	3								// pin para d5
#define DAT6	4								// pin para d6
#define DAT7	5								// pin para d7
#define port	PORTD							// asignamos el puerto a usar ej. PORTB

// -------------------------------- Comandos de control para HD44780 ----------------------------------
#define CLEARDISPLAY 0x01						// Limpia la pantalla
#define SETCURSOR 0x80							// Fija el cursor

void msDelay(int delay)							// Retardo exclusivo para el manejo del LCD
{
	for (int i=0;i<delay;i++)
	_delay_ms(1);
}

void PulseEnableLine ()							// Función para habilitar el LCD
{
	SetBit(port,LCD_E);							// Manda un 1 en el pin ENABLE
	_delay_us(40);								// Retardo de 40 microsegundos
	ClearBit(port,LCD_E);						// Manda un 0 en el pin ENABLE
}

void SendNibble(byte data)						// Función para manejo de cuartetos
{
	port &= 0xC3;								// 11000011 = limpia 4 lineas de datos
	if(data & (1<<4))							
	{
		SetBit(port,DAT4);						// Manda un 1 en DAT4
	}
	if(data & (1<<5))
	{
		SetBit(port,DAT5);						// Manda un 1 en DAT5
	}
	if(data & (1<<6))
	{
		SetBit(port,DAT6);						// Manda un 1 en DAT6
	}
	if(data & (1<<7))
	{
		SetBit(port,DAT7);						// Manda un 1 en DAT7
	}
	PulseEnableLine();							// clock 4 bits into controller
}

void SendByte (byte data)						// Función para enviar 8 bits (1 byte)
{
	SendNibble(data);							// Envía los 4 bits mas significativos
	SendNibble(data<<4);						// Envía los 4 bits menos significativos
	ClearBit(port,5);							// Limpia 
}

void LCD_Cmd (byte cmd)							// Función para comandos del HD44780
{
	ClearBit(port,LCD_RS);						// Pone un 0 en R/S = comandos
	SendByte(cmd);								// Envía los comandos
}

void LCD_Char (byte ch)							// Función para characteres
{
	SetBit(port,LCD_RS);						// Pone un 1 en R/S = characteres
	SendByte(ch);								// Envía los characteres
}

void LCD_Init()
{
	LCD_Cmd(0x33);								// Inicializa el controlador
	LCD_Cmd(0x32);								// Configura en modo de solo 4 bits de entrada
	LCD_Cmd(0x28);								// Configura 2 líneas, y matriz 5x7
	LCD_Cmd(0x0C);								// Apaga el cursor (0x0E para encenderlo)
	LCD_Cmd(0x06);								// Dirección del cursor = derecha
	LCD_Cmd(0x01);								// Inicia con el display límpio
	msDelay(3);									// Retardo para inicializar el LCD
}

void LCD_Clear()								// Función para limpiar el LCD
{
	LCD_Cmd(CLEARDISPLAY);						// Limpia el LCD
	msDelay(3);									// Retardo para procesar el comando
}

void LCD_Home()									// Función para colocar el cursor en home sin limpiar
{
	LCD_Cmd(SETCURSOR);							// Comando para colocar el cursor en posición home
}

void LCD_Gotoxy(byte x, byte y)					// Función para mover el cursor a una posición específica
{
	byte addr = 0;								// La línea 0 comienza en la dirección 0x00
	switch (y)
	{
		case 1: addr = 0x40; break;				// La línea 1 comienza en la dirección 0x40
		case 2: addr = 0x14; break;
		case 3: addr = 0x54; break;
	}
	LCD_Cmd(SETCURSOR+addr+x);					// Actualiza la posición del cursor en x,y
}

void LCD_Line(byte row)							// Función para mover el cursor a una línea especifíca
{
	LCD_Gotoxy(0,row);							// Se mueve el cursor a la columna 0, linea y
}

void LCD_Message(const char *text)				// Función para mostrar una cadena en el LCD
{
	while (*text)								// 
	{
		LCD_Char(*text++);						// Envía un character y se actualiza el puntero *text	
	}
	
}

void LCD_Hex(int data)							// Muestra el valor hexadecimal de los datos actuales en el LCD
{
	char st[8] = "";							// Guarda espacio para los resultados
	itoa(data,st,16);							// convierte a ascii hexadecimal
	//LCD_Message("0x");						// add prefix "0x" if desired
	LCD_Message(st);							// Manda el resultado al LCD
}
void LCD_Integer(int data)						// Muestra el valor entero de los datos actuales en el LCD
{
	char st[8] = "";							// Guarda espacio para los resultados
	itoa(data,st,10);							// Convierte a ascii
	LCD_Message(st);							// Muestra el resultado en el LCD
}
// --------------------------------- Funciones Demo ------------------------------------------
void UpdateCursor (byte count)					// Función para FillScreen
{
	switch(count)
	{
		case 0: LCD_Line(0); break;
		case 16: LCD_Line(1); break;
		case 32: LCD_Line(2); break;
		case 48: LCD_Line(3); break;
	}
}

char GetNextChar(char ch)						// Función para FillScreen
{
	if ((ch<0x20) | (ch>=0xFF))
	return 0x20;
	if ((ch>=0x7F) & (ch<0xA0))
	return 0xA0;
	return ++ch;
}

#define NUMCHARS 64								// Número de caracteres por pantalla

void FillScreen ()
// Llena la pantalla con caracteres ascii
// NUMCHARS debe de tener un valor entre 32 a 64 characteres, dependiendo del tamaño del display
// NUMCAHRS = 32 para displays de 16x2; NUMCHARS = 64 para display 20x4.
// para displays de 4 lineas el contador acendente debe de ser de 1-99.
{
	char ch = 'A';
	LCD_Clear();
	for (byte count=1;count<100;count++)
	{
		LCD_Gotoxy(18,0);
		LCD_Integer(count);						// show counter (vis on 4-liners only)
		for (byte i=0;i<NUMCHARS;i++)			// do a screenful of characters
		{
			UpdateCursor(i);					// go to next line, if necessary
			LCD_Char(ch);						// show current ascii character
			ch = GetNextChar(ch);				// update to next character
			msDelay(60);						// set animation speed
		}
	}
}

#endif