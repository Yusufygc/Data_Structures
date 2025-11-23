/** 
* @file                                                 sayi.cpp
* @description                                          basamak ekleme ,tek değerleri başa alma ve sayıyı tersten yazdırma fonksiyonlarının gövdesi bulunur ve bu işlemleri yapar.
* @course Dersi aldığınız eğitim türü ve grup           1.öğretim A grubu
* @assignment Kaçıncı ödev olduğu                       1.ödev
* @date Kodu oluşturduğunuz Tarih                       16/11/2023-26/11/2023
* @author Gruptakilerin yazar adları ve mail adresleri  yusuf.yagci@ogr.sakarya.edu.tr
*/
#include "sayi.hpp"
#include <iostream>


Sayi::Sayi() : basamaklar(nullptr) {}

void Sayi::ekleBasamak(int val) {
    Basamak* yeniBasamak = new Basamak(val);
    yeniBasamak->sonraki = basamaklar;
    basamaklar = yeniBasamak;
}

int Sayi::getDeger() const {
    int deger = 0;
    Basamak* iter = basamaklar;
    while (iter != nullptr) {
        deger = deger * 10 + iter->deger;
        iter = iter->sonraki;
    }
    return deger;
}

void Sayi::tekDegerTasi() {
      if (!basamaklar) {
            return;
        }

        Basamak* tekDegerler = nullptr;
        Basamak* iter = basamaklar;
        Basamak* onceki = nullptr;

        while (iter != nullptr) {
            if (iter->deger % 2 == 1) {  // Tek değeri olan düğümü bul
                if (onceki == nullptr) {
                    basamaklar = iter->sonraki;  // Listenin başındaysa
                } else {
                    onceki->sonraki = iter->sonraki;  // Listenin içindeyse
                }

                iter->sonraki = tekDegerler;  // Taşı ve yeni listenin başına ekle
                tekDegerler = iter;
                iter = (onceki == nullptr) ? basamaklar : onceki->sonraki;
            } else {
                onceki = iter;
                iter = iter->sonraki;
            }
        }

        // Tek değerli düğümleri listenin başına ekle
        while (tekDegerler != nullptr) {
            Basamak* temp = tekDegerler;
            tekDegerler = tekDegerler->sonraki;
            temp->sonraki = basamaklar;
            basamaklar = temp;
        }
}

void Sayi::tersle() {
        if (!basamaklar) {
            return;
        }

        Basamak* onceki = nullptr;
        Basamak* suanki = basamaklar;
        Basamak* sonraki = nullptr;

        while (suanki != nullptr) {
            sonraki = suanki->sonraki;
            suanki->sonraki = onceki;
            onceki = suanki;
            suanki = sonraki;
        }

        basamaklar = onceki;
    }
