/** 
* @file FileManager.cpp
* @description = Bu dosya, MainList içindeki MainNode'lar ve 
                onların ShapeList'lerindeki şekillerin
                dosyaya kaydedilmesi ve dosyadan yüklenmesi işlemlerini gerçekleştirir
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
/*
    metin formatı:
    satır1: mainNodeCount
    sonra her düğüm için: shapeCount ve shapeCount satır: type x y size ch z
        type: 'R' dikdörtgen, 'T' üçgen, 'S' yıldız
        x,y: poz
        size: temel boyut
        ch: çizim karakteri
        z: çizim önceliği

*/
#include <fstream>
#include "FileManager.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Star.hpp"
#include "ClampUtil.hpp"

static void writeShape(std::ofstream &fileWriter, const Shape* shape){
// tür tespiti için dynamic_cast kullandım bu sayede farklı şekil türleri ayırt edilebilir
// dynamic_cast => çalışma zamanında tür kontrolü ve dönüştürme yapar
    char shapeType='R';
    if(dynamic_cast<const Triangle*>(shape)) {
        shapeType='T';
    }
    else if(dynamic_cast<const Star*>(shape)) {
        shapeType='S';
    }
    fileWriter << shapeType << ' ' << shape->getX() << ' ' << shape->getY() << ' ' << shape->getSize()
    << ' ' << shape->getChar() << ' ' << shape->getZ() << "\n";
}

// dosyadan şekil bilgilerini oku ve uygun Shape nesnesi oluştur
static Shape* readShape(std::ifstream &fileReader){
    char type; 
    int x,y,size,z; 
    char ch; 
    if(!(fileReader>>type>>x>>y>>size>>ch>>z)) {
        return 0;
    }
    if(type=='T') {
        return new Triangle(x,y,size,ch,z);
    }
    if(type=='S') {
        return new Star(x,y,size,ch,z);
    }
    return new Rectangle(x,y,size,ch,z);
}

// dosyaya kaydetme
bool FileManager::save(const MainList& list, const char* path){
    std::ofstream fileWriter(path);
    if(!fileWriter.is_open()) {
        return false;
    }
    fileWriter << list.size() << "\n";
    for(int i=0;i<list.size();++i){
        MainNode* node = list.getAt(i);
        int shapeCount = node->shapes.size();
        fileWriter << shapeCount << "\n";
        for(int j=0;j<shapeCount;++j){ 
            writeShape(fileWriter, node->shapes.getAt(j));
        }
    }
    return true;
}

// dosyadan yükleme
bool FileManager::load(MainList& list, const char* path){
    std::ifstream fileReader(path);

    if(!fileReader.is_open()) return false;

    int mainNodeCount=0; 

    if(!(fileReader>>mainNodeCount)) return false;
    for(int i=0;i<mainNodeCount;++i){

        MainNode* node = new MainNode();

        int shapeCount=0; 

        if(!(fileReader>>shapeCount)) { delete node; return false; }

        for(int j=0;j<shapeCount;++j){ 

            Shape* loadedShape=readShape(fileReader); 
            if(loadedShape) {
                // Şekil dosyadan yüklendiği ANDA
                // pozisyonunu kontrol ediyoruz (menü alanına taşma var mı).
                ClampUtil::clampPosition(loadedShape); 
                
                node->shapes.pushFront(loadedShape); 
            }
        }
        list.pushBack(node);
    }
    return true;
}