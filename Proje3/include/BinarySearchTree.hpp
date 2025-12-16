/** 
* @file BinarySearchTree.hpp
* @description : İkili Arama Ağacı (Binary Search Tree) sınıfının bildirimi.
*                Ekleme, yükseklik hesaplama, postorder ile veri çıkarma ve 
*                iteratif temizleme fonksiyonlarını içerir.
*                Ekleme kuralı: < sol, > sağ, == sol
* @course      : 1.Öğretim C grubu 
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/
#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "TreeNode.hpp"

class BinarySearchTree
{
private:
    TreeNode* root;
    int nodeCount;

    // Yardımcı metodlar 
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
    // buffer  : çağıran tarafından allocate edilmiş int dizisi.
    // maxCount: buffer kapasitesi
    // outCount: kaç adet veri doldurulduğunu döndürür.
    void extractAllPostOrder(int* buffer, int maxCount, int& outCount);

    bool isEmpty() const;

    // Ağacı yığın kullanarak iteratif olarak temizler
    void clearIterative();

};

#endif 
