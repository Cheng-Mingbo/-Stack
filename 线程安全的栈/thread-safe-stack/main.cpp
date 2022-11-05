#include <iostream>
#include "threadsafe_stack.h"
#include <thread>
#include <unistd.h>


threadsafe_stack<int> iStack;

int main(int argc, char const *argv[])
{
    std::thread t1([](){
        std::cout << "thread 1 start..." << std::endl;
        for (int i = 0; i < 10; ++i) {
            iStack.push(i);
            usleep(110);
        }
        std::cout << "thread 1 ending..." << std::endl;
    });

    std::thread t2([](){
        std::cout << "thread 2 start..." << std::endl;
        try {
            while(true) {
                usleep(100);
                int ret = 0;
                iStack.pop(ret);

            }
        } catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        std::cout << "thread 2 ending..." << std::endl;
    });

    t1.join();
    t2.join();

    return 0;
}
