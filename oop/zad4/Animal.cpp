#include "Animal.h"

Animal::Animal(std::string name) 
    : name(name) {}
void Animal::sound() {
    std::cout << "say something";
}