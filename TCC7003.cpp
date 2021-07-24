/* 
 *	TCC7003.h - Library for TCC 7003 display assembly 
 * 	Created by Lucas Volwater, July 2021 
 *  based on hardware description and example code from Aart Schipper
 * 
 * 
 */


#include "Arduino.h"
#include "TCC7003.h"

/* if no pins are given as arguments, use defaults: D0 on pin 0 to D7 on pin 7, EN unused (wire to GND), LE on pin 8, WR on pin 9 */
TCC7003::TCC7003()
{
	construct(0,1,2,3,4,5,6,7,8,9,-1); 
}
	
/* if pins are given, use those instead of defaults */	
TCC7003::TCC7003(int D0,int D1,int D2,int D3,int D4,int D5,int D6,int D7,int LE,int WR,int EN)
{
  construct(D0,D1,D2,D3,D4,D5,D6,D7,LE,WR,EN);
}

void TCC7003::construct(int D0,int D1,int D2,int D3,int D4,int D5,int D6,int D7,int LE,int WR,int EN)
{
  _D0=D0;
  _D1=D1;
  _D2=D2;
  _D3=D3;
  _D4=D4;
  _D5=D5;
  _D6=D6;
  _D7=D7;
  _LE=LE;
  _EN=EN;
  _WR=WR;

	
  pinMode (_EN, OUTPUT);
  digitalWrite (_EN, LOW);  

  pinMode (_D0, OUTPUT); 
  pinMode (_D1, OUTPUT); 
  pinMode (_D2, OUTPUT); 
  pinMode (_D3, OUTPUT); 
  pinMode (_D4, OUTPUT); 
  pinMode (_D5, OUTPUT); 
  pinMode (_D6, OUTPUT); 
  pinMode (_D7, OUTPUT); 

  digitalWrite (_WR, HIGH);  
  pinMode (_WR, OUTPUT); 

  digitalWrite (_LE, LOW);  
  pinMode (_LE, OUTPUT);
  
  clear();
  setBrightness(3);
  
  for(int i = 0; i<NUMDISP;i++)
  {
	_buffer[i] = ' ';  
  }	
}

	
void TCC7003::write(char text[])
{
	int len = strlen(text);
	if (len>=NUMDISP) len = NUMDISP-1;
	memcpy(_buffer,text,len);
	refresh();
}
	
/* write at row 1 to 5, col 1-8*/	
void TCC7003::writeAt(int row, int col, char text[])
{
	if(row<1) row = 1;
	if(row>5) row = 5;
	if(col<1) col = 1;
	if(col>8) col = 8;
	unsigned int pos = (col-1) + (row-1)*8; 
	unsigned int len = strlen(text);
	
	if(pos>=NUMDISP) pos = NUMDISP-1;
	if(len>(NUMDISP-pos)) len = NUMDISP-pos;
	
	memcpy(&_buffer[pos],text,len);
	refresh();
}

void TCC7003::module_9443_setDigit (char digit, char content) {
  // write address register
  digitalWrite(_LE, LOW);
  writeData(digit);
  digitalWrite(_LE, HIGH);
  delayMicroseconds(1); 
  //write data to digit
  writeData(content);
  digitalWrite(_WR, LOW);
  delayMicroseconds(1); 
  digitalWrite(_WR, HIGH);
}

void TCC7003::writeData(byte Data) {
  digitalWrite (_D0,((Data >> 0) & 1));
  digitalWrite (_D1,((Data >> 1) & 1));
  digitalWrite (_D2,((Data >> 2) & 1));
  digitalWrite (_D3,((Data >> 3) & 1));
  digitalWrite (_D4,((Data >> 4) & 1));
  digitalWrite (_D5,((Data >> 5) & 1));
  digitalWrite (_D6,((Data >> 6) & 1));
  digitalWrite (_D7,((Data >> 7) & 1));
}

char TCC7003::adress (char disp){
  /* input: display number 0-39, output what should be put on adress bus */
// 0|(1<<6)|((disp&1)<<0)|((disp&2)<<1)|((disp&4)<<2)((disp&8)<<3)|((disp&16)<<4)((disp&32)<<5); // start at 0, leave EN low, set A2 for normal operation and the rest is displ. number  
// or simper:return (disp&0x3F)|(0x40);
// except that is mirrored. row is correct, collumn is mirrord and digit 0-3 whitin a display is mirrored. So invert lower 3 bits.
return ((disp&0x3F)^0x07)|(0x40);
  }

void TCC7003::control(char disp, char cword){
  /* sends control word to display 0-39*/
  /* Cword: D7 = clear, D6 =lamp test, D5 = blink disp, d4 = enable attributes, d3,2 = atributes 00 cursor 01 blink char, 10 blink cursor 11 alternate curs/char d1,0=brightness */
  module_9443_setDigit((disp&0x3F)^0x07,cword); /* A2 is low, so control word*/
  }

 void TCC7003::clear(void){
  for(char i=0;i<NUMDISP;i++){
    control(i,0x80);
    _buffer[i]=' ';
    }
 }
 
void TCC7003::setBrightness (char br){
  
  if(br>3) br=3;
  for(char i=0;i<NUMDISP;i++){
    control(i,br);
    }
  }
  
  void TCC7003::refresh()
{
	for(char disp=0;disp<NUMDISP;disp++){
		module_9443_setDigit(adress(disp),_buffer[disp]);
	}
}
