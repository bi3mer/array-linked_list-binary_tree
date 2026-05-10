#pragma once
#include <cstddef>
#include "linear_interface.hpp"

struct LLTNode
{
    int data;
    LLTNode* next;
};

class LinkedListTail : public LinearInterface
{
public:
    LinkedListTail();
    ~LinkedListTail() override;

    // O(1)
    void insert_front(int value) override;

    // O(1)
    void insert_back(int value) override;

    // insert value at a sorted index O(n)
    void insert_sorted(int value);

    void insert(int value) override;
    void insert(std::size_t index, int value) override;

    bool remove(int value) override;
    void remove_front() override;
    void remove_back() override;
    void remove_index(std::size_t index) override;

    int* find_element(int value) const override;

    // full node access, null if not found
    LLTNode* find(int value) const;

private:
    LLTNode* head;
    LLTNode* tail;
};
