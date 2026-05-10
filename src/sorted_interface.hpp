#pragma once

class SortedInterface
{
public:
    virtual ~SortedInterface() = default;

    virtual void insert(int value) = 0;
    virtual bool remove(int value) = 0;
    virtual int* find_element(int value) const = 0;
};
