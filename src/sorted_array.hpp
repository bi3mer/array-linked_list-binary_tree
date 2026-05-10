#pragma once
#include "sorted_interface.hpp"

class SortedArray : public SortedInterface
{
public:
    explicit SortedArray(int capacity);
    ~SortedArray() override;

    // always inserts at sorted position O(n)
    void insert(int value) override;

    // true if value found and removed, else false O(n)
    bool remove(int value) override;

    // binary search O(log n)
    int* find_element(int value) const override;

private:
    int* data;
    int size;
    int capacity;

    void shift_right(int index);
    void shift_left(int index);
};
