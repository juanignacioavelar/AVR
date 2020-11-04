#ifndef GPIO_H_
#define GPIO_H_

#define BIT(x)	(1<<(x))
#define 
#define OUTPUT_HIGH(port,bit) (port) |= (1 << (bit))
#define OUTPUT_LOW(port,bit) (port) &= ~(1 << (bit))
#define PUSH_BUTTON_PB(bit) (PINB & (1<<bit))
#define PUSH_BUTTON_PD(bit) (PIND & (1<<bit))

//------------------------------------------------- Funciones ---------------------------------------------------

void GPIO_Init()
{
	//DDRB = 0b11111111;
	//DDRC = 0b11111111;
	DDRD = 0b11111111;
}

#endif
