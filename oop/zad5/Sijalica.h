#ifndef SIJALICA_H
#define SIJALICA_H

#include "Uredjaj.h"
#include "interfejsi.h"
#include <iostream>

class Sijalica : public Uredjaj, public Prekidac, public Potrosac {
int vati;
bool stanje;

public:
    Sijalica(const std::string& naziv, int vati);
    int snaga();
    bool ukljucen();
    void ukljuci();
    void iskljuci();
    std::string tip() const override;
    std::string opis() const override;
};

#endif