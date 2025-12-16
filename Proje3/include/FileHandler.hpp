/**
* @file FileHandler.hpp
* @description : Dosya okuma işlemlerini yöneten sınıf.
* @course      : 1.Öğretim C grubu 
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/
#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include "CircularHexagonList.hpp"
#include <string>


class FileHandler
{
public:
    // Ana fonksiyon: Süreci yönetir.
    static bool loadData(const char* fileName, CircularHexagonList& hexList);

private:
    // 1. Yardımcı: Dosyadaki satır sayısını sayar.
    static int countLines(const char* fileName);

    // 2. Yardımcı: Satırdaki gereksiz karakterleri (köşeli parantez vb.) temizler.
    static std::string cleanLine(const std::string& line);

    // 3. Yardımcı: Temizlenmiş bir satırdan BinarySearchTree oluşturur.
    static BinarySearchTree* createTreeFromLine(const std::string& line);

    // 4. Yardımcı: Toplam satır sayısına göre boş altıgen listesini hazırlar.
    // Geriye toplam altıgen sayısını döndürür.
    static int initializeListStructure(CircularHexagonList& hexList, int lineCount);
    
    // 5. Yardımcı: Dosya yolunu doğrular (../ kontrolü yapar)
    static std::string getValidFilePath(const char* fileName);
};

#endif