/**
* @file NodeStack.hpp
* @description : TreeNode işaretçilerini tutan basit yığın (stack) veri yapısı.
* STL vector veya stack kullanmak yasak olduğu için, dinamik dizi mantığıyla
* kendi LIFO (Last In First Out) yapımızı oluşturdum.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#ifndef NODESTACK_HPP
#define NODESTACK_HPP

#include "TreeNode.hpp"

// İkili Arama Ağacı'nı (BST) temizlerken rekürsif olmayan (iteratif) yöntemler
// kullanmak için gerekli olan Yığın (Stack) sınıfı.
// Hazır kütüphane (STL) kullanımı yasak olduğu için elle yazılmıştır.
class NodeStack
{
private:
    TreeNode** data; // Verileri (Node pointer'ları) tutan dinamik dizi
    int capacity;    // Yığının o anki maksimum kapasitesi
    int topIndex;    // En üstteki elemanın indeksi (Boşsa -1)

    // Dizi dolduğunda kapasiteyi iki katına çıkaran yardımcı fonksiyon.
    void grow();

public:
    // Kurucu ve Yıkıcı
    NodeStack(int initialCapacity); 
    ~NodeStack();                 

    // Yığına yeni eleman ekler (LIFO mantığıyla en üste).
    void push(TreeNode* node);

    // Yığından en üstteki elemanı çıkarır ve döndürür.
    TreeNode* pop();

    // Yığının boş olup olmadığını kontrol eder.
    bool isEmpty() const;
};

#endif 