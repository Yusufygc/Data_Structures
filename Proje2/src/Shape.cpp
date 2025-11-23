/** 
* @file Shape.cpp
* @description =Bu dosya Shape sınıfının işlevlerini içerir.
                Shape, temel şekil özelliklerini ve işlevlerini tanımlayan soyut bir sınıftır.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "Shape.hpp"

Shape::Shape(int x,int y,int size,char ch,int z)
    : x(x), y(y), size(size), ch(ch), z(z) {}

Shape::~Shape() {}

// şekli dx, dy kadar hareket ettirir
void Shape::moveBy(int dx,int dy) { 
    x += dx; 
    y += dy; 
}

// erişim işlemleri
int  Shape::getX()   const { return x; }
int  Shape::getY()   const { return y; }
int  Shape::getSize()const { return size; }
char Shape::getChar()const { return ch; }
int  Shape::getZ()   const { return z; }

// ayarlama işlemleri
void Shape::setX(int newX)   { x = newX; }
void Shape::setY(int newY)   { y = newY; }
void Shape::setSize(int newSize){ size = newSize; }
void Shape::setChar(char newChar){ ch = newChar; }
void Shape::setZ(int newZ)   { z = newZ; }