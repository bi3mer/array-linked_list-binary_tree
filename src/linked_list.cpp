#include "linked_list.hpp"
#include <cassert>

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList()
{
    LLNode* curr = head;
    while (curr != nullptr)
    {
        LLNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

void LinkedList::insert(int value)
{
    insert_back(value);
}

void LinkedList::insert(std::size_t index, int value)
{
    if (index == 0)
    {
        insert_front(value);
        return;
    }
    LLNode* curr = head;
    for (std::size_t i = 0; i < index - 1; ++i)
    {
        assert(curr != nullptr);
        curr = curr->next;
    }
    assert(curr != nullptr);
    curr->next = new LLNode{value, curr->next};
}

void LinkedList::insert_front(int value)
{
    head = new LLNode{value, head};
}

void LinkedList::insert_back(int value)
{
    LLNode* node = new LLNode{value, nullptr};
    if (head == nullptr)
    {
        head = node;
        return;
    }
    LLNode* curr = head;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = node;
}

void LinkedList::insert_sorted(int value)
{
    LLNode* node = new LLNode{value, nullptr};
    if (head == nullptr || value <= head->data)
    {
        node->next = head;
        head = node;
        return;
    }
    LLNode* curr = head;
    while (curr->next != nullptr && curr->next->data < value)
    {
        curr = curr->next;
    }
    node->next = curr->next;
    curr->next = node;
}

void LinkedList::remove_front()
{
    assert(head != nullptr);
    LLNode* tmp = head;
    head = head->next;
    delete tmp;
}

void LinkedList::remove_back()
{
    assert(head != nullptr);
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }
    LLNode* curr = head;
    while (curr->next->next != nullptr)
    {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
}

void LinkedList::remove_index(std::size_t index)
{
    assert(head != nullptr);
    if (index == 0)
    {
        remove_front();
        return;
    }
    LLNode* curr = head;
    for (std::size_t i = 0; i < index - 1; ++i)
    {
        assert(curr->next != nullptr);
        curr = curr->next;
    }
    assert(curr->next != nullptr);
    LLNode* tmp = curr->next;
    curr->next = tmp->next;
    delete tmp;
}

bool LinkedList::remove(int value)
{
    if (head == nullptr)
    {
        return false;
    }
    if (head->data == value)
    {
        LLNode* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }
    LLNode* curr = head;
    while (curr->next != nullptr)
    {
        if (curr->next->data == value)
        {
            LLNode* tmp = curr->next;
            curr->next = tmp->next;
            delete tmp;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

int* LinkedList::find_element(int value) const
{
    LLNode* curr = head;
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

LLNode* LinkedList::find(int value) const
{
    LLNode* curr = head;
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
