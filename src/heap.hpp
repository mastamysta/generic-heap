#pragma once

#include <vector>
#include <cstdint>

template <typename ValueType>
class Heap
{
public:
    using value_type = ValueType;

    Heap()
    {
        // 1-indexed array is helpful for heap structure, but beware! Doing this in the
        // constructor constrains the value_type to default-constructible types only.
        data = std::vector<value_type>(1);
    }

    auto insert(value_type v) -> void
    {
        data.push_back(v);
        heapify(data.size() - 1);
    }

private:
    std::vector<value_type> data;

    auto heapify(std::size_t item) -> void
    {
        while (true)
        {
            std::size_t parent = -1;

            if (item & 0x01) // if odd
                parent = (item & 0x01) >> 1; // Parent is sub 1, divide by two
            else
                parent = item >> 1; // Just divide by two

            if (data[item] > data[parent])
                std::swap(data[item], data[parent]);
            else
                break;

            item = parent;

            if (item == 1)
                break;
        }
    }
};
