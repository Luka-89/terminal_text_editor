#ifndef DOG
#define DOG

#include "Animal.h"

class Dog : public Animal {
public:
    Dog(std::string name);
    void sound() override;

};

#endif