#include "Animal.h"

Animal::Animal(
    const std::string& n,
    const std::string& k,
    const std::string& a,
    const std::string& f,
    int d,
    double p)
    : name(n), kind(k), allergy(a), food(f), days(d), price(p)
{
}