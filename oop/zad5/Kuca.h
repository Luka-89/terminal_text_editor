#ifndef KUCA_H
#define KUCA_H

#include <memory>
#include <vector>
#include "Uredjaj.h"

class Kuca {
private:

std::vector<std::unique_ptr<Uredjaj>> uredjaji;

public:
    void dodaj(std::unique_ptr<Uredjaj> u);
    bool ukloni(int id);

};

#endif