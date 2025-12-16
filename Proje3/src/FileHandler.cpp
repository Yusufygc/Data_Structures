/**
* @file FileHandler.cpp
* @description : Dosya okuma işlemlerini gerçekleştiren kaynak dosya.
* Dosyadan satır satır veri okuma, temizleme ve sayıları ayıklama işlemlerini burada yaptım.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include "FileHandler.hpp"
#include "ConsolePrinter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <conio.h> // _getch() fonksiyonu için

// Dosyanın yerini bulmak bazen sorun olabiliyor, o yüzden bu kontrolü ekledim.
std::string FileHandler::getValidFilePath(const char* fileName) {
    std::string path = fileName;
    std::ifstream file(path.c_str());
    
    // Bazen IDE'ler executable dosyasını farklı klasöre atıyor.
    // O yüzden dosya mevcut klasörde yoksa bir üst klasöre ("../") bakmasını sağladım.
    if (!file.is_open()) {
        path = "../" + std::string(fileName);
    } else {
        file.close();
    }
    return path;
}

// Data dosyasında [..] gibi kısımlar olabiliyor, bunları temizlemek için yazdım.
std::string FileHandler::cleanLine(const std::string& line) {
    // ']' işaretini bulup sonrasını (sayıları) alıyorum.
    size_t bracketPos = line.find(']');
    if (bracketPos != std::string::npos) {
        return line.substr(bracketPos + 1);
    }
    return line; // Eğer parantez yoksa olduğu gibi döndür.
}

// Dosyadaki bir satırdan koca bir İkili Arama Ağacı üreten fonksiyon.
BinarySearchTree* FileHandler::createTreeFromLine(const std::string& line) {
    // Önce gereksiz karakterleri temizledim.
    std::string cleanedData = cleanLine(line);
    
    if (cleanedData.empty()) return 0;

    // Stringstream kullanarak satırın içinde gerçekten sayı var mı kontrol ettim.
    // Bazen boş satırlar programı patlatabiliyor.
    std::stringstream controlStream(cleanedData);
    int checkVal;
    if (!(controlStream >> checkVal)) return 0;

    // Gerçek verileri okuyup ağaca ekleme kısmı.
    BinarySearchTree* newTree = new BinarySearchTree();
    std::stringstream dataStream(cleanedData);
    int value;
    
    // while döngüsü ile "okuyabildiğin sürece al" mantığı kurdum.
    // Böylece satırda kaç tane sayı olduğu fark etmiyor.
    while (dataStream >> value) {
        newTree->insert(value);
    }
    
    return newTree;
}

// Toplam satır sayısına göre kaç tane altıgen gerektiğini hesaplayıp listeyi oluşturdum.
int FileHandler::initializeListStructure(CircularHexagonList& hexList, int lineCount) {
    if (lineCount <= 0) return 0;

    // Her altıgen 6 ağaç tutuyor. Toplam sayıyı 6'ya böldüm.
    int totalHexagons = (int)std::ceil((double)lineCount / 6.0);

    // Hesaplanan sayı kadar boş altıgeni listeye ekledim.
    for (int i = 0; i < totalHexagons; i++) {
        hexList.createAndAppendHexagon();
    }
    
    return totalHexagons;
}

// Dosyadaki toplam satır sayısını saydım ki ona göre yer ayırayım.
int FileHandler::countLines(const char* fileName)
{
    std::string validPath = getValidFilePath(fileName);
    std::ifstream file(validPath.c_str());
    
    if (!file.is_open()) return 0;

    int totalLines = 0;
    std::string rawLine;
    
    while (std::getline(file, rawLine)) {
        std::string processed = cleanLine(rawLine);
        if (!processed.empty()) {
            std::stringstream ss(processed);
            int temp;
            // Sadece dolu satırları saydım, boşlukları atladım.
            if (ss >> temp) totalLines++;
        }
    }
    file.close();
    return totalLines;
}

// Ana fonksiyon: Tüm dosya okuma sürecini yönetiyor.
bool FileHandler::loadData(const char* fileName, CircularHexagonList& hexList)
{
    // 1. Dosya Yolu Kontrolü
    std::string filePath = getValidFilePath(fileName);
    std::ifstream file(filePath.c_str());
    
    if (!file.is_open()) {
        std::cout << "HATA: Dosya bulunamadi -> " << fileName << std::endl;
        return false;
    }

    // 2. Satır Sayısı ve Liste Hazırlığı
    int lineCount = countLines(fileName); 
    if (lineCount == 0) {
        file.close();
        return false;
    }

    // Listeyi baştan kaç tane olacağını bilerek oluşturdum.
    int totalHexagons = initializeListStructure(hexList, lineCount);

    // 3. Kullanıcı Arayüzü (Boş Durum Gösterimi)
    // Önce boş tabloyu gösterip kullanıcıdan tuşa basmasını istedim.
    ConsolePrinter::clearScreen();
    ConsolePrinter::printWindowAsSnake(hexList);
    
    std::cout << "Bos Altigenler Olusturuldu." << std::endl;
    std::cout << "Toplam Altigen Sayisi: " << totalHexagons << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Verileri dosyadan yuklemek icin bir tusa basin..." << std::endl;
    _getch(); 

    // 4. Verilerin Okunması ve Ağaçların Yerleştirilmesi
    Hexagon* currentHex = hexList.getHead(); 
    int treesInCurrentHex = 0;
    std::string lineReader;

    while (std::getline(file, lineReader))
    {
        // Yardımcı fonksiyonu kullanarak satırdan ağacı oluşturdum.
        BinarySearchTree* newTree = createTreeFromLine(lineReader);

        if (newTree != 0) {
            if (currentHex != 0) {
                currentHex->addTree(newTree);
                treesInCurrentHex++;

                // Bir altıgen dolunca (6 ağaç olunca) sıradaki altıgene geçtim.
                // Circular linked list olduğu için otomatik başa dönüyor.
                if (treesInCurrentHex >= 6) {
                    currentHex = currentHex->getNext();
                    treesInCurrentHex = 0;
                }
            }
        }
    }

    file.close();

    // 5. Son Durumun Gösterilmesi
    ConsolePrinter::clearScreen();
    ConsolePrinter::printWindowAsSnake(hexList);
    std::cout << "Veri yukleme tamamlandi. Toplam Altigen: " << totalHexagons << std::endl;

    return true;
}