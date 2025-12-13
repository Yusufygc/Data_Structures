#include "NodeStack.hpp"
#include <iostream>

NodeStack::NodeStack(int initialCapacity)
{
    if (initialCapacity < 8) initialCapacity = 8;

    capacity = initialCapacity;
    topIndex = -1;
    data = new TreeNode*[capacity];

    for (int i = 0; i < capacity; i++)
        data[i] = 0;
}

NodeStack::~NodeStack()
{
    delete[] data;
    data = 0;
    capacity = 0;
    topIndex = -1;
}

bool NodeStack::isEmpty() const
{
    return topIndex < 0;
}

void NodeStack::grow()
{
    int newCapacity = capacity * 2;
    TreeNode** newData = new TreeNode*[newCapacity];

    for (int i = 0; i < newCapacity; i++)
        newData[i] = 0;

    for (int i = 0; i <= topIndex; i++)
        newData[i] = data[i];

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void NodeStack::push(TreeNode* node)
{
    if (topIndex + 1 >= capacity)
        grow();

    topIndex++;
    data[topIndex] = node;
}

TreeNode* NodeStack::pop()
{
    if (isEmpty())
        return 0;

    TreeNode* node = data[topIndex];
    data[topIndex] = 0;
    topIndex--;
    return node;
}
