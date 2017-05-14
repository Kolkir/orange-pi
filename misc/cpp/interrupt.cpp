extern "C" {
#include <wiringPi.h>
}
#include <iostream>

bool flag = false;

void myInterrupt0 (void) { flag = true; }

int main(int arcg, char* argv[]) {

    wiringPiSetup () ;

    wiringPiISR (4, INT_EDGE_FALLING, &myInterrupt0) ;

    while(!flag){
    	std::cout << "wait\n";
    }
    
    return 0;
}
