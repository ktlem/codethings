/*
 * Pixel.c
 *
 *  Created on: -----
 *      Author: -----
 */

#include "Pixel.h"

#define ctrl *(uint8_t *) 0x41220008
#define channel *(uint8_t *) 0x41220000

/******use these if you know how*********
//Table for pixel dots. dots[page][X][Y][COLOR]
//volatile uint8_t dots[Page_size][8][8][3]={0};
//volatile uint8_t page=0;
****************************************/

//Table for pixel dots.
//				 dots[X][Y][COLOR]
volatile uint8_t dots[8][8][3]={0};



void setup(){


	//reseting screen at start is a MUST to operation. Hint 1: reset is active low. Hint 2: Reset pin from CPU to DM163 is default 0
	ctrl|=0x01; // reset


	//Write code that sets 6-bit values in register of DM163 chip. Recommended that every bit in that register is set to 1. 6-bits and 24 "bytes", so some kind of loop structure could be nice

	ctrl|=0x10;

	for( int i=0; i<144; i++ ){
		ctrl&=~0x08; //SET only BIT3 to 0 in control signal (CLK bit)
		ctrl|=0x08; //SET only BIT3 to 1 in control signal (CLK bit)
	}

	ctrl|=0x4;

}

//Set value of one pixel at led matrix
void SetPixel(uint8_t x,uint8_t y, uint8_t r, uint8_t g, uint8_t b){

	//Set new pixel value. Put function paremeter values to dots array at correct places
	dots[x][y][2] = r;
	dots[x][y][1] = g;
	dots[x][y][0] = b;
}


//Put new data to led matrix. Hint: This function is supposed to send 24-bytes and parameter x is for x-coordinate.
void run(uint8_t x){
	channel=0;
	for(uint8_t y=0; y<8; y++){
		for(uint8_t color=0; color<3; color++){
			uint8_t data = dots[x][y][color];
			for(uint8_t byte_count=0;byte_count<8;byte_count++){
				if(data & 0x80) ctrl|=0x10;  //SET only BIT4 to 1 in control signal (SDA bit)
				else ctrl&=~0x10; //SET only BIT4 to 0 in control signal (SDA bit)
				ctrl&=~0x08; //SET only BIT3 to 0 in control signal (CLK bit)
				data<<=1; //shift one to left
				ctrl|=0x08; //SET only BIT3 to 1 in control signal (CLK bit)
			}
		}
	}

	latch();
	open_line(x);
	//Write code that writes data to led matrix driver (8-bit data). Use values from dots array

}

//latch signal. See colorshield.pdf in project folder how latching works
void latch(){
	ctrl |= 0x02;
	ctrl &=~0x02;
}


//Set one line as active per time.
void open_line(uint8_t x){
	switch(x){
	case 0:
		channel=1;
		break;
	case 1:
		channel=2;
		break;
	case 2:
		channel=4;
		break;
	case 3:
		channel=8;
		break;
	case 4:
		channel=16;
		break;
	case 5:
		channel=32;
		break;
	case 6:
		channel=64;
		break;
	case 7:
		channel=128;
		break;
	}
}



