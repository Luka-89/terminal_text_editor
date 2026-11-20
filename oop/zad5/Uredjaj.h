#ifndef UREDJAJ_H
#define UREDJAJ_H

#include <string>

class Uredjaj{

//Atributi
private:
    static int sledeciID;
    static int brojZivih;
    int id;
    
protected:
    std::string naziv;


//Metode
private:

protected:
    Uredjaj(const std::string& s);
    Uredjaj(const Uredjaj& u) = delete;
    Uredjaj& operator=(const Uredjaj& u) = delete;
    virtual ~Uredjaj();

public:
    static int getBrojZivih();
    int getId() const;
    const std::string& getNaziv() const;
    virtual std::string tip() const = 0;
    virtual std::string opis() const;
};

#endif