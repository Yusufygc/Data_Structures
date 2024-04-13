/** 
* @file                                                 dugum.cpp
* @description                                          dugum.hpp dosyasında tanımlı methodun gövdesi bulunur.Yapıcı ve yıkıcı fonksiyon işlevleri yerine getirilir
* @course Dersi aldığınız eğitim türü ve grup           1.öğretim A grubu
* @assignment Kaçıncı ödev olduğu                       1.ödev
* @date Kodu oluşturduğunuz Tarih                       16/11/2023-26/11/2023
* @author Gruptakilerin yazar adları ve mail adresleri  yusuf.yagci@ogr.sakarya.edu.tr
*/

#include "dugum.hpp"
#include "sayi.hpp"
#include <iostream>
Dugum::Dugum(Sayi* s) : sayi(s), sonraki(nullptr) {}

Dugum::~Dugum() {
    delete sayi;
}
