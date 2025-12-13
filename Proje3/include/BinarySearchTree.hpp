#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "TreeNode.hpp"

// İkili arama ağacı sınıfı.
// - Ekleme kuralı: < sol, > sağ, == sol
// - Yükseklik hesaplama
// - Postorder ile bütün verileri alıp silme (extract)
class BinarySearchTree
{
private:
    TreeNode* root;
    int nodeCount;

    // Yardımcı metodlar (özel, recursive).
    void destroyRecursive(TreeNode* node);
    TreeNode* insertRecursive(TreeNode* node, int value);
    int heightRecursive(TreeNode* node) const;
    void extractPostOrderRecursive(TreeNode* node, int* buffer, int& index);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int value);             // Ağaca yeni değer ekler.
    int getRootValue() const;           // Kök değerini döndürür (ağaç boşsa -1).
    int getHeight() const;              // Ağacın yüksekliğini döndürür (boşsa 0).
    int getNodeCount() const;           // Düğüm sayısı.

    // Bütün verileri postorder ile alıp ağacı tamamen boşaltır.
    // buffer: çağıran tarafından allocate edilmiş int dizisi.
    // maxCount: buffer kapasitesi
    // outCount: kaç adet veri doldurulduğunu döndürür.
    void extractAllPostOrder(int* buffer, int maxCount, int& outCount);

    bool isEmpty() const;

    // Ağacı iteratif olarak temizler (yığın kullanarak).
    void clearIterative();

};

#endif // BINARYSEARCHTREE_H
