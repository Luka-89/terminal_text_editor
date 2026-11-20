#ifndef TACKA_H
#define TACKA_H

#include <cmath>

class Tacka {
private:
    double x;
    double y;

public:
    Tacka();
    Tacka(double x, double y);

    double getX();
    double getY();
    void setX(double x);
    void setY(double y);
    double rastojanje(Tacka t);
};

#endif 