// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - Sorcerer.h

#ifndef SORCERER_H
#define SORCERER_H
#include <string>

using namespace std;

class Sorcerer
{
    private:
        int health;
    public:
        Sorcerer();
        int getHealth();
        void setHealth(int health_);
        void removeHealth(int health_);
};

#endif