#ifndef SAYI_HPP
#define SAYI_HPP
#include "basamak.hpp"

class Sayi {
public:
    Basamak* basamaklar;

    Sayi();

    void ekleBasamak(int val);
    int getDeger() const;
    void tekDegerTasi();
    void tersle();
};

#endif 
