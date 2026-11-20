#include "Kvadrat.h"

Kvadrat::Kvadrat(Tacka A, Tacka B)
: gornja(A), donja(B) {}

Kvadrat::~Kvadrat() {
    std::cout << "why kill me";
}

double Kvadrat::povrsina() {
    return abs(donja.getX() - gornja.getX()) * abs(donja.getY() - gornja.getY());
}

double Kvadrat::obim() {
    return 2*( abs(donja.getX() - gornja.getX()) + abs(donja.getY() - gornja.getY()) );
}

double Kvadrat::presjek(Kvadrat K) {
    if(gornja.getX() < K.donja.getX() || donja.getX() > K.gornja.getX()) return 0;
    //bla bla bla... 
}