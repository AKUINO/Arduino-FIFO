# Arduino-FIFO
Simple FIFO buffer for Arduino or other embedded processors

The default size of the buffer is 32760 bytes.
With the default buffer size this library uses only 32766 bytes of memory.
(32760 byte buffer + 3 * 2 byte integers)

If you wish to change the buffer size then edit the ```#define FIFO_SIZE 32760``` inside of "FIFO.h"
