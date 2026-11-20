#include "Dog.h"

Dog::Dog(std::string s)
    : Animal(s) {}

void Dog::sound() {
    std::cout << "woof woof";
}