/** 
* @file MainList.hpp
* @description = bu sınıf, çift bağlı liste yapısını temsil eder ve MainNode düğümlerini yönetir.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef MAINLIST_HPP
#define MAINLIST_HPP
#include "MainNode.hpp"

class MainList {
    private:
        MainNode* head;  // listenin baş düğümü
        MainNode* tail;  // listenin son düğümü
        int count;       // düğüm sayısı

    public:
    // constructor ve destructor
        MainList();
        ~MainList();

    void pushBack(MainNode* node);      // liste sonuna düğüm ekler
    int size() const;                   // listenin boyutunu döndürür
    MainNode* getHead() const;          // listenin baş düğümünü döndürür
    MainNode* getTail() const;          // listenin son düğümünü döndürür
    MainNode* getAt(int index) const;   // Belirtilen indisteki düğümü döndürür
    void removeAt(int index);           // Belirtilen indisteki düğümü siler
};

#endif