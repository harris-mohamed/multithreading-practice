#include <iostream> 
#include <thread> 
#include <mutex>
#include <vector> 

#define MAX_THREADS std::thread::hardware_concurrency() 
#define ELEMENTS_TO_ADD 40

std::vector<int> buffer;  // Global buffer 
std::mutex mutex;         // Global mutex lock 

void removeFromBuffer()
{
    std::lock_guard<std::mutex> guard(mutex); 
    
    for (int i = 0; i < ELEMENTS_TO_ADD; i++)
    {
        if (!buffer.empty())
        {
            std::cout << "removeFrombuffer popped: " << buffer.back() << "\n";
            buffer.pop_back();
        } 
        else 
        {
          break;
        }
    }
}

void addToBuffer(int x)
{
    std::lock_guard<std::mutex> guard(mutex);
    
    for (int i = x; i < x + ELEMENTS_TO_ADD; i++)
    {
        std::cout << "addToBuffer added: " << i << "\n";
        buffer.push_back(i);
    }
}

int main()
{
    std::vector<std::thread> threads; 

    for (int i = 0; i < 50 * MAX_THREADS; i++)
    {
        buffer.push_back(i);
    }

    for (int i = 0; i < MAX_THREADS; i++)
    {
        if (i % 2 != 0)
        {
            threads.push_back(std::thread(addToBuffer, i));
        } 
        else
        {
            threads.push_back(std::thread(removeFromBuffer));
        }
    }

    for (auto &th: threads) 
    {
        th.join();
    }

    return 0;
}
