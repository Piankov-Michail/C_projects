#ifndef __DOUBLE_DAMAGE_ABILITY_CLASS_H__
#define __DOUBLE_DAMAGE_ABILITY_CLASS_H__

#include "interface.hpp"
#define DOUBLE_DAMAGE_INFO "You use Double Damage Ability, your shoot damage will be double!"
#define DOUBLE_DAMAGE_NAME "Double Damage ability"

class Double_Damage: public Interface
{
    public:
        Double_Damage(bool* multilplier = nullptr);
        void Use_Ability();
        void Print_Ability_Info();
        void Put_Map_Data(bool* multiplier, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions);
        void Put_Coords(int x, int y);
        void Print();
        bool Is_Inputable();
        enum ABILITY Get_Type();
    private:
        bool* multiplier;
};

#endif //__DOUBLE_DAMAGE_ABILITY_CLASS_H__