#ifndef DUGUM_HPP
#define DUGUM_HPP

class Sayi;

class Dugum {
public:
    Sayi* sayi;
    Dugum* sonraki;

    Dugum(Sayi* s);
    ~Dugum();
};

#endif
