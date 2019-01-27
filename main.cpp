#include <iostream>
#include <thread>

#include "flat_timer.h"

using namespace std::literals;

int main()
{
    std::cout << "Hello world!\n" << std::flush;

    flat_timer timerInterval;
    flat_timer timerTimeout;

    timerInterval.set_interval([]{
        std::cout << "Hello " << std::flush;
    }, 2s);

    timerTimeout.set_timeout([&timerTimeout, &timerInterval]{
        std::cout << "World!\n" << std::flush;
        timerTimeout.set_timeout([&timerInterval]{
            std::cout << "Cpp!\n" << std::flush;
            timerInterval.stop();
        }, 2s);
    }, 2s);

    while(true){
        timerInterval.update();
        timerTimeout.update();
    }

    std::thread th([&timerInterval](){
        while(true){
            std::this_thread::sleep_for(timerInterval.remainder());
            timerInterval.update();
        }
    });
    th.detach();

    while(true);

    return 0;
}
