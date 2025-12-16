/** 
* @file CircularHexagonList.hpp
* @description : Bu sınıf projenin ana veri yapısını yönetir ve şunları yapar:
* - Altıgenleri (Hexagon) birbirine bağlayarak tek yönlü dairesel bağlı liste (circular linked list) oluşturur.
* - Her tur başında, kurallara göre (tek/çift tur) altıgenlerden ağaçları çıkarır.
* - Çıkarılan ağaçların verilerini toplar ve bu verileri sağdaki (bir sonraki) komşu altıgene dağıtır.
* - Ekrana yazdırma işlemleri sırasında referans alınacak 'en yüksek ağaç kök değerini' hesaplar.
* @course      : 1.Öğretim C grubu 
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#ifndef CIRCULARHEXAGONLIST_HPP
#define CIRCULARHEXAGONLIST_HPP

#include "Hexagon.hpp"

class CircularHexagonList
{
private:
    Hexagon* head;    // Listenin başlangıç düğümü
    int hexagonCount; // Toplam altıgen sayısı

    // Tur başında ağaçları çıkarma işlemini yapan fonksiyon.
    // Önemli Not: Ağacı çıkarınca sayı azalmasın diye yerine boş bir ağaç ekliyorum.
    void collectTreesAndReplace(int turnNumber, int** dataBuffers, int* dataCounts);

    // Toplanan verileri (buffer'daki sayıları) sağdaki komşu altıgene dağıtan fonksiyon.
    void distributeToNeighbors(int** dataBuffers, int* dataCounts);

    // İşlem bitince bellekte yer kaplamasın diye dizileri temizleyen fonksiyon.
    void cleanUpBuffers(int** dataBuffers, int* dataCounts, int size);

public:
    CircularHexagonList();  
    ~CircularHexagonList(); 

    // Listeye yeni bir altıgen ekler ve dairesel yapıyı korur.
    Hexagon* createAndAppendHexagon();
    
    // Başlangıç düğümüne erişim sağlar.
    Hexagon* getHead() const;
    
    // Toplam kaç altıgen olduğunu döndürür.
    int getHexagonCount() const;
    
    // Her turda yapılacak işlemleri yöneten ana fonksiyon.
    // Karmaşık olmasın diye işlemleri yukarıdaki private fonksiyonlara böldüm.
    void processTurn(int turnNumber);
    
};

#endif