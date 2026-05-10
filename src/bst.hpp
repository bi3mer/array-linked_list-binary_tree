#pragma once
#include "sorted_interface.hpp"

struct BSTNode
{
    int data;
    BSTNode* left;
    BSTNode* right;
};

class BST : public SortedInterface
{
public:
    BST();
    ~BST() override;

    void insert(int value) override;
    bool remove(int value) override;
    int* find_element(int value) const override;

    // full node access, null if not found
    BSTNode* find(int value) const;

private:
    BSTNode* root;

    BSTNode* do_insert(BSTNode* node, int value);
    BSTNode* erase(BSTNode* node, int value, bool& removed);
    BSTNode* min_node(BSTNode* node) const;
    BSTNode* search(BSTNode* node, int value) const;
    void destroy(BSTNode* node);
};
