#include <iostream>

#include "heap.hpp"

int main()
{
    Heap<int> h;

    h.insert(1);
    h.insert(2);
    h.insert(100);
    h.insert(50);
    
    for (int i = 0; i < 4; i++)
    {
        std::cout << h.peek() << std::endl;
        h.pop();
    }

    return 0;
}
