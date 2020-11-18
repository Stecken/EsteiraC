/*
 * CafeteiraMegaBlaster.cpp
 *
 * Created: 11/10/2020 23:11:43
 * Author : T-Gamer
 */ 

#include "def_principais.h"
#define CILINDRO PORTB0
#define ESTEIRA PORTB1
#define LEDINI PORTB2

const unsigned char Tabela[] PROGMEM = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void procedimentoS0(){
	set_bit(PORTB, CILINDRO);
	set_bit(PORTB, ESTEIRA);
	set_bit(PORTB, LEDINI);
}

void procedimentoS1(){
	while(tst_bit(PINC, 1)){}
	clr_bit(PORTB, CILINDRO);
}
void procedimentoS2(){
	while(tst_bit(PINC, 2)){}
	clr_bit(PORTB, ESTEIRA);
	_delay_ms(5000);
	set_bit(PORTB, ESTEIRA);
}

void procedimentoS3(){
	while(tst_bit(PINC, 3)){}
}

int main(void){
	// inicio do procedimento
	DDRD = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0;
	PORTD = 0;
	PORTB = 0;
	PORTC = 0b11111111;
	
	
	while(true){
		int counter = 0;
		int proc = 0;
		PORTB = 0;
		PORTD = pgm_read_byte(&Tabela[counter]);
		if(!tst_bit(PINC, 0)){
			while(counter <= 6){
				switch(proc){
					case 0:
						procedimentoS0();
						proc = 1;
						break; 
						
					case 1:
						procedimentoS1();
						proc = 2; 
						break;
						
					case 2:
						procedimentoS2(); 
						proc = 3;
						break;
						
					case 3:
						procedimentoS3(); 
						++counter;
						proc = 0;
						break;
				}
			PORTD = pgm_read_byte(&Tabela[counter]);
			}
		}
	}
	return 0;
}