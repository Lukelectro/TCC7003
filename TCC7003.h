/* 
 *	TCC7003.h - Library for TCC 7003 display assembly 
 * 	Created by Lucas Volwater, July 2021 
 *  based on hardware description and example code from Aart Schipper
 * 
 */

/*
 * 10x 9443 display module
 * 
 * Logic board: 
 * 
 * 34_pin   function  register function
 * 
 * 1,2,3,4  V+
 * 
 * 5        D0        display A0
 * 6        D1        display A1
 * 7        D2        odd or !even column
 * 8        D3        A0 row
 * 9        D4        A1 row
 * 10       D5        A2 row
 * 11       D6        Display A2   
 * 12       D7        EN or !EN module via ST2, pos 1 is !EN ( ? - klopt dit ?)
 * 
 * 17       !EN module via ST2 
 * 20       !EN module bia ST2, pos 1  Tied to GND on header.          
 * 19       !WR display
 * 15       LE  latch register    
 * 
 * 31,32        GND
 * 
 * 
 * if no pins are given as arguments, these are the defaults: 
 *  D0 on pin 0, D1 on pin 1, D2 on pin 2, etc. up to D7 on pin 7,
 *  EN unused (wire to GND)
 *  LE on pin 8
 *  WR on pin 9
 *  
 *  Otherwise alternatives can be given in this order: (D0,D1,D2,D3,D4,D5,D6,D7,LE,WR,EN). 
 * 	So that would be for example TCC7003 led_display(0,1,2,3,4,5,6,7,8,9,13);
 *  to use pin 13 as enble.
 * 
 */

#ifndef TCC7003_H
#define TCC7003_H

#include "Arduino.h"
#define NUMDISP 40

class TCC7003
{
	public:
		TCC7003();
		TCC7003(int D0,int D1,int D2,int D3,int D4,int D5,int D6,int D7,int LE,int WR,int EN);
		void control(char disp, char cword);
		void clear(void); 					/* clear full display */
		void setBrightness(char br); 		/* set brightness for full display */
		void write(char text[]); 			/* Write from start of display */
		void writeAt(int row, int col, char text[]);
	private:
		int _D0,_D1,_D2,_D3,_D4,_D5,_D6,_D7,_EN,_WR,_LE;
		void construct(int D0,int D1,int D2,int D3,int D4,int D5,int D6,int D7,int LE,int WR,int EN);
		void module_9443_setDigit(char digit, char content);
		char adress(char disp);
		void writeData(byte Data);
	};

#endif
