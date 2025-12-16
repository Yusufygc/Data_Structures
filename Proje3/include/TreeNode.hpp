/**
* @file TreeNode.hpp
* @description : İkili Arama Ağacı (BST) yapısının temel birimi olan Düğüm (Node) sınıfı.
* Her düğüm bir veri (tam sayı) ve sağ/sol çocuklara giden işaretçileri tutar.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#ifndef TREENODE_HPP
#define TREENODE_HPP

// Ağaç veri yapısının en küçük yapı taşı olan düğüm sınıfı.
// Kapsülleme (Encapsulation) yerine struct mantığıyla public bıraktım,
// çünkü bu düğümleri yönetme işi tamamen BinarySearchTree sınıfında olacak.
class TreeNode
{
public:
    int value;       // Düğümün taşıdığı asıl sayısal veri
    TreeNode* left;  // Sol alt ağaca giden işaretçi (Kendisinden küçük veya eşitler)
    TreeNode* right; // Sağ alt ağaca giden işaretçi (Kendisinden büyükler)

    // Kurucu: Düğüm oluşturulurken veriyi atar ve çocuk işaretçilerini null (0) yapar.
    TreeNode(int value);
    
    // Yıkıcı: Düğüm silindiğinde yapılacak işlemler
    ~TreeNode();
};

#endif 