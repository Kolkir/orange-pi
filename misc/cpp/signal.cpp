#include <signal.h>
#include <errno.h>

#include <iostream>
#include <thread>
#include <chrono>

void tfunc(pthread_t tid){
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    pthread_kill(tid, SIGUSR1);
    std::cout << "thread end\n";
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
    std::cout << "Waiting for a SIGINT signal\n";

    pthread_t tid = pthread_self();
    std::thread t([&](){tfunc(tid);});

    ret_val = sigwait(&set,sigptr);
    if(ret_val == -1)
        perror("sigwait failed\n");
    else {
        std::cout << "sigwait returned with sig: " << *sigptr << std::endl;
    }

    t.join();

    return 0;
}
