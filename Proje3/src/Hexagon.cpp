/**
* @file Hexagon.cpp
* @description : Altıgen (Kuyruk) yapısının işlevlerini gerçekleştiren kaynak dosya.
* Ağaç ekleme, öncelikli ağacı bulma ve verileri dağıtma mantığını burada kodladım.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include "Hexagon.hpp"
#include <iostream>

// Kurucu: Dizi elemanlarını ve değişkenleri sıfırladım ki çöp değer kalmasın.
Hexagon::Hexagon()
{
    treeCount = 0;
    frontIndex = 0; // FIFO mantığı için başı 0 kabul ettim.
    next = 0;

    for (int i = 0; i < MAX_TREES; i++)
    {
        trees[i] = 0;
    }
}

// Yıkıcı: Altıgen silinirken içindeki ağaçları da bellekten sildim.
Hexagon::~Hexagon()
{
    for (int i = 0; i < treeCount; i++)
    {
        if (trees[i] != 0)
        {
            delete trees[i];
            trees[i] = 0;
        }
    }
    treeCount = 0;
}

// ==========================================================
// YARDIMCI FONKSİYONLAR
// ==========================================================

// Öncelikli kuyruk (Priority Queue) mantığını burada kurdum.
// Tüm ağaçları tek tek gezerek yüksekliği (Height) en fazla olanı buluyorum.
int Hexagon::findMaxHeightTreeIndex() const
{
    if (isEmpty()) return -1;

    int maxH = -1;
    int targetIndex = 0;

    for (int i = 0; i < treeCount; i++)
    {
        // Boş olmayan ağaçları kontrol ettim.
        if (trees[i] != 0 && !trees[i]->isEmpty()) {
            int h = trees[i]->getHeight();
            // Eğer daha yüksek bir ağaç bulursam onu seçtim.
            if (h > maxH)
            {
                maxH = h;
                targetIndex = i;
            }
        }
    }
    return targetIndex;
}

// Ekrana yazılacak değeri hesaplayan fonksiyon.
// Normal kuyruğun başındaki (0. indeks) ve en yüksek ağacın kökünü kullandım.
int Hexagon::getRawValueDivisor() const
{
    // Normal Kök (Sıradaki ilk ağaç)
    int normalRoot = 0;
    if (treeCount > 0 && trees[0] != 0 && !trees[0]->isEmpty()) {
        normalRoot = trees[0]->getRootValue();
    }

    // Öncelikli Kök (En yüksek ağaç)
    int priorityIndex = findMaxHeightTreeIndex();
    int priorityRoot = 1;

    if (priorityIndex != -1 && trees[priorityIndex] != 0) {
        priorityRoot = trees[priorityIndex]->getRootValue();
    }

    // Bölme işleminde payda 0 olursa program çöker (Divide by Zero).
    // O yüzden eğer kök 0 ise onu 1 yaptım.
    if (priorityRoot == 0) priorityRoot = 1;

    return normalRoot / priorityRoot;
}

// Bir ağacı diziden silip, dizide oluşan boşluğu kaydırma yöntemiyle kapattım.
BinarySearchTree* Hexagon::removeTreeAtIndex(int index)
{
    if (index < 0 || index >= treeCount) return 0;

    // Hedef ağacı kaybetmemek için bir değişkene aldım.
    BinarySearchTree* targetTree = trees[index];

    // Sildiğim elemandan sonrakileri birer adım sola kaydırdım.
    // Böylece dizide arada boşluk kalmadı.
    for (int i = index + 1; i < treeCount; i++)
    {
        trees[i - 1] = trees[i];
    }
    
    // Son elemanı boşa çıkardım ve sayıyı azalttım.
    trees[treeCount - 1] = 0;
    treeCount--;

    return targetTree;
}
//==========================================================

bool Hexagon::isFull() const
{
    return treeCount >= MAX_TREES;
}

bool Hexagon::isEmpty() const
{
    return treeCount == 0;
}

bool Hexagon::addTree(BinarySearchTree* tree)
{
    if (isFull()) return false;

    trees[treeCount] = tree;
    treeCount++;
    return true;
}

// Tek turlarda: Sıradaki ilk elemanı (0. indeks) çıkardım.
BinarySearchTree* Hexagon::popNormalTree()
{
    if (isEmpty()) return 0;
    return removeTreeAtIndex(0);
}

// Çift turlarda: En yüksek ağacı (Priority) bulup çıkardım.
BinarySearchTree* Hexagon::popPriorityTree()
{
    if (isEmpty()) return 0;
    // Hangi ağacın öncelikli olduğunu buldum.
    int targetIndex = findMaxHeightTreeIndex();
    return removeTreeAtIndex(targetIndex);
}

// Diğer altıgenden gelen verileri bu altıgendeki ağaçlara dağıttığım fonksiyon.
void Hexagon::distributeValues(int* values, int count)
{
    if (count <= 0) return;

    // Güvenlik önlemi: Hiç ağaç yoksa bir tane ekledim ki dağıtacak yer olsun.
    if (treeCount == 0) {
        addTree(new BinarySearchTree());
    }

    // Dağıtımı sadece mevcut olan ağaçlara yapıyorum, yeni eklenenlere değil.
    int limitIndex = treeCount; 
    int currentTreeIdx = 0;

    for (int i = 0; i < count; i++)
    {
        // Olası bir hata durumunda (slot boşsa) kontrol ettim.
        if (trees[currentTreeIdx] == 0) {
            if (!isFull()) {
                addTree(new BinarySearchTree());
            } else {
                currentTreeIdx = 0; // Yer yoksa başa döndüm.
            }
        }
        
        // Değeri ağaca ekledim.
        if (trees[currentTreeIdx] != 0) {
             trees[currentTreeIdx]->insert(values[i]);
        }

        // Round-Robin (Sırayla) dağıtım mantığı.
        // Bir sonrakine geçtim, eğer son ağaca geldiysem tekrar başa döndüm.
        currentTreeIdx++;
        
        if (currentTreeIdx >= limitIndex)
        {
            currentTreeIdx = 0;
        }
    }
}


int Hexagon::calculateSpecialDisplayValue() const
{
    if (isEmpty()) return 0;
    return getRawValueDivisor();
}


// Bağlı liste için sonraki düğüm işlemleri.
Hexagon* Hexagon::getNext() const { return next; }
void Hexagon::setNext(Hexagon* nextHexagon) { next = nextHexagon; }

int Hexagon::getTreeCount() const { return treeCount; }




