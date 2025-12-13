#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <limits> // numeric_limits için
#include <windows.h> // Sleep fonksiyonu için
#include "BinarySearchTree.hpp"
#include "CircularHexagonList.hpp"
#include "ConsolePrinter.hpp"

// Dosya okuma ve 18'li paketler halinde gorsellestirme fonksiyonu
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

    // 1. ADIM: Satır sayısını bularak toplam altıgen sayısını hesapla
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

    // 2. ADIM: Boş altıgenleri önceden oluştur
    for (int i = 0; i < totalHexagons; i++) {
        hexList.createAndAppendHexagon();
    }

    // İlk boş durumu (ilk 18'li) ekrana bas
    ConsolePrinter::clearScreen();
    std::cout << "Dosya okuma baslatiliyor..." << std::endl;
    std::cout << "Toplam Altigen Kapasitesi: " << totalHexagons << std::endl;
    
    Hexagon* windowStart = hexList.getHead();
    hexList.printWindowAsSnake(windowStart);

    // Kullanıcı ilk boş ekranı görsün diye bekleme
    Sleep(100);

    // 3. ADIM: Dosyayı tekrar aç ve verileri doldur
    std::ifstream file(filePath.c_str());
    Hexagon* currentHex = hexList.getHead(); 
    int treesInCurrentHex = 0;
    int hexFilledCount = 0;

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

            // Eğer altıgen dolduysa (6 ağaç)
            if (treesInCurrentHex >= 6) {
                
                hexFilledCount++;

                // Her 18 altıgen dolduğunda ekranı güncelle
                if (hexFilledCount % 18 == 0) {
                    ConsolePrinter::clearScreen();
                    std::cout << "Veri yukleniyor... (" << hexFilledCount << " / " << totalHexagons << " altigen doldu)" << std::endl;
                    
                    hexList.printWindowAsSnake(windowStart);
                    
                    // --- GÜNCELLEME 1: YAVAŞLATILMIŞ GÖSTERİM ---
                    // Değişimi gözle görebilmek için 300 ms bekleme
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
         std::cout << "Veri yukleme tamamlanmak uzere..." << std::endl;
         hexList.printWindowAsSnake(windowStart);
         Sleep(500);
    }

    file.close();
}

int main()
{
    CircularHexagonList hexList;

    // 1) Verileri oku ve animasyonlu göster
    loadDataFromFile("Data.txt", hexList);

    if (hexList.getHexagonCount() == 0) {
        std::cout << "Veri yuklenemedigi icin program sonlandiriliyor." << std::endl;
        return 0; 
    }

    // Okuma bitti, başa dön
    ConsolePrinter::clearScreen();
    std::cout << "Tum veriler yuklendi. Baslangic Durumu:" << std::endl;
    hexList.printWindowAsSnake(hexList.getHead());

    // --- GÜNCELLEME 2: TUR SAYISI GİRİŞİ ve KONTROLÜ ---
    int totalTurns = 0;
    
    while (true) {
        std::cout << "Tur sayisini giriniz : ";
        if (std::cin >> totalTurns) {
            if (totalTurns > 0) {
                break; // Geçerli bir sayı girildi
            } else {
                std::cout << "Lutfen 0'dan buyuk bir sayi giriniz." << std::endl;
            }
        } else {
            // Hatalı giriş (harf vb.) durumunda akışı temizle
            std::cout << "Hatali giris! Lutfen sadece sayi giriniz." << std::endl;
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    
    // Enter karakterini temizle (gerekirse)
    // std::cin.ignore(); 

    // --- GÜNCELLEME 3: DİREKT BAŞLAMA ---
    // "Baslamak icin tusa basin" kısmı kaldırıldı.
    // Kullanıcı sayıyı girip Enter'a basınca direkt döngü başlar.

    // 3) Tur Döngüsü
    for (int i = 1; i <= totalTurns; i++)
    {
        hexList.processTurn(i);

        ConsolePrinter::clearScreen();
        std::cout << "Tur : " << i << std::endl;
        hexList.printWindowAsSnake(hexList.getHead());
        
        // Tur geçişlerinde hafif bekleme (100 ms)
        Sleep(100);
    }

    std::cout << "Tum turlar tamamlandi. Program sonu." << std::endl;
    return 0;
}