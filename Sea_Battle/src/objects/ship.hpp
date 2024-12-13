#ifndef __SHIP_CLASS_H__
#define __SHIP_CLASS_H__

#include<iostream>
#include<vector>

#define SHIP_HIT "Hit!"
#define SHIP_DEFEAT "Destroyed!"
#define MISS "Miss!"
#define ENOUGH_DAMAGE "You have already hit that!"

enum ORIENTATION
{
    HORZ = 0,
    VERT = 1,
    WRONG = -1
};

enum SEGMENT
{
    ERROR = -1,
    DESTROYED = 0,
    HALF = 1,
    FULL = 2
};

struct cell
{
    enum SEGMENT segment;
    bool user_action;
};

enum LENGTH
{
    EMPTY = 0,
    BOAT = 1,
    CORVETTE = 2,
    FRIGATE = 3,
    BATTLE_SHIP = 4
};

class Ship
{
    public:
        Ship(enum LENGTH length);
        Ship(const Ship& other);
        Ship(enum LENGTH length, std::vector<cell>cells);
        bool Is_Defeat();
        void Ability_Hit(int index, bool multiplier);
        void User_Hit(int index, bool multiplier);
        enum LENGTH Get_Length();
        enum SEGMENT Get_Cell_Health(int index);
        bool Get_Cell_Action(int index);
        std::vector<cell> Get_Cells();
        void Set_Cells(std::vector<cell>cells);
        void Set_Length(enum LENGTH length);
        ~Ship();
    private:
        void Hit(int index, bool multiplier);
        enum LENGTH length;
        std::vector<cell>cells;
};

#endif //__SHIP_CLASS_H__