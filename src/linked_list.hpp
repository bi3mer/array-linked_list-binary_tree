#pragma once
#include <cstddef>
#include "linear_interface.hpp"

struct LLNode
{
    int data;
    LLNode* next;
};

class LinkedList : public LinearInterface
{
public:
    LinkedList();
    ~LinkedList() override;

    // insert value at the front of the list O(1)
    void insert_front(int value) override;

    // insert value at the end of the list O(n)
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
    LLNode* find(int value) const;

private:
    LLNode* head;
};
