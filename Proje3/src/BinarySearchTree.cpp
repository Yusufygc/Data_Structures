/**
* @file BinarySearchTree.cpp
* @description : İkili Arama Ağacı (BST) sınıfının fonksiyon gövdelerini içeren dosya.
* Ağaca ekleme, silme, postorder dolaşma gibi işlemleri burada gerçekleştirdim.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include "BinarySearchTree.hpp"
#include "NodeStack.hpp"
#include <iostream>


BinarySearchTree::BinarySearchTree()
{
    root = 0;       
    nodeCount = 0;  
}

BinarySearchTree::~BinarySearchTree()
{
    clearIterative();
}

// Yardımcı fonksiyon: Verilen düğümü ve altındakileri recursive olarak sildim.
void BinarySearchTree::destroyRecursive(TreeNode* node)
{
    if (node == 0)
    {
        return;
    }

    // Önce çocukları sildim, sonra düğümün kendisini sildim (Postorder mantığı).
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
}

// Dışarıdan çağrılan ekleme fonksiyonu. İşlemi recursive yardımcıya devrettim.
void BinarySearchTree::insert(int value)
{
    root = insertRecursive(root, value);
}

// Recursive ekleme mantığını burada kurdum.
// Kural: Küçükse sola, büyükse sağa, eşitse sola ekledim (Proje isteri).
TreeNode* BinarySearchTree::insertRecursive(TreeNode* node, int value)
{
    // Eğer yer boşsa yeni düğümü burada oluşturdum.
    if (node == 0)
    {
        nodeCount++; // Toplam düğüm sayısını artırdım.
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
        // Eşitlik durumu: Proje kuralı gereği sol tarafa ekleme yaptım.
        node->left = insertRecursive(node->left, value);
    }

    return node;
}

// Ağacın kök değerini döndürdüm. Ağaç boşsa hata kodu olarak -1 döndürdüm.
int BinarySearchTree::getRootValue() const
{
    if (root == 0)
    {
        return -1;
    }
    return root->value;
}

// Ağacın yüksekliğini hesaplamak için yardımcı fonksiyonu çağırdım.
int BinarySearchTree::getHeight() const
{
    return heightRecursive(root);
}

// Yüksekliği recursive olarak hesapladım.
// Her düğüm için sol ve sağın yüksekliğine bakıp büyük olanı seçtim ve 1 ekledim.
int BinarySearchTree::heightRecursive(TreeNode* node) const
{
    if (node == 0)
    {
        return 0; // Boş düğümün yüksekliği 0.
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

// toplam düğüm sayısı
int BinarySearchTree::getNodeCount() const
{
    return nodeCount;
}

// Ağacın boş olup olmadığının kontrolu 
bool BinarySearchTree::isEmpty() const
{
    return root == 0;
}

// Projenin en kritik fonksiyonlarından biri.
// Ağaçtaki tüm verileri Postorder sırayla alıp buffer dizisine kaydettim ve düğümleri sildim.
void BinarySearchTree::extractAllPostOrder(int* buffer, int maxCount, int& outCount)
{
    outCount = 0;

    // Ağaç boşsa veya buffer yoksa işlem yapmadan çıktım.
    if (root == 0 || maxCount <= 0)
    {
        return;
    }

    extractPostOrderRecursive(root, buffer, outCount);

    // İşlem bitince ağacı tamamen sıfırladım.
    root = 0;
    nodeCount = 0;
}

// Postorder dolaşma (Sol -> Sağ -> Kök) mantığıyla verileri alıp sildim.
void BinarySearchTree::extractPostOrderRecursive(TreeNode* node, int* buffer, int& index)
{
    if (node == 0)
    {
        return;
    }

    // Önce sol ve sağ alt ağaçları işledim.
    extractPostOrderRecursive(node->left, buffer, index);
    extractPostOrderRecursive(node->right, buffer, index);

    // En son kök düğümün verisini buffer'a aldım.
    buffer[index] = node->value;
    index++;

    // Veriyi aldıktan sonra düğümü bellekten sildim.
    delete node;
}

// Ağacı iteratif (döngüsel) olarak temizlemek için bu fonksiyonu yazdım.
// Recursive yerine kendi yazdığım Stack yapısını kullandım.
void BinarySearchTree::clearIterative()
{
    if (root == 0)
    {
        nodeCount = 0;
        return;
    }

    // Postorder silme işlemi için iki stack yöntemini kullandım.
    // Çünkü recursive silme çok derin ağaçlarda stack overflow yapabilir.
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
        delete n; // Düğümleri burada sildim.
    }

    root = 0;
    nodeCount = 0;
}