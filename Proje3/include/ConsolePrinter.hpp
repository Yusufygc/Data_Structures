/** 
* @file ConsolePrinter.hpp
* @description : Konsol ekranına yazdırma işlemlerini yöneten sınıfın başlık dosyasıdır.
* Bu sınıf, altıgen veri yapısındaki ağaçların özel matematiksel değerlerini hesaplayarak (Kök/EnYüksekKök),
* elde edilen bu değerleri 6 sütunlu bir tablo halinde ekrana basar.
* Özellikle 'Yılan (Snake)' algoritması kullanılarak, çift satırların soldan sağa, tek satırların ise sağdan sola doğru yazdırılmasını sağlar.
* @course      : 1.Öğretim C grubu 
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#ifndef CONSOLEPRINTER_HPP
#define CONSOLEPRINTER_HPP

#include "CircularHexagonList.hpp"

class ConsolePrinter
{
public:
    // Ekranı temizleyen fonksiyon (Windows için cls, Linux için clear çalıştırır).
    static void clearScreen();

    // Listeyi alıp proje isterine uygun şekilde yılan gibi kıvrılarak ekrana basan ana fonksiyon.
    static void printWindowAsSnake(const CircularHexagonList& list);

private:
    // Tüm listeyi dolaşıp, ekrana basılacak özel değerleri (bölüm sonuçlarını)
    // hesaplayıp bir diziye aktaran fonksiyon.
    // 'outCount' parametresi referans olduğu için eleman sayısını dışarıya söyler.
    static int* prepareGridData(const CircularHexagonList& list, int& outCount);

    // Hazırlanan diziden sadece o satıra ait olan kısmı ekrana basar.
    // Satır numarası çiftse düz(0,2,4...), tekse(1,3,5...) ters (sağdan sola) yazar.
    static void printRowSnake(const int* values, int totalCount, int rowIndex, int rowWidth);
};

#endif