/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 *
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

// Main program for exercise

//****************************************************
//By default, every outputs used in this exercise is 0
//****************************************************
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xgpiops.h"
#include "xttcps.h"
#include "xscugic.h"
#include "xparameters.h"
#include "Pixel.h"
#include "Interrupt_setup.h"

//***Hint: Use sleep(x)  or usleep(x) if you want some delays.****
//to call assember code found in blinker.S, call it using "blinker();".


//Comment this if you want to disable all interrupts
#define enable_interrupts
#define led *(uint8_t *) 0x41200000
#define ctrl *(uint8_t *) 0x41220008
#define channel *(uint8_t *) 0x41220000
#define status *(uint8_t *) 0xE000A068

volatile uint8_t alien_x = 0;
volatile char alien_dir = 'R';
volatile uint8_t ship_x = 1;
volatile uint8_t score = 0;
volatile int ammo_y = -1;
volatile uint8_t ammo_x = 8;
volatile int shoot = 0;
volatile int hp = 8;

int main()
{
	//**DO NOT REMOVE THIS****
	    init_platform();
	//************************


#ifdef	enable_interrupts
	    init_interrupts();
#endif

	    //setup screen
	    setup();


	    Xil_ExceptionEnable();
	    //SetPixel(1,1,0,0,255);
	    //SetPixel(6,6,255,0,0);


		//Main loop
		while(1){

		}


		cleanup_platform();
		return 0;
}


//Interrupt handler for switches and buttons. Connected buttons and switches are at bank2. Reading Status will tell which button or switch was used
void ButtonHandler(void *CallBackRef, u32 Bank, u32 Status)
{
	//****Write code here ****


	if(Status==0x01) { //btn 0
		//SetPixel(0,0,0,0,255);
		//run(0);
		Shoot();
	}
	else if(Status==0x02){ // btn 1
		//MoveShip('R');
		MoveRight();
		DrawShip();
		//run(1);
		//open_line(1);
	}
	else if(Status==0x04){ // btn2
		//MoveShip('L');
		MoveLeft();
		DrawShip();
		//run(6);
		//open_line(6);
	}
	else if(Status==0x08){ //btn 3
		RestartGame();
	}
	else if(Status==0x10){ // switch 0

	}
	else if(Status==0x20){ // switch 1

	}


	//****END OF OWN CODE*****************
}

//Timer interrupt handler for led matrix update. Frequency is 800Hz
void TickHandler(void *CallBackRef){
	//Don't remove this
	uint32_t StatusEvent;

	//exceptions must be disabled when updating screen
	Xil_ExceptionDisable();

	//****Write code here ****

	static uint8_t x=0;

	run(x);

	x++;
	if(x==8) x=0;


	//DrawShip();

	//****END OF OWN CODE*****************

	//*********clear timer interrupt status. DO NOT REMOVE********
	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);
	//*************************************************************
	//enable exeptions
	Xil_ExceptionEnable();
}


//Timer interrupt for moving alien, shooting... Frequency is 10Hz by default
void TickHandler1(void *CallBackRef){

	//Don't remove this
	uint32_t StatusEvent;

	//****Write code here ****

	//ClearMatrix();
	MoveAlien();
	MoveAmmo();
	DrawAlien();
	DrawShip();
	DrawAmmo();
	DrawHP();
	CheckHits();
	CheckWinCondition();


	//****END OF OWN CODE*****************
	//clear timer interrupt status. DO NOT REMOVE
	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);

}

void MoveAlien(){
	SetPixel(alien_x,0,0,0,0);
	if(alien_dir == 'R'){
		alien_x = alien_x + 1;
	}else{
		alien_x = alien_x - 1;
	}
	if(alien_x==6){
		alien_dir = 'L';
	}else if(alien_x==0){
		alien_dir = 'R';
	}
}


void DrawAlien(){
	SetPixel(alien_x,0,0,255,0);
}

void DrawShip(){
	SetPixel(ship_x,7,0,0,255);
	SetPixel(ship_x-1,7,0,0,255);
	SetPixel(ship_x+1,7,0,0,255);
	SetPixel(ship_x,6,0,0,255);
}

void DrawAmmo(){
	SetPixel(ammo_x,ammo_y,255,0,0);
}

void DrawHP(){
	for(int i=0;i<8;i++){
		SetPixel(7,i,148,0,211);
	}

	for(int i=0;i<8-hp;i++){
		SetPixel(7,i,0,0,0);
	}
}

void ClearMatrix(){
	for(uint8_t x=0; x<8; x++){
		for(uint8_t y=0; y<8; y++){
			SetPixel(x,y,0,0,0);
		}
	}
}

void MoveShip(char dir){

	//if(dir=='R'){
	ship_x = ship_x + 1;
	//}

	//switch(dir){
	//	case 'R':
	//		if(ship_x<7){
	//			ship_x = ship_x + 1;
	//		}
	//	case 'L':
	//		if(ship_x>0){
	//			ship_x = ship_x - 1;
	//		}
	//}
}

void MoveRight(){
	SetPixel(ship_x,7,0,0,0);
	SetPixel(ship_x-1,7,0,0,0);
	SetPixel(ship_x+1,7,0,0,0);
	SetPixel(ship_x,6,0,0,0);
	if(ship_x<5){
			ship_x = ship_x + 1;
	}
}

void MoveLeft(){
	SetPixel(ship_x,7,0,0,0);
	SetPixel(ship_x-1,7,0,0,0);
	SetPixel(ship_x+1,7,0,0,0);
	SetPixel(ship_x,6,0,0,0);
	if(ship_x>1){
			ship_x = ship_x - 1;
	}
}

void MoveAmmo(){
	SetPixel(ammo_x,ammo_y,0,0,0);
	if(shoot){
		ammo_x = ship_x;
		if(ammo_y>-1){
			ammo_y = ammo_y - 1;
		}



		//ammo_x = ship_x;
		//ammo_y = 6;
		//for(uint8_t y=0; y>7; y++){
		//	ammo_y--;
		//}
	}
}

void Shoot(){
	if(ammo_y==-1){
		ammo_y = 6;
		shoot = 1;
	}
}

void CheckHits(){
	if(ammo_x==alien_x){
		if(ammo_y==0){
			hp--;
		}
	}
}

void RestartGame(){
	ClearMatrix();
	alien_x = 0;
	alien_dir = 'R';
	ship_x = 1;
	score = 0;
	ammo_y = -1;
	ammo_x = 8;
	shoot = 0;
	hp = 8;
}

void CheckWinCondition(){
	if(hp==0){
		ClearMatrix();
		for(int i=1;i<7;i++){
			SetPixel(1,i,148,0,211);
			SetPixel(5,i,148,0,211);
		}
		SetPixel(2,5,148,0,211);
		SetPixel(4,5,148,0,211);
		SetPixel(3,4,148,0,211);

		for(int i=1;i<5;i++){
			SetPixel(7,i,25,175,33);
		}
		SetPixel(7,6,25,175,33);

	}
}
