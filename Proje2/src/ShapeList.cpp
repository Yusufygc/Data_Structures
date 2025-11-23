/** 
* @file ShapeList.cpp
* @description =Bu dosya ShapeList sınıfının işlevlerini içerir.
                ShapeList, bağlı liste yapısını kullanarak şekil nesnelerini yönetir.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "ShapeList.hpp"
#include "Shape.hpp"
#include "Screen.hpp"

ShapeList::ShapeList() {
    this->head = 0;
    this->count = 0;
}

ShapeList::~ShapeList(){
    ShapeNode* cur=head; 
    while(cur){ 
        ShapeNode* nextNode=cur->next; 
        delete cur; 
        cur=nextNode; 
    }
}

// liste başına şekil ekler
void ShapeList::pushFront(Shape* newShape){
    ShapeNode* newNode=new ShapeNode(newShape);
    newNode->next=head; 
    head=newNode; 
    ++count;
}

// belirtilen indisteki şekli siler
bool ShapeList::removeAt(int index){
    if(index<0||index>=count) {
        return false;
    }

    ShapeNode* prev=0; 
    ShapeNode* cur=head; 
    int i=0;
    while(cur && i<index){ 
        prev=cur; 
        cur=cur->next; 
        ++i; 
    }
    if(!cur) {
        return false;
    }
    if(prev) {
        prev->next=cur->next;
    } 
    else {
        head=cur->next;
    }
    cur->next=0; 
    delete cur; 
    --count; 
    return true;
}

// belirtilen indisteki şekli döndürür
Shape* ShapeList::getAt(int index) const{
    if(index<0||index>=count) return 0;
    ShapeNode* cur=head; 
    int i=0; 
    while(cur && i<index){ 
        cur=cur->next; ++i; 
    }
    return cur?cur->data:0;
}

// listedeki şekil sayısını döndürür
int ShapeList::size() const{ return count; }

// z değerine göre sıralayıp çizer
void ShapeList::drawAllByZ(Screen &scr) const{
    if(count==0) return;
    // şekil işaretçilerini diziye kopyalar ve z'ye göre seçim sıralaması yapar
    Shape** shapeArray=new Shape*[count];
    ShapeNode* cur=head; 
    int i=0; 
    while(cur){ 
        shapeArray[i++]=cur->data; 
        cur=cur->next; 
    }
    // selection sort by z (küçükten büyüğe)
    for(int a=0;a<count-1;++a){
        int minIdx=a; 
        for(int b=a+1;b<count;++b){ 
            if(shapeArray[b]->getZ() < shapeArray[minIdx]->getZ()) 
                minIdx=b; 
        }
        if(minIdx!=a){ 
            Shape* tmp=shapeArray[a]; 
            shapeArray[a]=shapeArray[minIdx]; 
            shapeArray[minIdx]=tmp; 
        }
    }
    for(int k=0;k<count;++k) shapeArray[k]->draw(scr);
    delete[] shapeArray;
}