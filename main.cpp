#include <iostream>
#include <thread>
#include "inc/dllWhitelist.cpp"
#include "inc/Sleep.h"

int main()
{
    std::cout << "Starting POC..." << std::endl;
    
    std::thread t(ForceDllWhitelist, 500);
    t.detach();

    customSleep(5000); // Sleep for 5 seconds

    std::cout << "POC finished." << std::endl;
    return 0;
}