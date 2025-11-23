/** 
* @file                                                 main.cpp
* @description                                          dosya okuma ve menü ifadelerini gerçekleştirme
* @course Dersi aldığınız eğitim türü ve grup           1.öğretim A grubu
* @assignment Kaçıncı ödev olduğu                       1.ödev
* @date Kodu oluşturduğunuz Tarih                       16/11/2023-26/11/2023
* @author Gruptakilerin yazar adları ve mail adresleri  yusuf.yagci@ogr.sakarya.edu.tr
*/


#include "sayi.hpp"
#include "sayilarListesi.hpp"
#include "dugum.hpp"
#include "basamak.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	SayilarListesi sayilarListesi;

    std::ifstream dosya("Sayilar.txt");
    int sayi;
    while (dosya >> sayi) {
        Sayi* yeniSayi = new Sayi();
        while (sayi > 0) {
            int basamak = sayi % 10;
            yeniSayi->ekleBasamak(basamak);
            sayi /= 10;
        }
        sayilarListesi.ekleSayi(yeniSayi);
    }
    dosya.close();

    int secim;
    do {
		std::cout<<"\n";
        sayilarListesi.yazdir();
        std::cout << "1. Tek deger tutanlari listenin basina tasi\n";
        std::cout << "2. Sayi listelerini tersten yazdir\n";
		std::cout << "3. En buyuk sayiyi sil\n";
        std::cout << "4. Cikis\n";
        std::cout << "Seciminiz: ";
        std::cin >> secim;


        switch (secim) {
            case 1:

                {
                    Dugum* iter = sayilarListesi.bas;
                    while (iter != nullptr) {
                        iter->sayi->tekDegerTasi();
                        iter = iter->sonraki;
                    }
                    std::cout << "Basamak dugumleri taşındı.\n";
                }
                break;

            case 2:
                {
                    Dugum* iter = sayilarListesi.bas;
                    while (iter != nullptr) {
                        iter->sayi->tersle();
                        iter = iter->sonraki;
                    }
                    std::cout << "Basamak dugumleri terslendi.\n";
                }
                break;

            case 3:
				{
				Dugum* oncekiDugum = nullptr;
				Dugum* maxSayiDugum = sayilarListesi.bulEnBuyukSayi(oncekiDugum);
				sayilarListesi.silDugum(maxSayiDugum, oncekiDugum);
						
				sayilarListesi.yazdir();
				}
                break;

            case 4:
                std::cout << "Program sonlandiriliyor.\n";
                break;

            default:
                std::cout << "Gecersiz secim. Tekrar deneyin.\n";
        }
    } while (secim != 4);

    return 0;
}

	
