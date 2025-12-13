#include "Hexagon.hpp"
#include <iostream>

Hexagon::Hexagon()
{
    treeCount = 0;
    frontIndex = 0;
    next = 0;
    for (int i = 0; i < MAX_TREES; i++) trees[i] = 0;
}

Hexagon::~Hexagon()
{
    for (int i = 0; i < treeCount; i++)
    {
        if (trees[i] != 0) delete trees[i];
    }
    treeCount = 0;
}

bool Hexagon::isFull() const { return treeCount >= MAX_TREES; }
bool Hexagon::isEmpty() const { return treeCount == 0; }

bool Hexagon::addTree(BinarySearchTree* tree)
{
    if (isFull()) return false;
    trees[treeCount++] = tree;
    return true;
}

BinarySearchTree* Hexagon::popNormalTree()
{
    if (isEmpty()) return 0;

    BinarySearchTree* frontTree = trees[0];
    // Kaydırma
    for (int i = 1; i < treeCount; i++)
    {
        trees[i - 1] = trees[i];
    }
    trees[treeCount - 1] = 0;
    treeCount--;
    return frontTree;
}

BinarySearchTree* Hexagon::popPriorityTree()
{
    if (isEmpty()) return 0;

    // En yüksek ağacı bul
    int maxH = -1;
    int targetIndex = 0;

    for (int i = 0; i < treeCount; i++)
    {
        // BinarySearchTree sınıfında getHeight() metodu olduğunu varsayıyoruz.
        // Eşitlik durumunda, kuyruk mantığı gereği öndeki (daha eski giren) alınır,
        // o yüzden sadece > kullanıyoruz (>= değil).
        int h = trees[i]->getHeight();
        if (h > maxH)
        {
            maxH = h;
            targetIndex = i;
        }
    }

    BinarySearchTree* targetTree = trees[targetIndex];

    // Kaydırma işlemi (aradan çıkarma)
    for (int i = targetIndex + 1; i < treeCount; i++)
    {
        trees[i - 1] = trees[i];
    }
    trees[treeCount - 1] = 0;
    treeCount--;

    return targetTree;
}

BinarySearchTree* Hexagon::getTreeAt(int index) const
{
    if (index < 0 || index >= treeCount) return 0;
    return trees[index];
}

void Hexagon::distributeValues(int* values, int count)
{
    if (treeCount == 0 || count <= 0) return;

    // "kuyruğun önünden başlayıp sonuna doğru... teker teker"
    int currentTreeIdx = 0;

    for (int i = 0; i < count; i++)
    {
        trees[currentTreeIdx]->insert(values[i]);
        
        currentTreeIdx++;
        // Dairesel dağıtım (aynı altıgen içindeki ağaçlar arasında)
        if (currentTreeIdx >= treeCount)
        {
            currentTreeIdx = 0;
        }
    }
}

int Hexagon::getTreeCount() const { return treeCount; }

int Hexagon::getDisplayRootValue() const
{
    if (isEmpty()) return 0;
    // Öncelikli de olsa normal de olsa, ekranda "çıkmak üzere olan" (yani 0. indisteki) gösterilir kuralı genelde geçerlidir.
    // Ancak ödevde "Kuyruktan çıkmak üzere olan ağacın..." denmiş.
    // Bu, o anki mod (Priority/Normal) neyse ona göre mi değişmeli?
    // Genellikle görselleştirmede en öndeki (kuyruk başı) baz alınır.
    BinarySearchTree* frontTree = trees[0];
    if (frontTree && !frontTree->isEmpty()) return frontTree->getRootValue();
    return 0;
}

Hexagon* Hexagon::getNext() const { return next; }
void Hexagon::setNext(Hexagon* nextHexagon) { next = nextHexagon; }

int Hexagon::calculateSpecialDisplayValue() const
{
    if (isEmpty()) return 0;

    // 1. PAY (Numerator): Çıkmak üzere olan normal ağacın kökü
    // Kuyruk mantığı (FIFO) -> trees[0]
    int numerator = 0;
    if (trees[0] != 0 && !trees[0]->isEmpty()) {
        numerator = trees[0]->getRootValue();
    }

    // 2. PAYDA (Denominator): Öncelikli çıkmak üzere olan ağacın kökü
    // Öncelik kuralı: Yüksekliği en fazla olan.
    int maxH = -1;
    int denominator = 1; // 0'a bölme hatası olmasın diye varsayılan 1

    for (int i = 0; i < treeCount; i++)
    {
        if (trees[i] != 0 && !trees[i]->isEmpty()) {
            int h = trees[i]->getHeight();
            // Eğer yükseklik daha büyükse, bu ağaç önceliklidir.
            if (h > maxH) {
                maxH = h;
                denominator = trees[i]->getRootValue();
            }
        }
    }

    // Güvenlik kontrolleri
    if (denominator == 0) return 0; 

    // İSTENEN İŞLEM: Tam sayı bölmesi
    return numerator / denominator;
}