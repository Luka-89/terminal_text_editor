#include "Racun.h"

int Racun::brRacuna = 1;

Racun::Racun( double stanje, std::string vlasnik)
: vlasnik(vlasnik), stanje(stanje), mojBrRacuna(brRacuna) {
    brRacuna++;
}

Racun::Racun() : vlasnik("Jhon Doe"), stanje(0), mojBrRacuna(brRacuna) {
    brRacuna++;
}

void Racun::uplata(double iznos) { stanje += iznos; };

bool Racun::isplata(double iznos) { 
    if(iznos > stanje) return false;
    stanje -= iznos; 
    return true;
};

void Racun::prikazi() const {
    std::cout << vlasnik << ": " << stanje << " broj racuna: "<< this->mojBrRacuna << std::endl;
}
