/** 
* @file Star.cpp
* @description =Bu dosya Star sınıfının işlevlerini içerir.
                Star, Shape sınıfından türetilmiş bir sınıftır 
                ve yıldız şekillerini temsil eder.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "Star.hpp"
#include "Screen.hpp"
#include <cmath> // abs fonksiyonu için gerekli

Star::Star(int x, int y, int size, char ch, int z)
    : Shape(x, y, size, ch, z) {}

int Star::getWidth() const {
    // Örn: size=2 ise genişlik 3 (1,3,1)
    // Örn: size=3 ise genişlik 5 (1,3,5,3,1)
    return 2 * size - 1;
}

int Star::getHeight() const {
    // Elmas kare bir kutu içine oturur, yükseklik genişliğe eşittir
    return 2 * size - 1;
}

void Star::draw(Screen &scr) const {
    int h = getHeight();
    int mid = size - 1; // Şeklin orta satırının indeksi

    for (int i = 0; i < h; ++i) {
        // Merkeze (mid) olan dikey uzaklık
        int dist = std::abs(mid - i);
        
        // Bu satırda kaç tane karakter basılacak?
        // Merkezden uzaklaştıkça sayı azalır (örn: 5, 3, 1)
        int starCount = 2 * (size - dist) - 1;
        
        // Satırın başlangıç X koordinatı (sola yaslı x + boşluk miktarı)
        int startX = x + dist;

        for (int k = 0; k < starCount; ++k) {
            scr.setPixel(startX + k, y + i, ch);
        }
    }
}