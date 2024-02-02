// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - ActionDriver.cpp

#include "Map.h"
#include <cassert>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include "Party.h"
#include "Status.h"
#include "Inventory.h"
#include "Sorcerer.h"

using namespace std;

// Algorithm: Function that splits a string into an array at a certain delimeter
// Splits a input_string into a array
// When delimeter is noticed
// Input the string into the array
// Parameters: string input_string, char separator, string arry[], int arry_size
// Return int splits
int split(string input_string, char separator, string arry[], int arry_size)
{
    int count=0;
    int j=0;
    string new_string;

    //Loop through all the characters in the input string.
    for(int i=0; i<=input_string.length(); i++)
    {
        //If a character of the string equals the seperator character or i equals the length of the string.
        //Then we know that that is a point where we will have to split the input string.
        if((input_string[i]==separator)||(input_string.length()==i))
        {
            // can't store in the array if array is already full
            if(count<arry_size) 
            {
                arry[count] = new_string; //Store String into array
            }
            new_string=""; //Reset string when stored into the array
            count++;
            j++;
        }
        else
        {
            new_string += input_string[i]; 
            //As long as we don't reach a seperator then add each character of the input string into our place holder array.
        }
    }
    if(arry[0]=="") //If the first value of the array is empty then return 0.
    {
        return 0;
    }
    if(j>arry_size) //Too many seperators for arry size then return -1.
    {
        return -1;
    }
    else
    {
    return j; //Return amount of splits that happened.
    }
}

// Algorithm: Finds what type of tile the player is on and prints the name of it
// Parameters: Map &map
// Return void
void mapTile(Map &map)
{
    if(map.isNPCLocation(map.getPlayerRow(),map.getPlayerCol()))
    {
        cout << "Merchant Tile" << endl;
    }
    else if(map.isRoomLocation(map.getPlayerRow(),map.getPlayerCol()))
    {
        cout << "Room Tile" << endl;
    }
    else if(map.isExplored(map.getPlayerRow(),map.getPlayerCol()))
    {
        cout << "Explored Tile" << endl;
    }
    else if(map.isDungeonExit(map.getPlayerRow(),map.getPlayerCol()))
    {
        cout << "Exit Tile" << endl;
    }
    else if(map.isFreeSpace(map.getPlayerRow(),map.getPlayerCol()))
    {
        cout << "Unexplored Tile" << endl;
    }
}

// Algorithm: Prompts a random riddle from a text file and returns whether the user got it right or wrong
// Parameters: N/A
// Return int
int riddle()
{
    srand(time(0));
    int rid = (rand()%20)+1; //Random number between 1-20
    ifstream in_file;
    in_file.open("riddles.txt"); //open the riddle text file
    string temp[20];
    for(int i=0; i<20; i++)
    {
        getline(in_file,temp[i]); //Put all the riddles into our array
    }
    string splity[2];
    string answer;
    split(temp[rid],'~',splity,2); //Split a random index so we have the answer and the riddle
    cout << "To trade with me answer this riddle" << endl;
    cout << splity[0] << endl; //cout the riddle
    cin >> answer; //cin the answer
    if(answer == splity[1]) //If the answer they gave is the right answer return 1
    {
        return 1;
    }
    else //Else return 0
    {
        return 0;
    }

     
}

// If the player tries to open the door without a key they will be prompted to play this game
// Create an empty map and randomly position the player somewhere on the map
// player has to identify which row and column they are on
// Paramters: N/A
// Return int
int doorGame()
{
    Map map; //create a map object
    int ans1;
    int ans2;
    srand(time(0));
    int rand1 = rand()%12; //get a random index for row
    int rand2 = rand()%12;  //get a random index for col
    map.setPlayerPosition(rand1, rand2); //set the player position to the random location
    int row = map.getPlayerRow(); // Save the row 
    int col = map.getPlayerCol(); // save the col
    cout << "To save the room you must solve this puzzle..." << endl;
    usleep(1000000);
    cout << "The X marks the spot...Locate the Row and Column of the X." << endl;
    usleep(1000000);
    map.displayMap();
    usleep(5000000);
    cout << "*********" << endl;
    cout << "Row: ";
    cin >> ans1; //save the answer for row
    cout << "Column: ";
    cin >> ans2; //save the answer for col
    ans1--;
    ans2--;
    if((ans1==row)&&(ans2==col)) //compare the 2
    {
        return 1; //If they match return 1
    }
    else 
    {
        return 0; //if they are wrong return 0
    }

}

// Algorithm: Function that checks if there is a room, npc, or dungeon exit
// Parameters: Map &map
// Return int
int check(Map &map)
{
    // npc map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())
    // room map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol())
    if(map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol())==true)
    {
        return 1; // There is a room
    }
    if(map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())==true)
    {
        return 2; //There is an npc
    }
    if(map.isDungeonExit(map.getPlayerRow(),map.getPlayerCol()))
    {
        return 3; //It is the dungeon exit
    }
    return 0; //Nothing
}

// Algorithm: 40% chance the function does something
// When it does do something -> 30% chance of randrob , 30% chance of poison, 30% chance of falling in a ditch, 10% chance of a random break.
// If the random number is in between a certain probability
// Perform the misfortune that is prompted
// the misfortune functions are within the inventory and party cpp files
// Parameters: Party party[], Inventory &inventory
// Return void
void randMisfort(Party party[], Inventory &inventory)
{
   srand(time(NULL));
 
   if (rand() % 100 < 40) //40 percent chance of occuring
   {
       cout << "OH NO! A misfortune has occurred!" << endl;
 
       int random = rand() % 100;
 
       if (30 > random) //30% chance of randrob
       {
           inventory.randRob();
       }
       else if (60 > random)//30% chance of poison
       {
           party[(rand() % 4) + 1].poison();
       }
       else if (90 > random)//30% chance of falling in a ditch
       {
           srand(time(NULL));
           int locked = (rand() % 4) + 1;
           if (locked == 1)
           {
               party[0].setFullness(party[0].getFullness()-5);
               cout << party[0].getName() << " fell in a ditch (-5)" << endl;
           }
           if (locked == 2)
           {
               party[1].setFullness(party[1].getFullness()-5);
               cout << party[1].getName() << " fell in a ditch (-5)" << endl;
           }
           if (locked == 3)
           {
               party[2].setFullness(party[2].getFullness()-5);
               cout << party[2].getName() << " fell in a ditch (-5)" << endl;
           }
           if (locked == 4)
           {
               party[3].setFullness(party[3].getFullness()-5);
               cout << party[3].getName() << " fell in a ditch (-5)" << endl;
           }
       }
       else if (100 > random) //10% chance of random break
       {
           inventory.randBreak();
       }
   }
}

// Carries out the math of a fight based on how many rooms cleared. If the player is already
// on a room then it will do a room battle. If the player wins a room battle then the room disapears
void fight(Map &map, Party party[],Inventory &inventory, Status &Status,vector<string> &Monsters_lvl1,vector<string> &Monsters_lvl2,vector<string> &Monsters_lvl3,vector<string> &Monsters_lvl4,vector<string> &Monsters_lvl5,vector<string> &Monsters_lvl6)
{
    srand(time(0));
    int prob;
    int rand_part;
    double strength;
    int option;
    int gold;
    int locked;
    if(Status.getRooms()==0) //If the player has cleared 0 rooms
    {
        {
            prob = rand()%Monsters_lvl1.size();
            cout << "A " << Monsters_lvl1[prob] << " has appeared!" << endl;
            cout << "Get ready to fight! ... Or surrender" << endl;
            cout << "Choose || 1:Fight | 2:Surrender ||" << endl;
            cin >> option; //Give them the option to fight or surrendur
            switch(option)
            {
                case 1: //Case 1 is to fight calculate the parties strength
                    strength = (((rand()%6)+1)*(inventory.weaponDamage())+inventory.checkWeapons())-((((rand()%6)+1)*(1))/inventory.getArmor()+1);
                    if(strength>0)//If strength>0 then the player wins
                    {
                        if(map.isRoomLocation(map.getPlayerRow(),map.getPlayerCol())) //check if it is a room
                        {
                            if(Monsters_lvl1.size()==0)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            cout << "Congrats you have defeated " << Monsters_lvl1[prob] << endl;
                            Monsters_lvl1.erase(Monsters_lvl1.begin()+(prob)); //Remove the monster you beat
                            inventory.setTresAt(inventory.getTresAt(0)+1,Status.getRooms());
                            cout << "You found a Silver Ring!" << endl;
                            cout << "Room Cleared" << endl;
                            usleep(1000000);
                            Status.addRooms(); //Add to cleared rooms
                            map.removeRoom(map.getPlayerRow(),map.getPlayerCol()); //Remove the room
                            inventory.setIngred(5);
                            inventory.setGold(10);
                            Status.randKey();
                            
                        }
                        else //Regular fight
                        {
                            if(Monsters_lvl1.size()<=1) //Save one monster for the room fight
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            else
                            {
                                cout << "Congrats you have defeated " << Monsters_lvl1[prob] << endl;
                                inventory.setIngred(5);
                                inventory.setGold(inventory.getGold()+10);
                                Status.randKey();
                                Monsters_lvl1.erase(Monsters_lvl1.begin()+(prob)); //Remove the moster that you beat
                            }
                        }
                    }
                    else //Lost the ight
                    {
                        cout << "You have been bested!" << endl;
                        cout << "You lost 5kg of ingredients and a quarter of your gold" << endl;
                        inventory.setIngred(-5);
                        gold = inventory.getGold() * 0.25;
                        inventory.setGold(inventory.getGold()-gold);
                        locked = (rand() % 4) + 1;
                        //Take 10 fullness from one of the party at random
                        if (locked == 1)
                        {
                            party[0].setFullness(party[0].getFullness()-10);
                            cout << party[0].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 2)
                        {
                            party[1].setFullness(party[1].getFullness()-10);
                            cout << party[1].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 3)
                        {
                            party[2].setFullness(party[2].getFullness()-10);
                            cout << party[2].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 4)
                        {
                            party[3].setFullness(party[3].getFullness()-10);
                            cout << party[3].getName() << " got injured in the fight (-10)" << endl;
                        }
                        
                    }
                    break;

                case 2: //Case 2 surrendur the fight -> one party member is killed off

                    cout << "You surrenderred!" << endl;
                    rand_part=rand()%4;
                    cout << Monsters_lvl1[prob] << " took " << party[rand_part].getName() << "!!" << endl;
                    party[rand_part].setFullness(0); //kill the rand party member off
                    break;
            }
        }
    }
    else if(Status.getRooms()==1)//If the player has cleared 1 room
    {                            //Same process as above, just different monsters and harder fight
            prob = rand()%Monsters_lvl2.size();
            cout << "A " << Monsters_lvl2[prob] << " has appeared!" << endl;
            cout << "Get ready to fight! ... Or surrender" << endl;
            cout << "Choose || 1:Fight | 2:Surrender ||" << endl;
            cin >> option;
            switch(option)
            {
                case 1: 
                    strength = (((rand()%6)+1)*(inventory.weaponDamage())+inventory.checkWeapons())-((((rand()%6)+1)*(2))/inventory.getArmor()+1);
                    if(strength>0)
                    {
                        if(map.isRoomLocation(map.getPlayerRow(),map.getPlayerCol()))
                        {
                            if(Monsters_lvl2.size()==0)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            cout << "Congrats you have defeated " << Monsters_lvl2[prob] << endl;
                            Monsters_lvl2.erase(Monsters_lvl2.begin()+(prob));
                            inventory.setTresAt(inventory.getTresAt(1)+1,Status.getRooms());
                            cout << "You found a Ruby necklace!" << endl;
                            cout << "Room Cleared" << endl;
                            usleep(1000000);
                            Status.addRooms();
                            map.removeRoom(map.getPlayerRow(),map.getPlayerCol());
                            inventory.setIngred(5);
                            inventory.setGold(inventory.getGold()+10);
                            Status.randKey();
                        }
                        else
                        {
                            if(Monsters_lvl2.size()<=1)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            else
                            {
                                cout << "Congrats you have defeated " << Monsters_lvl2[prob] << endl;
                                inventory.setIngred(5);
                                inventory.setGold(inventory.getGold()+10);
                                Status.randKey();
                                Monsters_lvl2.erase(Monsters_lvl2.begin()+(prob));
                                
                            }
                        }
                    }
                    else
                    {
                        cout << "You have been bested!" << endl;
                        cout << "You lost 10kg of ingredients and a quarter of your gold" << endl;
                        inventory.setIngred(-10);
                        gold = inventory.getGold() * 0.25;
                        inventory.setGold(inventory.getGold()-gold);
                        locked = (rand() % 4) + 1;
                        if (locked == 1)
                        {
                            party[0].setFullness(party[0].getFullness()-10);
                            cout << party[0].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 2)
                        {
                            party[1].setFullness(party[1].getFullness()-10);
                            cout << party[1].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 3)
                        {
                            party[2].setFullness(party[2].getFullness()-10);
                            cout << party[2].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 4)
                        {
                            party[3].setFullness(party[3].getFullness()-10);
                            cout << party[3].getName() << " got injured in the fight (-10)" << endl;
                        }
                    }
                    break;

                case 2:
                    cout << "You surrenderred!" << endl;
                    rand_part=rand()%4;
                    cout << Monsters_lvl2[prob] << " took " << party[rand_part].getName() << "!!" << endl;
                    party[rand_part].setFullness(0);
                    break;
            }
    }
    else if(Status.getRooms()==2)//If the player has cleared 2 rooms
    {
            prob = rand()%Monsters_lvl3.size();
            cout << "A " << Monsters_lvl3[prob] << " has appeared!" << endl;
            cout << "Get ready to fight! ... Or surrender" << endl;
            cout << "Choose || 1:Fight | 2:Surrender ||" << endl;
            cin >> option;
            switch(option)
            {
                case 1: 
                    strength = (((rand()%6)+1)*(inventory.weaponDamage())+inventory.checkWeapons())-((((rand()%6)+1)*(3))/inventory.getArmor()+1);
                    if(strength>0)
                    {
                        if(map.isRoomLocation(map.getPlayerRow(),map.getPlayerCol()))
                        {
                            if(Monsters_lvl3.size()==0)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            cout << "Congrats you have defeated " << Monsters_lvl3[prob] << endl;
                            inventory.setTresAt(inventory.getTresAt(2)+1,Status.getRooms());
                            cout << "You found a Emerald Bracelet!" << endl;
                            cout << "Room Cleared" << endl;
                            usleep(1000000);
                            Status.addRooms();
                            map.removeRoom(map.getPlayerRow(),map.getPlayerCol());
                            inventory.setIngred(5);
                            inventory.setGold(inventory.getGold()+10);
                            Status.randKey();
                            Monsters_lvl3.erase(Monsters_lvl3.begin()+(prob));
                        }
                        else
                        {
                            if(Monsters_lvl3.size()<=1)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            else
                            {
                                cout << "Congrats you have defeated " << Monsters_lvl3[prob] << endl;
                                inventory.setIngred(5);
                                inventory.setGold(inventory.getGold()+10);
                                Status.randKey();
                                Monsters_lvl3.erase(Monsters_lvl3.begin()+(prob));
                            }
                        }
                    }
                    else
                    {
                        cout << "You have been bested!" << endl;
                        cout << "You lost 15kg of ingredients and a quarter of your gold" << endl;
                        inventory.setIngred(-15);
                        gold = inventory.getGold() * 0.25;
                        inventory.setGold(inventory.getGold()-gold);
                        locked = (rand() % 4) + 1;
                        if (locked == 1)
                        {
                            party[0].setFullness(party[0].getFullness()-10);
                            cout << party[0].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 2)
                        {
                            party[1].setFullness(party[1].getFullness()-10);
                            cout << party[1].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 3)
                        {
                            party[2].setFullness(party[2].getFullness()-10);
                            cout << party[2].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 4)
                        {
                            party[3].setFullness(party[3].getFullness()-10);
                            cout << party[3].getName() << " got injured in the fight (-10)" << endl;
                        }
                        
                    }
                    break;

                case 2:
                    cout << "You surrenderred!" << endl;
                    rand_part=rand()%4;
                    cout << Monsters_lvl3[prob] << " took " << party[rand_part].getName() << "!!" << endl;
                    party[rand_part].setFullness(0);
                    break;
            }
    }
    else if(Status.getRooms()==3)//If the player has cleared 3 rooms
    {
            prob = rand()%Monsters_lvl4.size();
            cout << "A " << Monsters_lvl4[prob] << " has appeared!" << endl;
            cout << "Get ready to fight! ... Or surrender" << endl;
            cout << "Choose || 1:Fight | 2:Surrender ||" << endl;
            cin >> option;
            switch(option)
            {
                case 1: 
                    strength = (((rand()%6)+1)*(inventory.weaponDamage())+inventory.checkWeapons())-((((rand()%6)+1)*(4))/inventory.getArmor()+1);
                    if(strength>0)
                    {
                        if(map.isRoomLocation(map.getPlayerRow(),map.getPlayerCol()))
                        {
                            if(Monsters_lvl4.size()==0)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            cout << "Congrats you have defeated " << Monsters_lvl4[prob] << endl;
                            inventory.setTresAt(inventory.getTresAt(3)+1,Status.getRooms());
                            cout << "You found a Diamond Circlet!" << endl;
                            cout << "Room Cleared" << endl;
                            usleep(1000000);
                            Status.addRooms();
                            map.removeRoom(map.getPlayerRow(),map.getPlayerCol());
                            Monsters_lvl4.erase(Monsters_lvl4.begin()+(prob));
                            inventory.setIngred(5);
                            inventory.setGold(inventory.getGold()+10);
                            Status.randKey();
                        }
                        else
                        {
                            if(Monsters_lvl4.size()<=1)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            else
                            {
                                cout << "Congrats you have defeated " << Monsters_lvl4[prob] << endl;
                                
                                inventory.setIngred(5);
                                inventory.setGold(inventory.getGold()+10);
                                Status.randKey();
                                Monsters_lvl4.erase(Monsters_lvl4.begin()+(prob));
                            }
                        }
                    }
                    else
                    {
                        cout << "You have been bested!" << endl;
                        cout << "You lost 20kg of ingredients and a quarter of your gold" << endl;
                        inventory.setIngred(-20);
                        gold = inventory.getGold() * 0.25;
                        inventory.setGold(inventory.getGold()-gold);
                        locked = (rand() % 4) + 1;
                        if (locked == 1)
                        {
                            party[0].setFullness(party[0].getFullness()-10);
                            cout << party[0].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 2)
                        {
                            party[1].setFullness(party[1].getFullness()-10);
                            cout << party[1].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 3)
                        {
                            party[2].setFullness(party[2].getFullness()-10);
                            cout << party[2].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 4)
                        {
                            party[3].setFullness(party[3].getFullness()-10);
                            cout << party[3].getName() << " got injured in the fight (-10)" << endl;
                        }
                        
                    }
                    break;

                case 2:
                    cout << "You surrenderred!" << endl;
                    rand_part=rand()%4;
                    cout << Monsters_lvl4[prob] << " took " << party[rand_part].getName() << "!!" << endl;
                    party[rand_part].setFullness(0);
                    break;
            }
    }
    else if(Status.getRooms()==4)//If the player has cleared 4 rooms
    {
            prob = rand()%Monsters_lvl5.size();
            cout << "A " << Monsters_lvl5[prob] << " has appeared!" << endl;
            cout << "Get ready to fight! ... Or surrender" << endl;
            cout << "Choose || 1:Fight | 2:Surrender ||" << endl;
            cin >> option;
            switch(option)
            {
                case 1: 
                    strength = (((rand()%6)+1)*(inventory.weaponDamage())+inventory.checkWeapons())-((((rand()%6)+1)*(5))/inventory.getArmor()+1);
                    if(strength>0)
                    {
                        if(map.isRoomLocation(map.getPlayerRow(),map.getPlayerCol()))
                        {
                            if(Monsters_lvl5.size()==0)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            cout << "Congrats you have defeated " << Monsters_lvl5[prob] << endl;
                            Monsters_lvl5.erase(Monsters_lvl5.begin()+(prob));
                            inventory.setTresAt(inventory.getTresAt(4)+1,Status.getRooms());
                            cout << "You found a Gem-encrusted Goblet!" << endl;
                            cout << "Room Cleared" << endl;
                            usleep(1000000);
                            Status.addRooms();
                            map.removeRoom(map.getPlayerRow(),map.getPlayerCol());
                            inventory.setIngred(5);
                            inventory.setGold(inventory.getGold()+10);
                            Status.randKey();
                        }
                        else
                        {
                            if(Monsters_lvl5.size()==0)
                            {
                                cout << "No monsters found...Try clearing more rooms" << endl;
                            }
                            else
                            {
                                cout << "Congrats you have defeated " << Monsters_lvl5[prob] << endl;
                                inventory.setIngred(5);
                                inventory.setGold(inventory.getGold()+10);
                                Status.randKey();
                                Monsters_lvl5.erase(Monsters_lvl5.begin()+(prob));
                            }
                        }
                    }
                    else
                    {
                        cout << "You have been bested!" << endl;
                        cout << "You lost 25kg of ingredients and a quarter of your gold" << endl;
                        inventory.setIngred(-25);
                        gold = inventory.getGold() * 0.25;
                        inventory.setGold(inventory.getGold()-gold);
                        locked = (rand() % 4) + 1;
                        if (locked == 1)
                        {
                            party[0].setFullness(party[0].getFullness()-10);
                            cout << party[0].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 2)
                        {
                            party[1].setFullness(party[1].getFullness()-10);
                            cout << party[1].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 3)
                        {
                            party[2].setFullness(party[2].getFullness()-10);
                            cout << party[2].getName() << " got injured in the fight (-10)" << endl;
                        }
                        if (locked == 4)
                        {
                            party[3].setFullness(party[3].getFullness()-10);
                            cout << party[3].getName() << " got injured in the fight (-10)" << endl;
                        }
                        
                    }
                    break;

                case 2:
                    cout << "You surrenderred!" << endl;
                    rand_part=rand()%4;
                    cout << Monsters_lvl5[prob] << " took " << party[rand_part].getName() << "!!" << endl;
                    party[rand_part].setFullness(0);
                    break;
        }
    }
    else if(Status.getRooms()==5)//If the player has cleared 5 rooms
    {
        //Tell them to go to the exit for the final boss
        cout << "No fights all monsters have retreated to the exit of the dungeon." << endl;
    }
    
    
}

// Algorithm: Prompt user for which cookware and ingredients to use and prompt if the cook happened or did not
// Prompt for cookware 
// Based on the cookware chosen, make sure they have the item to cook, if not prompt them
// If they do have the cook item and enough ingredients, remove the ingredients and restore the health of everyone
// Parameters: Party party[], Party &you, Inventory &inventory
// Return void
void Cook_Eat(Party party[], Party &you, Inventory &inventory)
{
   char user_cookware; // user input of cookware
   int user_ingred; // user input of ingredients
 
   cout << "Select which cookware item you would like to use. (P,F,C)" << endl; // prompt for cookware to use
   cin >> user_cookware;
   cout << "How many kg of ingredients would you like to use for cooking. (increments of 5 kg)" << endl; // prompt for amount of ingredients to use
   cin >> user_ingred;
 
   if (user_cookware == 'P') // if they input P
   {
    if (inventory.getCookAt(0) > 0) // if they have a P
    {
       if (inventory.cookDamage(0) == true) // if the probability of the cookdamage comes back true
       {
           cout << "OH NO! Cook was unsuccessful!" << endl;
           inventory.setIngred(inventory.getIngred() - user_ingred); // removes the ingredients
       }
        else if (inventory.getCookAt(0) > 0) // if they have the P
        {
        if (inventory.getIngred() >= user_ingred) // if they have enough ingredients that they asked to cook with
        {
           you.setFullness(you.getFullness() + user_ingred / 5); // set all the fullness of each player evenly using / 5
           party[0].setFullness(party[0].getFullness() + user_ingred / 5);
           party[1].setFullness(party[1].getFullness() + user_ingred / 5);
           party[2].setFullness(party[2].getFullness() + user_ingred / 5);
           party[3].setFullness(party[3].getFullness() + user_ingred / 5);

           inventory.setIngred(inventory.getIngred() - user_ingred); // removes the ingredients
 
           cout << "Cook was successful!" << endl;
        }
        else
        {
            cout << "You do not have enough gold!" << endl;
        }
        }
   }
   else 
    {
        cout << "You do not have a ceramic pot to cook." << endl;
    }
   }
   if (user_cookware == 'F') // if they input F
   {
    if (inventory.getCookAt(1) > 0) // if they have a F
    {
       if (inventory.cookDamage(1) == true) // if the probability of the cookdamage comes back true
       {
           cout << "OH NO! Cook was unsuccessful!" << endl;
           inventory.setIngred(-user_ingred); // removes the ingredients
       }
       else if (inventory.getCookAt(1) > 0) // if they have F
       {
        if (inventory.getIngred() >= user_ingred) // if they have enough ingredients that they asked to cook with
        {
           you.setFullness(you.getFullness() + user_ingred / 5); // set all the fullness of each player evenly using / 5
           party[0].setFullness(party[0].getFullness() + user_ingred / 5);
           party[1].setFullness(party[1].getFullness() + user_ingred / 5);
           party[2].setFullness(party[2].getFullness() + user_ingred / 5);
           party[3].setFullness(party[3].getFullness() + user_ingred / 5);

           inventory.setIngred(-user_ingred); // removes the ingredients
 
           cout << "Cook was successful!" << endl;
       }
       else
       {
            cout << "You do not have enough gold!" << endl;
       }
   }
   }
    else
   {
        cout << "You do not have a frying pan to cook." << endl;
   }
   }
   if (user_cookware == 'C') // if they input C
   {
    if (inventory.getCookAt(2) > 0) // if they have a C
    {
       if (inventory.cookDamage(2) == true) // if the probability of the cookdamage comes back true
       {
           cout << "OH NO! Cook was unsuccessful!" << endl;
           inventory.setIngred(-user_ingred); // removes the ingredients
       }
       else if (inventory.getCookAt(2) > 0) // if they have C
       {
            if (inventory.getIngred() >= user_ingred) // // if they have enough ingredients that they asked to cook with
            {
                you.setFullness(you.getFullness() + user_ingred / 5); // set all the fullness of each player evenly using / 5
                party[0].setFullness(party[0].getFullness() + user_ingred / 5);
                party[1].setFullness(party[1].getFullness() + user_ingred / 5);
                party[2].setFullness(party[2].getFullness() + user_ingred / 5);
                party[3].setFullness(party[3].getFullness() + user_ingred / 5);

                inventory.setIngred(inventory.getIngred() - user_ingred); // removes the ingredients
        
                cout << "Cook was successful!" << endl;
            }
            else
            {
                cout << "You do not have enough gold!" << endl;
            }
       } 
   }
    else
    {
        cout << "You do not have a cauldron to cook." << endl;
    }
    }
}

// Algorithm: Prompt user for which items they want to buy or sell. Update the inventory menu
// Display the merchant menu and prompt for choices
// Based of which choice, add to their menu if they have enough gold
// If not tell them they do not have enough gold
// Allow them to purchase items until they decide to leave
// Parameters: Inventory &inventory, Status &Status
// Return void
void merchantMenu(Inventory &inventory, Status &Status)
{
int user_input = 0; // user's choice
int amount = 0; // price percent change
 
 
do // prompt until they input 6 to exit
{
cout << "+-------------+" << endl;
cout << "| INVENTORY   |" << endl;
cout << "+-------------+" << endl;
cout << "| Gold        |" << inventory.getGold() << endl;
cout << "| Ingredients |" << inventory.getIngred() << "kg" << endl;
cout << "| Cookware    | P:" << inventory.getCookAt(0) << "| F:" << inventory.getCookAt(1) << "| C:" << inventory.getCookAt(2) << endl;
cout << "| Weapons     | C:" << inventory.getWeaponsAt(0) << "| S:" << inventory.getWeaponsAt(1) << "| R:" << inventory.getWeaponsAt(2) << "| B:" << inventory.getWeaponsAt(3) << "| L:" << inventory.getWeaponsAt(4) << endl;
cout << "| Armor       |" << inventory.getArmor() << endl;
cout << "| Treasures   | R:" << inventory.getTresAt(0) << "| N:" << inventory.getTresAt(1) << "| B:" << inventory.getTresAt(2) << "| C:" << inventory.getTresAt(3) << "| G:" << inventory.getTresAt(4) << endl;
cout << "Choose one of the following:" << endl;
cout << "1. Ingredients: To make food, you have to cook raw ingredients." << endl;
cout << "2. Cookware: You will need something to cook those ingredients." << endl;
cout << "3. Weapons: It's dangerous to go alone, take this!" << endl;
cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
 
cin >> user_input;
 
double price_incr; // amount the price will change based of rooms cleared
 
   if (Status.getRooms() == 0) // 0 room
   {
       price_incr = 0;
   }
   if (Status.getRooms() == 1) // 1 rooms
   {
       price_incr = .25;
   }
   if (Status.getRooms() == 2) // 2 rooms
   {
       price_incr = .50;
   }
   if (Status.getRooms() == 3) // 3 rooms
   {
       price_incr = .75;
   }
   if (Status.getRooms() == 4) // 4 rooms
   {
       price_incr = 1.00;
   }
   if (Status.getRooms() == 5) // 5 rooms
   {
       price_incr = 1.25;
   }
  
if (user_input == 1){ // choose to buy ingredients
 
   cout << "How many kilograms of ingredients can I get you? [" << int(1 + 1 * price_incr) << "Gold]" << endl;
 
   cin >> amount;
   if (amount > inventory.getGold()) // if their gold is not more than the price
   {
       cout << "You do not have enough gold, purchase again!" << endl;
   }
   else
   {
       inventory.setIngred(amount); // change the ingredients
       cout << "Thank you for your patronage! What else can I get for you?" << endl;
 
       inventory.setGold(inventory.getGold() - amount); // remove gold
   }
 
}
 
if (user_input == 2){ // choose to buy cookware 
 
   int choice2 = 0;
 
   cout << "I have a several types of cookware, which one would you like?" << endl; // prompt for which cookware
   cout << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;
 
 
   cout << "Choose one of the following:" << endl;
   cout << "1. (25%) Ceramic Pot [" << int(2 + 2 * price_incr) << " Gold]" << endl;
   cout << "2. (10%) Frying Pan [" << int(10 + 10 * price_incr) << " Gold]" << endl;
   cout << "3. ( 2%) Cauldron [" << int(20 + 20 * price_incr) << " Gold]" << endl;
   cout << "4. Cancel" << endl;
 
   cin >> choice2;
 
   int amount;
 
   if (choice2 == 1){ // choose to buy ceramic pot
       cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
 
       cin >> amount;
       if (amount * 2 > inventory.getGold()) // not enough gold to buy
       {
           cout << "You do not have enough gold, purchase again!" << endl;
       }
       else if (amount > 0) // enough gold to buy
       {
           inventory.setCookAt(amount, choice2 - 1); // add the cook item to menu
           cout << "Thank you for your patronage! What else can I get for you?" << endl;
           inventory.setGold(inventory.getGold() - (2 * amount)); // remove the gold
       }
       else
       {
           break;
       }
   }
 
   if (choice2 == 2){ // choose to buy frying pan
       cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
 
       cin >> amount;
       if (amount * 12 > inventory.getGold()) // not enough gold to buy
       {
           cout << "You do not have enough gold, purchase again!" << endl;
       }
       else if (amount > 0) // enough gold to buy
       {
           inventory.setCookAt(amount, choice2 - 1); // add the cook item to menu
           cout << "Thank you for your patronage! What else can I get for you?" << endl;
           inventory.setGold(inventory.getGold() - 12 * amount); // remove the gold
       }
       else
       {
           break;
       }
   }
 
   if (choice2 == 3){ // choose to buy cauldron
       cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
 
       cin >> amount;
       if (amount * 20 > inventory.getGold()) // not enough gold to buy
       {
           cout << "You do not have enough gold, purchase again!" << endl;
       }
 
       else if (amount > 0) // enough gold to buy
       {
           inventory.setCookAt(amount, choice2 - 1); // add the cook item to menu
           cout << "Thank you for your patronage! What else can I get for you?" << endl;
           inventory.setGold(inventory.getGold() - 20 * amount); // remove the gold
       }
       else
       {
           break;
       }
   }
 
   if (choice2 == 4){
       continue;
   }
  
}
 
if (user_input == 3){ // choose to buy weapons
 
   int choice3 = 0;
 
   cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl;
   cout << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;
 
   cout << "Choose one of the following:" << endl; // prompt the weapons they can buy
   cout << "1. Stone Club [" << int(2 + 2 * price_incr) << " Gold]" << endl;
   cout << "2. Iron Spear [" << int(2 + 2 * price_incr) << " Gold]" << endl;
   cout << "3. (+1) Mythril Rapier [" << int(5 + 5 * price_incr) << " Gold]" << endl;
   cout << "4. (+2) Flaming Battle-Axe [" << int(15 + 15 * price_incr) << " Gold]" << endl;
   cout << "5. (+3) Vorpal Longsword [" << int(50 + 50 * price_incr) << " Gold]" << endl;
   cout << "6. Cancel" << endl;
 
   cin >> choice3;
 
 
   if (choice3 == 1){ // choose to buy stone club
       cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
 
       cin >> amount;
       if (amount * 2 > inventory.getGold()) // not enough gold
       {
           cout << "You do not have enough gold, purchase again!" << endl;
       }
 
       else if (amount > 0) // enough gold
       {
           inventory.setWeaponsAt(amount, choice3 - 1); // add the weapon
           cout << "Thank you for your patronage! What else can I get for you?" << endl;
           inventory.setGold(inventory.getGold() - (2 * amount)); // remove the gold
       }
       else
       {
           break;
       }
   }
 
   if (choice3 == 2){ // choose to buy iron spear
       cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
 
       cin >> amount;
       if (amount * 2 > inventory.getGold()) // not enough gold
       {
           cout << "You do not have enough gold, purchase again!" << endl;
       }
 
       else if (amount > 0) // enough gold 
       {
           inventory.setWeaponsAt(amount, choice3 - 1); // add the weapon
           cout << "Thank you for your patronage! What else can I get for you?" << endl;
           inventory.setGold(inventory.getGold() - 2 * amount); // remove the gold
       }
       else
       {
           break;
       }
   }
 
   if (choice3 == 3){ // choose to buy Mythril Rapier
       cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
 
       cin >> amount;
       if (amount * 5 > inventory.getGold()) // not enough gold
       {
           cout << "You do not have enough gold, purchase again!" << endl;
       }
 
       else if (amount > 0) // enough gold
       {
           inventory.setWeaponsAt(amount, choice3 - 1); // add the weapon
           cout << "Thank you for your patronage! What else can I get for you?" << endl;
           inventory.setGold(inventory.getGold() - 5 * amount); // remove the gold
       }
       else
       {
           break;
       }
   }
 
   if (choice3 == 4){ // choose to buy Flaming Battle-Axe
       cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
 
       cin >> amount;
       if (amount * 15 > inventory.getGold()) // not enough gold
       {
           cout << "You do not have enough gold, purchase again!" << endl;
       }
 
       else if (amount > 0) // enough gold
       {
           inventory.setWeaponsAt(amount, choice3 - 1); //add the weapon
           cout << "Thank you for your patronage! What else can I get for you?" << endl;
           inventory.setGold(inventory.getGold() - 15 * amount); // remove the gold
       }
       else
       {
           break;
       }
   }
 
   if (choice3 == 5){ // choose to buy Vorpal Longsword
       cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
 
       cin >> amount;
       if (amount * 50 > inventory.getGold()) // not enough gold
       {
           cout << "You do not have enough gold, purchase again!" << endl;
       }
 
       else if (amount > 0) // enough gold 
       {
           inventory.setWeaponsAt(amount, choice3 - 1); // add the weapon
           cout << "Thank you for your patronage! What else can I get for you?" << endl;
           inventory.setGold(inventory.getGold() - 50 * amount); // remove the gold
       }
       else
       {
           break;
       }
   }
 
   if (choice3 == 6){
       continue;
   }
 }
 
if (user_input == 4){ // choose to buy armor 
  
   cout << "How many suits of armor can I get you? [" << int(1 + 1 * price_incr) << "Gold]" << endl; // prompt for how much armor 
 
   cin >> amount;
   if (amount > inventory.getGold()) // not enough gold 
   {
       cout << "You do not have enough gold, purchase again!" << endl;
   }
   else
   {
       inventory.setArmor(amount); // set the armor based of how much they purchased 
       cout << "Thank you for your patronage! What else can I get for you?" << endl; 
       inventory.setGold(inventory.getGold() - amount); // remove the gold
   }
  
}
 
if (user_input == 5){ // decide to sell treasure
 
   int choice5 = 0;
 
   cout << "I have a space for numerous treasures, what would you like to sell me?" << endl;
 
   cout << "1 Room: Silver ring (R) - 10 gold pieces each" << endl;
   cout << "2 Rooms: Ruby necklace (N) - 20 gold pieces each" << endl;
   cout << "3 Rooms: Emerald bracelet (B) - 30 gold pieces each" << endl;
   cout << "4 Rooms: Diamond circlet (C) - 40 gold pieces each" << endl;
   cout << "5 Rooms: Gem-encrusted goblet (G) - 50 gold pieces each" << endl;
 
   cin >> choice5;
 
   if (choice5 == 1){
       if (inventory.getTresAt(0) > 0) // if they have a silver ring
       {
           inventory.setGold(inventory.getGold() + 10); // increase gold
           inventory.setTresAt(inventory.getTresAt(0)-1, 0); // remove the treasure
       }
       else 
       {
        cout << "You do not own a Silver ring" << endl;
       }
   }
 
   if (choice5 == 2){
       if (inventory.getTresAt(1) > 0) // if they have a ruby necklace
       {
           inventory.setGold(inventory.getGold() + 20); // increase gold
           inventory.setTresAt(inventory.getTresAt(1)-1, 1); // remove the treasure
       }
       else
       {
            cout << "You do not own a Ruby necklace" << endl;
       }
   }
 
   if (choice5 == 3){
       if (inventory.getTresAt(2) > 0) // if they have emerald bracelet
       {
           inventory.setGold(inventory.getGold() + 30); // increase gold
           inventory.setTresAt(inventory.getTresAt(2)-1, 2); // remove the treasure
       }
       else
       {
            cout << "You do not own a Emerald bracelet" << endl;
       }
   }
 
   if (choice5 == 4){ 
       if (inventory.getTresAt(3) > 0) // if they have a diamond circlet
       {
           inventory.setGold(inventory.getGold() + 40); // add gold
           inventory.setTresAt(inventory.getTresAt(3)-1, 3); // remove the treasure
       }
       else
       {
            cout << "You do not own a Diamond circlet" << endl;
       }
   }
 
   if (choice5 == 5){ 
       if (inventory.getTresAt(4) > 0) // if they have a Gem-encrusted goblet
       {
           inventory.setGold(inventory.getGold() + 50); // add gold
           inventory.setTresAt(inventory.getTresAt(4)-1, 4); // remove the treasure
       }
       else
       {
            cout << "You do not own a Gem-encrusted goblet" << endl;
       }
   }
}
 
} while (user_input != 6);

    

}

// Algorithm: Check how many monsters have been killed by the player
// Parameters: vector<string> &Monsters_lvl1,vector<string> &Monsters_lvl2,vector<string> &Monsters_lvl3,vector<string> &Monsters_lvl4,vector<string> &Monsters_lvl5,vector<string> &Monsters_lvl6)
// Return int
int monstSlayed(vector<string> &Monsters_lvl1,vector<string> &Monsters_lvl2,vector<string> &Monsters_lvl3,vector<string> &Monsters_lvl4,vector<string> &Monsters_lvl5,vector<string> &Monsters_lvl6)
{
    //Add all the sizes of the monster vectors
    int remain = Monsters_lvl1.size() + Monsters_lvl2.size() + Monsters_lvl3.size() + Monsters_lvl4.size() + Monsters_lvl5.size() + Monsters_lvl6.size();
    int slay = 21 - remain;//subtract the remaining from the total 21
    return slay; //return the amount of monsters killed
}

// Algorithm: If getRoom is equal to 5 the game is over and the team has won
// If atleast one team member plus the main member are still alive when 5 rooms have been reached, game has been won
// Print message congratulating the player on their success
// Print the final game stats
// Save stats into the filename
// Parameters: Status &status, Party party[], Party &you, Inventory &inventory, int turns, int explore, int slay
// Return void
void winGame(Status &status, Party party[], Party &you, Inventory &inventory, int turns, int explore, int slay)
{
   int alive = 0; // tracker for party members alive
   int leader = 0; // tracker for leader is alive
 
   if (status.getRooms() == 5) // if all the rooms have been completed
   {
       if (you.getFullness() > 0) // if the leader's health is above 0 (alive)
       {
           leader++; // add one to main
       }
 
       for (int i = 0; i < 4; i++) // loop through all other players
       {
           if (party[i].getFullness() > 0) // if the player at index i health is above 0
           {
               alive++; // add one to alive
           }
       }
       if ((alive >= 1) && (leader == 1)) // if the leader is alive and there is atleast one other remaining player alive
       {
           cout << "GAME OVER! Congratulations your team has won the game!" << endl; // print game ending message
       }
   
 
        ofstream fil; // create a file to read stats into
        
        fil.open("results.txt"); // open the file
        
        if (fil.is_open()) // if the file is open
        {
            cout << "GAME ENDING STATS" << endl;
            cout << "~~~~~~~~~~~~~~~~~" << endl;
        
            cout << "Leader's Name: " << you.getName() << endl; // print the party leader's name
            fil << you.getName(); // read name into file
        
            for (int i = 0; i < 4; i++) // loop through all other names
            {
                cout << "Member " << i+1 << ": " << party[i].getName() << endl; // print the other names
                fil << party[i].getName(); // read other names into file
            }
        
            cout << "Remaining Gold: " << inventory.getGold() << endl; // print the remaining gold
            fil << inventory.getGold(); // read gold into file
        
            cout << "Turns: " << turns << endl; // print the number of turns
            fil << turns; // read turns into file
        
            cout << "Spaces Explored: " << explore << endl; // print the number of spaces explored
            fil << explore; // read number of spaces explored into file
        
            cout << "Monsters Defeated: " << slay << endl; // print the number monsters killed
            fil << slay; // read number monsters killed into file
                cout << "Remaining Treasures: " << endl;
            for (int j = 0; j < 5; j++)
            {
                string tres_names[5] = {"Silver ring" , "Ruby necklace" , "Emerald bracelet" , "Diamond circlet" , "Gem-encrusted goblet"};
        
                    if (inventory.getTresAt(j) == 1) // if their is treasure left still
                    {
                        cout << tres_names[j] << endl;
                        fil << tres_names[j]; // read into file the treasures 
                    }
            }
        }
    }
}

// Algorithm: If sorcer anger level is 100, sorcer destroys all players and game ends
// Print a message informing the tragic event that caused the loss
// Print the final game stats
// Save stats into the filename
// Parameters: Status &status, Party party[], Party &you, Inventory &inventory, int turns, int explore, int slay
// Return void
void loseToSorc(Status &status, Party party[], Party &you, Inventory &inventory, int turns, int explore, int slay)
{
   if (status.getAnger() == 100) // if the sorcers anger is 100
   {
       cout << "GAME OVER! Your team lost to the sorcer!" << endl; // print game ending message
   
 
        ofstream fil; // create a file to read stats into
        
        fil.open("results.txt"); // open the file
        
        if (fil.is_open()) // if the file is open
        {
            cout << "GAME ENDING STATS" << endl;
            cout << "~~~~~~~~~~~~~~~~~" << endl;
        
            cout << "Leader's Name: " << you.getName() << endl; // print the party leader's name
            fil << "-" << you.getName(); // read name into file
        
            for (int i = 0; i < 4; i++) // loop through all other names
            {
                cout << "Member " << i+1 << ": " << party[i].getName() << endl; // print the other names
                fil << "-" << party[i].getName(); // read other names into file
            }
        
            cout << "Remaining Gold: " << inventory.getGold() << endl; // print the remaining gold
            fil << "-" << inventory.getGold(); // read gold into file
        
            cout << "Turns: " << turns << endl; // print the number of turns
            fil << "-" << turns; // read turns into file
        
            cout << "Spaces Explored: " << explore << endl; // print the number of spaces explored
            fil << "-" << explore; // read number of spaces explored into file
        
            cout << "Monsters Defeated: " << slay << endl; // print the number monsters killed
            fil << "-" << slay; // read number monsters killed into file
        
                cout << "Remaining Treasures: " << endl;
            for (int j = 0; j < 5; j++)
            {
                string tres_names[5] = {"Silver ring" , "Ruby necklace" , "Emerald bracelet" , "Diamond circlet" , "Gem-encrusted goblet"};
        
                    if (inventory.getTresAt(j) == 1) // if their are treasures
                    {
                        cout << tres_names[j] << endl;
                        fil << "-" << tres_names[j]; // read treasures into file
                    }
            }
        } 
    }   
}

// Algorithm: If the party leader dies from hunger (party vector is empty) then they lose immediately and the game ends
// Print a message informing the tragic event that caused the loss
// Print the final game stats
// Save stats into the filename
// Parameters: Status &status, Party party[], Party &you, Inventory &inventory, int turns, int explore, int slay
// Return void
void deathByHungAll(Status &status, Party party[], Party &you, Inventory &inventory, int turns, int explore, int slay)
{
   if (you.getFullness() == 0) // if the leader's health is 0
   {
       cout << "GAME OVER! Your team has died from hunger!" << endl; // print the game ending message
        
        
        ofstream fil; // create a file to read stats into
        
        fil.open("results.txt"); // open the file
        
        if (fil.is_open()) // if the file is open
        {
            cout << "GAME ENDING STATS" << endl;
            cout << "~~~~~~~~~~~~~~~~~" << endl;
        
            cout << "Leader's Name: " << you.getName() << endl; // print the party leader's name
            fil << "-" << you.getName(); // read name into file
        
            for (int i = 0; i < 4; i++) // loop through all other names
            {
                cout << "Member " << i+1 << ": " << party[i].getName() << endl; // print the other names
                fil << "-" << party[i].getName(); // read other names into file
            }
        
            cout << "Remaining Gold: " << inventory.getGold() << endl; // print the remaining gold
            fil << "-" << inventory.getGold(); // read gold into file
        
            cout << "Turns: " << turns << endl; // print the number of turns
            fil << "-" << turns; // read turns into file
        
            cout << "Spaces Explored: " << explore << endl; // print the number of spaces explored
            fil << "-" << explore; // read number of spaces explored into file
        
            cout << "Monsters Defeated: " << slay << endl; // print the number monsters killed
            fil << "-" << slay; // read number monsters killed into file
        
                cout << "Remaining Treasures: " << endl;

            for (int j = 0; j < 5; j++)
            {
                string tres_names[5] = {"Silver ring" , "Ruby necklace" , "Emerald bracelet" , "Diamond circlet" , "Gem-encrusted goblet"};

                    if (inventory.getTresAt(j) == 1) // if their is a treasure
                    {
                        cout << tres_names[j] << endl;
                        fil << tres_names[j]; // read treasures into file
                    }
            }
        } 
   }
}

// Algorithm: If user chooses the option to give up after every time they move print the game ending stats
// Print a message informing the tragic event that caused the loss
// Print the final game stats
// Save stats into the filename
// Parameters: Status &status, Party party[], Party &you, Inventory &inventory, int turns, int explore, int slay
// Return void
void giveUp(Status &status, Party party[], Party &you, Inventory &inventory, int turns, int explore, int slay)
{
   cout << "GAME OVER! Your team decided to give up!" << endl; // print the game ending message
 
   ofstream fil; // create a file to read stats into
  
   fil.open("results.txt"); // open the file
 
   if (fil.is_open()) // if the file is open
   {
       cout << "GAME ENDING STATS" << endl;
       cout << "~~~~~~~~~~~~~~~~~" << endl;
 
       cout << "Leader's Name: " << you.getName() << endl; // print the party leader's name
       fil << "-" << you.getName(); // read name into file
 
       for (int i = 0; i < 4; i++) // loop through all other names
       {
           cout << "Member " << i+1 << ": " << party[i].getName() << endl; // print the other names
           fil << "-" << party[i].getName(); // read other names into file
       }
 
       cout << "Remaining Gold: " << inventory.getGold() << endl; // print the remaining gold
       fil << "-" << inventory.getGold(); // read gold into file
 
       cout << "Turns: " << turns << endl; // print the number of turns
       fil << "-" << turns; // read turns into file
 
       cout << "Spaces Explored: " << explore << endl; // print the number of spaces explored
       fil << "-" << explore; // read number of spaces explored into file
 
       cout << "Monsters Defeated: " << slay << endl; // print the number monsters killed
       fil << slay; // read number monsters killed into file

        cout << "Remaining Treasures: " << endl;

       for (int j = 0; j < 5; j++)
       {
           string tres_names[5] = {"Silver ring" , "Ruby necklace" , "Emerald bracelet" , "Diamond circlet" , "Gem-encrusted goblet"};
 
               if (inventory.getTresAt(j) == 1) // if their is a treasure
               {
                   cout << tres_names[j] << endl;
                   fil << "-" << tres_names[j]; // read treasures into file
               }
       }
   }    
}

// Algorithm: First part of the final battle
// Similar mechanics to the fight, but just modified for it to be a final battle
// Paramters: Status &status, Party party[], Party &you, Inventory &inventory
// Return int
int battle1(Status &status, Party party[], Party &you, Inventory &inventory)
{
    int option;
    int strength;
    int rand1;
    srand(time(0));
    cout << "The sorcerer Has sent 3 wizards to fight you!" << endl;
    cout << "Get ready to fight!" << endl;
    cout << "1: Fight!" << endl;
    cin >> option;
    usleep(1000000);
    //First a regular fight but harder than any fight yet
    strength = ((rand()%6)*(inventory.weaponDamage())+inventory.checkWeapons())-(((rand()%6)*(7))/inventory.getArmor());
    if(strength > 0) //The player  has won the fight
    {
        cout << "You have defeated the Wizards!" << endl;
        cout << "Sorcerer: 'You may have beat me here but be ready to pay!" << endl;
        usleep(100000);
        cout << "3 more wizard henchmen are after you" << endl;
        usleep(100000);
        //Two choices for the player. Take a potion or just a normal fight
        cout << "You have two options to defeat them:" << endl;
        cout << "1: Fight normally" << endl;
        cout << "2: Take the potion that is on the ground" << endl;
        cin >> option; 
        switch(option)
        {   //Same fight as the first one
            case 1: strength = (((rand()%6)+1)*(inventory.weaponDamage())+inventory.checkWeapons())-(((rand()%6)*(6))/inventory.getArmor());
                    if(strength>0) //Win the second battle
                    {
                        cout << "You have won the Battle!" << endl;
                        usleep(100000);
                        return 1; //will send you to the final battle
                    }
                    else    //lose the second battle
                    {
                        cout << "The wizards have bested you!" << endl;
                        usleep(100000);
                        return 0; //You lost the game
                    }
        
            case 2: rand1 = (rand()%20)+1; //Higher chance of winning the battle with the potion
            strength = (rand1*(inventory.weaponDamage())+inventory.checkWeapons())-((((rand()%6)+1)*(7))/inventory.getArmor());
                    if(strength>0)//Win the second battle
                    {
                        cout << "You have won the Battle!" << endl;
                        
                        return 1; //Takes you to the final battle
                    }
                    else //Lost the second battle
                    {
                        cout << "The wizards have bested you!" << endl;
                        return 0; //You lost the game
                    }    
        }

    }
    else //Lost the first battle
    {   
        //you lost the game
        cout << "The wizards have bested you!" << endl;
        return 0;
    }


    

}

// Algorithm: Final battle vs the sorcerer
// Every time you fight there is a chance that you take damage
// Kill the sorcerer before it kills you
// Parameters: Status &status, Party party[], Party &you, Inventory &inventory, Sorcerer &sorcerer
// Return int
int finalBattle(Status &status, Party party[], Party &you, Inventory &inventory, Sorcerer &sorcerer)
{
    cout << "You beat my wizards, but they are ants compared to me." << endl;
    usleep(100000);
    cout << "Prepare to die!" << endl;
    usleep(2000000);
    cout << "                  o" << endl;
    cout << "                   O       /`-.__" << endl;
    cout << "                          /  \\ '^|" << endl;
    cout << "             o           T    l  *" << endl;
    cout << "                        _|-..-|_" << endl;
    usleep(100000);
    cout << "                 O    (^ '----' `)" << endl;
    cout << "                       `\\-....-/^" << endl;
    cout << "             O       o  ) ""/" " (" << endl;
    usleep(100000);
    cout << "                       _( (-)  )_" << endl;
    cout << "                   O  /\\ )    (  /\\" << endl;
    cout << "                     /  \\(    ) |  \\" << endl;
    cout << "                 o  o    \\)  ( /    \\" << endl;
    usleep(100000);
    cout << "                   /     |(  )|      \\" << endl;
    cout << "                  /    o \\ \\( /       \\" << endl;
    cout << "            __.--'   O    \\_ /   .._   \\" << endl;
    cout << "           //|)\\      ,   (_)   /(((\\^)'\\" << endl;
    cout << "              |       | O         )  `  |" << endl;
    usleep(100000);
    cout << "              |      / o___      /      /" << endl;
    cout << "             /  _.-''^^__O_^^''-._     /" << endl;
    cout << "           .'  /  -''^^    ^^''-  \\--'^" << endl;
    usleep(100000);
    cout << "         .'   .`.  `'''----'''^  .`. \\" << endl;
    cout << "       .'    /   `'--..____..--'^   \\ \\" << endl;
    cout << "      /  _.-/                        \\ \\" << endl;
    cout << "  .::'_/^   |                        |  `." << endl;
    cout << "         .-'|                        |    `-." << endl;
    usleep(100000);
    cout << "   _.--'`   \\                        /       `-." << endl;
    cout << "  /          \\                      /           `-._" << endl;
    cout << "  `'---..__   `.                  .�_.._   __       \\" << endl;
    usleep(100000);
    cout << "           ``'''`.              .'gnv   `'^  `''---'^" << endl;
    cout << "                  `-..______..-'" << endl;

    srand(time(0));
    int rand1;
    int strength;
    int math;
    while (sorcerer.getHealth() > 0) //While the sorcerer is alive
    { 
        //3 different prompts that the wizard can say uring the fight each turn
        rand1 = rand() % 3;
        if (rand1 == 0)
        {
            cout << "You can't best me!" << endl;
            usleep(1000000);
        }
        else if (rand1 == 1)
        {
            cout << "                    ____ " << endl;
            cout << "                  .'* *.'" << endl;
            cout << "               __/_*_*(_" << endl;
            cout << "              / _______ \\" << endl;
            usleep(100000);
            cout << "             _\\_)/___\\(_/_ " << endl;
            cout << "            / _((\\- -/))_ \\" << endl;
            cout << "            \\ \\())(-)(()/ /" << endl;
            cout << "             ' \\(((()))/ '" << endl;
            usleep(100000);
            cout << "            / ' \\)).))/ ' \\" << endl;
            cout << "           / _ \\ - | - /_  \\" << endl;
            cout << "          (   ( .;''';. .'  )" << endl;
            cout << "          _\\ __ /    )\\ __ /_" << endl;
            cout << "            \\/     ' /  \\/" << endl;
            cout << "             .'  '...' ' )" << endl;
            usleep(100000);
            cout << "              / /  |  \\ \\" << endl;
            cout << "             / .   .   . \\" << endl;
            usleep(100000);
            cout << "            /   .     .   \\" << endl;
            cout << "           /   /   |   \\   \\" << endl;
            cout << "         .'   /    b    '.  '." << endl;
            usleep(100000);
            cout << "     _.-'    /     Bb     '-. '-._ " << endl;
            cout << " _.-'       |      BBb       '-.  '-. " << endl;
            cout << " (________mrf\\____.dBBBb.________)____)" << endl;
            cout << "Try your best " << you.getName() << endl;
            usleep(2000000);
        }
        else if(rand1==2)
        {
            cout << "You don't have a chance" << endl;
            usleep(1000000);
        }
        cout << "What attack would you like to use?" << endl;
        cout << "|| 1: Melee | 2: Bow | 3: Magic ||" << endl;
        cin >> math; //Give the player options of what to use so that the fight is more interactive
        //Calculate strength a little bit easier than regular fights
        strength = (((rand()%15)+1)*(inventory.weaponDamage())+inventory.checkWeapons())-((((rand()%3))*(5))/inventory.getArmor());
        sorcerer.removeHealth(strength);
        //Remove whatever strength you got from the sorcerer health
        cout << "You hit the sorcerer for " << strength << "!" << endl;
        if(sorcerer.getHealth()<=0) //If the sorcerer is dead end the game
        {
            //won the game
            return 1;
        }
        rand1 = rand()%100;
        if(rand1<10) //10 percent chance of getting hit for 15 damage
        {
            you.setFullness(you.getFullness()-15);
            cout << "Sorcerer hit you with his fireball! (-15)" << endl;
            usleep(100000);
        }
        else if(rand1<30)
        {
            you.setFullness(you.getFullness()-10); // 20 percent chance of getting hit for 10
            cout << "Sorcerer knocked you back with his Acid Splash! (-10)" << endl;
            usleep(100000);
        }
        else if(rand1<50) //20 percent chance of getting hit for 8
        {
            you.setFullness(you.getFullness()-8);
            cout << "Sorcerer hit you with his staff! (-8)" << endl;
            usleep(100000);
        }
        else if(rand1<90)   // 40% chance of getting hit for 5
        {
            you.setFullness(you.getFullness()-5);
            cout << "Sorcerer grazed your head with an ice spike! (-5)" << endl;
            usleep(100000);
        }
        else if(rand1<100) //10 percent chance of dodging his attack
        {
            you.setFullness(you.getFullness());
            cout << "You dodged the sorcerers attack!" << endl;
            usleep(100000);
        }
        math = you.getFullness();
        if(math==0) //If you are at 0 health end the game
        {
            return 0; //Lose to sorcerer
        }
        if(sorcerer.getHealth()<=0) //if sorcerer is dead end the game
        {
            return 1; //Game win
        }
        //Print the health of both the player and the sorcerer
        cout << "You have " << you.getFullness() << " fullness left!" << endl;
        cout << "The sorcerer has " << sorcerer.getHealth() << " health left" << endl;
        usleep(2000000);
    }
    if(sorcerer.getHealth()<=0) //Sorcerer is dead
    {
        return 1; //Player wins
    }
}

// Algorithm: Sorting system -> sorts the party members based on fullness
// Parameters: Party party[]
// Return void
void partySort(Party party[])
{
    for(int i=0; i<4; i++) //Since our array has 4 values in it we go until i = 4.
    {   
        for (int j=0; j<4; j++)
        {
            if(party[i].getFullness()>party[j].getFullness()) //compares the values inside of the arrays at different points of the array.
            {   
                Party var; //Place holder to switch the values of the different positions in the arrays
                var = party[i]; //Save the value of party[i] in var since we are going to swap the values at party[i] and at party[j]
                party[i]=party[j]; //swap the values of party[i] and party[j]
                party[j]=var; //Now give the old value of the position party[i] to position party[j]
            }
        }
    }
}






int main()
{
    Inventory inventory;
    Status Status;
    Map map; 
    Sorcerer sorcerer;

    inventory.setArmor(100);
    inventory.setWeaponsAt(5,4);
    Status.addRooms();
    Status.addRooms();
    Status.addRooms();
    Status.addRooms();
    Status.addRooms();
    
    int turns=0;
    int explore=0;
    int slay=0;
    int fight_result;
    int option;
    int strength;
    //Initialize monster vectors
    vector<string> Monsters_lvl1 = {"Animated Armor","Bugbear","Harpy","Scarecrow"};
    vector<string> Monsters_lvl2 = {"Minotaur","Owlbear","Banshee","Wereboar"};
    vector<string> Monsters_lvl3 = {"Giant Crocodile","Troll","Hobgoblin Warlord","Mammoth"};
    vector<string> Monsters_lvl4 = {"Stone Giant","Night Hag","Assassin","Hydra"};
    vector<string> Monsters_lvl5 = {"Cloud Giant","Silver Dragon","Vampire","Lich"};
    vector<string> Monsters_lvl6 = {"Sorcerer"};

    //Starting screen
    cout << "              Welcome to Dungeon Escape" << endl;
    usleep(2000000);

    cout << "                     ___====-_  _-====___" << endl;
    cout << "           _--^^^#####//      \\#####^^^--_" << endl;
    cout << "        _-^##########// (    ) \\##########^-_" << endl;\
    usleep(100000);
    cout << "       -############//  |\\^^/|  \\############-" << endl;
    cout << "     _/############//   (@::@)    \\############\\_" << endl;
    usleep(100000);
    cout << "    /#############((     \\ //     ))#############\\ " << endl;
    cout << "   -###############\\\\   (oo)    //###############-" << endl;
    cout << " -#################\\   /    \\   //#################-" << endl;
    usleep(100000);
    cout << " -###################\\/      \\//###################-" << endl;
    cout << "_#/|##########/\\######(   /\\   )######/\\##########|\\#_" << endl;
    cout << "|/ |#/\\#/\\#/\\/  \\#/\\##\\  |  |  /##/\\#/  \\/\\#/\\#/\\#| \\|" << endl;
    cout << "`  |/  V  V  `   V  \\#\\| |  | |/#/  V   '  V  V  \\|  '" << endl;
    cout << "   `   `  `      `   / | |  | | \\ " << endl;
    cout << "                    (  | |  | |  )" << endl;
    usleep(100000);
    cout << "                   __\\ | |  | | /__" << endl;
    cout << "                  (vvv(VVV)(VVV)vvv)" << endl;

    //Have the player name all the players in his party
    string main_name;
    cout << "Enter your name:";
    cin >> main_name;
    string names[4];
    cout << "Enter the names of your party members:(4 names)" << endl;
    cin >> names[0] >> names[1] >> names[2] >> names[3];
    Party you(main_name);
    Party party[4];
    for(int i=0; i<4; i++)
    {
        party[i] = Party(names[i]);
    }

    //Give the player some instructions and guidance
    cout << "Between the 5 of you, you have 100 gold pieces." << endl;
    cout << "You will need to spend your money on the following items:" << endl;
    usleep(1000000);
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl;
    cout << "- COOKWARE. If you want to cook, you have to have cookware first." << endl;
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl;
    usleep(5000000);

    cout << "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way. But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;
    usleep(100000);

    //Open the merchant menu and let the player buy their items
    merchantMenu(inventory,Status);
    
    int count=0;
    int var;
    int prob;
    srand(time(0));
    //Create the random map
    while(count < 5) //add 5 rooms at random
    {
        int coord1=rand() % 12;
        int coord2=rand() % 12;
        if(map.addRoom(coord1, coord2) == false )
        {

        }
        else
        {
            count++;
            map.addRoom(coord1, coord2);
        }
    }
    count = 0;
    while(count < 5) //Add 5 npcs at random
    {
        int coord1=rand() % 12;
        int coord2=rand() % 12;
        if(map.addNPC(coord1, coord2) == false )
        {

        }
        else
        {
            count++;
            map.addNPC(coord1, coord2);
        }
    }
    map.displayMap(); //Display the map
    mapTile(map);
    int npcRoom;
    int choice;
    char dir;
    do
    {
        //Sort the party members by fullness
        partySort(party);
        //Check for ways to lose before every turn
        deathByHungAll(Status,party,you,inventory,turns,explore,slay);
        loseToSorc(Status,party,you,inventory,turns,explore,slay);
        slay = monstSlayed(Monsters_lvl1,Monsters_lvl2,Monsters_lvl3,Monsters_lvl4,Monsters_lvl5,Monsters_lvl6);
        turns++; //counter for turns
        //print the Status every turn
        cout << "+-------------+" << endl;
        cout << "| STATUS      |" << endl;
        cout << "+-------------+" << endl;
        cout << "| Rooms Cleared:" << Status.getRooms() << "| Keys:" << Status.getKeys() << "| Anger Level:" << Status.getAnger() << endl;
        cout << "+-------------+" << endl;
        cout << "| INVENTORY   |" << endl;
        cout << "+-------------+" << endl;
        cout << "| Gold        |" << inventory.getGold() << endl;
        cout << "| Ingredients |" << inventory.getIngred() << "kg" << endl;
        cout << "| Cookware    | P:" << inventory.getCookAt(0) << "| F:" << inventory.getCookAt(1) << "| C:" << inventory.getCookAt(2) << endl;
        cout << "| Weapons     | C:" << inventory.getWeaponsAt(0) << "| S:" << inventory.getWeaponsAt(1) << "| R:" << inventory.getWeaponsAt(2) << "| B:" << inventory.getWeaponsAt(3) << "| L:" << inventory.getWeaponsAt(4) << endl;
        cout << "| Armor       |" << inventory.getArmor() << endl;
        cout << "| Treasures   | R:" << inventory.getTresAt(0) << "| N:" << inventory.getTresAt(1) << "| B:" << inventory.getTresAt(2) << "| C:" << inventory.getTresAt(3) << "| G:" << inventory.getTresAt(4) << endl;
        cout << "+-------------+" << endl;
        cout << "| PARTY       |" << endl;
        cout << "+-------------+" << endl;
        cout << "| " << you.getName() << "| Fullness: " << you.getFullness() << endl;
        cout << "| " << party[0].getName() << "| Fullness: " << party[0].getFullness() << endl;
        cout << "| " << party[1].getName() << "| Fullness: " << party[1].getFullness() << endl;
        cout << "| " << party[2].getName() << "| Fullness: " << party[2].getFullness() << endl;
        cout << "| " << party[3].getName() << "| Fullness: " << party[3].getFullness() << endl;
        cout << "+-------------+" << endl;
        cout << "Choose one of the following" << endl;
        cout << "1: Move" << endl;
        cout << "2: Investigate" << endl;
        cout << "3: Pick A Fight" << endl;
        cout << "4: Cook And Eat" << endl;
        cout << "5: Give up" << endl;
        cin>>choice;
        while((choice<1)||(choice>5)) //Make sure they choose a valid input
        {
            map.displayMap();
            cout << "+-------------+" << endl;
            cout << "| STATUS      |" << endl;
            cout << "+-------------+" << endl;
            cout << "| Rooms Cleared:" << Status.getRooms() << "| Keys:" << Status.getKeys() << "| Anger Level:" << Status.getAnger() << endl;
            cout << "+-------------+" << endl;
            cout << "| INVENTORY   |" << endl;
            cout << "+-------------+" << endl;
            cout << "| Gold        |" << inventory.getGold() << endl;
            cout << "| Ingredients |" << inventory.getIngred() << "kg" << endl;
            cout << "| Cookware    | P:" << inventory.getCookAt(0) << "| F:" << inventory.getCookAt(1) << "| C:" << inventory.getCookAt(2) << endl;
            cout << "| Weapons     | C:" << inventory.getWeaponsAt(0) << "| S:" << inventory.getWeaponsAt(1) << "| R:" << inventory.getWeaponsAt(2) << "| B:" << inventory.getWeaponsAt(3) << "| L:" << inventory.getWeaponsAt(4) << endl;
            cout << "| Armor       |" << inventory.getArmor() << endl;
            cout << "| Treasures   | R:" << inventory.getTresAt(0) << "| N:" << inventory.getTresAt(1) << "| B:" << inventory.getTresAt(2) << "| C:" << inventory.getTresAt(3) << "| G:" << inventory.getTresAt(4) << endl;
            cout << "+-------------+" << endl;
            cout << "| PARTY       |" << endl;
            cout << "+-------------+" << endl;
            cout << "| " << you.getName() << "| Fullness: " << you.getFullness() << endl;
            cout << "| " << party[0].getName() << "| Fullness: " << party[0].getFullness() << endl;
            cout << "| " << party[1].getName() << "| Fullness: " << party[1].getFullness() << endl;
            cout << "| " << party[2].getName() << "| Fullness: " << party[2].getFullness() << endl;
            cout << "| " << party[3].getName() << "| Fullness: " << party[3].getFullness() << endl;
            cout << "+-------------+" << endl;
            mapTile(map);
            cout << "Enter a Valid Input" << endl;
            cout << "1: Move" << endl;
            cout << "2: Investigate" << endl;
            cout << "3: Pick A Fight" << endl;
            cout << "4: Cook And Eat" << endl;
            cout << "5: Give up" << endl;
            cin>>choice;
        }
        switch(choice) //Switch menu dependin on what the player chose
        {
            case 1: //Case 1 is to move 
                    //Prompt which direction they want to move
                    cout << "Choose a direction to go" << endl;
                    cout << "'a' for left" << endl;
                    cout << "'s' for down" << endl;
                    cout << "'w' for up" << endl;
                    cout << "'d' for right" << endl;
                    map.displayMap();
                    mapTile(map);
                    cin >> dir;
                    //Make sure they put in a valid input
                    while((dir!='a')&&(dir!='w')&&(dir!='s')&&(dir!='d'))
                    {
                        cout << "Enter a valid Input" << endl;
                        cout << "Choose a direction to go" << endl;
                        cout << "'a' for left" << endl;
                        cout << "'s' for down" << endl;
                        cout << "'w' for up" << endl;
                        cout << "'d' for right" << endl;
                        map.displayMap();
                        mapTile(map);
                        cin >> dir;
                    }
                    map.move(dir); //move the player in the dirrection they choose
                    if(!map.isExplored(map.getPlayerRow(),map.getPlayerCol()))
                    {
                        Status.addAnger(); //Add sorcerer anger everytime the player moves to an unexplored spot
                    }
                    //chance of party loosing a point of fullness
                    prob = (rand() % 100);
                    you.lose20(prob);

                    prob = (rand() % 100);
                    party[0].lose20(prob);

                    prob = (rand() % 100);
                    party[1].lose20(prob);

                    prob = (rand() % 100);
                    party[2].lose20(prob);

                    prob = (rand() % 100);
                    party[3].lose20(prob);
                    
                    npcRoom = check(map);
                    map.displayMap();
                    mapTile(map);
                    if(npcRoom==1) //If there is a room then
                    {   //Prompt the options that the player can do in a room
                        cout << "You have come by a room..." << endl;
                        cout << "There are 3 options:" << endl;
                        cout << "1: Move" << endl;
                        cout << "2: Go inside" << endl;
                        cout << "3: Give up" << endl;
                        cin >> choice;

                        switch(choice) //choice 1 is to move -> same as the move before
                        {
                            case 1: cout << "Choose a direction to go" << endl;
                                    cout << "'a' for left" << endl;
                                    cout << "'s' for down" << endl;
                                    cout << "'w' for up" << endl;
                                    cout << "'d' for right" << endl;
                                    map.displayMap();
                                    mapTile(map);
                                    cin >> dir;
                                    while((dir!='a')&&(dir!='w')&&(dir!='s')&&(dir!='d'))
                                    {
                                        cout << "Enter a valid Input" << endl;
                                        cout << "Choose a direction to go" << endl;
                                        cout << "'a' for left" << endl;
                                        cout << "'s' for down" << endl;
                                        cout << "'w' for up" << endl;
                                        cout << "'d' for right" << endl;
                                        map.displayMap();
                                        mapTile(map);
                                        cin >> dir;
                                    }
                                    map.move(dir);
                                    if(!map.isExplored(map.getPlayerRow(),map.getPlayerCol()))
                                    {
                                        Status.addAnger();
                                    }
                                    randMisfort(party,inventory);
                                    prob = (rand() % 100);
                                    you.lose20(prob);

                                    prob = (rand() % 100);
                                    party[0].lose20(prob);

                                    prob = (rand() % 100);
                                    party[1].lose20(prob);

                                    prob = (rand() % 100);
                                    party[2].lose20(prob);

                                    prob = (rand() % 100);
                                    party[3].lose20(prob);
                                    
                                    map.displayMap();
                                    mapTile(map);
                                    break;
                            
                            case 2: //If the character has a key
                                    //Battle a monster
                                    //Remove room


                                        cout << "You may now use a key on the door to pass through..." << endl;
                                        usleep(500000);
                                        cout << "Proceed with caution" << endl;
                                        usleep(500000);

                                        if(Status.getKeys()>0) //If theyt have a key then remove the key and start a fight
                                        {
                                            cout << "You have opened the door using a key!" << endl;
                                            usleep(500000);
                                            Status.removeKeys();
                                            fight(map,party,inventory,Status,Monsters_lvl1,Monsters_lvl2,Monsters_lvl3,Monsters_lvl4,Monsters_lvl5,Monsters_lvl6);
                                        }
                                        else //If they don't have a key
                                        {
                                            cout << "You can't open this yet. You need a key!" << endl;
                                            cout << "Solve this puzzle to ever see this door again" << endl;
                                            usleep(500000);
                                            var = doorGame(); //Play the door game
                                            if(var==1)//If they complete the door game
                                            {
                                                cout << "Congrats you have solved the puzzle ... return once you have found a key" << endl;
                                                usleep(500000);
                                            }
                                            else//if they fail the door game remove the door and put it in a random place
                                            {
                                                cout << "You have failed the puzzle ... The door is now gone!" << endl;
                                                map.removeRoom(map.getPlayerRow(),map.getPlayerCol());
                                                while(count < 1) //add 1 rooms at random
                                                {
                                                    int coord1=rand() % 12;
                                                    int coord2=rand() % 12;
                                                    if(map.addRoom(coord1, coord2) == false )
                                                    {

                                                    }
                                                    else
                                                    {
                                                        count++;
                                                        map.addRoom(coord1, coord2);
                                                    }
                                                }
                                            }
                                            usleep(500000);
                                        }
                                    break;

                            case 3: //Give up
                                    //Give up function ends the game
                                    giveUp(Status,party,you,inventory,turns,explore,slay);
                                    return 0;
                        
                        }

                    }
                    else if(npcRoom == 2) //Found a merchant
                    {   //Three choices for merchant tiles
                        cout << "You have found a Merchant" << endl;
                        cout << "You have three options:" << endl;
                        cout << "1: Move" << endl;
                        cout << "2: Trade with the Merchant" << endl;
                        cout << "3: Give Up" << endl;
                        cin >> choice;

                        switch(choice) //switch case for the 3 choices
                        {   
                            //move same as earlier
                            case 1: cout << "Choose a direction to go" << endl;
                                    cout << "'a' for left" << endl;
                                    cout << "'s' for down" << endl;
                                    cout << "'w' for up" << endl;
                                    cout << "'d' for right" << endl;
                                    map.displayMap();
                                    mapTile(map);
                                    cin >> dir;
                                    while((dir!='a')&&(dir!='w')&&(dir!='s')&&(dir!='d'))
                                    {
                                        cout << "Enter a valid Input" << endl;
                                        cout << "Choose a direction to go" << endl;
                                        cout << "'a' for left" << endl;
                                        cout << "'s' for down" << endl;
                                        cout << "'w' for up" << endl;
                                        cout << "'d' for right" << endl;
                                        map.displayMap();
                                        mapTile(map);
                                        cin >> dir;
                                    }
                                    map.move(dir);
                                    if(!map.isExplored(map.getPlayerRow(),map.getPlayerCol()))
                                    {
                                        Status.addAnger();
                                    }
                                    you.lose20(prob);
                                    rand();
                                    party[0].lose20(prob);
                                    rand();
                                    party[1].lose20(prob);
                                    rand();
                                    party[2].lose20(prob);
                                    rand();
                                    party[3].lose20(prob);
                                    map.displayMap();
                                    mapTile(map);
                                    break;

                            case 2: //Puzzle to talk to npc
                                    //if fail then fight monster
                                    //else open merchant menu
                                    //Remove the npc
                                    var = riddle();//Run the riddle function
                                    if(var == 1)//If they get the riddle right
                                    {
                                        cout << "Well done you passed my test...you can trade with me all that you want." << endl;
                                        //Open merchant menu
                                        merchantMenu(inventory,Status);
                                        cout << "Pleasure doing business with you..." << endl;
                                        usleep(1000000);
                                        map.removeNPC(map.getNumRows(),map.getPlayerCol()); //Remove the npc when they are done trading
                                        
                                    }
                                    else //If they get the riddle wrong
                                    {
                                        cout << "INCORRECT, now you will have to pay" << endl;
                                        usleep(500000);
                                        //Start fight
                                        fight(map,party,inventory,Status,Monsters_lvl1,Monsters_lvl2,Monsters_lvl3,Monsters_lvl4,Monsters_lvl5,Monsters_lvl6);
                                        map.removeNPC(map.getNumRows(),map.getPlayerCol()); //Remove the npc
                                    }
                                    break;

                            case 3: //Give up lose game
                                    giveUp(Status,party,you,inventory,turns,explore,slay);
                                    return 0;
                        }
                        map.removeNPC(map.getPlayerRow(),map.getPlayerCol());
                        map.exploreSpace(map.getPlayerRow(),map.getPlayerCol()); //Set the space to explored
                    }
                    else if(npcRoom==3) //If the tile is the exit to the dungeon
                    {
                        if(Status.getRooms()==5) //if they have cleared all the doors then give the player 2 options
                        {
                            cout << "You have reached the exit of the dungeon!" << endl;
                            cout << "1: Enter" << endl;
                            cout << "2: move" << endl;
                            cin >> option;
                            switch(option)
                            {   //If they choose to fight then the final battle starts
                                case 1: cout << "HAHAHAHA Welcome to your end" << endl; 
                                        usleep(1000000);
                                        cout << "              _,-'|"<< endl; 
                                        cout << "           ,-'._  |"<< endl; 
                                        cout << " .||,      |####\\ |"<< endl; 
                                        usleep(500000);
                                        cout << "\\.`',/     \\####| |"<< endl; 
                                        cout << "= ,. =      |###| |"<< endl; 
                                        usleep(500000);
                                        cout << "/ || \\    ,-'\\#/,'`."<< endl; 
                                        cout << "||     ,'   `,,. `."<< endl; 
                                        cout << ",|____,' , ,;' \\| |"<< endl; 
                                        cout << "(3|\\    _/|/'   _| |"<< endl; 
                                        usleep(500000);
                                        cout << "||/,-''  | >-'' _,\\"<< endl; 
                                        cout << "||'      ==\\ ,-'  ,'"<< endl; 
                                        cout << "||       |  V \\ ,|"<< endl; 
                                        cout << "||       |    |` |"<< endl; 
                                        cout << "||       |    |   \\"<< endl; 
                                        usleep(500000);
                                        cout << "||       |    \\    \\"<< endl; 
                                        cout << "||       |     |    \\"<< endl; 
                                        cout << "||       |      \\_,-'"<< endl; 
                                        usleep(500000);
                                        cout << "||       |___,,-- )_\\"<< endl; 
                                        cout << "||         |_|   ccc/"<< endl; 
                                        cout << "||        ccc/"<< endl; 
                                        usleep(500000);
                                        //Start the opening battle
                                        strength = battle1(Status,party,you,inventory);
                                        if(strength == 1) //If they win the openening battle
                                        {   //Take away 50 health from the sorcerer
                                            sorcerer.removeHealth(50);
                                            //Start the final battle
                                            strength = finalBattle(Status,party,you,inventory,sorcerer);
                                            if(strength==1) //IF they win the final battle
                                            {
                                                Monsters_lvl6.pop_back(); //Remove the sorcerer from his vector
                                                //Run the win game function and end the game
                                                winGame(Status,party,you,inventory,turns,explore,slay);
                                                return 0;
                                            }
                                            else //If they lose the final battle
                                            {
                                                //set anger to 100 and run the lose to sorcerer function
                                                //End the game
                                                Status.setAnger(100);
                                                loseToSorc(Status,party,you,inventory,turns,explore,slay);
                                                return 0;
                                            }


                                        }
                                        else
                                        {
                                            //Lose the first battle lose the game
                                            Status.setAnger(100);
                                            loseToSorc(Status,party,you,inventory,turns,explore,slay);
                                        }
                                        break;

                                //Case 2 move like the other move before
                                case 2:cout << "Choose a direction to go" << endl;
                                    cout << "'a' for left" << endl;
                                    cout << "'s' for down" << endl;
                                    cout << "'w' for up" << endl;
                                    cout << "'d' for right" << endl;
                                    map.displayMap();
                                    mapTile(map);
                                    cin >> dir;
                                    while((dir!='a')&&(dir!='w')&&(dir!='s')&&(dir!='d'))
                                    {
                                        cout << "Enter a valid Input" << endl;
                                        cout << "Choose a direction to go" << endl;
                                        cout << "'a' for left" << endl;
                                        cout << "'s' for down" << endl;
                                        cout << "'w' for up" << endl;
                                        cout << "'d' for right" << endl;
                                        map.displayMap();
                                        mapTile(map);
                                        cin >> dir;
                                    }
                                    map.move(dir);
                                    if(!map.isExplored(map.getPlayerRow(),map.getPlayerCol()))
                                    {
                                        Status.addAnger();
                                    }
                                    prob = (rand() % 100);
                                    you.lose20(prob);

                                    prob = (rand() % 100);
                                    party[0].lose20(prob);

                                    prob = (rand() % 100);
                                    party[1].lose20(prob);

                                    prob = (rand() % 100);
                                    party[2].lose20(prob);

                                    prob = (rand() % 100);
                                    party[3].lose20(prob);
                                    
                                    map.displayMap();
                                    mapTile(map);
                                    break;
                            }
                        }
                        else //IF the don't have 5 keys then they can't do anything at the tile
                        {
                            cout << "You can't enter here yet! Try clearing more rooms." << endl;
                        }
                    }
                    break;

            //Investigate 
            case 2: //Check if the tile is explored
                    if(map.isExplored(map.getPlayerRow(),map.getPlayerCol()))
                    {
                        //print if tile is explored
                        cout << "You already explored this area!" << endl;
                        cout << "Choose another option" << endl;
                    }
                    else
                    {
                        //tile was not explored
                        prob = rand()%100;
                        if(prob<20)//20 percent chance a key is found
                        {
                            //Find key
                            Status.addKeys();
                            cout << "You found a Key!" << endl;
                            cout << "Use keys to open rooms." << endl;
                        }
                        else if(prob<40) //20% chance they find a treasure
                        {
                            //Find treasure
                            
                            if(Status.getRooms()==1)
                            {
                                inventory.setTresAt(1,Status.getRooms()-1);
                                cout << "You found a Silver Ring!" << endl;
                            }
                            else if(Status.getRooms()==2)
                            {
                                inventory.setTresAt(1,Status.getRooms()-1);
                                cout << "You found a Ruby Necklace!" << endl;
                            }
                            else if(Status.getRooms()==3)
                            {
                                inventory.setTresAt(1,Status.getRooms()-1);
                                cout << "You found a Emerald Bracelet!" << endl;
                            }
                            else if(Status.getRooms()==4)
                            {
                                inventory.setTresAt(1,Status.getRooms()-1);
                                cout << "You found a Diamond Circlet!" << endl;
                            }
                            else if(Status.getRooms()==5)
                            {
                                inventory.setTresAt(1,Status.getRooms()-1);
                                cout << "You found a Gem-Encrusted Goblet!" << endl;
                            }
                        }
                        else if(prob<60) //20% percent chance a monster appears
                        {
                            fight(map,party,inventory,Status,Monsters_lvl1,Monsters_lvl2,Monsters_lvl3,Monsters_lvl4,Monsters_lvl5,Monsters_lvl6);
                        }
                        map.exploreSpace(map.getDungeonExitRow(),map.getPlayerCol());
                        explore++;
                        //50% chance hunger goes down
                        //50% chance hunger goes down
                        prob = (rand() % 100);
                        you.lose50(prob);

                        prob = (rand() % 100);
                        party[0].lose50(prob);

                        prob = (rand() % 100);
                        party[1].lose50(prob);

                        prob = (rand() % 100);
                        party[2].lose50(prob);

                        prob = (rand() % 100);
                        party[3].lose50(prob);
                        
                        map.displayMap();
                    }
                    randMisfort(party,inventory); //Chance a misfortune happens
                    break;
            
            case 3: //Pick a fight
                    //Run the fight function
                    fight(map,party,inventory,Status,Monsters_lvl1,Monsters_lvl2,Monsters_lvl3,Monsters_lvl4,Monsters_lvl5,Monsters_lvl6);
                    randMisfort(party,inventory);//Chance a misfortune happens
                    //50% chance hunger goes down
                    prob = (rand() % 100);
                    you.lose50(prob);

                    prob = (rand() % 100);
                    party[0].lose50(prob);

                    prob = (rand() % 100);
                    party[1].lose50(prob);

                    prob = (rand() % 100);
                    party[2].lose50(prob);

                    prob = (rand() % 100);
                    party[3].lose50(prob);

                    map.displayMap();
                    break;

            case 4: //Cook and eat
                    //Run the cook_eat function
                    Cook_Eat(party,you,inventory);
                    randMisfort(party,inventory);//Chance a misfortune happens
                    break;

            case 5: //End the game and run giveup function
            giveUp(Status,party,you,inventory,turns,explore,slay);
            return 0;
        }

    } while (choice != 5);
    return 0;
}