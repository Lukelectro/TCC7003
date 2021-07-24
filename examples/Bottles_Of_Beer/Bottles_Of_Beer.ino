/* extended example for TCC7003 display. Sends text and variables to the display */

#include "TCC7003.h"

TCC7003 leddisplay;                         /* make new instance, use default pins */
//TCC7003 display2(1,2,3,4,5,6,7,8,9,0,13); /* or tell the library what pins to use*/

/*
 * if no pins are given as arguments, these are the defaults: 
 *  D0 on pin 0, D1 on pin 1, D2 on pin 2, etc. up to D7 on pin 7,
 *  EN unused (wire to GND)
 *  LE on pin 8
 *  WR on pin 9
*/
 
void setup() {

leddisplay.setBrightness(2);        /* set display brightness, 1 to 3*/
leddisplay.write("Hello");          /* Write from start of display */
leddisplay.writeAt(2,1, "World!");  /* Write from a row, collumn */
delay(2000);
leddisplay.clear();                 /* clear the entire display. */
leddisplay.setBrightness(3);        /* clear also sets brighness to 0, so re-set brightness */

/* if you want to clear only part of the display, you can use writeAt to write spaces. 
 * For example to overwrite a previous reading or other higher number of which no digits should be left. 
 * non-overwritten text stays
 */
 
leddisplay.writeAt(1,1,"100");
leddisplay.writeAt(2,1,"bottles of beer on the  wall");
delay(1000);
leddisplay.writeAt(1,1,"99");  /* Oops! 199 bottles!*/
leddisplay.writeAt(5,1,"OOPS!");
delay(1000);
leddisplay.writeAt(1,1,"99 ");  /* That's better!*/
leddisplay.writeAt(5,1,"wall "); /* note the extra space */
delay(1000);
}

void loop() {
  
  char strbuff[8];
  static unsigned int bottles=99;

  bottles--; 
  sprintf(strbuff, "%d", bottles);    /* convert number to string. */
  leddisplay.writeAt(1,1,"        "); /* clear part of the display */
  leddisplay.writeAt(1,1,strbuff);
  

  delay(500);

}
