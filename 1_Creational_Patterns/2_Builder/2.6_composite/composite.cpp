//
// Created by admin on 2022-09-22.
//
#include <string>
#include <vector>
#include <iostream>

#include "Person.h"


int main()
{
    Person p = Person::create()
            .lives().at("123, London Road")
            .with_postcode("SW1 1GB");

    return 0;
}