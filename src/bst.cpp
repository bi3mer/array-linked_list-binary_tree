#include "bst.hpp"

BST::BST() : root(nullptr) {}

BST::~BST()
{
    destroy(root);
}

void BST::destroy(BSTNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void BST::insert(int value)
{
    root = do_insert(root, value);
}

BSTNode* BST::do_insert(BSTNode* node, int value)
{
    if (node == nullptr)
    {
        return new BSTNode{value, nullptr, nullptr};
    }
    if (value < node->data)
    {
        node->left = do_insert(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = do_insert(node->right, value);
    }
    return node;
}

bool BST::remove(int value)
{
    bool removed = false;
    root = erase(root, value, removed);
    return removed;
}

BSTNode* BST::erase(BSTNode* node, int value, bool& removed)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (value < node->data)
    {
        node->left = erase(node->left, value, removed);
    }
    else if (value > node->data)
    {
        node->right = erase(node->right, value, removed);
    }
    else
    {
        removed = true;
        if (node->left == nullptr)
        {
            BSTNode* tmp = node->right;
            delete node;
            return tmp;
        }
        if (node->right == nullptr)
        {
            BSTNode* tmp = node->left;
            delete node;
            return tmp;
        }
        // replace with in-order successor
        BSTNode* successor = min_node(node->right);
        node->data = successor->data;
        node->right = erase(node->right, successor->data, removed);
    }
    return node;
}

BSTNode* BST::min_node(BSTNode* node) const
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

int* BST::find_element(int value) const
{
    BSTNode* node = search(root, value);
    return node ? &node->data : nullptr;
}

BSTNode* BST::find(int value) const
{
    return search(root, value);
}

BSTNode* BST::search(BSTNode* node, int value) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (value == node->data)
    {
        return node;
    }
    if (value < node->data)
    {
        return search(node->left, value);
    }
    return search(node->right, value);
}
