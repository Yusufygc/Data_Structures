/**
 * Test.cpp
 * Proje İsterleri Doğrulama Modülü (Full Gerçek Veri Entegrasyonu)
 *
 * Bu modül, Data.txt dosyasından okunan gerçek satırları kullanarak:
 * 1. BST yapısının doğruluğunu (Kök kontrolü, eleman sayısı),
 * 2. Öncelikli Kuyruk mantığını (En yüksek ağacın seçilmesi),
 * 3. Veri dağıtım mantığını (Eşit dağılım) test eder.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cmath> // abs icin
#include "BinarySearchTree.hpp"
#include "Hexagon.hpp"
#include "CircularHexagonList.hpp"
#include "ConsolePrinter.hpp"

// Renkli çıktılar
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

void printHeader(const char* title) {
    std::cout << "\n" << BLUE << "========================================" << RESET << std::endl;
    std::cout << BLUE << " TEST: " << title << RESET << std::endl;
    std::cout << BLUE << "========================================" << RESET << std::endl;
}

void assertTest(bool condition, const char* message) {
    if (condition) {
        std::cout << GREEN << "[PASS] " << message << RESET << std::endl;
    } else {
        std::cout << RED << "[FAIL] " << message << RESET << std::endl;
    }
}

// ---------------------------------------------------------
// YARDIMCI: Data.txt'den BELİRLİ BİR SATIRI okur
// targetLineIndex: 0'dan başlar (0 = ilk satır)
// ---------------------------------------------------------
int* readLineAtIndex(const char* filename, int targetLineIndex, int& outCount) {
    std::string filePath = filename;
    std::ifstream file(filePath.c_str());
    
    // Dosya yolu kontrolü
    if (!file.is_open()) {
        filePath = "../" + std::string(filename);
        file.open(filePath.c_str());
    }

    if (!file.is_open()) {
        std::cout << RED << "HATA: " << filename << " acilamadi!" << RESET << std::endl;
        outCount = 0;
        return 0;
    }

    std::string line;
    int currentIndex = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue; // Boş satırları atla ama indeksi artırma
        
        // Bu satırda sayı var mı kontrol et
        std::stringstream ssCheck(line);
        int temp;
        if (!(ssCheck >> temp)) continue; 

        // Hedef satıra geldik mi?
        if (currentIndex == targetLineIndex) {
            // Sayı adedini bul
            std::stringstream ssCount(line);
            int count = 0;
            int val;
            while (ssCount >> val) count++;

            if (count == 0) { file.close(); return 0; }

            // Diziyi oluştur ve doldur
            int* data = new int[count];
            std::stringstream ssRead(line);
            int i = 0;
            while (ssRead >> val) {
                data[i++] = val;
            }
            
            outCount = count;
            file.close();
            return data; 
        }
        
        currentIndex++;
    }

    file.close();
    std::cout << YELLOW << "Uyari: Dosyada " << targetLineIndex << ". satir bulunamadi." << RESET << std::endl;
    outCount = 0;
    return 0;
}

// ---------------------------------------------------------
// TEST 1: BST Temel Mantık (Data.txt Satır 0 ile)
// ---------------------------------------------------------
void testBinarySearchTree() {
    printHeader("BST Mantigi (Data.txt Satir 0)");
    
    int count = 0;
    int* data = readLineAtIndex("Data.txt", 0, count); // İlk satırı oku

    if (!data) {
        std::cout << RED << "[SKIP] Yeterli veri yok." << RESET << std::endl;
        return;
    }

    BinarySearchTree* tree = new BinarySearchTree();
    for(int i=0; i<count; i++) {
        tree->insert(data[i]);
    }

    std::cout << "Okunan Veri Sayisi: " << count << std::endl;
    std::cout << "Agac Kok Degeri: " << tree->getRootValue() << std::endl;

    assertTest(!tree->isEmpty(), "Agac bos degil");
    // İlk giren eleman kök olmalı (BST kuralı)
    assertTest(tree->getRootValue() == data[0], "Kok degeri dosyadaki ilk sayi ile eslesti");
    assertTest(tree->getNodeCount() == count, "Dugum sayisi dosyadaki sayi adedi ile eslesti");
    
    int h = tree->getHeight();
    std::cout << "Agac Yuksekligi: " << h << std::endl;
    assertTest(h >= 1, "Yukseklik hesaplandi");

    delete tree;
    delete[] data;
}

// ---------------------------------------------------------
// TEST 2: Öncelik Mantığı (Data.txt Satır 1, 2, 3 ile)
// ---------------------------------------------------------
void testHexagonPriority() {
    printHeader("Kuyruk Oncelik Mantigi (Data.txt Satir 1-2-3)");
    
    Hexagon* hex = new Hexagon();
    int maxObservedHeight = -1;
    int expectedRootValue = -1;

    // 3 farklı satırı oku ve 3 ağaç oluştur
    for(int i=1; i<=3; i++) {
        int count = 0;
        int* data = readLineAtIndex("Data.txt", i, count);
        
        if (data) {
            BinarySearchTree* tree = new BinarySearchTree();
            for(int j=0; j<count; j++) tree->insert(data[j]);
            
            int h = tree->getHeight();
            int root = tree->getRootValue();
            
            std::cout << "Agac " << i << " -> Yukseklik: " << h << " | Kok: " << root << std::endl;

            // En yüksek olanı takip et (Beklenen sonucu belirlemek için)
            if (h > maxObservedHeight) {
                maxObservedHeight = h;
                expectedRootValue = root;
            }
            
            hex->addTree(tree);
            delete[] data;
        }
    }

    if (hex->getTreeCount() < 2) {
        std::cout << YELLOW << "[SKIP] Yeterli satir okunmadi (En az 2 agac lazim)." << RESET << std::endl;
        delete hex;
        return;
    }

    // TEST: Çift turlarda (Priority) en yüksek olan çıkmalı
    std::cout << YELLOW << "Beklenen (En Yuksek) Agac Koku: " << expectedRootValue << RESET << std::endl;

    BinarySearchTree* pTree = hex->popPriorityTree();
    
    assertTest(pTree != 0, "Oncelikli agac kuyruktan cikarildi");
    if (pTree) {
        std::cout << "Cikarilan Agac Koku: " << pTree->getRootValue() << " | Yukseklik: " << pTree->getHeight() << std::endl;
        
        // Eşit yükseklik durumunda FIFO bozulabilir ama en yükseklerden biri gelmeli
        assertTest(pTree->getHeight() == maxObservedHeight, "En yuksek agac basariyla secildi");
        
        // Eğer yükseklikleri eşit birden fazla ağaç varsa, kodumuz ilkini alır.
        // Bu durumda kök değeri farklı olabilir ama yükseklik kesinlikle max olmalı.
        
        delete pTree;
    }
    
    delete hex;
}

// ---------------------------------------------------------
// TEST 3: Veri Dağıtım Mantığı (Data.txt Satır 4 ile)
// ---------------------------------------------------------
void testDistributionWithRealData() {
    printHeader("Veri Dagitim Mantigi (Data.txt Satir 4)");

    int dataCount = 0;
    // 4. satırdaki verileri okuyup bir paket (array) haline getir
    int* realData = readLineAtIndex("Data.txt", 4, dataCount);

    if (realData == 0) {
        std::cout << YELLOW << "[SKIP] Satir 4 okunamadi." << RESET << std::endl;
        return;
    }

    std::cout << "Dagitilacak Veri Paketi (" << dataCount << " adet): ";
    for(int i=0; i<dataCount && i<5; i++) std::cout << realData[i] << " ";
    if(dataCount > 5) std::cout << "...";
    std::cout << std::endl;

    Hexagon* hex = new Hexagon();
    
    // 3 tane boş ağaç ekleyelim (Hedef ağaçlar)
    BinarySearchTree* t1 = new BinarySearchTree();
    BinarySearchTree* t2 = new BinarySearchTree();
    BinarySearchTree* t3 = new BinarySearchTree();
    hex->addTree(t1); hex->addTree(t2); hex->addTree(t3);

    // Gerçek verileri dağıt
    hex->distributeValues(realData, dataCount);

    // Kontrol: Veriler eşit dağılmalı (veya 1 farkla)
    int c1 = t1->getNodeCount();
    int c2 = t2->getNodeCount();
    int c3 = t3->getNodeCount();

    std::cout << "Hedef Agaclara Dusan Elemanlar: " << c1 << ", " << c2 << ", " << c3 << std::endl;

    int totalNodes = c1 + c2 + c3;
    assertTest(totalNodes == dataCount, "Tum veriler eksiksiz dagitildi");
    
    // Dairesel dağıtım farkı en fazla 1 olabilir
    bool balanced = (std::abs(c1 - c2) <= 1) && (std::abs(c1 - c3) <= 1) && (std::abs(c2 - c3) <= 1);
    assertTest(balanced, "Veriler dengeli (sirayla) dagitildi");

    delete[] realData;
    delete hex;
}

int main() {
    // Windows konsolunu temizle
    ConsolePrinter::clearScreen(); 
    
    std::cout << "GERCEK VERI SETI ILE DEBUG MODU BASLATILIYOR..." << std::endl;
    std::cout << "Kullanilan Dosya: Data.txt\n" << std::endl;
    
    testBinarySearchTree();
    testHexagonPriority();
    testDistributionWithRealData();

    std::cout << "\n" << GREEN << "DEBUG ISLEMI TAMAMLANDI." << RESET << std::endl;
    
    // Kapanmadan önce beklesin
    std::cout << "Cikmak icin Enter'a basin..." << std::endl;
    std::cin.get();
    
    return 0;
}