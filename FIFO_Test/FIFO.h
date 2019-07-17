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

#ifndef __FIFO__
#define __FIFO__
#include <stdint.h>
#ifndef FIFO_SIZE
    #define FIFO_SIZE 512
#endif


#include <iostream>
#include <cstdlib>

class FIFO {
  private:
    int head;
    int tail;
    int numElements;
    uint8_t buffer[FIFO_SIZE];
  public:
    FIFO();
    ~FIFO();
    bool push(uint8_t data);
    bool pushBuffer(const uint8_t* src, int src_size);
    uint8_t pop();
    int popBuffer(uint8_t* dest, int dest_size);
    int size();
    uint8_t peek();
    int peekBuffer(uint8_t* dest, int dest_size);
    bool isEmpty();
};

#endif
