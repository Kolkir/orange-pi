extern "C" {
#include <wiringPi.h>
}

#include <signal.h>
#include <errno.h>

#include <iostream>
#include <thread>
#include <chrono>

void gpio4Callback(void) {
    std::cout << "Hello" << std::endl;   
}

int main(){
    sigset_t set;
    int sig;
    int *sigptr = &sig;
    int ret_val;
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    sigaddset(&set, SIGUSR1);
    sigprocmask( SIG_BLOCK, &set, NULL );
    std::cout << "Waiting for a signal or button\n";

    wiringPiSetup () ;

    wiringPiISR (4, INT_EDGE_FALLING, &gpio4Callback) ;

    ret_val = sigwait(&set,sigptr);
    if(ret_val == -1)
        perror("sigwait failed\n");
    else {
        std::cout << "sigwait returned with sig: " << *sigptr << std::endl;
    }

    return 0;
}
