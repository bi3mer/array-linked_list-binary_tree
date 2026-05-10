#pragma once
#include <cstddef>

class LinearInterface
{
public:
    virtual ~LinearInterface() = default;

    virtual void insert(int value) = 0;
    virtual void insert(std::size_t index, int value) = 0;
    virtual void insert_front(int value) = 0;
    virtual void insert_back(int value) = 0;

    virtual bool remove(int value) = 0;
    virtual void remove_front() = 0;
    virtual void remove_back() = 0;
    virtual void remove_index(std::size_t index) = 0;

    virtual int* find_element(int value) const = 0;
};
