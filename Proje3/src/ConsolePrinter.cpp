/**
* @file ConsolePrinter.cpp
* @description : Konsol ekranına yazdırma işlemlerini yapan kaynak dosya.
* Özellikle yılan (snake) algoritmasını kurarken indeks hesaplamalarına çok dikkat ettim.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include "ConsolePrinter.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>

// Ekran temizleme komutunu işletim sistemine göre seçtim.
void ConsolePrinter::clearScreen()
{
    #ifdef _WIN32
        std::system("cls");  // Windows için
    #else
        std::system("clear"); // Linux/Mac için
    #endif
}

// ==========================================================
// YARDIMCI FONKSİYONLAR
// ==========================================================

// Yazdırma işlemiyle hesaplama işlemini karıştırsaydım
// yılan mantığını kurmak çok zor olacaktı. O yüzden önce tüm verileri
// düz bir diziye (array) çıkardım, sonra yazdırma kısmına geçtim.
int* ConsolePrinter::prepareGridData(const CircularHexagonList& list, int& outCount)
{
    int count = list.getHexagonCount();
    outCount = count;

    // Eğer liste boşsa null döndürdüm ki çökme olmasın.
    if (count == 0) return 0;

    // Hesaplanan değerleri tutacak dinamik dizi oluşturdum.
    int* values = new int[count];
    Hexagon* current = list.getHead();
    
    // Tüm listeyi tek tek gezdim.
    for(int i = 0; i < count; i++) {
        if(current->isEmpty()) {
            values[i] = -1; // -1'i "Boş Altıgen" işareti (Sentinel Value) olarak kullandım.
        } else {
            // Hexagon sınıfındaki matematiksel hesaplama
            values[i] = current->calculateSpecialDisplayValue();
        }
        current = current->getNext();
    }
    
    return values;
}

// Yılan (Snake) mantığının kurulduğu en kritik fonksiyon burası.
// Satır numarasına göre diziyi düz veya ters okuyorum.
void ConsolePrinter::printRowSnake(const int* values, int totalCount, int rowIndex, int rowWidth)
{
    // O satırın dizideki başlangıç indeksini buldum.
    int startIdx = rowIndex * rowWidth;
    
    // PÜF NOKTASI: Satır indeksi tek sayı ise (1, 3, 5...) sağdan sola (ters) yazdırılmalı.
    // Çift sayılarda (0, 2, 4...) normal soldan sağa yazdırılmalı.
    bool isReverse = (rowIndex % 2 != 0);

    if (!isReverse) 
    {
        // --- Düz Yazdırma (Soldan Sağa) ---
        // Normal for döngüsü: 0'dan 6'ya kadar artarak gider.
        for (int k = 0; k < rowWidth; k++)
        {
            int idx = startIdx + k;
            
            // Dizi sınırlarını kontrol ettim, veri bittiyse hata vermesin diye.
            if (idx < totalCount) {
                if (values[idx] == -1) std::cout << "#\t"; // -1 ise # bastım
                else std::cout << values[idx] << "\t";
            } else {
                std::cout << " \t"; // Veri bittiyse boşluk bastım
            }
        }
    }
    else 
    {
        // --- Ters Yazdırma (Sağdan Sola / Yılan Kıvrımı) ---
        // PÜF NOKTASI: Döngüyü tersten (5'ten 0'a) kurdum.
        // Böylece konsolda sağdan sola doğru gidiyormuş gibi göründü.
        for (int k = rowWidth - 1; k >= 0; k--)
        {
            int idx = startIdx + k;
            
            //  sınır kontrolü
            if (idx >= totalCount) {
                std::cout << " \t"; 
            } else {
                if (values[idx] == -1) std::cout << "#\t";
                else std::cout << values[idx] << "\t";
            }
        }
    }
   
    std::cout << std::endl;
}

// ==========================================================
//  ANA FONKSİYON
// ==========================================================

void ConsolePrinter::printWindowAsSnake(const CircularHexagonList& list)
{
    int totalCount = 0;

    // 1. ADIM: Hesaplama Kısmı 
    // Listeyi dolaşıp sayıları bir diziye çektim.
    int* gridValues = prepareGridData(list, totalCount);

    if (gridValues == 0 || totalCount == 0) {
        std::cout << "Gosterilecek liste bos." << std::endl;
        return;
    }

    std::cout << "----------------------------------------------------" << std::endl;

    // 2. ADIM: Yazdırma Kısmı
    // Satırda 6 eleman olacak şekilde toplam satır sayısını hesapladım (ceil ile yukarı yuvarladım).
    int itemsPerRow = 6;
    int totalRows = (int)std::ceil((double)totalCount / (double)itemsPerRow);

    for (int r = 0; r < totalRows; r++)
    {
        // Her satırı, yılan mantığını bilen yardımcı fonksiyona gönderdim.
        printRowSnake(gridValues, totalCount, r, itemsPerRow);
    }
    
    std::cout << "----------------------------------------------------" << std::endl;
    
    // Dinamik bellek kullandığım için işim bitince temizledim.
    delete[] gridValues;
}