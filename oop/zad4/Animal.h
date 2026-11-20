#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>

class Animal {
private:
    std::string name;

public:
    Animal(std::string name);
    virtual void sound();

};

#endif