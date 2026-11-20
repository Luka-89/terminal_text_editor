#ifndef TERMOSTAT_H
#define TERMOSTAT_H

#include "Uredjaj.h"
#include "interfejsi.h"
#include <iostream>

class Termostat : public Uredjaj, public Podesiv {
int temperatura;
int lowerBound = 16;
int upperBound = 30;

public:
    Termostat(const std::string& naziv);
    std::string tip() const;
    std::string opis() const;
};

#endif