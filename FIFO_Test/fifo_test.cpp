#include "FIFO.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int getSize() {
	int min = 25;
	int max = 50;
	return min + std::rand() % ((max + 1) - min);
}

void fillTab(char* tab, char fillinDigit, int tabSize) {
	for (int i = 0; i < tabSize; i++) {
		tab[i] = fillinDigit;
	}
}

void fillFifo(FIFO* exFIFO, char* tab, int tabSize) {
	exFIFO->push((uint8_t)tabSize);
	for(int i = 0; i < tabSize; i++) {
		exFIFO->push((uint8_t)tab[i]);
	}
}

void display( uint8_t* tab, int tabSize) {
	for (int i = 0; i < tabSize; i++) {
		std::cout << (char)tab[i];
	}
	std::cout << std::endl;
}

int test_empty_size(){
    FIFO exFIFO;
	uint8_t displayBuf[50];
	std::cout <<"Test exFIFO with an empty size" << std::endl;

	if(exFIFO.pop() != 0){
        std::cout << "Error exFIFO.pop()"<< std::endl;
        return -1;
    }

    if(exFIFO.peek() != 0){
        std::cout << "Error exFIFO.peek()"<< std::endl;
        return -1;
    }

    if(exFIFO.peekString(displayBuf, 50) != 0){
        std::cout << "Error exFIFO.peekString()"<< std::endl;
        return -1;
    }

    if(exFIFO.popString(displayBuf, 50) != 0){
        std::cout << "Error exFIFO.popString()"<< std::endl;
        return -1;
    }
    if(exFIFO.size() !=0){
        std::cout << "Error exFIFO.size()"<< std::endl;
        return -1;
    }

    if(!exFIFO.isEmpty()){
        std::cout << "Error exFIFO.isEmpty()"<< std::endl;
        return -1;
    }
    return 0;
}

int test_one_element(){
    FIFO exFIFO;
	uint8_t displayBuf[50];
	exFIFO.push(0);
	std::cout <<"Test exFIFO with one element" << std::endl;

	if(exFIFO.pop() != 0){
        std::cout << "Error exFIFO.pop()"<< std::endl;
        return -1;
    }
    exFIFO.push(0);
    if(exFIFO.peek() != 0){
        std::cout << "Error exFIFO.peek()"<< std::endl;
        return -1;
    }

    if(exFIFO.peekString(displayBuf, 50) != 0){
        std::cout << "Error exFIFO.peekString()"<< std::endl;
        return -1;
    }
    if(exFIFO.popString(displayBuf, 50) != 0){
        std::cout << "Error exFIFO.popString()"<< std::endl;
        return -1;
    }
    exFIFO.push(0);
    if(exFIFO.size() !=1){
        std::cout << "Error exFIFO.size()"<< std::endl;
        return -1;
    }
    if(exFIFO.isEmpty()){
        std::cout << "Error exFIFO.isEmpty()"<< std::endl;
        return -1;
    }
    exFIFO.pop();
    return 0;
}

int test_one_bad_element(){
    FIFO exFIFO;
	uint8_t displayBuf[50];
	exFIFO.push(17);
	std::cout <<"Test exFIFO with one element but bad value" << std::endl;
    if(exFIFO.peekString(displayBuf, 50) != -1){
        std::cout << "Error exFIFO.peekString()"<< std::endl;
        return -1;
    }
    if(exFIFO.popString(displayBuf, 50) != -1){
        std::cout << "Error exFIFO.popString()"<< std::endl;
        return -1;
    }
    return 0;
}

int test_random_input(){
    FIFO exFIFO;
	uint8_t displayBuf[50];
	int test_size[10];
    int total_elem =0;
    std::cout <<"Test exFIFO with random values" << std::endl;
    for( int i =0; i < 10; i++){
        test_size[i] = getSize();
        total_elem += 1 + test_size[i];
        char ex1[test_size[i]];

        fillTab(ex1, 48+i, sizeof(ex1));
        fillFifo(& exFIFO,ex1,sizeof(ex1));

        if(exFIFO.size() != total_elem){
            std::cout << "Error exFIFO.size()"<< std::endl;
            return -1;
        }
    }
	while(!(exFIFO.isEmpty())) {
        uint8_t test = exFIFO.peek();
        if(exFIFO.peekString(displayBuf, test) != test){
            std::cout << "Error exFIFO.peekString()"<< std::endl;
            return -1;
        }
        if(exFIFO.popString(displayBuf, test) != test){
            std::cout << "Error exFIFO.popString()"<< std::endl;
            return -1;
        }
    }
    return 0;
}

int test_toomuch_elements(){
    std::cout <<"Test exFIFO out of bounds" << std::endl;
    FIFO exFIFO;
	uint8_t displayBuf[511];
    exFIFO.push(255);
    for(int i=0; i < 255; i++){
        exFIFO.push(i);
    }
    exFIFO.push(255);
    for(int i=0; i < 255; i++){
        exFIFO.push(i);
    }
    if(exFIFO.size() !=512){
        std::cout << "Error exFIFO.size()"<< std::endl;
        return -1;
    }
    if(exFIFO.push(23)){
        std::cout << "Error exFIFO.push()"<< std::endl;
        return -1;
    }
    if(exFIFO.peekString(displayBuf,511) != 255){
        std::cout << "Error exFIFO.peekString()" << std::endl;
        return -1;
    }
    if(exFIFO.popString(displayBuf,511) != 255){
        std::cout << "Error exFIFO.popString()" << std::endl;
        return -1;
    }
    if(exFIFO.peekString(displayBuf,511) != 255){
        std::cout << "Error exFIFO.peekString()"<< exFIFO.peekString(displayBuf,511) << std::endl;
        return -1;
    }
    if(exFIFO.popString(displayBuf,511) != 255){
        std::cout << "Error exFIFO.popString()"<< exFIFO.peekString(displayBuf,511) << std::endl;
        return -1;
    }
    return 0;
}

int test_max_size() {
    FIFO exFIFO;
	uint8_t displayBuf[70];
	int total_elem = 0;
    std::cout <<"Test exFIFO with max size" << std::endl;
	for (int i = 0; i < 8; i++) {
        char ex1[63];
        total_elem += 64;
        fillTab(ex1, 48 + i, sizeof(ex1));
        fillFifo(& exFIFO,ex1,sizeof(ex1));
        if(exFIFO.size() != total_elem){
            std::cout << "Error exFIFO.size() "<< std::endl;
            return -1;
        }
	}
	uint8_t test = exFIFO.peek();
    exFIFO.popString(displayBuf, test);
    char ex1[63];
    fillTab(ex1, 48+8, sizeof(ex1));
    fillFifo(& exFIFO, ex1, sizeof(ex1));
	while(!(exFIFO.isEmpty())) {
        uint8_t test = 63;
        if(exFIFO.peekString(displayBuf, 70) != test){
            std::cout << "Error exFIFO.peekString()"<< std::endl;
            return -1;
        }
        if(exFIFO.popString(displayBuf, 70) != test){
            std::cout << "Error exFIFO.popString()"<< std::endl;
            return -1;
        }
    }
    return 0;
}

int main() {
    if(test_empty_size() !=0)
        return -1;
    if(test_one_element() != 0)
        return -1;
    if(test_one_bad_element() != 0)
        return -1;
    if(test_random_input()!= 0)
        return -1;
    if(test_toomuch_elements() != 0)
        return -1;
	if(test_max_size()!= 0)
        return -1;

	return 0;
}
