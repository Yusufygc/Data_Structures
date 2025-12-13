#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <windows.h> // Sleep için
#include "BinarySearchTree.hpp"
#include "CircularHexagonList.hpp"
#include "ConsolePrinter.hpp"

// --- YENİ GÖRÜNTÜLEME FONKSİYONU (YILAN MODU) ---
// Tüm altıgenleri 6 sütunluk tablo halinde, YILAN (SNAKE) mantığıyla basar.
// 1. Satır: Sol -> Sağ
// 2. Satır: Sağ -> Sol (Ters)
// 3. Satır: Sol -> Sağ ...
void printFullGrid(const CircularHexagonList& hexList)
{
    Hexagon* current = hexList.getHead();
    int count = hexList.getHexagonCount();

    if (current == 0 || count == 0) {
        std::cout << "Liste Bos." << std::endl;
        return;
    }

    std::cout << "--- TUM ALTIGENLERIN DURUMU (YILAN GOSTERIMI) ---" << std::endl;
    std::cout << "Toplam Altigen: " << count << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    // 1. ADIM: Tüm değerleri geçici bir diziye al (Dolaşımı kolaylaştırmak için)
    int* values = new int[count];
    Hexagon* temp = current;
    for(int i = 0; i < count; i++) {
        if(temp->isEmpty()) {
            values[i] = -1; // Boş ise işaretçi
        } else {
            values[i] = temp->calculateSpecialDisplayValue();
        }
        temp = temp->getNext();
    }

    // 2. ADIM: Satır satır yılan mantığıyla yazdır
    int totalRows = (int)std::ceil((double)count / 6.0);

    for (int r = 0; r < totalRows; r++)
    {
        int startIdx = r * 6;
        
        // Çift Satırlar (0, 2, 4...): DÜZ (Sol -> Sağ)
        if (r % 2 == 0)
        {
            for (int k = 0; k < 6; k++)
            {
                int idx = startIdx + k;
                if (idx < count) {
                    if (values[idx] == -1) std::cout << "^#\t";
                    else std::cout << values[idx] << "\t";
                } else {
                    std::cout << " \t"; // Liste bittiyse boşluk
                }
            }
        }
        // Tek Satırlar (1, 3, 5...): TERS (Sağ -> Sol)
        else
        {
            // Ters sırada yazdırırken hizalamanın doğru olması için
            // mantıksal sıradaki en sondakini (start + 5) en başa (sola) yazmalıyız.
            // Böylece görsel olarak sağdan sola doluyormuş gibi görünür.
            // Örnek: 11 10 9 8 7 6  -> Ekranda böyle görünürse 6 en sağda kalır (5'in altı).
            
            for (int k = 5; k >= 0; k--)
            {
                int idx = startIdx + k;
                if (idx >= count) {
                    std::cout << " \t"; // Henüz o indekste veri yoksa (Padding)
                } else {
                    if (values[idx] == -1) std::cout << "^#\t";
                    else std::cout << values[idx] << "\t";
                }
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "----------------------------------------------------" << std::endl;
    delete[] values;
}

// Dosya okuma (Main.cpp ile aynı mantık ama printFullGrid kullanıyor)
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

    for (int i = 0; i < totalHexagons; i++) {
        hexList.createAndAppendHexagon();
    }

    ConsolePrinter::clearScreen();
    // İlk boş durumu yılan şeklinde göster
    printFullGrid(hexList);

    std::cout << "Verileri okumak icin bir tusa basin..." << std::endl;
    std::cin.get(); 

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

            if (treesInCurrentHex >= 6) {
                hexFilledCount++;
                
                // Her satır dolduğunda (6 altıgen) ekranı güncelle
                if (hexFilledCount % 6 == 0) {
                    ConsolePrinter::clearScreen();
                    std::cout << "Veri yukleniyor... (" << hexFilledCount << " / " << totalHexagons << ")" << std::endl;
                    printFullGrid(hexList);
                    Sleep(100); 
                }

                currentHex = currentHex->getNext();
                treesInCurrentHex = 0;
            }
        }
    }

    if (hexFilledCount % 6 != 0 || treesInCurrentHex > 0) {
         ConsolePrinter::clearScreen();
         std::cout << "Veri yukleme tamamlandi." << std::endl;
         printFullGrid(hexList);
         Sleep(500);
    }

    file.close();
}

int main()
{
    CircularHexagonList hexList;

    loadDataFromFile("Data.txt", hexList);

    if (hexList.getHexagonCount() == 0) {
        std::cout << "Veri yok." << std::endl;
        return 0; 
    }

    ConsolePrinter::clearScreen();
    std::cout << "BASLANGIC DURUMU" << std::endl;
    printFullGrid(hexList);

    int totalTurns = 0;
    while (true) {
        std::cout << "Tur sayisini giriniz (Debug Modu): ";
        if (std::cin >> totalTurns) {
            if (totalTurns > 0) break;
            else std::cout << "Pozitif sayi giriniz." << std::endl;
        } else {
            std::cout << "Sadece sayi!" << std::endl;
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    for (int i = 1; i <= totalTurns; i++)
    {
        hexList.processTurn(i);

        ConsolePrinter::clearScreen();
        std::cout << "Tur : " << i << std::endl;
        printFullGrid(hexList);
        
        Sleep(200); 
    }

    std::cout << "Debug turlari tamamlandi." << std::endl;
    //std::cin.get(); 
    return 0;
}