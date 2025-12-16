/**
* @file main.cpp
* @description : Programın giriş noktası (Entry Point).
* Tüm parçaları (Dosya okuma, Veri yapısı, Ekran çıktısı, Simülasyon) burada birleştirdim.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include <iostream>
#include "CircularHexagonList.hpp"
#include "FileHandler.hpp"
#include "SimulationManager.hpp"
#include "ConsolePrinter.hpp"

int main()
{
    // 1. Veri Yapısını Oluşturma
    // Tüm altıgenleri tutacak ana listeyi burada stack'te oluşturdum.
    // Dinamik (new) ile oluşturmadım çünkü main bitince zaten her şey silinecek.
    CircularHexagonList hexList;

    // 2. Verileri Dosyadan Yükleme
    // FileHandler sınıfını "static" metodlarla tasarladığım için
    // nesne oluşturmadan direkt sınıf adıyla çağırdım (Utility Class mantığı).
    if (!FileHandler::loadData("Data.txt", hexList)) {
        // Dosya bulunamazsa veya boşsa programı güvenli şekilde sonlandırıyorum.
        return 0;
    }

    // Güvenlik kontrolü: Dosya var ama içi boş olabilir.
    if (hexList.getHexagonCount() == 0) {
        std::cout << "Islem yapilacak veri yok. Program sonlandiriliyor." << std::endl;
        return 0; 
    }

    // Okuma bitti, başlangıç durumu
    ConsolePrinter::clearScreen();
    
    // Önce tabloyu yılan (snake) formatında bastım.
    ConsolePrinter::printWindowAsSnake(hexList);
    
    // Kullanıcıya bilgi verdim.
    std::cout << "Tum veriler hazir." << std::endl;
    std::cout << "Toplam Altigen: " << hexList.getHexagonCount() << std::endl;

    // 3. Simülasyon
    // Simülasyon yöneticisine listeyi referans (&) olarak verdim.
    // Böylece kopyalama yapmadan orijinal liste üzerinde çalışılmasını sağladım.
    SimulationManager simManager(hexList);
    simManager.run();
    
    return 0;
}