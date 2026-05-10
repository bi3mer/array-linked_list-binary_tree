#include "doubly_linked_list.hpp"
#include <cassert>

DoublyLinkedList::DoublyLinkedList() : head(nullptr) {}

DoublyLinkedList::~DoublyLinkedList()
{
    LLDNode* curr = head;
    while (curr != nullptr)
    {
        LLDNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

void DoublyLinkedList::insert(int value)
{
    insert_back(value);
}

void DoublyLinkedList::insert_front(int value)
{
    LLDNode* node = new LLDNode{value, head, nullptr};
    if (head != nullptr)
    {
        head->prev = node;
    }
    head = node;
}

void DoublyLinkedList::insert_back(int value)
{
    LLDNode* node = new LLDNode{value, nullptr, nullptr};
    if (head == nullptr)
    {
        head = node;
        return;
    }
    LLDNode* curr = head;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = node;
    node->prev = curr;
}

void DoublyLinkedList::insert_sorted(int value)
{
    if (head == nullptr || value <= head->data)
    {
        insert_front(value);
        return;
    }
    LLDNode* curr = head;
    while (curr->next != nullptr && curr->next->data < value)
    {
        curr = curr->next;
    }
    LLDNode* node = new LLDNode{value, curr->next, curr};
    if (curr->next != nullptr)
    {
        curr->next->prev = node;
    }
    curr->next = node;
}

void DoublyLinkedList::insert(std::size_t index, int value)
{
    if (index == 0)
    {
        insert_front(value);
        return;
    }
    LLDNode* curr = head;
    for (std::size_t i = 0; i < index - 1; ++i)
    {
        assert(curr != nullptr);
        curr = curr->next;
    }
    assert(curr != nullptr);
    LLDNode* node = new LLDNode{value, curr->next, curr};
    if (curr->next != nullptr)
    {
        curr->next->prev = node;
    }
    curr->next = node;
}

void DoublyLinkedList::remove_front()
{
    assert(head != nullptr);
    LLDNode* tmp = head;
    head = head->next;
    if (head != nullptr)
    {
        head->prev = nullptr;
    }
    delete tmp;
}

void DoublyLinkedList::remove_back()
{
    assert(head != nullptr);
    LLDNode* curr = head;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    if (curr->prev != nullptr)
    {
        curr->prev->next = nullptr;
    }
    else
    {
        head = nullptr;
    }
    delete curr;
}

void DoublyLinkedList::remove_index(std::size_t index)
{
    assert(head != nullptr);
    if (index == 0)
    {
        remove_front();
        return;
    }
    LLDNode* curr = head;
    for (std::size_t i = 0; i < index; ++i)
    {
        assert(curr != nullptr);
        curr = curr->next;
    }
    assert(curr != nullptr);
    curr->prev->next = curr->next;
    if (curr->next != nullptr)
    {
        curr->next->prev = curr->prev;
    }
    delete curr;
}

bool DoublyLinkedList::remove(int value)
{
    LLDNode* curr = head;
    while (curr != nullptr)
    {
        if (curr->data == value)
        {
            if (curr->prev != nullptr)
            {
                curr->prev->next = curr->next;
            }
            else
            {
                head = curr->next;
            }
            if (curr->next != nullptr)
            {
                curr->next->prev = curr->prev;
            }
            delete curr;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

int* DoublyLinkedList::find_element(int value) const
{
    LLDNode* curr = head;
    while (curr != nullptr)
    {
        if (curr->data == value)
        {
            return &curr->data;
        }
        curr = curr->next;
    }
    return nullptr;
}

LLDNode* DoublyLinkedList::find(int value) const
{
    LLDNode* curr = head;
    while (curr != nullptr)
    {
        if (curr->data == value)
        {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}
