/** 
* @file MainList.cpp
* @description = Bu dosya, çift bağlı liste yapısı olan MainList'in
                 üye fonksiyonlarının implementasyonlarını içerir.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "MainList.hpp"

// Constructor
MainList::MainList() {
    this->head = 0;
    this->tail = 0;
    this->count = 0;
}

// Destructor
MainList::~MainList(){
    MainNode* cur=head; //current düğümü başa ayarla
    while(cur){ 
        MainNode* nextNode=cur->next; 
        delete cur; 
        cur=nextNode; 
    }
}

// Liste sonuna düğüm ekleme fonksiyonu
void MainList::pushBack(MainNode* node){
    node->prev=tail; node->next=0;
    if(!head){ 
        head=tail=node; 
    } 
    else{ 
        tail->next=node; tail=node; 
    }
    ++count;
}


int MainList::size() const{ return count; }         // Listenin boyutunu döndüren fonksiyon
MainNode* MainList::getHead() const{ return head; } // Listenin baş düğümünü döndüren fonksiyon
MainNode* MainList::getTail() const{ return tail; } // Listenin son düğümünü döndüren fonksiyon

// Belirtilen indisteki düğümü döndüren fonksiyon
MainNode* MainList::getAt(int index) const{
    if(index<0||index>=count) return 0;
    
    MainNode* cur=head; int i=0; 

    while(cur && i<index){ 
        cur=cur->next; ++i; 
    }
    return cur;
}

//Düğüm silme fonksiyonu
void MainList::removeAt(int index) {
    if (index < 0 || index >= count) return;

    MainNode* toDel = head; // Silinecek düğümü bulmak için head i toDel e atadık böylece listeyi baştan tarayabiliriz
    int i = 0;
    while (toDel && i < index) {
        toDel = toDel->next;
        i++;
    }

    if (!toDel) {
        return;
    }

    // Önceki düğümü bağla
    if (toDel->prev) {
        toDel->prev->next = toDel->next;
    } else {
        head = toDel->next; // Eğer baştaki elemansa head değişir
    }

    // Sonraki düğümü bağla
    if (toDel->next) {
        toDel->next->prev = toDel->prev;
    } else {
        tail = toDel->prev; // Eğer sondaki elemansa tail değişir
    }

    delete toDel;
    count--;
}