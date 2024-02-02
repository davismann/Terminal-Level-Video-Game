// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - Inventory.cpp
 
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include "Inventory.h"
 
using namespace std;
 
       Inventory::Inventory()
       {
           gold = 100;
           ingred = 0;
           armor = 0;
           for (int i = 0; i < 5; i++) // set all the cook items to 0
           {
               cook[i] = 0;
           }
           for (int i = 0; i < 5; i++) // set all the weapon items to 0
           {
               weapons[i] = 0;
               tres[i] = 0;
           }
       }
       void Inventory::setGold(int gold_) // set gold
       {
           gold = gold_;
       }
       int Inventory::getGold() // return gold
       {
           return gold;
       }
       void Inventory::setIngred(int ingred_) // set ingred
       {
           ingred += ingred_;
       }
       int Inventory::getIngred() // get ingred
       {
           return ingred;
       }
       void Inventory::setCookAt(int cook_, int index) // set cook at certain index
       {
           if ((index >= 0) && (index < 3))
           {
               cook[index] += cook_;
           }
       }
       int Inventory::getCookAt(int index) // get cook at certain index
       {
           if ((index >= 0) && (index < 3))
           {
              return cook[index];
           }
       }
       void Inventory::setWeaponsAt(int weapons_, int index) // set weapon at certain index
       {
           if ((index >= 0) && (index < 5))
           {
               weapons[index] += weapons_;
           }
       }
       int Inventory::getWeaponsAt(int index) // get cook at certain index
       {
           if ((index >= 0) && (index < 5))
           {
              return weapons[index];
           }
       }
       void Inventory::setArmor(int armor_) // set armor
       {
           armor += armor_;
       }
       int Inventory::getArmor() // return armor
       {
           return armor;
       }
       void Inventory::setTresAt(int tres_, int index) // sell certain tres
       {
           if ((index >= 0) && (index < 5))
           {
               tres[index] = tres_;
           }
       }
       int Inventory::getTresAt(int index) // get tres at certain index
       {
           if ((index >= 0) && (index < 5))
           {
               return tres[index];
           }
       }
       
        // Algorithm: Calculate the weapon damage for fighting
        // Calculate strength using formula
        // Parameters: N/A
        // Return int
       int Inventory::weaponDamage()
       {
           int amountWeap = 0;
           for (int i = 0; i < 5; i++) // loop to count amount of weapons
           {
               amountWeap += weapons[i];
           }
 
           int strength = 5*(amountWeap) + 1*(weapons[2]) + 2*(weapons[3]); // formula to calculate strength
           return strength;
       }

        // User choices which cookware to use
        // Depending one which cookware was selected to use
        // Each cookware has a probability of breaking: Pan = 25%, Pot = 10%, Cauldron = 2%
        // Return if the cookware breaks
        // Lose ingredients used to make and remove the cookware from inventory
       bool Inventory::cookDamage(int index)
       {
           if (index == 0)
           {
               if ((rand() % 100) < 25)
               {
                   cook[0]--;
                   return true;
               }
               else
               {
                   return false;
               }
           }
           if (index == 1)
           {
               if ((rand() % 100) < 10)
               {
                   cook[1]--;
                   return true;
               }
               else
               {
                   return false;
               }
           }
           if (index == 2)
           {
               if ((rand() % 100) < 2)
               {
                   cook[2]--;
                   return true;
               }
               else
               {
                   return false;
               }
           }
       }

        // Algorithm: Team gets robbed based on a certain probability
        // Randomly lose 10kg of ingredients, 1 cookware item, 1 armor item
        // Print message stating you got robbed
        // Parameters: N/A
        // Return void
       void Inventory::randRob()
       {
           srand(time(NULL));
 
           cout << "Your team was robbed by dungeon bandits!" << endl;
           int randNum = (rand() % 3) + 1;
 
           if (randNum == 1) // lose 10kg of ingredients if the random number is 1
           {
               if (getIngred() > 9)
               {
                   setIngred(getIngred() - 10);
                   cout << "You lost 10kg of ingredients!" << endl;
               }
           }
           else if (randNum == 2) // lose 1 cookware if the random number is 2
           {
               srand(time(NULL));
               int randNum2 = (rand() % 3) + 1;
 
               if (randNum2 == 1)
               {
                   if (getCookAt(0) > 0)
                   {
                       setCookAt(getCookAt(0) - 1, 0);
                       cout << "You lost 1 ceramic pot!" << endl;
                   }
               }
               if (randNum == 2)
               {
                   if (getCookAt(1) > 0)
                   {
                       setCookAt(getCookAt(1) - 1, 0);
                       cout << "You lost 1 frying pan!" << endl;
                   }
               }
               if (randNum == 3)
               {
                   if (getCookAt(2) > 0)
                   {
                       setCookAt(getCookAt(2) - 1, 0);
                       cout << "You lost 1 cauldron!" << endl;
                   }
               }
 
           }
           else if (randNum == 3) // lose 1 armor item if the random number is 3
           {
               if (getArmor() > 0)
               {
                   setArmor(getArmor() - 1);
                   cout << "You lost 1 item of armor!" << endl;
               }
           }
           else
           {
                cout << "Yay! The gods were on your side this time." << endl;
                cout << "No misfortune has been overturned." << endl;
           }
 
       }

        // Algorithm: One weapons or armor breaks at random probability
        // Print message stating a random break occured
        // Parameters: N/A
        // Return void
       void Inventory::randBreak()
       {
           srand(time(NULL));
 
           cout << "One of your weapons broke!" << endl;
           int randNum = (rand() % 5) + 1;
 
           if (randNum == 1) // lose a club
           {
                if(weapons[0]>0)
                {
                    weapons[0]--;
                    cout << "You lost 1 club!" << endl;
                }
                else
                {
                    randNum++;
                }
           }
           else if (randNum == 2) // // lose a spear
           {
                if(weapons[1]>0)
                {
                    weapons[1]--;
                    cout << "You lost 1 spear!" << endl;
                }
                else
                {
                    randNum++;
                }
           }
           else if (randNum == 3) // lose a rapier
           {
                if(weapons[1]>0)
                {
                    weapons[2]--;
                    cout << "You lost 1 rapier!" << endl;
                }
                else
                {
                    randNum++;
                }
           }
           else if (randNum == 4) // lose a battle-axe
           {
                if(weapons[3]>0)
                {
                    weapons[3]--;
                    cout << "You lost 1 battle-axe!" << endl;
                }
                else
                {
                    randNum++;
                }
           }
           else if (randNum == 5) // lose a longsword
           {
                if(weapons[4]>0)
                {
                    weapons[4]--;
                    cout << "You lost 1 longsword!" << endl;
                }
                else
                {
                    randNum++;
                }
           }
           else
           {
                cout << "Yay! The gods were on your side this time." << endl;
                cout << "No misfortune has been overturned." << endl;
           }
       }

        // Algorithm: Check if players have 5 different weapons
        // If they do return 4
        // Parameters: N/A
        // Return int
       int Inventory::checkWeapons()
       {
            if((weapons[0]>=1)&&(weapons[1]>=1)&&(weapons[2]>=1)&&(weapons[3]>=1)&&(weapons[4]>=1))
            {
                return 4;
            }
            else
            {
                return 1;
            }
       }
 