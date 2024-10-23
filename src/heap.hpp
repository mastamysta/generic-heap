#pragma once

#include <vector>
#include <cstdint>
#include <algorithm>
#include <optional>
#include <concepts>

template <typename T>
concept LessThanAble = requires (T t, T u)
{
    { t < u } -> std::same_as<bool>;
    { u < t } -> std::same_as<bool>;
};

template <LessThanAble ValueType>
class Heap;

template <LessThanAble ValueType>
class HeapIterator
{
public:
    using value_type = ValueType;
    using difference_type = int32_t;
    using iterator_categort = std::forward_iterator_tag;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    explicit HeapIterator() : index(1), data(nullptr) {}
    explicit HeapIterator(typename Heap<value_type>::size_type i, const std::vector<value_type>* d) : index(i), data(d) {}
    HeapIterator(const HeapIterator& other) : index(other.index), data(other.data) {}

    auto operator++() -> HeapIterator
    {
        index++;
        return *this;
    }

    auto operator++(int) -> HeapIterator
    {
        auto before = *this;
        index++;
        return before;
    }

    auto operator*() const -> const_reference
    {
        return (*data)[index];
    }

    auto operator->() const -> pointer
    {
        return &((*data)[index]);
    }

    friend auto operator==(HeapIterator lhs, HeapIterator rhs) -> bool
    {
        return lhs.index == rhs.index;
    }

    friend auto operator!=(HeapIterator lhs, HeapIterator rhs) -> bool
    {
        return lhs.index != rhs.index;
    }

private:
    const std::vector<value_type>* data;
    typename Heap<value_type>::size_type index;
};

template <LessThanAble ValueType>
class Heap
{
public:
    using value_type = ValueType;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using iterator = HeapIterator<value_type>;
    using const_iterator = const HeapIterator<value_type>;
    using difference_type = int32_t;

    explicit Heap()
    {
        // 1-indexed array is helpful for heap structure, but beware! Doing this in the
        // constructor constrains the value_type to default-constructible types only.
        data = std::vector<value_type>(1, value_type());
    }

    explicit Heap(const Heap& other)
    {
        data.resize(other.data.size());
        std::copy(other.data.begin(), other.data.end(), data.begin());
    }

    auto insert(const value_type& v) -> void
    {
        data.push_back(v);
        heapify(data.size() - 1);
    }

    auto peek() const -> const value_type&
    {
        return data[1];
    }

    auto pop() -> void
    {
        auto parent = 1;

        data[parent] = data.back();
        data.pop_back();

        while (true)
        {
            auto lchild = parent << 1, rchild = lchild + 1;

            if (lchild >= data.size())
                break; // Parent is a leaf, done!

            auto max_child_index = -1;
            
            if (rchild < data.size())
                max_child_index = data[rchild] < data[lchild] ? lchild : rchild;
            else
                max_child_index = lchild;

            if (data[parent] < data[max_child_index])
                std::swap(data[parent], data[max_child_index]);

            parent = max_child_index;
        }
    }

    auto size() const -> size_type
    {
        return data.size() - 1;
    }

    auto empty() const -> bool
    {
        return data.size() == 1;
    }

    auto clear() -> void
    {
        data.clear();
        data.push_back(value_type());
    }

    auto begin() const -> iterator
    {
        return iterator(1, &data);
    }

    auto end() const -> iterator
    {
        return iterator(data.size(), &data);
    }

private:
    std::vector<value_type> data;

    auto heapify(std::size_t item) -> void
    {
        if (item == 1)
            return;

        while (true)
        {
            std::size_t parent = -1;

            if (item & 0x01) // if odd
                parent = (item - 1) >> 1; // Parent is sub 1, divide by two
            else
                parent = item >> 1; // Just divide by two

            if (data[parent] < data[item])
                std::swap(data[item], data[parent]);
            else
                break;

            item = parent;

            if (item == 1)
                break;
        }
    }
};
