#ifndef SAYILARLISTESI_HPP
#define SAYILARLISTESI_HPP
#include <iostream>
#include "sayi.hpp"
class Dugum;

class SayilarListesi {
public:
    Dugum* bas;

    SayilarListesi();

    void ekleSayi(Sayi* s);
    void yazdir();
    Dugum* bulEnBuyukSayi(Dugum*& oncekiDugum);
    void silDugum(Dugum* silinecek, Dugum* onceki);
    ~SayilarListesi();
    
};

#endif 