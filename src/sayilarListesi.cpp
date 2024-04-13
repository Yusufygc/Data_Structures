/** 
* @file                                                 sayilarListesi.cpp
* @description                                          sayı ekleme,sayıları yazdırma,en büyük sayıyı bulma ve silme ve yıkıcı fonksiyon gövdeleri ve işlevleri yerine getirilir.    
* @course Dersi aldığınız eğitim türü ve grup           1.öğretim A grubu
* @assignment Kaçıncı ödev olduğu                       1.ödev
* @date Kodu oluşturduğunuz Tarih                       16/11/2023-26/11/2023
* @author Gruptakilerin yazar adları ve mail adresleri  yusuf.yagci@ogr.sakarya.edu.tr
*/


#include "sayilarListesi.hpp"
#include "dugum.hpp"
#include "sayi.hpp"
#include <iostream>

SayilarListesi::SayilarListesi() : bas(nullptr) {}

void SayilarListesi::ekleSayi(Sayi* s) {
    Dugum* yeniDugum = new Dugum(s);

    if (bas == nullptr) {
        bas = yeniDugum;
    } else {
        Dugum* iter = bas;
        while (iter->sonraki != nullptr) {
            iter = iter->sonraki;
        }
        iter->sonraki = yeniDugum;
    }
}
void SayilarListesi::yazdir() {
    Dugum* iter = bas;
        while (iter != nullptr) {
            
            std::cout << "Liste Adresi  : " << iter << std::endl;
			
			int sayiDeger = iter->sayi->getDeger();
            std::cout << "Sayi Degeri   : " << sayiDeger << std::endl;
			
            Basamak* basamakIter = iter->sayi->basamaklar;
            while (basamakIter != nullptr) {
                std::cout << " Basamak Adresi: " << basamakIter<< " Deger: " << basamakIter->deger << std::endl;
                basamakIter = basamakIter->sonraki;
				std::cout<<std::endl;
            }

            iter = iter->sonraki;
        }
}

Dugum* SayilarListesi::bulEnBuyukSayi(Dugum*& oncekiDugum) {
        Dugum* maxSayiDugum = nullptr;
        oncekiDugum = nullptr;
        Dugum* iter = bas;
        Dugum* onceki = nullptr;
        int maxDeger = 0;

        while (iter != nullptr) {
            int suankiDeger = iter->sayi->getDeger();
            if (suankiDeger > maxDeger) {
                maxDeger = suankiDeger;
                maxSayiDugum = iter;
                oncekiDugum = onceki;
            }
            onceki = iter;
            iter = iter->sonraki;
        }

        return maxSayiDugum;
}

void SayilarListesi::silDugum(Dugum* silinecek, Dugum* onceki) {
      if (silinecek == nullptr) {
			std::cout<<"liste bos"<<std::endl;
            return ;
        }

        if (onceki == nullptr) {  // Listenin başındaysa
            bas = silinecek->sonraki;
        } else {  // Listenin ortasındaysa
            onceki->sonraki = silinecek->sonraki;
        }

        delete silinecek;
}

SayilarListesi::~SayilarListesi() {
         Dugum* iter = bas;
        while (iter != nullptr) {
            Dugum* temp = iter;
            iter = iter->sonraki;
            delete temp;
        }
    }
