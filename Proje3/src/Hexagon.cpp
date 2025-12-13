#include "Hexagon.hpp"
#include <iostream>

// Kurucu: başlangıçta hiç ağaç yok.
Hexagon::Hexagon()
{
    treeCount = 0;
    frontIndex = 0;
    next = 0;

    for (int i = 0; i < MAX_TREES; i++)
    {
        trees[i] = 0;
    }
}

// Yıkıcı: içindeki tüm ağaçları temizler.
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

// Hexagon dolu mu? (en fazla 6 ağaç)
bool Hexagon::isFull() const
{
    return treeCount >= MAX_TREES;
}

// Hexagon boş mu?
bool Hexagon::isEmpty() const
{
    // İçinde hiç ağaç yoksa boştur.
    // Ancak ağaçlar var ama hepsi boşsa da boş sayılabilir.
    // Şimdilik sadece ağaç varlığına bakıyoruz.
    return treeCount == 0;
}

// Kuyruğun sonuna ağaç ekler. Başarılı ise true döner.
bool Hexagon::addTree(BinarySearchTree* tree)
{
    if (isFull())
    {
        return false;
    }

    trees[treeCount] = tree;
    treeCount++;

    return true;
}

// Normal kuyruk mantığı: frontIndex'teki ağacı döndürür ve hexagondan çıkarır.
BinarySearchTree* Hexagon::popNormalTree()
{
    if (isEmpty())
    {
        return 0;
    }

    // Önden çıkacak ağaç her zaman index 0'daki olsun diye diziyi kaydırıyoruz.
    BinarySearchTree* frontTree = trees[0];

    for (int i = 1; i < treeCount; i++)
    {
        trees[i - 1] = trees[i];
    }

    trees[treeCount - 1] = 0;
    treeCount--;

    return frontTree;
}

// Öncelikli ağaç (En yüksek olan)
BinarySearchTree* Hexagon::popPriorityTree()
{
    if (isEmpty()) return 0;

    // En yüksek ağacı bul
    int maxH = -1;
    int targetIndex = 0;

    for (int i = 0; i < treeCount; i++)
    {
        // BinarySearchTree sınıfında getHeight() metodu olduğunu varsayıyoruz.
        // Eşitlik durumunda, kuyruk mantığı gereği öndeki (daha eski giren) alınır.
        if (trees[i] != 0) {
            int h = trees[i]->getHeight();
            if (h > maxH)
            {
                maxH = h;
                targetIndex = i;
            }
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

// Belirli indeksteki (0..treeCount-1) ağaca eriş.
BinarySearchTree* Hexagon::getTreeAt(int index) const
{
    if (index < 0 || index >= treeCount)
    {
        return 0;
    }
    return trees[index];
}

// Öncelikli ağaç senaryosu için belirli indeksteki ağacı diziden çıkarır (delete etmez).
void Hexagon::removeTreeAt(int index)
{
    if (index < 0 || index >= treeCount)
    {
        return;
    }

    for (int i = index + 1; i < treeCount; i++)
    {
        trees[i - 1] = trees[i];
    }

    trees[treeCount - 1] = 0;
    treeCount--;
}

// Dışarıdan gelen veri yığınını, mevcut ağaçlara sırayla ekler.
void Hexagon::distributeValues(int* values, int count)
{
    if (count <= 0) return;

    // --- KRİTİK DÜZELTME: EĞER HİÇ AĞAÇ YOKSA YENİ BİR TANE EKLE ---
    // Böylece veriler kaybolmaz, yeni bir ağaçta toplanır.
    if (treeCount == 0) {
        addTree(new BinarySearchTree());
    }

    // "kuyruğun önünden başlayıp sonuna doğru... teker teker"
    int currentTreeIdx = 0;

    for (int i = 0; i < count; i++)
    {
        // Eğer o anki indisteki ağaç null ise (olmamalı ama güvenlik)
        if (trees[currentTreeIdx] == 0) {
             // Yer varsa yeni ağaç ekle, yoksa başa dön
             if (!isFull()) {
                 addTree(new BinarySearchTree());
             } else {
                 // Full ise ve null ise bir hata vardır, 0. indekse dön
                 currentTreeIdx = 0;
             }
        }

        trees[currentTreeIdx]->insert(values[i]);
        
        currentTreeIdx++;
        // Dairesel dağıtım (aynı altıgen içindeki ağaçlar arasında)
        if (currentTreeIdx >= treeCount)
        {
            currentTreeIdx = 0;
        }
    }
}

// Ekranda "kuyruktan çıkacak ağacın" kök değeri.
// YENİ MANTIK: Kendi içindeki (Baş / Max) değerini hesaplar.
int Hexagon::calculateSpecialDisplayValue() const
{
    if (isEmpty()) return 0;

    // 1. PAY (Numerator): Kuyruğun başındaki (index 0) ağacın kökü
    int numerator = 0;
    if (trees[0] != 0 && !trees[0]->isEmpty()) {
        numerator = trees[0]->getRootValue();
    }

    // 2. PAYDA (Denominator): Bu altıgendeki EN YÜKSEK (Öncelikli) ağacın kökü
    int maxH = -1;
    int denominator = 1; // 0'a bölme hatası olmasın

    for (int i = 0; i < treeCount; i++)
    {
        if (trees[i] != 0 && !trees[i]->isEmpty()) {
            int h = trees[i]->getHeight();
            // Yükseklik daha büyükse yeni öncelikli budur
            if (h > maxH) {
                maxH = h;
                denominator = trees[i]->getRootValue();
            }
        }
    }

    if (denominator == 0) return 0; 

    // Tam sayı bölmesi
    return numerator / denominator;
}

// Eski fonksiyon (uyumluluk için)
int Hexagon::getDisplayRootValue() const
{
    return calculateSpecialDisplayValue();
}

int Hexagon::getTreeCount() const
{
    return treeCount;
}

Hexagon* Hexagon::getNext() const
{
    return next;
}

void Hexagon::setNext(Hexagon* nextHexagon)
{
    next = nextHexagon;
}