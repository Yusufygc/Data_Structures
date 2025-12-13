#include "BinarySearchTree.hpp"
#include "NodeStack.hpp"
#include <iostream> // Debug çıktıları için kullanacağız.

// Kurucu: başlangıçta ağaç boş.
BinarySearchTree::BinarySearchTree()
{
    root = 0;
    nodeCount = 0;
}

// Yıkıcı: tüm düğümleri serbest bırak.
BinarySearchTree::~BinarySearchTree()
{
    clearIterative();
}

// Ağaçtaki tüm düğümleri recursive olarak siler.
void BinarySearchTree::destroyRecursive(TreeNode* node)
{
    if (node == 0)
    {
        return;
    }

    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
}

// Dışarıdan insert çağrısı.
void BinarySearchTree::insert(int value)
{
    root = insertRecursive(root, value);
}

// BST ekleme kuralı: < sol, > sağ, == sol (özelleştirilmiş kural).
TreeNode* BinarySearchTree::insertRecursive(TreeNode* node, int value)
{
    if (node == 0)
    {
        nodeCount++;
        TreeNode* newNode = new TreeNode(value);
        return newNode;
    }

    if (value < node->value)
    {
        node->left = insertRecursive(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = insertRecursive(node->right, value);
    }
    else
    {
        // value == node->value durumu: sol tarafa ekle.
        node->left = insertRecursive(node->left, value);
    }

    return node;
}

// Kök değeri (ağaç boşsa -1 döndürüyoruz; sen istersen başka sentinel de seçebilirsin).
int BinarySearchTree::getRootValue() const
{
    if (root == 0)
    {
        return -1;
    }
    return root->value;
}

// Yükseklik hesaplama (boş ağaç için 0).
int BinarySearchTree::getHeight() const
{
    return heightRecursive(root);
}

// Recursive yükseklik fonksiyonu.
int BinarySearchTree::heightRecursive(TreeNode* node) const
{
    if (node == 0)
    {
        return 0;
    }

    int leftHeight = heightRecursive(node->left);
    int rightHeight = heightRecursive(node->right);

    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
}

// Node sayısı (debug ve extract için faydalı).
int BinarySearchTree::getNodeCount() const
{
    return nodeCount;
}

// Ağaç boş mu?
bool BinarySearchTree::isEmpty() const
{
    return root == 0;
}

// Bütün verileri postorder sıralama ile buffer'a yazar ve ağacı tamamen boşaltır.
// buffer kapasitesini aşmamak için maxCount kullanılır.
void BinarySearchTree::extractAllPostOrder(int* buffer, int maxCount, int& outCount)
{
    outCount = 0;

    if (root == 0 || maxCount <= 0)
    {
        return;
    }

    extractPostOrderRecursive(root, buffer, outCount);

    // Bütün düğümleri sildikten sonra kökü sıfırla.
    root = 0;
    nodeCount = 0;
}

// Postorder: sol, sağ, kök.
// Her düğüm için değeri buffer'a yazıp düğümü sileriz.
void BinarySearchTree::extractPostOrderRecursive(TreeNode* node, int* buffer, int& index)
{
    if (node == 0)
    {
        return;
    }

    extractPostOrderRecursive(node->left, buffer, index);
    extractPostOrderRecursive(node->right, buffer, index);

    // Kökteyiz: değeri buffer'a koy.
    buffer[index] = node->value;
    index++;

    delete node;
}

void BinarySearchTree::clearIterative()
{
    if (root == 0)
    {
        nodeCount = 0;
        return;
    }

    // Postorder delete için 2 stack tekniği (rekürsiyonsuz).
    NodeStack s1(128);
    NodeStack s2(128);

    s1.push(root);

    while (!s1.isEmpty())
    {
        TreeNode* n = s1.pop();
        s2.push(n);

        if (n->left != 0)  s1.push(n->left);
        if (n->right != 0) s1.push(n->right);
    }

    while (!s2.isEmpty())
    {
        TreeNode* n = s2.pop();
        delete n;
    }

    root = 0;
    nodeCount = 0;
}