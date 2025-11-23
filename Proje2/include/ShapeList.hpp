/** 
* @file ShapeList.hpp
* @description = 
        Bu dosya, ShapeList sınıfının tanımını içerir.
        ShapeList, ShapeNode düğümlerinden oluşan tek yönlü bağlı liste yapısını temsil eder.
        Her ShapeNode, bir Shape nesnesine işaret eder.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef SHAPELIST_HPP
#define SHAPELIST_HPP
#include "ShapeNode.hpp"

/*
İleri bildirim: 
ShapeList.hpp içinde Screen tanımına ihtiyaç duymadan 
Screen& işaretçilerini kullanabiliriz.
*/
class Screen; 

class ShapeList {
    private:
        ShapeNode* head; // listenin baş düğümü
        int count;       // listedeki şekil sayısı

    public:
        ShapeList();
        ~ShapeList();

        void pushFront(Shape* s);       // liste başına şekil ekler
        bool removeAt(int index);       // belirtilen indisteki şekli siler
        Shape* getAt(int index) const;  // belirtilen indisteki şekli döndürür
        int size() const;               // listedeki şekil sayısını döndürür

        void drawAllByZ(Screen &scr) const; // z değerine göre sıralayıp çizer
};

#endif