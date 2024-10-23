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

    for (const auto& i: cc)
        std::cout << i << std::endl;

    cc.clear();

    cc.insert(1000);
    cc.insert(100);
    cc.insert(10000);
    cc.insert(100000);
    cc.insert(1000000);
    cc.insert(1);

    for (const auto& i: cc)
        std::cout << i << std::endl; // We should NOT expect iteration to go greatest to largest!

    while (!cc.empty())
    {
        std::cout << cc.peek() << std::endl; // This will generate correct in-order behaviour.
        cc.pop();
    }

    return 0;
}
