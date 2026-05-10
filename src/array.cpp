#include "array.hpp"
#include <stdexcept>

Array::Array(int capacity)
    : data(nullptr), size(0), capacity(capacity)
{
    if (capacity <= 0)
    {
        throw std::invalid_argument("capacity must be greater than 0");
    }
    data = new int[capacity];
}

Array::~Array()
{
    delete[] data;
}

void Array::shift_right(int index)
{
    for (int i = size; i > index; --i)
    {
        data[i] = data[i - 1];
    }
}

void Array::shift_left(int index)
{
    for (int i = index; i < size - 1; ++i)
    {
        data[i] = data[i + 1];
    }
}

void Array::insert(int value)
{
    insert_back(value);
}

void Array::insert(std::size_t index, int value)
{
    if (static_cast<int>(index) > size)
    {
        throw std::out_of_range("index out of range");
    }
    if (size == capacity)
    {
        throw std::length_error("array is full");
    }
    shift_right(static_cast<int>(index));
    data[index] = value;
    ++size;
}

void Array::insert_front(int value)
{
    if (size == capacity)
    {
        throw std::length_error("array is full");
    }
    shift_right(0);
    data[0] = value;
    ++size;
}

void Array::insert_back(int value)
{
    if (size == capacity)
    {
        throw std::length_error("array is full");
    }
    data[size++] = value;
}

void Array::insert_sorted(int value)
{
    if (size == capacity)
    {
        throw std::length_error("array is full");
    }
    int index = 0;
    while (index < size && data[index] < value)
    {
        ++index;
    }
    shift_right(index);
    data[index] = value;
    ++size;
}

void Array::remove_front()
{
    if (size == 0)
    {
        throw std::underflow_error("array is empty");
    }
    shift_left(0);
    --size;
}

void Array::remove_back()
{
    if (size == 0)
    {
        throw std::underflow_error("array is empty");
    }
    --size;
}

void Array::remove_index(std::size_t index)
{
    if (static_cast<int>(index) >= size)
    {
        throw std::out_of_range("index out of range");
    }
    shift_left(static_cast<int>(index));
    --size;
}

bool Array::remove(int value)
{
    for (int i = 0; i < size; ++i)
    {
        if (data[i] == value)
        {
            shift_left(i);
            --size;
            return true;
        }
    }
    return false;
}

int* Array::find_element(int value) const
{
    for (int i = 0; i < size; ++i)
    {
        if (data[i] == value)
        {
            return &data[i];
        }
    }
    return nullptr;
}
