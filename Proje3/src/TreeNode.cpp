#include "TreeNode.hpp"

// Basit düğüm kurucusu.
TreeNode::TreeNode(int value)
{
    this->value = value;
    this->left = 0;
    this->right = 0;
}

// Yıkıcı: Çocukları burada silmiyoruz; bu iş BinarySearchTree tarafından yapılacak.
// Böylece ağaç yönetimi tek bir sınıfta toplanmış olur.
TreeNode::~TreeNode()
{
    // Boş; yönetim BinarySearchTree'de.
}
