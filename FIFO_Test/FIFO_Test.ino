/*
 * FIFO Buffer Test Program
 * Pushes then pops items onto FIFO buffer.
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Daniel Eisterhold, Maxime Franco
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
void setup() {
  //Open serial port at 9600 baud
  Serial.begin(9600);

  //Wait until the serial port has opened
  while (!Serial) delay(1);

  //Wait a little bit to make sure we don't get any garbage on the serial monitor
  delay(100);
  randomSeed(analogRead(0));
  delay(100);
}

void loop() {
    Serial.println("Starting tests...");
    if(test_empty_size() !=0)
        Serial.println("Error in test");
    if(test_one_element() != 0)
        Serial.println("Error in test");
    if(test_one_bad_element() != 0)
        Serial.println("Error in test");
    if(test_random_input()!= 0)
        Serial.println("Error in test");
    if(test_toomuch_elements() != 0)
        Serial.println("Error in test");
    if(test_max_size()!= 0)
        Serial.println("Error in test");
    if(test_max_coverage()!= 0)
        Serial.println("Error in test");

    while (1);
   
}

int getSize() {
    return random(25,50);
}

void fillTab(uint8_t* tab, char fillinDigit, int tabSize) {
    for (int i = 0; i < tabSize; i++) {
        tab[i] = fillinDigit;
    }
}

int test_empty_size(){
    FIFO exFIFO;
  uint8_t displayBuf[50];
  Serial.println("Test exFIFO with an empty size" );

  if(exFIFO.pop() != 0
  ){
        Serial.println( "Error exFIFO.pop()");
        return -1;
    }

    if(exFIFO.peek() != 0){
        Serial.println( "Error exFIFO.peek()" );
        return -1;
    }

    if(exFIFO.peekBuffer(displayBuf, 50) != -1){
        Serial.println( "Error exFIFO.peekBuffer()");
        return -1;
    }

    if(exFIFO.popBuffer(displayBuf, 50) != -1){
        Serial.println( "Error exFIFO.popBuffer()");
        return -1;
    }
    if(exFIFO.size() !=0){
        Serial.println( "Error exFIFO.size()");
        return -1;
    }

    if(!exFIFO.isEmpty()){
        Serial.println( "Error exFIFO.isEmpty()");
        return -1;
    }
    return 0;
}

int test_one_element(){
    FIFO exFIFO;
  uint8_t displayBuf[50];
  exFIFO.push(0);
  Serial.println("Test exFIFO with one element" );

  if(exFIFO.pop() != 0){
        Serial.println( "Error exFIFO.pop()");
        return -1;
    }
    exFIFO.push(0);
    if(exFIFO.peek() != 0){
        Serial.println( "Error exFIFO.peek()");
        return -1;
    }

    if(exFIFO.peekBuffer(displayBuf, 50) != 0){
        Serial.println( "Error exFIFO.peekBuffer()");
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf, 50) != 0){
        Serial.println( "Error exFIFO.popBuffer()");
        return -1;
    }
    exFIFO.push(0);
    if(exFIFO.size() !=1){
        Serial.println( "Error exFIFO.size()");
        return -1;
    }
    if(exFIFO.isEmpty()){
        Serial.println( "Error exFIFO.isEmpty()");
        return -1;
    }
    exFIFO.pop();
    return 0;
}

int test_one_bad_element(){
    FIFO exFIFO;
  uint8_t displayBuf[50];
  exFIFO.push(17);
  Serial.println("Test exFIFO with one element but bad value" );
    if(exFIFO.peekBuffer(displayBuf, 50) != -1){
        Serial.println( "Error exFIFO.peekBuffer()");
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf, 50) != -1){
        Serial.println( "Error exFIFO.popBuffer()");
        return -1;
    }
    return 0;
}

int test_random_input(){
    FIFO exFIFO;
  uint8_t displayBuf[50];
  int test_size[10];
    int total_elem =0;
    Serial.println("Test exFIFO with random values" );
    for( int i =0; i < 10; i++){
        test_size[i] = getSize();
        total_elem += 1 + test_size[i];
        uint8_t ex1[test_size[i]];

        fillTab(ex1, 48+i, sizeof(ex1));
        exFIFO.pushBuffer(ex1,test_size[i]);

        if(exFIFO.size() != total_elem){
            Serial.println( "Error exFIFO.size()");
            return -1;
        }
    }
    while(!(exFIFO.isEmpty())) {
        uint8_t test = exFIFO.peek();
        if(exFIFO.peekBuffer(displayBuf, test) != test){
            Serial.println( "Error exFIFO.peekBuffer()");
            return -1;
        }
        if(exFIFO.popBuffer(displayBuf, test) != test){
            Serial.println( "Error exFIFO.popBuffer()");
            return -1;
        }
    }
    return 0;
}

int test_toomuch_elements(){
    Serial.println("Test exFIFO out of bounds" );
    FIFO exFIFO;
    uint8_t displayBuf[511];
    for(int i=0; i < 255; i++){
        displayBuf[i] = i;
    }
    exFIFO.pushBuffer(displayBuf, 255);
    exFIFO.pushBuffer(displayBuf, 255);

    if(exFIFO.size() !=512){
        Serial.println( "Error exFIFO.size()");
        return -1;
    }
    if(exFIFO.push(23)){
        Serial.println( "Error exFIFO.push()");
        return -1;
    }
    if(exFIFO.peekBuffer(displayBuf,511) != 255){
        Serial.println( "Error exFIFO.peekBuffer()" );
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf,511) != 255){
        Serial.println( "Error exFIFO.popBuffer()" );
        return -1;
    }
    if(exFIFO.peekBuffer(displayBuf,511) != 255){
        Serial.println( "Error exFIFO.peekBuffer()" );
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf,511) != 255){
        Serial.println( "Error exFIFO.popBuffer()" );
        return -1;
    }
    return 0;
}

int test_max_size() {
    FIFO exFIFO;
    uint8_t displayBuf[70];
    int total_elem = 0;
    Serial.println("Test exFIFO with max size" );
    for (int i = 0; i < 8; i++) {
        uint8_t ex1[63];
        total_elem += 64;
        fillTab(ex1, 48 + i, 63);
        exFIFO.pushBuffer(ex1, 63);
        if(exFIFO.size() != total_elem){
            Serial.println( "Error exFIFO.size() ");
            return -1;
        }
    }
    uint8_t test = exFIFO.peek();
    exFIFO.popBuffer(displayBuf, test);
    uint8_t ex1[63];
    fillTab(ex1, 48+8, 63);
    exFIFO.peekBuffer(ex1, 63);
    while(!(exFIFO.isEmpty())) {
        uint8_t test = 63;
        if(exFIFO.peekBuffer(displayBuf, 70) != test){
            Serial.println( "Error exFIFO.peekBuffer()");
            return -1;
        }
        if(exFIFO.popBuffer(displayBuf, 70) != test){
            Serial.println( "Error exFIFO.popBuffer()");
            return -1;
        }
    }
    return 0;
}

int test_max_coverage(){
    Serial.println("Test exFIFO test_max_coverage" );
    FIFO exFIFO;
    uint8_t displayBuf[7];
    uint8_t ex1[63];
    fillTab(ex1, 48, 63);
    exFIFO.pushBuffer(ex1,63);

    if(exFIFO.size() !=64){
        Serial.println( "Error exFIFO.size()");
        return -1;
    }

    if(exFIFO.isEmpty()){
        Serial.println( "Error exFIFO.isEmpty()");
        return -1;
    }
    if(exFIFO.peekBuffer(displayBuf,7) != 63){
        Serial.println( "Error exFIFO.peekBuffer()" );
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf,7) != 63){
        Serial.println( "Error exFIFO.popBuffer()" );
        return -1;
    }
    if(exFIFO.size() != 0){
        Serial.println( "Error exFIFO.size()");
        return -1;
    }
    exFIFO.push(45);
    for(int i=0; i < 10; i++){
        exFIFO.push(48);
    }
    if(exFIFO.peekBuffer(displayBuf,7) != -1){
        Serial.println( "Error exFIFO.peekBuffer()" );
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf,7) != -1){
        Serial.println( "Error exFIFO.popBuffer()" );
        return -1;
    }
    return 0;
}
