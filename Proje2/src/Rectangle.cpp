/** 
* @file Rectangle.cpp
* @description = Bu dosya Rectangle sınıfının işlevlerini içerir.
                Rectangle, Shape sınıfından türetilmiş bir sınıftır ve dikdörtgen şekillerini temsil eder.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "Rectangle.hpp"
#include "Screen.hpp"

Rectangle::Rectangle(int x,int y,int size,char ch,int z): Shape(x,y,size,ch,z) {}

int Rectangle::getWidth() const {
    // Böylece görsel ağırlığı eşitledim.
    return 2 * size; 
}

int Rectangle::getHeight() const {
    // Yüksekliği de orantılı artırdım.
    // "size" değeri kadar yükseklik iyi bir dikdörtgen oluşturur.
    return size; 
}

void Rectangle::draw(Screen &scr) const {
    int w = getWidth();
    int h = getHeight();

    // Dolu dikdörtgen çiz
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            scr.setPixel(x + col, y + row, ch);
        }
    }
}

