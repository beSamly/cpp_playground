#include <iostream>
#include "ThreadManager.h"
#include <chrono>

int main()
{
    
    auto current_hardware_concurrency = std::thread::hardware_concurrency(); // return number of logical core(usually twice of physical core)
    ThreadManager thread_manager;
    for (int i = 0; i < 20; i++) {
        thread_manager.Start([](auto LThreadId) {
            while (true) {
				std::cout << "Thread id is " << LThreadId << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        });
    }
    thread_manager.Join();
}
