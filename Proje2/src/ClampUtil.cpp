/** 
* @file ClampUtil.cpp
* @description = Bu dosya, ClampUtil sınıfının uygulamasını içerir. 
                ClampUtil, Shape nesnelerinin pozisyonlarını 
                belirli sınırlar içinde tutmak için kullanılır.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include "ClampUtil.hpp"
#include "Shape.hpp"

void ClampUtil::clampPosition(Shape* shape) {
    if (!shape) return;

    int x = shape->getX();      // Mevcut pozisyon
    int y = shape->getY();
    int width = shape->getWidth();  // Şeklin genişliği
    int height = shape->getHeight(); // Şeklin yüksekliği

    // Sol sınır kontrolü - şeklin EN SOL pikseli SHAPE_MIN_X'ten küçük olamaz
    if (x < SHAPE_MIN_X) {
        x = SHAPE_MIN_X;
    }
    
    // Üst sınır kontrolü
    if (y < SHAPE_MIN_Y) {
        y = SHAPE_MIN_Y;
    }

    // Sağ sınır kontrolü - şeklin EN SAĞ pikseli SHAPE_MAX_X'ten büyük olamaz
    if (x + width - 1 > SHAPE_MAX_X) {
        x = SHAPE_MAX_X - width + 1;
    }
    
    // Alt sınır kontrolü - şeklin EN ALT pikseli SHAPE_MAX_Y'den büyük olamaz
    if (y + height - 1 > SHAPE_MAX_Y) {
        y = SHAPE_MAX_Y - height + 1;
    }

    shape->setX(x);// Güncellenmiş x konumunu ayarla
    shape->setY(y);// Güncellenmiş y konumunu ayarla
}