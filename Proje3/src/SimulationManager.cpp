/**
* @file SimulationManager.cpp
* @description : Simülasyonun akışını ve kullanıcı etkileşimini yöneten kaynak dosya.
* Kullanıcıdan güvenli veri alma ve tur döngülerini burada kurguladım.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include "SimulationManager.hpp"
#include "ConsolePrinter.hpp"
#include <iostream>
#include <limits> // std::numeric_limits için gerekli

// Kurucu Fonksiyon
SimulationManager::SimulationManager(CircularHexagonList& list) 
    : hexList(list) 
{
    // 'hexList' bir referans üyesi olduğu için constructor gövdesinde değil,
    // başlatma listesinde (initializer list) atama yapmam zorunluydu.
    // Ayrıca referans kullanarak koca listeyi kopyalamaktan kaçındım.
}

// Kullanıcıdan Tur Sayısını İsteyen Fonksiyon
int SimulationManager::getTurnCountFromUser()
{
    int totalTurns = 0;
    while (true) {
        std::cout << "Tur sayisini giriniz : ";

        if (std::cin >> totalTurns) {
            if (totalTurns > 0) {
                break; // Geçerli sayı girildiyse döngüden çık.
            } else {
                std::cout << "Lutfen 0'dan buyuk bir sayi giriniz." << std::endl;
            }
        } else {
            // Hatalı giriş (harf vb.) yapıldıysa:
            std::cout << "Hatali giris! Lutfen sadece sayi giriniz." << std::endl;
            
            // 1. Hata bayrağını temizle.
            std::cin.clear();
            
            // 2. Tamponda kalan hatalı karakterleri temizle (yoksa döngü sürekli döner).
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    // Enter tuşunun tamponda kalmasını önlemek için bir temizlik daha yaptım.
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    return totalTurns;
}

// Turları sırasıyla çalıştıran fonksiyon
void SimulationManager::executeTurns(int totalTurns)
{
    // İstenen tur sayısı kadar döngü kurdum.
    for (int i = 1; i <= totalTurns; i++)
    {
        // 1. O tura ait işlemleri (ağaç çıkarma, dağıtma) yaptım.
        hexList.processTurn(i);

        // 2. Ekranı temizledim ki animasyon gibi görünsün.
        ConsolePrinter::clearScreen();
        
        // 3. Güncel durumu yılan formatında ekrana bastım.
        ConsolePrinter::printWindowAsSnake(hexList);
        
        // Tur bilgisini ve toplam altıgen sayısını gösterdim.
        std::cout << "Tur : " << i << " / Toplam Altigen: " << hexList.getHexagonCount() << std::endl;
    }
}

// Programı başlatan ana fonksiyon
void SimulationManager::run()
{
    // Önce kullanıcıdan kaç tur istediğini aldım.
    int turns = getTurnCountFromUser();
    
    // Sonra simülasyonu başlattım.
    executeTurns(turns);

    std::cout << "Tum turlar tamamlandi." << std::endl;
}