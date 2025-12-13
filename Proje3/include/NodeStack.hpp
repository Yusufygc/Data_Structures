#ifndef NODESTACK_HPP
#define NODESTACK_HPP

#include "TreeNode.hpp"

// TreeNode* tutan basit bir stack (LIFO).
// STL yok, template yok.
class NodeStack
{
private:
    TreeNode** data;
    int capacity;
    int topIndex;

    void grow();

public:
    NodeStack(int initialCapacity);
    ~NodeStack();

    void push(TreeNode* node);
    TreeNode* pop();
    bool isEmpty() const;
};

#endif // NODESTACK_H
