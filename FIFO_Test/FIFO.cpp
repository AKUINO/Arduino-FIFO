/*
 * FIFO Buffer
 * Implementation uses arrays to conserve memory
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Daniel Eisterhold
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "FIFO.h"

FIFO::FIFO() {
  head = 0;
  tail = 0;
  numElements = 0;
}

FIFO::~FIFO() {
}

bool FIFO::push(uint8_t data) {
  if(numElements == FIFO_SIZE) {
//    Serial.println(F("Buffer full"));
    return false;
  }
  else {
    //Increment size
    numElements++;

    //Only move the tail if there is more than one element
    if(numElements > 1) {
      //Increment tail location
      tail++;

      //Make sure tail is within the bounds of the array
      tail %= FIFO_SIZE;
    }
  
    //Store data into array
    buffer[tail] = data;
    return true;
  }
}

uint8_t FIFO::pop() {
  if(numElements == 0) {
//    Serial.println(F("Buffer empty"));
    return 0;
  }
  else {
    //Decrement size
    numElements--;

    uint8_t data = buffer[head];

    if(numElements >= 1) {
      //Move head up one position
      head++;

      //Make sure head is within the bounds of the array
      head %= FIFO_SIZE;
    }

    return data;
  }
}

int FIFO::size() {
  return numElements;
}

uint8_t FIFO::peek() {
  if (numElements == 0)  {
    Serial.println("NULL");
    return 0;
  }
  else {
    return buffer[head];
  }
}

void FIFO::peekString(uint8_t* peekTab, int tabSize) {
  if (numElements == 0)  {
    Serial.println("Empty FIFO");
  }
  else {
    int peekTabSize = buffer[head];
    for (int i = 0; i < peekTabSize; i++) {
      if ((i > numElements) || (i > tabSize)) {
        Serial.println("Element out of FIFO bounds");
      }
      peekTab[i] = buffer[(head + i + 1) % FIFO_SIZE];
    }
  }
}

bool FIFO::isEmpty() {
  return numElements == 0;
}

uint8_t FIFO::popString(uint8_t* popTab, uint8_t maxTabSize) {
  if(numElements == 0) {
//    Serial.println(F("Buffer empty"));
    Serial.println("Empty FIFO");
    return 0;
  }
  else {
    uint8_t tabSize = pop();
    Serial.print("TabSize = ");
    Serial.println(tabSize);
    for(uint8_t i = 0; (i < tabSize) && (i < maxTabSize); i++) {
      popTab[i] = pop();
    }
    return tabSize;
  }
  
}


/*47
77
TabSize = 77
TmpBuffer[0] = 77
77
M=4&B=4.331&A0=0&A1=2&A2=36&C1=27.911&H1=44.671


47
TabSize = 47
TmpBuffer[0] = 47
77
M=4&B=4.325&A0=0&A1=2&A2=37&C1=28.111&H1=43.806*/