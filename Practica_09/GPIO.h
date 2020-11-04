#ifndef GPIO_H_
#define GPIO_H_
				    		
#define SALIDA_UNO(port,bit) (port) |= (1<<(bit))
#define SALIDA_CERO(port,bit) (port) &= ~(1<<(bit))
#define BOTON_PRESIONADO_PB(bit) (PINB & (1<<bit))
#define BOTON_PRESIONADO_PC(bit) (PINC & (1<<bit))
#define BOTON_PRESIONADO_PD(bit) (PIND & (1<<bit))

void GPIO_Conf()
{
	DDRB = 0b11111111;
	DDRC = 0b11110000;
	DDRD = 0b00000000; 
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000000;
}
#endif