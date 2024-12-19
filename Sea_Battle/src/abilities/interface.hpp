#ifndef __INTERFACE_CLASS_H__
#define __INTERFACE_CLASS_H__

#include "../objects/ship.hpp"
#include<map>

enum ABILITY
{
    DOUBLE_DAMAGE = 1,
    SCANNER = 2,
    SHELLING = 3
};

class Interface
{
    public:
        virtual void Use_Ability() = 0;
        virtual void Print_Ability_Info() = 0;
        virtual void Print() = 0;
        virtual void Put_Map_Data(bool* multiplier, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions) = 0;
        virtual void Put_Coords(int x, int y) = 0;
        virtual bool Is_Inputable() = 0;
        virtual enum ABILITY Get_Type() = 0;
        virtual ~Interface();
};
#endif //__INTERFACE_CLASS_H__