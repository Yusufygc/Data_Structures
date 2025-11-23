/** 
* @file FileManager.hpp
* @description = Bu sınıf, MainList nesnelerinin dosyaya kaydedilmesi ve dosyadan yüklenmesi için statik fonksiyonlar sağlar.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#include "MainList.hpp"

class FileManager {
    public:
        static bool save(const MainList& list, const char* path); // kayıt
        static bool load(MainList& list, const char* path);       // yükleme
};

#endif