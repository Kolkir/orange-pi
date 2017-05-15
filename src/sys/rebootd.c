#include <wiringPi.h>

#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/reboot.h>
#include <stdio.h>

void gpio4Callback(void) {
    sync();
    reboot(RB_AUTOBOOT);
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
    sigprocmask( SIG_BLOCK, &set, NULL );

    wiringPiSetup () ;

    wiringPiISR (4, INT_EDGE_FALLING, &gpio4Callback) ;

    ret_val = sigwait(&set,sigptr);
    if(ret_val == -1)
        perror("sigwait failed\n");

    return 0;
}
