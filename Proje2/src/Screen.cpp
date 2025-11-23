/** 
* @file Screen.cpp
* @description =Bu dosya Screen sınıfının işlevlerini içerir.
                Screen, basit bir metin tabanlı ekran tamponunu temsil eder.
                detaylandırmak istersek şöyle diyebiliriz :metin tabanlı ekran tamponu, 
                karakterlerin 2D dizisi olarak saklandığı ve yönetildiği bir yapıdır.
                Ekran tamponu, karakterlerin geçici olarak depolandığı ve 
                gerektiğinde ekrana yazdırıldığı bir bellek alanıdır.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include <iostream>
#include "Screen.hpp"

using std::cout;

// kurucu
Screen::Screen() {
    clear(' ');
}

// Ekranı temizler
void Screen::clear(char ch) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            buffer[r][c] = ch;
}

// Ekran tamponunu konsola yazdırır
void Screen::setPixel(int x, int y, char ch) {
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS)
        buffer[y][x] = ch;
}

// render fonksiyonu ==> Belirtilen satırı ve ofseti ekrana çizer. ofset, menü genişliği için kullanılır
void Screen::renderLine(int row, int offset) const {
    for (int c = offset; c < COLS; c++)
        cout << buffer[row][c];
    
    cout << "\n";
}
 // getCharAt fonksiyonu ==> Belirtilen konumdaki karakteri döndürür
char Screen::getCharAt(int x, int y) const {
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS)
        return buffer[y][x];
    return ' ';
}

int Screen::getHeight() const {
    return ROWS;
}

int Screen::getWidth() const {
    return COLS;
}