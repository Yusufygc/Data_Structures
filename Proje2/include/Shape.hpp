/** 
* @file Shape.hpp
* @description = Bu sınıf, temel şekil özelliklerini ve davranışlarını tanımlar. Diğer şekil türleri bu sınıftan türetilir.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef SHAPE_HPP
#define SHAPE_HPP
/*
İleri bildirim : Shape.hpp içinde Screen tanımına ihtiyaç duymadan 
Screen& işaretçilerini kullanabiliriz.
*/
class Screen;

class Shape {
protected:
    int x;      // pozisyon
    int y;
    int size;   // şeklin temel boyutu
    char ch;    // çizim karakteri
    int z;      // çizim önceliği

public:
    Shape(int x, int y, int size, char ch, int z); 
    virtual ~Shape(); // sanal destructor şu işe yarar: Türemiş sınıfların destructor'ları doğru şekilde çağrılır.
                      // böylece  şekiller silindiğinde bellek sızıntıları önlenir.
 
    virtual void draw(Screen &scr) const = 0;

    // boyut bilgisi (sınır kontrolü için)
    virtual int getWidth()  const = 0;
    virtual int getHeight() const = 0;

    // hareket & erişimciler
    void moveBy(int dx, int dy); // şekli dx, dy kadar hareket ettirir

    // erişim işlemleri
    int  getX() const;
    int  getY() const;
    int  getSize() const;
    char getChar() const;
    int  getZ() const;

    // ayarlama işlemleri
    void setX(int nx);
    void setY(int ny);
    void setSize(int ns);
    void setChar(char c);
    void setZ(int nz);
};

#endif
