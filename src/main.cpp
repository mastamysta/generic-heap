#include <iostream>

#include "heap.hpp"

int main()
{
    Heap<int> h;

    h.insert(1);
    h.insert(2);
    h.insert(100);
    h.insert(50);

    auto cc = Heap<int>(h);

    while (!h.empty())
    {
        std::cout << h.peek() << std::endl;
        h.pop();
    }

    for (auto i: cc)
        std::cout << i << std::endl;

    return 0;
}
