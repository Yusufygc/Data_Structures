/** 
* @file Triangle.cpp
* @description =Bu dosya Triangle sınıfının işlevlerini içerir.
                Triangle, Shape sınıfından türetilmiş bir sınıftır 
                ve üçgen şekillerini temsil eder.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "Triangle.hpp"
#include "Screen.hpp"
#include <cmath> // abs fonksiyonu için gerekli

Triangle::Triangle(int x,int y,int size,char ch,int z)
    : Shape(x,y,size,ch,z) {}

int Triangle::getWidth() const {
    return 2 * size - 1;   // en alt satır genişliği
}

int Triangle::getHeight() const {
    return size;           // yükseklik
}

void Triangle::draw(Screen &scr) const {
    // Üçgen: tepeden başlayıp aşağı doğru genişler
    // x koordinatı üçgenin EN SOL pikseli (alt kenarın sol ucu)
    
    for (int i = 0; i < size; ++i) {
        int width  = 2 * i + 1;           // Bu satırdaki piksel sayısı
        int offset = size - 1 - i;        // Soldan ne kadar içeri başlayacak
        int startX = x + offset;          // Bu satırın başlangıç x'i
        int yPos   = y + i;               // y pozisyonu (yukarıdan aşağıya)

        for (int k = 0; k < width; ++k) {
            scr.setPixel(startX + k, yPos, ch);
        }
    }
}