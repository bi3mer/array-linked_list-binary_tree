#include "sorted_array.hpp"
#include <cassert>

SortedArray::SortedArray(int capacity)
    : data(nullptr), size(0), capacity(capacity)
{
    assert(capacity > 0);
    data = new int[capacity];
}

SortedArray::~SortedArray()
{
    delete[] data;
}

void SortedArray::shift_right(int index)
{
    for (int i = size; i > index; --i)
    {
        data[i] = data[i - 1];
    }
}

void SortedArray::shift_left(int index)
{
    for (int i = index; i < size - 1; ++i)
    {
        data[i] = data[i + 1];
    }
}

void SortedArray::insert(int value)
{
    assert(size < capacity);
    int lo = 0;
    int hi = size;
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (data[mid] < value)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }
    shift_right(lo);
    data[lo] = value;
    ++size;
}

bool SortedArray::remove(int value)
{
    int* found = find_element(value);
    if (found == nullptr)
    {
        return false;
    }
    shift_left(static_cast<int>(found - data));
    --size;
    return true;
}

int* SortedArray::find_element(int value) const
{
    int lo = 0;
    int hi = size - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (data[mid] == value)
        {
            return &data[mid];
        }
        if (data[mid] < value)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }
    }
    return nullptr;
}
