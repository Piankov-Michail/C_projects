#include "double_damage.hpp"
#include <iostream>

Double_Damage::Double_Damage(bool* multiplier): multiplier(multiplier){}
void Double_Damage::Print_Ability_Info()
{
    std::cout<<DOUBLE_DAMAGE_INFO<<std::endl;
}
void Double_Damage::Put_Map_Data(bool* multiplier, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions)
{
    this->multiplier = multiplier;
}
void Double_Damage::Put_Coords(int x, int y){}
void Double_Damage::Use_Ability()
{
    if(multiplier != nullptr)
        *multiplier = true;
}
enum ABILITY Double_Damage::Get_Type()
{
    return DOUBLE_DAMAGE;
}
void Double_Damage::Print(){std::cout<<DOUBLE_DAMAGE_NAME<<std::endl;}
bool Double_Damage::Is_Inputable(){return false;}
inline bool* multiplier;