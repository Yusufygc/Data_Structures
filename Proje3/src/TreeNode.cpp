/**
* @file TreeNode.cpp
* @description : Ağaç düğümlerini oluşturan sınıfın kaynak dosyası.
* Düğüm oluşturma ve silme işlemlerindeki ince detayları (pointer yönetimi) burada hallettim.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include "TreeNode.hpp"


TreeNode::TreeNode(int value)
{
    this->value = value;
    
    // Pointer'ları oluşturur oluşturmaz 0 (NULL) değerine eşitledim.
    // Eğer bunu yapmazsam bellekteki rastgele bir adresi (garbage value) gösteriyorlar
    // ve program "Segmentation Fault" verip çöküyor.
    this->left = 0;
    this->right = 0;
}


TreeNode::~TreeNode()
{
    // Burada çocukları (left/right) recursive olarak silmek yerine boş bıraktım.
    // Neden? Çünkü ağaç çok derin olursa recursive silme işlemi "Stack Overflow" hatası veriyor.
    // O yüzden silme yönetimini BinarySearchTree sınıfındaki "clearIterative" fonksiyonuna bıraktım.
    // Burası sadece tek bir düğümü silmekten sorumlu.
}