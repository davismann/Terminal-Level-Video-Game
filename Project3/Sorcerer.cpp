// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - Sorcerer.cpp

#include <iostream>
#include "Sorcerer.h"

using namespace std;


Sorcerer::Sorcerer() // Default constructor
{
    health=1000;
}

int Sorcerer::getHealth() // return the health
{
    return health;
}

void Sorcerer::setHealth(int health_) // set the health
{
    health = health_;
}    

void Sorcerer::removeHealth(int health_) // remove health
{
    health -= health_;
}
