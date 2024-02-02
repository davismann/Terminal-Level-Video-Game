// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - Party.h

#ifndef PARTY_h
#define PARTY_h
#include <string>

using namespace std;

class Party
{
    private:
        int fullness;
        string name;
                
    public:
        Party();
        Party(string name);
        string getName();
        void setFullness(int fullness_);
        int getFullness();
        
        int lose20(int prob);
        int lose50(int prob);
        void fight();
        int poison();     
};

#endif