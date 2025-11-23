/** 
* @file Screen.hpp
* @description = Bu sınıf, ekranı temsil eder ve ekrana çizim işlemlerini yönetir.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>

class Screen {
public:
    static const int ROWS = 25; // Satır sayısı
    static const int COLS = 100; // Sütun sayısı

private:
    char buffer[ROWS][COLS];    // Ekran tamponu. bu 2D karakter dizisi ile temsil edilir

public:
    Screen(); 
    void clear(char fillChar = ' ');      // Ekranı temizler, varsayılan olarak boşluk karakteri ile doldurur
    void setPixel(int x, int y, char ch); // Belirtilen konuma karakter yerleştirir
    void display() const;                 // Ekran tamponunu konsola yazdırır
    
    void renderLine(int row, int offset) const; // Belirtilen satırı ve ofseti ekrana çizer. ofset, menü genişliği için kullanılır
    
    char getCharAt(int x, int y) const;  // Belirtilen konumdaki karakteri döndürür
    int getHeight() const;               // Ekranın yüksekliğini döndürür
    int getWidth() const;                // Ekranın genişliğini döndürür
};

#endif