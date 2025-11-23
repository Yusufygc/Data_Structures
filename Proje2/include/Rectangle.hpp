/** 
* @file Rectangle.hpp
* @description =Bu sınıf, dikdörtgen şekli temsil eder ve Shape sınıfından türetilir.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int size, char ch, int z);

    virtual void draw(Screen &scr) const override; //Şekli ekrana çizer
    virtual int getWidth()  const override;        //Genişlik bilgisi
    virtual int getHeight() const override;        //Yükseklik bilgisi
};

#endif
