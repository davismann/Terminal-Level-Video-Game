// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - Status.cpp

#include <iostream>
#include "Status.h"
#include <ctime>

using namespace std;

Status::Status() // Default constructor
{
    rooms = 0;
    keys = 0;
    anger = 0;
}

int Status::getRooms() // return rooms
{
    return rooms;
}

void Status::addRooms() // add rooms
{
    rooms++;
}

int Status::getKeys() // return the keys
{
    return keys;
}

void Status::addKeys() // add keys
{
    keys++;
}

void Status::removeKeys() // remove keys
{
    keys--;
}

int Status::getAnger() // return the anger
{
    return anger;
}

void Status::addAnger() // add anger
{
    anger++;
}

void Status::setAnger(int anger_) // set anger
{
    anger = anger_;
}

// Algorithm: 10 percent chance of finding a key
// Create a random number between 10
// If prob occurs
// Add to key
// Parameters: N/A
// Return void
void Status::randKey()
{
    srand(time(0));
    int prob = rand()%100; // probability of random key spawning
    if(prob < 10)
    {
        cout << "You have found a key!" << endl;
        keys++; // add to keys
    }
}
