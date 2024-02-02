// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - Status.cpp

#ifndef STATUS_h
#define STATUS_h
#include <string>

using namespace std;

class Status
{
    private:
        int rooms;
        int keys;
        int anger;
        const int tot_rooms = 5;

    public:
        Status();
        int getRooms();
        void addRooms();
        int getKeys();
        void addKeys();
        void removeKeys();
        int getAnger();
        void setAnger(int anger_);
        void addAnger();

        void randKey();
};

#endif