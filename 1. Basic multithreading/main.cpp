#include <iostream> 
#include <thread> 

void simple_thread()
{
    std::cout << "Thread!\n";  
}

int main()
{
    std::cout << "This CPU has " << std::thread::hardware_concurrency() << " available threads" << std::endl; // How many threads? 
    
    std::thread t1(&simple_thread);  // Defining the callable by using a function
    
    std::thread t2([]()   // Defining the callable by using a lambda function
    {
        std::cout << "Thread with lambda function!" << std::endl; 
    }
    );

    if (t1.joinable())
    {
        t1.join();
    }
    
    if (t2.joinable())
    {
        t2.join();
    }

    return 0;
}
