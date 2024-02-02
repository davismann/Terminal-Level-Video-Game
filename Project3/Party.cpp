// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - Party.cpp

#include <iostream>
#include "Party.h"
#include <ctime>

using namespace std;

Party::Party() // Default constructor
{
    fullness=50;
}

Party::Party(string name_) // Parameterized constructor
{
    name=name_;
    fullness = 50;
}

string Party::getName() // return name
{
    return name;
}

void Party::setFullness(int fullness_) // set fullness
{
    if(fullness_<=0)
    {
        fullness=0;
    }
    else if((fullness_<=50)&&(fullness_>=0))
    {
        fullness = fullness_;
    }
}

int Party::getFullness() // return fullness
{
    if(fullness == 0)
    {
        return 0; //Party member has died.
    }
    else
    {
        return fullness;
    }
}

// Algorithm: Everytime the user moves there is a 20% chance that the 
// Members of the party lose 1 point of fullness
// Parameters: int prob
// Return int
int Party::lose20(int prob)
{
    srand(time(0));
    if(fullness==0)
    {
        return 0;
    }
    if(prob<20)
    {
        fullness--;
        cout << name << " has lost 1 point of Fullness!!" << endl;
        if(fullness<=0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 2;
    }
}

// Algorithm: Everytime the user moves there is a 50% chance that the 
// Members of the party lose 1 point of fullness
// Parameters: int prob
// Return int
int Party::lose50(int prob)
{
    srand(time(0));
    if(fullness==0)
    {
        return 0;
    }
    if(prob<50)
    {
        fullness--;
        cout << name << " has lost 1 point of Fullness!" << endl;
        if(fullness<=0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 2;
    }
}

// Algorithm: If party member gets poisend they lose 10 fullness points
// If party member fullness reaches 0 then return -1 (Check for negative one after to kill of party member)
// Parameters; N/A
// Return int
int Party::poison()
{
    if(fullness<=0)
    {
        return 0;
    }
    else 
    {
        fullness = fullness-10;
        cout << name << " has been poisoned!(-10)" << endl;
        return 1;
    }
}

