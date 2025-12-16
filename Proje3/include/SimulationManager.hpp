/**
* @file SimulationManager.hpp
* @description : Simülasyonun genel akışını kontrol eden yönetici sınıf.
* Kullanıcıdan tur sayısını alır ve program döngüsünü başlatır.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#ifndef SIMULATIONMANAGER_HPP
#define SIMULATIONMANAGER_HPP

#include "CircularHexagonList.hpp"

class SimulationManager
{
public:
    // Kurucu: İşlem yapılacak listeyi referans olarak alır.
    // Kopyalama yapmaz, doğrudan orijinal liste üzerinde çalışır.
    SimulationManager(CircularHexagonList& list);

    // Programın ana döngüsünü başlatan fonksiyon.
    // Kullanıcıdan girdi ister ve simülasyonu çalıştırır.
    void run();

private:
    // Üzerinde işlem yapılacak altıgen listesi (Referans).
    CircularHexagonList& hexList;

    // Kullanıcıdan pozitif bir tam sayı (tur sayısı) girmesini bekleyen yardımcı fonksiyon.
    int getTurnCountFromUser();

    // Girilen tur sayısı kadar döngü kurarak her turda yapılması gerekenleri
    // (ekran temizleme, yazdırma, veri işleme) çağıran fonksiyon.
    void executeTurns(int totalTurns);
};

#endif