/**
 * DebugDistribution.cpp
 * * Amaç: "Ağaçtan Veri Alma (Postorder)" ve "Diğer Altıgene Dağıtma (Circular)"
 * işlemini maksimum görsellik ve matematiksel detayla simüle etmek.
 */

#include <iostream>
#include <iomanip> // std::setw için
#include <string>
#include <windows.h> // Renkler ve Sleep için
#include "BinarySearchTree.hpp"
#include "Hexagon.hpp"


// Renk Kodları
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

void printBox(std::string text, std::string color = RESET) {
    std::cout << color;
    std::cout << "+--------------------------------------------------+" << std::endl;
    std::cout << "| " << std::left << std::setw(48) << text << " |" << std::endl;
    std::cout << "+--------------------------------------------------+" << RESET << std::endl;
}

// Ağacı görselleştirmek için yardımcı (Recursive)
void printTreeVisual(TreeNode* node, int indent = 0, std::string prefix = "Kok: ") {
    if (node == 0) return;
    
    if (node->right) printTreeVisual(node->right, indent + 4, "R-- ");
    
    std::cout << std::string(indent, ' ') << prefix << YELLOW << "[" << node->value << "]" << RESET << std::endl;
    
    if (node->left) printTreeVisual(node->left, indent + 4, "L-- ");
}

// ---------------------------------------------------------
// ANA SİMÜLASYON FONKSİYONU
// ---------------------------------------------------------
void runDeepDebug() {
    printBox("BOLUM 1: ORTAM HAZIRLIGI", CYAN);

    // 1. Kaynak Altıgen ve Ağacı Oluştur
    std::cout << "\n" << CYAN << "1. ADIM: Kaynak Altigen (Source) Olusturuluyor..." << RESET << std::endl;
    Hexagon* sourceHex = new Hexagon();
    BinarySearchTree* sourceTree = new BinarySearchTree();
    
    // Ağacı özel bir yapıda kuralım ki Postorder sırası belirgin olsun
    // Yapı:       50
    //           /    \
    //         30      70
    //        /  \    /  \
    //      20   40  60   80
    // Postorder Beklentisi: Sol->Sağ->Kök 
    // (20, 40, 30), (60, 80, 70), 50 -> [20, 40, 30, 60, 80, 70, 50]
    
    int inputs[] = {50, 30, 70, 20, 40, 60, 80};
    for(int i=0; i<7; i++) sourceTree->insert(inputs[i]);
    sourceHex->addTree(sourceTree);

    std::cout << "Kaynak Agac Yapisi (Yan Yatik Gosterim):" << std::endl;
    // BinarySearchTree sınıfında root erişimi private olduğu için dolaylı yoldan
    // göstermek zorundayız ya da test için public varsayıyoruz.
    // (Burada görselleştirmeyi mantıken anlatıyorum)
    std::cout << "          50" << std::endl;
    std::cout << "        /    \\" << std::endl;
    std::cout << "      30      70" << std::endl;
    std::cout << "     /  \\    /  \\" << std::endl;
    std::cout << "   20   40  60   80" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    // 2. Hedef Altıgeni Oluştur (3 Tane Boş Ağacı Olsun)
    std::cout << "\n" << CYAN << "2. ADIM: Hedef Altigen (Target) Olusturuluyor..." << RESET << std::endl;
    std::cout << "Hedefte 3 adet agac var (Tree 0, Tree 1, Tree 2)." << std::endl;
    
    Hexagon* targetHex = new Hexagon();
    targetHex->addTree(new BinarySearchTree()); // Index 0
    targetHex->addTree(new BinarySearchTree()); // Index 1
    targetHex->addTree(new BinarySearchTree()); // Index 2

    // -----------------------------------------------------
    // İŞLEM BAŞLIYOR: EXTRACTION
    // -----------------------------------------------------
    printBox("BOLUM 2: POSTORDER CIKARMA (EXTRACTION)", MAGENTA);
    
    // Verileri çek
    int nodeCount = sourceTree->getNodeCount();
    int* dataBuffer = new int[nodeCount];
    int extractedCount = 0;
    
    std::cout << "Extraction islemi baslatiliyor..." << std::endl;
    std::cout << "Kural: Sol Cocuk -> Sag Cocuk -> Kok (Postorder)" << std::endl;
    
    sourceTree->extractAllPostOrder(dataBuffer, nodeCount, extractedCount);

    std::cout << "\n" << GREEN << "Cikarilan Veri Paketi (Buffer): " << RESET << std::endl;
    std::cout << "{ ";
    for(int i=0; i<extractedCount; i++) {
        std::cout << YELLOW << dataBuffer[i] << RESET;
        if(i < extractedCount-1) std::cout << ", ";
    }
    std::cout << " }" << std::endl;

    std::cout << "\nAnaliz:" << std::endl;
    std::cout << "20, 40 -> 30 (Sol Alt Agac bitti)" << std::endl;
    std::cout << "60, 80 -> 70 (Sag Alt Agac bitti)" << std::endl;
    std::cout << "50 (Kok en son alindi)" << std::endl;

    // Kaynak ağacı silme simülasyonu
    delete sourceTree; 
    // (Hexagon sınıfı içinde delete yapılır ama burada manuel gösteriyoruz)
    
    std::cout << RED << "Kaynak Agac Bellekten Silindi." << RESET << std::endl << std::endl;

    // -----------------------------------------------------
    // İŞLEM BAŞLIYOR: DISTRIBUTION (DAĞITIM)
    // -----------------------------------------------------
    printBox("BOLUM 3: DAITESEL DAGITIM (DISTRIBUTION)", BLUE);
    std::cout << "Hedef Altigendeki Agac Sayisi (N): " << targetHex->getTreeCount() << std::endl;
    std::cout << "Dagitilacak Veri Sayisi: " << extractedCount << std::endl;
    
    std::cout << "\nBaslamak icin ENTER'a basin..." << std::endl;
    std::cin.get();

    int currentTreeIndex = 0; // Her zaman 0. indeksten (ön) başlar
    int totalTrees = targetHex->getTreeCount();

    for(int i=0; i<extractedCount; i++) {
        int value = dataBuffer[i];
        
        // Matematiksel Hesaplama Görselleştirmesi
        std::cout << BLUE << "--- ADIM " << (i+1) << " ---" << RESET << std::endl;
        std::cout << "Eklenecek Veri: " << YELLOW << value << RESET << std::endl;
        std::cout << "Mevcut Hedef Indeks: " << currentTreeIndex << std::endl;
        
        // Ekleme İşlemi
        targetHex->getTreeAt(currentTreeIndex)->insert(value);
        
        std::cout << "Islem: Target->Tree[" << currentTreeIndex << "]->insert(" << value << ")" << std::endl;
        
        // Görsel Ok
        std::cout << "      " << YELLOW << value << RESET << std::endl;
        std::cout << "      |" << std::endl;
        std::cout << "      V" << std::endl;
        std::cout << "[ Agac " << currentTreeIndex << " ] <-- Eklendi" << std::endl;

        // Bir sonraki indeks hesabı (Matematik)
        int oldIndex = currentTreeIndex;
        currentTreeIndex++;
        
        // Dairesellik kontrolü
        if (currentTreeIndex >= totalTrees) {
            std::cout << "\n" << MAGENTA << ">>> Dairesel Donus Tetiklendi! <<<" << RESET << std::endl;
            std::cout << "Formul: (Index + 1) % AgacSayisi" << std::endl;
            std::cout << "Hesap:  " << currentTreeIndex << " % " << totalTrees << " = " << 0 << std::endl;
            currentTreeIndex = 0;
        } else {
            std::cout << "\nSiradaki Hedef: " << oldIndex << " + 1 = " << currentTreeIndex << std::endl;
        }
        
        std::cout << "---------------------------------" << std::endl;
        Sleep(500); // 0.5 saniye bekle (Gözlem için)
    }

    // -----------------------------------------------------
    // SONUÇ GÖSTERİMİ
    // -----------------------------------------------------
    printBox("SONUC: HEDEF ALTIGEN DURUMU", GREEN);
    
    for(int i=0; i<totalTrees; i++) {
        BinarySearchTree* t = targetHex->getTreeAt(i);
        std::cout << "Agac [" << i << "] Icindeki Veriler (Dugum Sayisi: " << t->getNodeCount() << "): ";
        // İçeriği göstermek için basitçe kökü yazalım veya extract edelim (test için)
        // Burada sadece sayıyı basıyoruz.
        std::cout << " (Root: " << t->getRootValue() << ")" << std::endl;
        
        // İçeriği doğrulamak için manuel kontrol:
        // Tree 0: 20, 60, 50 (3 eleman)
        // Tree 1: 40, 80 (2 eleman)
        // Tree 2: 30, 70 (2 eleman)
        // Sıra: 20->T0, 40->T1, 30->T2, 60->T0, 80->T1, 70->T2, 50->T0
    }

    delete[] dataBuffer;
    // Hexagon destructorları ağaçları temizler.
    delete sourceHex; // İçindeki tree zaten silinmişti ama structure silinsin
    delete targetHex;
}

int main() {
    runDeepDebug();
    return 0;
}