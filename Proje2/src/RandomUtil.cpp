/** 
* @file RandomUtil.cpp
* @description = Bu dosya RandomUtil sınıfının işlevlerini içerir.
                RandomUtil, rastgele sayı ve karakter üretimi için yardımcı işlevler sağlar.
* @course 1. Öğretim , C grubu
* @assignment 1.ödev
* @date 01/11/2025-20/11/2025
* @author Muhammed Yusuf YAĞCI - B211210017
*/
#include <ctime>
#include <cstdlib>
#include "RandomUtil.hpp"
#include <cstring>

// Rastgele sayı üreteciyi başlatır
void RandomUtil::init(){ 
    std::srand((unsigned)std::time(0)); 
}

// min ile max arasında rastgele tamsayı üretir
int RandomUtil::range(int min,int max){ 
    return min + (std::rand() % (max-min+1)); 
}

// Rastgele bir karakter seçer
char RandomUtil::pickChar(){
    const char* charSet = "#@%+*o$-=^";
    int idx = range(0, strlen(charSet) - 1);
    return charSet[idx];
}