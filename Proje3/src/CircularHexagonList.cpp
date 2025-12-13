#include "CircularHexagonList.hpp"
#include <iostream>

CircularHexagonList::CircularHexagonList()
{
    head = 0;
    hexagonCount = 0;
}

CircularHexagonList::~CircularHexagonList()
{
    if (head == 0) return;
    
    // Dairesel listede tüm altıgenleri dolaşıp sil.
    Hexagon* current = head;
    for (int i = 0; i < hexagonCount; i++)
    {
        Hexagon* next = current->getNext();
        delete current;
        current = next;
    }
    
    head = 0;
    hexagonCount = 0;
}

// Yeni altıgen oluşturup listeye ekler, dairesel bağlantıyı korur.
Hexagon* CircularHexagonList::createAndAppendHexagon()
{
    Hexagon* newHex = new Hexagon();

    if (head == 0)
    {
        head = newHex;
        head->setNext(head); // Tek elemanlı dairesel liste.
    }
    else
    {
        // Son elemanı (next'i head olan elemanı) bulana kadar git.
        Hexagon* current = head;
        while (current->getNext() != head)
        {
            current = current->getNext();
        }

        // current şu an gerçek son altıgen.
        current->setNext(newHex);
        newHex->setNext(head); // Daireselliği koru.
    }

    hexagonCount++;
    return newHex;
}

Hexagon* CircularHexagonList::getHead() const
{
    return head;
}

int CircularHexagonList::getHexagonCount() const
{
    return hexagonCount;
}

// Mantıksal olarak bir sonraki altıgen (dairede sağ komşu).
Hexagon* CircularHexagonList::getRightNeighbor(Hexagon* current) const
{
    if (current == 0)
    {
        return 0;
    }

    return current->getNext();
}

// Tur işlemlerini (çıkarma, silme, dağıtma) yöneten fonksiyon
void CircularHexagonList::processTurn(int turnNumber)
{
    if (head == 0) return;

    // Geçici veri saklama yapısı
    // Her altıgenin transfer edeceği verileri tutacağız.
    // Dinamik bellek yönetimi (vector yerine)
    int totalHex = hexagonCount;
    int** dataBuffers = new int*[totalHex];
    int* dataCounts = new int[totalHex];

    for(int i=0; i<totalHex; i++) {
        dataBuffers[i] = 0;
        dataCounts[i] = 0;
    }

    // 1. ADIM: Her altıgenden uygun ağacı çıkar ve verilerini al (Extract)
    Hexagon* current = head;
    bool isOddTurn = (turnNumber % 2 != 0); // Tek turlar: 1, 3, 5... (Normal Tree)

    for (int i = 0; i < totalHex; i++)
    {
        BinarySearchTree* removedTree = 0;

        if (isOddTurn)
        {
            // Tek turlar: Normal kuyruk mantığı (baştaki ağaç)
            removedTree = current->popNormalTree();
        }
        else
        {
            // Çift turlar: Öncelikli kuyruk (yüksekliği en fazla olan)
            removedTree = current->popPriorityTree();
        }

        if (removedTree != 0)
        {
            // Ağaçtaki düğüm sayısını al
            int count = removedTree->getNodeCount();
            if (count > 0)
            {
                dataBuffers[i] = new int[count];
                int outCount = 0;
                // Postorder extract: Verileri al ve ağacı boşalt
                removedTree->extractAllPostOrder(dataBuffers[i], count, outCount);
                dataCounts[i] = outCount;
            }
            // Ağacın kendisini bellekten sil
            delete removedTree; 
        }

        current = current->getNext();
    }

    // 2. ADIM: Alınan verileri bir sonraki (sağdaki) altıgene dağıt
    current = head;
    for (int i = 0; i < totalHex; i++)
    {
        // i. altıgenden çıkan veri (dataBuffers[i]), current->getNext()'e (sağındakine) eklenir.
        Hexagon* targetHex = current->getNext();
        
        if (dataBuffers[i] != 0 && dataCounts[i] > 0)
        {
            targetHex->distributeValues(dataBuffers[i], dataCounts[i]);
            
            // Kullanılan tamponu temizle
            delete[] dataBuffers[i];
        }

        current = current->getNext();
    }

    delete[] dataBuffers;
    delete[] dataCounts;
}

// Global en yüksek ağaç kök değerini bulur (Mantıksal ihtiyaçlar için kalsın)
int CircularHexagonList::findGlobalMaxHeightRootValue() const
{
    if (head == 0) return 1;

    int maxHeight = 0;
    int rootValueOfMax = 1;

    Hexagon* current = head;

    for (int i = 0; i < hexagonCount; i++)
    {
        for (int t = 0; t < current->getTreeCount(); t++)
        {
            BinarySearchTree* tree = current->getTreeAt(t);
            if (tree != 0 && !tree->isEmpty())
            {
                int h = tree->getHeight();
                if (h > maxHeight)
                {
                    maxHeight = h;
                    rootValueOfMax = tree->getRootValue();
                }
            }
        }
        current = current->getNext();
    }

    if (maxHeight == 0) return 1;
    return rootValueOfMax;
}

// Ekrana basılacak 18'lik pencereyi yılan formasyonunda yazdırır.
// Her hücrenin değeri kendi içindeki (Kuyruk Başı / En Yüksek Ağaç) formülüyle hesaplanır.
void CircularHexagonList::printWindowAsSnake(Hexagon* windowStart) const
{
    if (windowStart == 0)
    {
        std::cout << "Gosterilecek altigen yok." << std::endl;
        return;
    }

    // Ekranda gösterilecek maksimum altıgen sayısı (18 veya daha az)
    // Eğer toplam sayı 18'den azsa, sadece o kadarını gösteririz.
    int windowSize = (hexagonCount < 18) ? hexagonCount : 18;

    int values[18];
    // Diziyi -1 ile başlat (Boş yerleri göstermemek için)
    for (int i = 0; i < 18; i++) values[i] = -1;

    Hexagon* current = windowStart;

    // Sadece windowSize kadar altıgeni hesapla ve diziye al
    for (int i = 0; i < windowSize; i++)
    {
        if (current->isEmpty())
        {
            values[i] = 0; // İçi boş altıgen
        }
        else
        {
            // *** MANTIK: LOCAL HESAPLAMA ***
            // Global bir payda yerine, her altıgen kendi değerini hesaplar.
            // (Normal Kuyruk Başı / O Altıgendeki En Yüksek Ağaç)
            values[i] = current->calculateSpecialDisplayValue();
        }
        current = current->getNext();
    }

    std::cout << "Altigen sayisi: " << hexagonCount << std::endl;

    // --- 1. Satır (0..5) ---
    for (int i = 0; i < 6; i++) {
        if (values[i] != -1) std::cout << values[i] << "\t";
        else                 std::cout << " \t"; // Boşluk
    }
    std::cout << std::endl;

    // --- 2. Satır (11..6) TERS YÖN ---
    // Yılan kıvrımı: Sağdan sola doğru gitmeli.
    // Eğer 1. satır dolmadıysa 2. satıra hiç geçmemeli, bunu values kontrolü sağlar.
    for (int i = 11; i >= 6; i--) {
        if (values[i] != -1) std::cout << values[i] << "\t";
        else                 std::cout << " \t";
    }
    std::cout << std::endl;

    // --- 3. Satır (12..17) ---
    for (int i = 12; i < 18; i++) {
        if (values[i] != -1) std::cout << values[i] << "\t";
        else                 std::cout << " \t";
    }
    std::cout << std::endl << std::endl;
}

// Gerekirse kullanılmak üzere, tek pencere mantığını destekleyen referans fonksiyon.
int CircularHexagonList::findWindowMaxHeightRootValue(Hexagon* windowStart) const
{
    // Artık görüntüleme için kullanılmıyor, Hexagon::calculateSpecialDisplayValue kullanılıyor.
    return 1;
}

// Eski snake yazdırma fonksiyonu (Tüm listeyi basan).
// Geriye dönük uyumluluk için tutulabilir.
void CircularHexagonList::printAsSnake(int denominatorRoot) const
{
    if (head == 0 || hexagonCount == 0) return;
    printWindowAsSnake(head);
}