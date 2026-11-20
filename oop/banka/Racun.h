#ifndef RACUN_H
#define RACUN_H

#include <iostream>
#include <string>   


class Racun {
private:
    std::string vlasnik;
    double stanje;
    static int brRacuna;
    int mojBrRacuna;

    
public:    
    Racun( double stanje, std::string vlasnik = "Vook");
    Racun();

    void uplata(double iznos);

    bool isplata(double iznos);
    
    void prikazi() const;
};
#endif