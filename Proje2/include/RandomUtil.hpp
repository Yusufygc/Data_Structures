/** 
* @file RandomUtil.hpp
* @description =Bu sınıf, rastgele sayıda ve karakterde üretim için yardımcı fonksiyonlar sağlar.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#ifndef RANDOMUTIL_HPP
#define RANDOMUTIL_HPP

class RandomUtil {
    public:
        static void init();                    // Rastgele sayı üreteciyi başlatır
        static int range(int min, int max);    // min ile max arasında rastgele tamsayı üretir
        static char pickChar();                // Rastgele bir karakter seçer
};

#endif