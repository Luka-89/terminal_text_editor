#include "Racun.h"

int main() {

    Racun racun (694020.13);


    Racun racun2;

    racun.prikazi();
    racun2.prikazi();

    Racun& al = racun2;
    Racun* ptr = &racun2;

    al.prikazi();
    ptr->prikazi();

    return 0;
} 