#ifndef KVADRAT_H
#define KVADRAT_H

#include "Tacka.h"
#include <iostream>
class Kvadrat {
private:
    
    Tacka gornja;
    Tacka donja;

public:
    Kvadrat(Tacka A, Tacka B);
    ~Kvadrat();
    double povrsina();
    double obim();
    double presjek(Kvadrat K);

};

#endif