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
    return 0;
  }
  else {
    return buffer[head];
  }
}

uint8_t FIFO::peekString(uint8_t* dest, int dest_size) {
  if (numElements == 0)  {
    return 0;
  }
  else {
    int str_size = buffer[head];
    if( dest_size < str_size)
        return 0;
    if( str_size > numElements)
        return 0;

    for (int i = 0; i < dest_size; i++) {
      dest[i] = buffer[(head + i + 1) % FIFO_SIZE];
    }
    return str_size;
  }
}

bool FIFO::isEmpty() {
  return numElements == 0;
}

uint8_t FIFO::popString(uint8_t* dest, uint8_t dest_size) {
  if(numElements == 0) {
    return 0;
  }
  else {
    uint8_t str_size = pop();
    if(dest_size < str_size)
        return 0;
    if( str_size > numElements)
        return 0;
    for(uint8_t i = 0;i < str_size; i++) {
      dest[i] = pop();
    }
    return str_size;
  }
}

