#pragma once
#include <cstddef>
#include "linear_interface.hpp"

class Array : public LinearInterface
{
public:
    explicit Array(int capacity);
    ~Array() override;

    // insert value at front O(n)
    void insert_front(int value) override;

    // insert value at back O(1)
    void insert_back(int value) override;

    // insert value at sorted position O(n)
    void insert_sorted(int value);

    void insert(int value) override;
    void insert(std::size_t index, int value) override;

    bool remove(int value) override;
    void remove_front() override;
    void remove_back() override;
    void remove_index(std::size_t index) override;

    int* find_element(int value) const override;

private:
    int* data;
    int size;
    int capacity;

    void shift_right(int index);
    void shift_left(int index);
};
