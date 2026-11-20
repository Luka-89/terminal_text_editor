#include "Sijalica.h"

Sijalica::Sijalica(const std::string& naziv, int vati)
    : Uredjaj(naziv), vati(vati) {}

void Sijalica::ukljuci() {
    stanje = true;
}
void Sijalica::iskljuci() {
    stanje = false;
}
int Sijalica::snaga() {
    return stanje ? vati : 0;
}

std::string Sijalica::tip() const {
    return "Sijalica";
}

std::string Sijalica::opis() const{
    std::cout << " sija lica sdfhk aoll";
}