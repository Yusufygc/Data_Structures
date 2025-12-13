#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "BinarySearchTree.hpp"

class Hexagon
{
private:
    static const int MAX_TREES = 6;

    BinarySearchTree* trees[MAX_TREES];
    int treeCount;
    int frontIndex; // Aslında popNormalTree'de kaydırma yaptığımız için hep 0 kabul edebiliriz.

    Hexagon* next;

public:
    Hexagon();
    ~Hexagon();

    bool isFull() const;
    bool isEmpty() const;

    bool addTree(BinarySearchTree* tree);
    
    // Normal kuyruk davranışı (index 0'ı çıkarır)
    BinarySearchTree* popNormalTree();

    // Öncelikli kuyruk davranışı (En yüksek ağacı bulur ve çıkarır)
    BinarySearchTree* popPriorityTree();

    // Belirli bir indisteki ağaca erişim
    BinarySearchTree* getTreeAt(int index) const;
    
    // Elimizdeki veri dizisini (values), mevcut ağaçlara sırayla ekler.
    void distributeValues(int* values, int count);

    int getTreeCount() const;
    int getDisplayRootValue() const;

    Hexagon* getNext() const;
    void setNext(Hexagon* nextHexagon);

    // --- YENİ EKLENEN FONKSİYON ---
    // Proje isterine göre o altıgenin ekrana basılacak değerini hesaplar.
    int calculateSpecialDisplayValue() const;

    void removeTreeAt(int index);
};

#endif