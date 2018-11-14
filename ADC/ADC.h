/*
===============================================================================
Name        : ADC.h
Author      : Juan Ignacio Avelar Miranda
Version     : 1.0
License		: Open Source (LGPL)
Copyright   : Copyright (C)
Description : Librería para usar el ADC.

This is a free software and is opened for education, research and commercial developments under license policy of following terms:
- This is a free software and there is NO WARRANTY.
- No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
- Redistributions of source code must retain the above copyright notice.
===============================================================================
*/
#ifndef ADC_H_
#define ADC_H_

//------------------------------------------------- Funciones ---------------------------------------------------

void ADC_Init()	// Función para la configuración de los registros del ADC
{	
	ADMUX =  (0<<REFS1)|(1<<REFS0)|(0<<ADLAR);
	ADCSRA = (0<<ADEN) |(0<<ADSC) |(0<<ADATE)|(0<<ADIF) |(0<<ADIE) |(0<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRB = (0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);
	DIDR0 =  (1<<ADC5D)|(1<<ADC4D)|(1<<ADC3D)|(1<<ADC2D)|(1<<ADC1D)|(1<<ADC0D);
}

/*
	Ejemplo. 
	ADC_read(0);
	_delay_us(20);
	Valor_del_ADC = ADC
	Convertir_a_Voltaje = (Valor_del_ADC * 5 /1023)
	
	ADC_read(1);
	_delay_us(20);
	x = ADC
	y = (x * 5 /1023)
*/

void ADC_read(int channel)
{
	ADMUX &= 0b11110000;								// Limpia el multiplexor y evita que se modifiquen del bit 4 al 7 en el registro.
	ADMUX |= channel;									// Multiplexor para seleccionar el canal del ADC.
	ADCSRA |= (1<<ADEN)|(1<<ADSC);						// Enciende el ADC e inicia la conversión.
	while(!(ADCSRA&(1<<ADIF)));							// Entretenemos el sistema hasta que complete la conversión.
	ADCSRA &= ~(1<<ADIF);								// Limpiamos la bandera que nos indica que termino la conversión.
	ADCSRA &= ~(1<<ADEN);								// Apagamos el ADC.				
}

#endif