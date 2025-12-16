/**
* @file NodeStack.cpp
* @description : Kendi yazdığım Yığın (Stack) veri yapısının kaynak dosyası.
* Hazır kütüphane (vector, stack) kullanmak yasak olduğu için dinamik dizilerle
* LIFO mantığını burada kendim kurdum.
* @course      : 1.Öğretim C grubu
* @assignment  : 2.Ödev
* @date        : 03.12.2025-14.12.2025
* @author      : Muhammed Yusuf YAĞCI B211210017
*/

#include "NodeStack.hpp"
#include <iostream>


NodeStack::NodeStack(int initialCapacity)
{
    // Çok küçük bir değer verilirse en az 8 olsun diye kontrol koydum.
    if (initialCapacity < 8) initialCapacity = 8;

    capacity = initialCapacity;
    topIndex = -1; // Stack boşken indeks -1 olur.
    data = new TreeNode*[capacity];

    // Pointer dizisi olduğu için içini NULL (0) ile doldurdum.
    // Rastgele adresler (garbage value) kalırsa program çökebilir.
    for (int i = 0; i < capacity; i++)
        data[i] = 0;
}

NodeStack::~NodeStack()
{
    delete[] data;
    data = 0;
    capacity = 0;
    topIndex = -1;
}

// Stack boş mu kontrolü.
bool NodeStack::isEmpty() const
{
    return topIndex < 0;
}

// Kapasite dolunca diziyi büyüten fonksiyon.
void NodeStack::grow()
{
    // 1. Yeni kapasiteyi eskisinin 2 katı yaptım.
    int newCapacity = capacity * 2;
    
    // 2. Yeni ve daha büyük bir dizi oluşturdum.
    TreeNode** newData = new TreeNode*[newCapacity];

    // Yeni diziyi temizledim.
    for (int i = 0; i < newCapacity; i++)
        newData[i] = 0;

    // 3. Eski verileri yeni diziye kopyaladım.
    for (int i = 0; i <= topIndex; i++)
        newData[i] = data[i];

    // Eski küçük diziyi sildim ki Memory Leak olmasın.
    delete[] data;
    
    // 4. Pointer'ı yeni diziye yönlendirdim.
    data = newData;
    capacity = newCapacity;
}

// Yığına eleman ekleme (Push)
void NodeStack::push(TreeNode* node)
{
    // Eğer yer kalmadıysa önce büyütme fonksiyonunu çağırdım.
    if (topIndex + 1 >= capacity)
        grow();

    topIndex++;
    data[topIndex] = node;
}

// Yığından eleman çıkarma işlemi
TreeNode* NodeStack::pop()
{
    if (isEmpty())
        return 0; // Boşsa null döndürdüm.

    TreeNode* node = data[topIndex];
    data[topIndex] = 0; // Çıkan elemanın yerini temizledim.
    topIndex--;
    return node;
}