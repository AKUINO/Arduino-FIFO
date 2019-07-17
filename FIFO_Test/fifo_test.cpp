#include "FIFO.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int getSize() {
	int min = 25;
	int max = 50;
	return min + std::rand() % ((max + 1) - min);
}

void fillTab(uint8_t* tab, uint8_t fillinDigit, int tabSize) {
	for (int i = 0; i < tabSize; i++) {
		tab[i] = fillinDigit;
	}
}

int test_empty_size(){
    FIFO exFIFO;
	uint8_t displayBuf[50];
	std::cout <<"Test exFIFO with an empty size" << std::endl;

	if(exFIFO.pop() != 0
	){
        std::cout << "Error exFIFO.pop()"<< std::endl;
        return -1;
    }

    if(exFIFO.peek() != 0){
        std::cout << "Error exFIFO.peek()" << std::endl;
        return -1;
    }

    if(exFIFO.peekBuffer(displayBuf, 50) != -1){
        std::cout << "Error exFIFO.peekBuffer()"<<std::endl;
        return -1;
    }

    if(exFIFO.popBuffer(displayBuf, 50) != -1){
        std::cout << "Error exFIFO.popBuffer()"<< std::endl;
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

    if(exFIFO.peekBuffer(displayBuf, 50) != 0){
        std::cout << "Error exFIFO.peekBuffer()"<< std::endl;
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf, 50) != 0){
        std::cout << "Error exFIFO.popBuffer()"<< std::endl;
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
    if(exFIFO.peekBuffer(displayBuf, 50) != -1){
        std::cout << "Error exFIFO.peekBuffer()"<< std::endl;
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf, 50) != -1){
        std::cout << "Error exFIFO.popBuffer()"<< std::endl;
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
        uint8_t ex1[test_size[i]];

        fillTab(ex1, 48+i, sizeof(ex1));
        exFIFO.pushBuffer(ex1,test_size[i]);

        if(exFIFO.size() != total_elem){
            std::cout << "Error exFIFO.size()"<< std::endl;
            return -1;
        }
    }
	while(!(exFIFO.isEmpty())) {
        uint8_t test = exFIFO.peek();
        if(exFIFO.peekBuffer(displayBuf, test) != test){
            std::cout << "Error exFIFO.peekBuffer()"<< std::endl;
            return -1;
        }
        if(exFIFO.popBuffer(displayBuf, test) != test){
            std::cout << "Error exFIFO.popBuffer()"<< std::endl;
            return -1;
        }
    }
    return 0;
}

int test_toomuch_elements(){
    std::cout <<"Test exFIFO out of bounds" << std::endl;
    FIFO exFIFO;
	uint8_t displayBuf[511];
    for(int i=0; i < 255; i++){
        displayBuf[i] = i;
    }
    exFIFO.pushBuffer(displayBuf, 255);
    exFIFO.pushBuffer(displayBuf, 255);

    if(exFIFO.size() !=512){
        std::cout << "Error exFIFO.size()"<<std::endl;
        return -1;
    }
    if(exFIFO.push(23)){
        std::cout << "Error exFIFO.push()"<< std::endl;
        return -1;
    }
    if(exFIFO.peekBuffer(displayBuf,511) != 255){
        std::cout << "Error exFIFO.peekBuffer()" << std::endl;
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf,511) != 255){
        std::cout << "Error exFIFO.popBuffer()" << std::endl;
        return -1;
    }
    if(exFIFO.peekBuffer(displayBuf,511) != 255){
        std::cout << "Error exFIFO.peekBuffer()" << std::endl;
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf,511) != 255){
        std::cout << "Error exFIFO.popBuffer()" << std::endl;
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
        uint8_t ex1[63];
        total_elem += 64;
        fillTab(ex1, 48 + i, 63);
        exFIFO.pushBuffer(ex1, 63);
        if(exFIFO.size() != total_elem){
            std::cout << "Error exFIFO.size() "<<std::endl;
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
            std::cout << "Error exFIFO.peekBuffer()"<< std::endl;
            return -1;
        }
        if(exFIFO.popBuffer(displayBuf, 70) != test){
            std::cout << "Error exFIFO.popBuffer()"<< std::endl;
            return -1;
        }
    }
    return 0;
}

int test_max_coverage(){
    std::cout <<"Test exFIFO test_max_coverage" << std::endl;
    FIFO exFIFO;
	uint8_t displayBuf[7];
	uint8_t ex1[63];
    fillTab(ex1, 48, 63);
    exFIFO.pushBuffer(ex1,63);

    if(exFIFO.size() !=64){
        std::cout << "Error exFIFO.size()"<< std::endl;
        return -1;
    }

    if(exFIFO.isEmpty()){
        std::cout << "Error exFIFO.isEmpty()"<< std::endl;
        return -1;
    }
    if(exFIFO.peekBuffer(displayBuf,7) != 63){
        std::cout << "Error exFIFO.peekBuffer()" << std::endl;
        return -1;
    }
    if(exFIFO.popBuffer(displayBuf,7) != 63){
        std::cout << "Error exFIFO.popBuffer()" << std::endl;
        return -1;
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
    if(test_max_coverage()!= 0)
        return -1;

	return 0;
}
