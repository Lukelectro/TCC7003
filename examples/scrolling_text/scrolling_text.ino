/* Scrolling text example for TCC 7003 display */

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

leddisplay.setBrightness(3);        /* set display brightness, 1 to 3 */

}

void loop() {

  const char text[] = "Hello World on \"7003-assy\" board                 Be excellent to each other & try to not to be on fire.                     An apple a day keeps the doctor away - does that mean apples repel doctors? And vice versa? Can doctors eat apples?              42           ";
  static unsigned int i = 0;
  leddisplay.write(&text[i%strlen(text)]);
  delay(200);
  i++;
}
