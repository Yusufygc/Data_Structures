#ifndef TREENODE_HPP
#define TREENODE_HPP

// İkili arama ağacında kullanılacak düğüm yapısı.
// Bilerek basit tutuldu: değer, sol çocuk, sağ çocuk.
class TreeNode
{
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    // Kurucu & Yıkıcı sadece bildiriliyor, gövdesi .cpp'de.
    TreeNode(int value);
    ~TreeNode();
};

#endif // TREENODE_H
