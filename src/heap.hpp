#pragma once

#include <vector>

template <typename ValueType>
class Heap
{
public:
    using value_type = ValueType;

private:
    std::vector<value_type> data;
};
