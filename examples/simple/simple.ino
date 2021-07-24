/* Simple example for TCC 7003 display assembly. Just shows "Hello World!" */

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
leddisplay.write("Hello");          /* Write from start of display */
leddisplay.writeAt(2,1, "World!");  /* Write from a row, collumn */

}

void loop() {


}
