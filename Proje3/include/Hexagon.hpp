/** * @file Hexagon.hpp
* @description : Bu sınıf, projenin 'Öncelikli Kuyruk' (Priority Queue) yapısını temsil eden Altıgen düğümüdür.
* Veri Yapısı Mantığı:
* - Bu sınıf, bir 'Container' (Taşıyıcı) görevi görür ve içinde İkili Arama Ağaçlarını saklar.
* - Bir veri yapısının Öncelikli Kuyruk sayılabilmesi için çıkarma işleminde en öncelikli elemanı vermesi gerekir.
* - Bu sınıf, 'popPriorityTree' fonksiyonu ile içerisindeki ağaçlardan yüksekliği en fazla olanı (Öncelikli olanı)
* bulup döndürdüğü için teknik olarak bir Öncelikli Kuyruk davranışı sergiler.
* - Veri sayısı az (Max 6) olduğu için Heap yapısı yerine dizi üzerinde arama yöntemi tercih edilmiştir.
* @course      : 1.Öğretim C grubu 
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "BinarySearchTree.hpp"

class Hexagon
{
private:
    static const int MAX_TREES = 6; // Kuyruğun maksimum kapasitesi.

    BinarySearchTree* trees[MAX_TREES]; // Verileri (Ağaçları) tutan statik dizi.
    int treeCount;  // Kuyruktaki mevcut eleman sayısı.
    int frontIndex; // Kuyruğun başını temsil eder (FIFO mantığı için).
    Hexagon* next;  // Dairesel listedeki sonraki düğüm.

    // --- YARDIMCI FONKSİYONLAR ---
    
    // Öncelikli Kuyruk mantığının kalbi:
    // Mevcut ağaçlar arasında "Öncelik Skoru" (Yükseklik) en fazla olanın indeksini bulur.
    int findMaxHeightTreeIndex() const;

    // Ekrana yazılacak özel değeri hesaplayan yardımcı fonksiyon.
    int getRawValueDivisor() const;

    // Listeden eleman silme ve kaydırma işlemlerini yöneten fonksiyon.
    BinarySearchTree* removeTreeAtIndex(int index);

public:
    Hexagon(); 
    ~Hexagon(); 

    // Kuyruk Doluluk/Boşluk kontrolleri
    bool isFull() const;
    bool isEmpty() const;

    // Kuyruğa veri (Ağaç) ekleme (Enqueue işlemi).
    bool addTree(BinarySearchTree* tree);
    
    // Tek Turlarda: Normal Kuyruk (FIFO) mantığıyla eleman çıkarır (Dequeue).
    BinarySearchTree* popNormalTree();

    // Çift Turlarda: Öncelikli Kuyruk (Priority Queue) mantığıyla eleman çıkarır.
    // Yüksekliği en fazla olan ağacı tespit eder ve döndürür.
    BinarySearchTree* popPriorityTree();

    // Çıkarılan bir ağacın verilerini, bu kuyruktaki ağaçlara sırayla dağıtır.
    void distributeValues(int* values, int count);

    // Mevcut ağaç sayısını döndürür.
    int getTreeCount() const;
    
    // Bağlı Liste İşlemleri
    Hexagon* getNext() const;

    // Sonraki altıgeni ayarlar.
    void setNext(Hexagon* nextHexagon);

    // Görselleştirme için hesaplama fonksiyonu.
    int calculateSpecialDisplayValue() const;

};

#endif