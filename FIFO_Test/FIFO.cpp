/*
 * FIFO Buffer
 * Implementation uses arrays to conserve memory
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Daniel Eisterhold
 * Copyright (c) 2019 Romain Ceccotti, Maxime Franco (addind methods : pushBuffer, popBuffer, peekBuffer)
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
/**
* \fn bool FIFO::push(uint8_t data)
* \brief Allows a user to push one element inside the FIFO.
* \param data : the element to be pushed inside the FIFO.
* \return The function returns true if the element was pushed inside the FIFO, else return false.
*/
bool FIFO::push(uint8_t data) {
  if(numElements == FIFO_SIZE) {
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


/**
* \fn bool FIFO::pushBuffer(const uint8_t* src, int src_size)
* \brief Allows a user to push a buffer of uint8_t of length src_size inside the FIFO.
* \param *src : a pointer to the source buffer.
* \param src_size : the number of elements inside the source buffer.
* \return The function returns true if the elements were pushed inside the fifo, else return false
*/
bool FIFO::pushBuffer(const uint8_t* src, int src_size){
    if(numElements + 1 + src_size > FIFO_SIZE){
        return false;
    }
    if (push((uint8_t) src_size)){
        for(int i=0; i < src_size; i++){
            push(src[i]);
        }
        return true;
    }
    return false;
}

/**
* \fn uint8_t FIFO::pop()
* \brief Allows a user to pop a element from the FIFO.
* \return The function returns 0 if the FIFO is empty, else it returns the removed element.
*/
uint8_t FIFO::pop() {
  if(isEmpty()) {
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

/**
* \fn int FIFO::popBuffer(uint8_t* dest, int dest_size)
* \brief Allows a user to remove a buffer from the FIFO. The first element removed will be considered as the length of the buffer to remove. The removed buffer will be written inside the destination buffer.
* \param *dest : a pointer to the destination buffer.
* \param dest_size : the number of elements the destination buffer can contain.
* \return The function returns the number of elements written inside the destination buffer.
*/
int FIFO::popBuffer(uint8_t* dest, int dest_size) {
  if(isEmpty()) {
    return 0;
  }
  else {
    uint8_t str_size = pop();
    if(dest_size < str_size)
        return -1;
    if( str_size > numElements)
        return -1;
    for(uint8_t i = 0;i < str_size; i++) {
      dest[i] = pop();
    }
    return str_size;
  }
}

/**
* \fn uint8_t FIFO::size()
* \brief Returns the number of elements in the FIFO.
* \return The function returns the number of elements the FIFO contains.
*/
int FIFO::size() {
  return numElements;
}

/**
* \fn uint8_t FIFO::peek()
* \brief Returns the top element of the FIFO.
* \return The function returns first element inside the FIFO or 0 if the FIFO is empty.
*/
uint8_t FIFO::peek() {
  if (numElements == 0)  {
    return 0;
  }
  else {
    return buffer[head];
  }
}

/**
* \fn int FIFO::peekBuffer(uint8_t* dest, int dest_size)
* \brief Allows a user to get the top buffer from the FIFO. The first element will be considered as the length of the buffer to get, then the next elements will be written inside the destination buffer.
* \param *dest : a pointer to the destination buffer.
* \param dest_size : the number of elements the destination buffer can contain.
* \return The function returns the number of elements written inside the destination buffer or if the buffer is empty or if the destination buffer can't contain the number of elements, the function will return -1.
*/
int FIFO::peekBuffer(uint8_t* dest, int dest_size) {
  if (isEmpty())  {
    return -1;
  }
  else {
    int str_size = buffer[head];
    if( dest_size < str_size)
        return -1;
    if( str_size > numElements)
        return -1;

    for (int i = 0; i < dest_size; i++) {
      dest[i] = buffer[(head + i + 1) % FIFO_SIZE];
    }
    return str_size;
  }
}

bool FIFO::isEmpty() {
  return numElements == 0;
}


