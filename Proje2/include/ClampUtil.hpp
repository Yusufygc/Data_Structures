/** 
* @file ClampUtil.hpp
* @description = Bu sınıf, Shape nesnelerinin pozisyonlarını ekran sınırları içinde tutmak için yardımcı fonksiyonlar sağlar..
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef CLAMPUTIL_HPP
#define CLAMPUTIL_HPP

#include "Shape.hpp"
#include "Screen.hpp"
class ClampUtil {
public:
    // Menü 22 birim olacak,bu yüzden şekilleri 22 birimde de başlatıyoruz.
    static const int SHAPE_MIN_X = 22;               // Sol sınır
    static const int SHAPE_MIN_Y = 0;                // Üst sınır

    static const int SHAPE_MAX_X = Screen::COLS - 1; // Sağ sınır
    static const int SHAPE_MAX_Y = Screen::ROWS - 1; // Alt sınır

    static void clampPosition(Shape* s);             // Şeklin pozisyonunu ekran sınırları içinde tutar
};

#endif