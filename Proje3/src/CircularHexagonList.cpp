/**
* @file CircularHexagonList.cpp
* @description : Dairesel Altıgen Listesi sınıfının kaynak dosyası.
* Altıgenleri birbirine bağlama, tur işlemlerini yönetme ve veri dağıtım algoritmalarını burada kodladım.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include "CircularHexagonList.hpp"
#include <iostream>


CircularHexagonList::CircularHexagonList()
{
    head = 0;
    hexagonCount = 0;
}

// Yıkıcı fonksiyon: Program kapanırken bellek sızıntısı olmaması için
// dairesel listeyi tek tek dolaşıp tüm altıgenleri sildim.
CircularHexagonList::~CircularHexagonList()
{
    if (head == 0) return;
    
    Hexagon* current = head;
    // Dairesel olduğu için sonsuz döngüye girmesin diye sayı kadar döndürdüm.
    for (int i = 0; i < hexagonCount; i++)
    {
        Hexagon* next = current->getNext();
        delete current;
        current = next;
    }
    
    head = 0;
    hexagonCount = 0;
}

// Listeye yeni bir altıgen eklemek için bu fonksiyonu yazdım.
// Listenin boş olup olmamasına göre dairesel bağlantıyı kurdum.
Hexagon* CircularHexagonList::createAndAppendHexagon()
{
    Hexagon* newHex = new Hexagon();

    if (head == 0)
    {
        // İlk elemansa kendisine bağladım (Dairesel yapı başlangıcı).
        head = newHex;
        head->setNext(head);
    }
    else
    {
        // Liste doluysa son elemanı bulup yeni elemanı araya ekledim.
        Hexagon* current = head;
        while (current->getNext() != head)
        {
            current = current->getNext();
        }
        current->setNext(newHex);
        newHex->setNext(head); 
    }

    hexagonCount++;
    return newHex;
}

// Liste başındaki elemanı döndürür
Hexagon* CircularHexagonList::getHead() const
{
    return head;
}

// Toplam altıgen sayısını döndürür
int CircularHexagonList::getHexagonCount() const
{
    return hexagonCount;
}

// ==========================================================
// YARDIMCI FONKSİYONLAR
// ==========================================================

// Tur mantığına göre ağaçları çıkardığım ve yerine yenisini koyduğum fonksiyon.
void CircularHexagonList::collectTreesAndReplace(int turnNumber, int** dataBuffers, int* dataCounts)
{
    Hexagon* current = head;
    // Tur sayısının tek mi çift mi olduğunun kontrolü
    bool isOddTurn = (turnNumber % 2 != 0);

    for (int i = 0; i < hexagonCount; i++)
    {
        BinarySearchTree* removedTree = 0;
        
        // Tek turlarda baştaki (Normal), Çift turlarda en yüksek (Priority) ağacı seçtim.
        if (isOddTurn) {
            removedTree = current->popNormalTree();
        } else {
            removedTree = current->popPriorityTree();
        }

        if (removedTree != 0)
        {
            // Çıkarılan ağacın verilerini Postorder mantığıyla aldım.
            int count = removedTree->getNodeCount();
            if (count > 0)
            {
                dataBuffers[i] = new int[count]; 
                int outCount = 0;
                removedTree->extractAllPostOrder(dataBuffers[i], count, outCount);
                dataCounts[i] = outCount;
            }
            
            // İşimi bitirince ağacı sildim.
            delete removedTree; 
            removedTree = 0;

            // BURASI ÖNEMLİ: Kuyruktaki ağaç sayısı azalmasın diye çıkardığımın yerine
            // hemen boş bir ağaç ekledim. Böylece yapı bozulmadı.
            if (!current->isFull()) 
            {
                current->addTree(new BinarySearchTree());
            }
        }
        
        current = current->getNext();
    }
}

// Topladığım verileri bir sonraki (sağdaki) komşuya dağıttığım fonksiyon.
void CircularHexagonList::distributeToNeighbors(int** dataBuffers, int* dataCounts)
{
    Hexagon* current = head;
    
    for (int i = 0; i < hexagonCount; i++)
    {
        Hexagon* targetHex = current->getNext();
        
        // Eğer bu turda bu altıgenden veri çıktıysa dağıtım yaptım.
        if (dataBuffers[i] != 0 && dataCounts[i] > 0)
        {
            targetHex->distributeValues(dataBuffers[i], dataCounts[i]);
            
            // Dağıtım bitince geçici belleği temizledim.
            delete[] dataBuffers[i]; 
            dataBuffers[i] = 0;
        }
        
        current = current->getNext();
    }
}

// Güvenlik amacıyla oluşturduğum temizlik fonksiyonu.
void CircularHexagonList::cleanUpBuffers(int** dataBuffers, int* dataCounts, int size)
{
    // Olası silinmemiş buffer kalıntılarını kontrol edip sildim.
    for(int i = 0; i < size; i++) {
        if (dataBuffers[i] != 0) {
            delete[] dataBuffers[i];
            dataBuffers[i] = 0;
        }
    }
    delete[] dataBuffers;
    delete[] dataCounts;
}

// ==========================================================
// ANA SÜREÇ FONKSİYONU
// ==========================================================

// Her turda yapılacak işlemleri yöneten ana fonksiyonum.
void CircularHexagonList::processTurn(int turnNumber)
{
    if (head == 0 || hexagonCount == 0) return;

    // 1. Hazırlık: Verileri tutmak için geçici diziler oluşturdum.
    int** dataBuffers = new int*[hexagonCount];
    int* dataCounts = new int[hexagonCount];

    for(int i = 0; i < hexagonCount; i++) {
        dataBuffers[i] = 0;
        dataCounts[i] = 0;
    }

    // 2. İşlem: Ağaçları çıkardım ve yerini doldurdum.
    collectTreesAndReplace(turnNumber, dataBuffers, dataCounts);

    // 3. İşlem: Verileri komşulara dağıttım.
    distributeToNeighbors(dataBuffers, dataCounts);

    // 4. Bitiş: Belleği temizledim.
    cleanUpBuffers(dataBuffers, dataCounts, hexagonCount);
}

