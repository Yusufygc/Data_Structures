/** 
* @file Star.hpp
* @description = Bu sınıf, yıldız şeklini temsil eder ve Shape sınıfından türetilir.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef STAR_HPP
#define STAR_HPP

#include "Shape.hpp"

class Star : public Shape {
public:
    Star(int x, int y, int size, char ch, int z);

    virtual void draw(Screen &scr) const override;
    virtual int getWidth()  const override;
    virtual int getHeight() const override;
};

#endif
