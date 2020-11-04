#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "GPIO.h"
int main(void)
{
    GPIO_Conf();
    while (1) 
    {
		if(BOTON_PRESIONADO_PC(0) == 1)
		{
			SALIDA_UNO(PORTB,5);
		}
		if(BOTON_PRESIONADO_PC(0) == 0)
		{
			SALIDA_CERO(PORTB,5);
		}
    }
}

