#pragma once
#include <cstddef>
#include "linear_interface.hpp"

struct LLDNode
{
    int data;
    LLDNode* next;
    LLDNode* prev;
};

class DoublyLinkedList : public LinearInterface
{
public:
    DoublyLinkedList();
    ~DoublyLinkedList() override;

    // O(1)
    void insert_front(int value) override;

    // O(n)
    void insert_back(int value) override;

    // O(n)
    void insert_sorted(int value);

    void insert(int value) override;
    void insert(std::size_t index, int value) override;

    bool remove(int value) override;

    // O(1)
    void remove_front() override;

    // O(n)
    void remove_back() override;

    void remove_index(std::size_t index) override;

    int* find_element(int value) const override;
    LLDNode* find(int value) const;

private:
    LLDNode* head;
};
