#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <windows.h>
#include "BinarySearchTree.hpp"
#include "CircularHexagonList.hpp"
#include "ConsolePrinter.hpp"

// Dosya okuma ve görselleştirme fonksiyonu
void loadDataFromFile(const char* fileName, CircularHexagonList& hexList)
{
    std::string filePath = fileName;
    std::ifstream fileCheck(filePath.c_str());
    
    if (!fileCheck.is_open()) {
        filePath = "../" + std::string(fileName);
        fileCheck.open(filePath.c_str());
    }
    
    if (!fileCheck.is_open()) {
        std::cout << "HATA: Dosya acilamadi: " << fileName << std::endl;
        return;
    }

    // --- ADIM 1: ÖN HESAPLAMA VE BOŞ GÖSTERİM ---
    int lineCount = 0;
    std::string line;
    while (std::getline(fileCheck, line)) {
        if (!line.empty()) {
            std::stringstream ss(line);
            int dummy;
            if (ss >> dummy) lineCount++;
        }
    }
    fileCheck.close();

    int totalHexagons = (int)std::ceil((double)lineCount / 6.0);

    // Boş altıgenleri oluştur
    for (int i = 0; i < totalHexagons; i++) {
        hexList.createAndAppendHexagon();
    }

    ConsolePrinter::clearScreen();
    // İlk durumu göster (Boş oldukları için # basılacak)
    hexList.printWindowAsSnake(hexList.getHead());

    std::cout << "Verileri okumak icin bir tusa basin..." << std::endl;
    std::cin.get(); // Kullanıcıdan tuş bekle

    // --- ADIM 2: VERİ YÜKLEME VE CANLI GÜNCELLEME ---
    std::ifstream file(filePath.c_str());
    Hexagon* currentHex = hexList.getHead(); 
    int treesInCurrentHex = 0;
    int hexFilledCount = 0;
    Hexagon* windowStart = hexList.getHead();

    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        std::stringstream checkSS(line);
        int dummy;
        if (!(checkSS >> dummy)) continue;

        BinarySearchTree* tree = new BinarySearchTree();
        std::stringstream ss(line);
        int value;
        while (ss >> value) {
            tree->insert(value);
        }

        if (currentHex != 0) {
            currentHex->addTree(tree);
            treesInCurrentHex++;

            // Altıgen dolunca güncelleme yap
            if (treesInCurrentHex >= 6) {
                hexFilledCount++;

                // Her 18 altıgende bir ekranı yenile
                if (hexFilledCount % 18 == 0) {
                    ConsolePrinter::clearScreen();
                    std::cout << "Veri yukleniyor... (" << hexFilledCount << " / " << totalHexagons << " altigen doldu)" << std::endl;
                    hexList.printWindowAsSnake(windowStart);
                    
                    // YAVAŞLATILMIŞ GÖSTERİM (300ms)
                    Sleep(300);
                    
                    windowStart = currentHex->getNext();
                }

                currentHex = currentHex->getNext();
                treesInCurrentHex = 0;
            }
        }
    }

    // Son kalan kısmı göster
    if (hexFilledCount % 18 != 0 || treesInCurrentHex > 0) {
         ConsolePrinter::clearScreen();
         std::cout << "Veri yukleme tamamlandi." << std::endl;
         hexList.printWindowAsSnake(windowStart);
         Sleep(500);
    }

    file.close();
}

int main()
{
    CircularHexagonList hexList;

    // 1. Veri Okuma ve Animasyon
    loadDataFromFile("Data.txt", hexList);

    if (hexList.getHexagonCount() == 0) {
        std::cout << "Veri yuklenemedigi icin program sonlandiriliyor." << std::endl;
        return 0; 
    }

    // Okuma bitti, en başa dön
    ConsolePrinter::clearScreen();
    std::cout << "Tum veriler hazir. Baslangic Durumu:" << std::endl;
    hexList.printWindowAsSnake(hexList.getHead());

    // 2. Tur Sayısı Girişi (Sadece Sayı Kontrolü)
    int totalTurns = 0;
    while (true) {
        std::cout << "Tur sayisini giriniz : ";
        if (std::cin >> totalTurns) {
            if (totalTurns > 0) {
                break;
            } else {
                std::cout << "Lutfen 0'dan buyuk bir sayi giriniz." << std::endl;
            }
        } else {
            std::cout << "Hatali giris! Lutfen sadece sayi giriniz." << std::endl;
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    
    // Enter tuşunu temizle
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    // 3. Simülasyonu Başlat (Direkt Geçiş)
    for (int i = 1; i <= totalTurns; i++)
    {
        hexList.processTurn(i);

        ConsolePrinter::clearScreen();
        std::cout << "Tur : " << i << std::endl;
        hexList.printWindowAsSnake(hexList.getHead());
        
        // Tur geçiş hızı (100ms)
        Sleep(100);
    }

    std::cout << "Tum turlar tamamlandi. Program sonu." << std::endl;
    
    // BURADAKİ BEKLEME KALDIRILDI:
    // std::cin.get(); 
    
    return 0;
}