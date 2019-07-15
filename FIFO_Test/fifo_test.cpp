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
        std::cout << "Error exFIFO.size()"<< exFIFO.size()<< std::endl;
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
    if(exFIFO.peekString(displayBuf, 50) != 0){
        std::cout << "Error exFIFO.peekString()"<< std::endl;
        return -1;
    }
    if(exFIFO.popString(displayBuf, 50) != 0){
        std::cout << "Error exFIFO.popString()"<< std::endl;
        return -1;
    }
    return 0;
}
int test_random_input(){
    FIFO exFIFO;
	uint8_t displayBuf[50];
	int test1 = getSize();
	int test2 = getSize();
	int test3 = getSize();
	int test4 = getSize();
	int test5 = getSize();
	int test6 = getSize();
	int test7 = getSize();
	int test8 = getSize();
	int test9 = getSize();
	char ex1[test1];
	fillTab(ex1, '1', sizeof(ex1));
	fillFifo(& exFIFO,ex1,sizeof(ex1));
	char ex2[getSize()];
	fillTab(ex2, '2', sizeof(ex2));
	fillFifo(&exFIFO, ex2, sizeof(ex2));
	char ex3[getSize()];
	fillTab(ex3, '3', sizeof(ex3));
	fillFifo(&exFIFO, ex3, sizeof(ex3));
	char ex4[getSize()];
	fillTab(ex4, '4', sizeof(ex4));
	fillFifo(&exFIFO, ex4, sizeof(ex4));
	char ex5[getSize()];
	fillTab(ex5, '5', sizeof(ex5));
	fillFifo(&exFIFO, ex5, sizeof(ex5));
	char ex6[getSize()];
	fillTab(ex6, '6', sizeof(ex6));
	fillFifo(&exFIFO, ex6, sizeof(ex6));
	char ex7[getSize()];
	fillTab(ex7, '7', sizeof(ex7));
	fillFifo(&exFIFO, ex7, sizeof(ex7));
	char ex8[getSize()];
	fillTab(ex8, '8', sizeof(ex8));
	fillFifo(&exFIFO, ex8, sizeof(ex8));
	char ex9[getSize()];
	fillTab(ex9, '9', sizeof(ex9));
	fillFifo(&exFIFO, ex9, sizeof(ex9));
	while(!(exFIFO.isEmpty())) {
        uint8_t test = exFIFO.peek();
        exFIFO.popString(displayBuf, test);
        display(displayBuf, test);
    }
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

	return 0;
}



