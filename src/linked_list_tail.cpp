#include "linked_list_tail.hpp"
#include <cassert>

LinkedListTail::LinkedListTail() : head(nullptr), tail(nullptr) {}

LinkedListTail::~LinkedListTail()
{
    LLTNode* curr = head;
    while (curr != nullptr)
    {
        LLTNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

void LinkedListTail::insert(int value)
{
    insert_back(value);
}

void LinkedListTail::insert(std::size_t index, int value)
{
    if (index == 0)
    {
        insert_front(value);
        return;
    }
    LLTNode* curr = head;
    for (std::size_t i = 0; i < index - 1; ++i)
    {
        assert(curr != nullptr);
        curr = curr->next;
    }
    assert(curr != nullptr);
    LLTNode* node = new LLTNode{value, curr->next};
    curr->next = node;
    if (node->next == nullptr)
    {
        tail = node;
    }
}

void LinkedListTail::insert_front(int value)
{
    LLTNode* node = new LLTNode{value, head};
    if (head == nullptr)
    {
        tail = node;
    }
    head = node;
}

void LinkedListTail::insert_back(int value)
{
    LLTNode* node = new LLTNode{value, nullptr};
    if (tail != nullptr)
    {
        tail->next = node;
    }
    else
    {
        head = node;
    }
    tail = node;
}

void LinkedListTail::insert_sorted(int value)
{
    if (head == nullptr || value <= head->data)
    {
        insert_front(value);
        return;
    }
    if (value >= tail->data)
    {
        insert_back(value);
        return;
    }
    LLTNode* curr = head;
    while (curr->next != nullptr && curr->next->data < value)
    {
        curr = curr->next;
    }
    curr->next = new LLTNode{value, curr->next};
}

void LinkedListTail::remove_front()
{
    assert(head != nullptr);
    LLTNode* tmp = head;
    head = head->next;
    if (head == nullptr)
    {
        tail = nullptr;
    }
    delete tmp;
}

void LinkedListTail::remove_back()
{
    assert(head != nullptr);
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    LLTNode* curr = head;
    while (curr->next != tail)
    {
        curr = curr->next;
    }
    delete tail;
    curr->next = nullptr;
    tail = curr;
}

void LinkedListTail::remove_index(std::size_t index)
{
    assert(head != nullptr);
    if (index == 0)
    {
        remove_front();
        return;
    }
    LLTNode* curr = head;
    for (std::size_t i = 0; i < index - 1; ++i)
    {
        assert(curr->next != nullptr);
        curr = curr->next;
    }
    assert(curr->next != nullptr);
    LLTNode* tmp = curr->next;
    curr->next = tmp->next;
    if (tmp == tail)
    {
        tail = curr;
    }
    delete tmp;
}

bool LinkedListTail::remove(int value)
{
    if (head == nullptr)
    {
        return false;
    }
    if (head->data == value)
    {
        LLTNode* tmp = head;
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        delete tmp;
        return true;
    }
    LLTNode* curr = head;
    while (curr->next != nullptr)
    {
        if (curr->next->data == value)
        {
            LLTNode* tmp = curr->next;
            curr->next = tmp->next;
            if (tmp == tail)
            {
                tail = curr;
            }
            delete tmp;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

int* LinkedListTail::find_element(int value) const
{
    LLTNode* curr = head;
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

LLTNode* LinkedListTail::find(int value) const
{
    LLTNode* curr = head;
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
