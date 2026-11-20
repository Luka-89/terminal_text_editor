#include "Termostat.h"

Termostat::Termostat(const std::string& naziv) 
: Uredjaj(naziv) {}

std::string Termostat::tip() const{
    std::cout << "Termostat";
}

std::string Termostat::opis() const {
    std::cout << "opis termostata";
}