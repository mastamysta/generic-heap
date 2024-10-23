#include "heap.hpp"

int main()
{
    Heap<int> h;

    h.insert(1);
    h.insert(2);
    h.insert(100);
    h.insert(50);

    return 0;
}
