#include <iostream>
#include <vector>
#include "cqs.h"




int main()
{
    Creature c(100, 200);
    int strength, agility;

    std::cout << "Init" << std::endl;
    std::cout << "strength = " << c.get_strength() << ", agility = " << c.get_agility() << std::endl;
    c.set_strength(111);
    c.set_agility(222);
    std::cout << "Set" << std::endl;
    std::cout << "strength = " << c.get_strength() << ", agility = " << c.get_agility() << std::endl;
    return 0;
}