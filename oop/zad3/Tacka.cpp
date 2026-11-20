#include "Tacka.h"

Tacka::Tacka()
    : x(0), y(0) {}

Tacka::Tacka(double x, double y)
    : x(x), y(y) {}

double Tacka::getX() {
    return x;
}

double Tacka::getY() {
    return y;
}

void Tacka::setX(double x) {
    this->x = x;
}

void Tacka::setY(double y) {
    this->y = y;
}

double Tacka::rastojanje(Tacka T) {
    return sqrt(pow(x - T.getX(), 2) + pow(y - T.getY(), 2));
}