#ifndef INTERFEJSI_H
#define INTERFEJSI_H

class Prekidac {

public:
    virtual void ukljuci() = 0;
    virtual void iskljuci() = 0;
    virtual bool ukljucen() const = 0;
};

class Podesiv{
public:

    virtual bool postavi(int v) = 0;
    virtual int vrijednost() const = 0;
    virtual int minimum() const = 0;
    virtual int maksimum() const = 0;
};

class Potrosac {
public:
    virtual int snaga() const = 0;
    virtual ~Potrosac() = default;
};

#endif