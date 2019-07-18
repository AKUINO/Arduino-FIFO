# Arduino-FIFO
Simple FIFO buffer for Arduino or other embedded processors

The default size of the FIFO is 64 bytes.
With the default FIFO size this library uses only 70 bytes of memory.
(64 byte FIFO + 3 * 2 byte integers)

The size of the FIFO is modular by using ```#define FIFO_SIZE 1024``` in theArduino code.
However, if the FIFO size is declared nowhere, a default size is inside the header file as 512.

``` cpp
#ifndef
	#define FIFO_SIZE 512
#endif
```

This library also support filling FIFO with small buffers by the pushBuffer, popBuffer and peekBuffer functions.
When you want to push a small buffer in the FIFO, the pushBuffer function will push the size of your buffer in the FIFO first then the elements.
It returns true if the pushing step is a success.

Then, to peek your small buffer, the function peekBuffer will look at the first element of the FIFO (which is also the length of your  first small buffer)
and will push all the elements between index 1 and index length in the destination table.

The popBuffer function works like peekBuffer, it will look at the first element to get the size of the small buffer to pop.
Then, it will put all elements between index 1 and index length them in a destination table and pop them.

If you want to get the size of your first small buffer, the peek function will work as usual.

``` c
#include "FIFO.h"

void setup() {
  //Open serial port at 9600 baud
  Serial.begin(9600);

  //Wait until the serial port has opened
  while (!Serial) delay(1);

  //Wait a little bit to make sure we don't get any garbage on the serial monitor
  delay(100);
}

void loop() {

    char tab[] = "Hello World!";
    int tabSize = sizeof(tab);
    int tmpSize = 20;
    char tmp[tmpSize];
    FIFO exFifo;

    exFifo.pushBuffer((uint8_t*)tab, tabSize);
    Serial.println((int)exFifo.size());
    exFifo.peekBuffer((uint8_t*)tmp, tmpSize);

    for (int i = 0; i < tabSize; i++) {
        Serial.print((char)tmp[i]);
        tmp[i] = 0;
    }
    Serial.println("");
    exFifo.popBuffer((uint8_t*)tmp, tmpSize);
    for (int i = 0; i < tabSize; i++) {
        Serial.print((char)tmp[i]);
        tmp[i] = 0;
    }
    while(true);
}
```
