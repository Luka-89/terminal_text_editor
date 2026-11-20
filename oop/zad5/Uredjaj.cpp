#include "Uredjaj.h"

int Uredjaj::sledeciID = 0;
int Uredjaj::brojZivih = 0;

Uredjaj::Uredjaj(const std::string& s) 
    : id(sledeciID){
    sledeciID++;
    brojZivih++;
    naziv = s;
}

int Uredjaj::getBrojZivih() {
    return brojZivih;
}

Uredjaj::~Uredjaj() {
    brojZivih--;
}

int Uredjaj::getBrojZivih() {return brojZivih;}

int Uredjaj::getId() const {
    return id;
}

const std::string& Uredjaj::getNaziv() const {
    return "bez naziva";
}

std::string Uredjaj::opis() const{
    return "nema opis";
}
