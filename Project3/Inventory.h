// CSCI 1300 Fall 2022
// Author: Davis Mann, David Camargo
// Recitation: 302, 123 – Michelle Ramsahoye, Christopher Ojukwu
// Project 3 - Inventory.h
 
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cctype>
 
using namespace std;
 
class Inventory
{
   private:
       int gold;
       int ingred;
       int cook[3];
       int weapons[5];
       int armor;
       int tres[5];
 
   public:
       Inventory();
       void setGold(int gold_);
       int getGold();
       void setIngred(int ingred_);
       int getIngred();
       void setCookAt(int cook_, int index);
       int getCookAt(int index);
       void setWeaponsAt(int weapons_, int index);
       int getWeaponsAt(int index);
       void setArmor(int armor_);
       int getArmor();
       void setTresAt(int tres_, int index);
       int getTresAt(int index);
       int checkWeapons();


       int weaponDamage();
       bool cookDamage(int index);
 
       void randRob();
       void randBreak();
 
};
