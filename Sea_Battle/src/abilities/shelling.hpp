#ifndef __SHELLING_CLASS_H__
#define __SHELLING_CLASS_H__
#include "../abilities/interface.hpp"
#include "../objects/map.hpp"
#include <random>

#define SHELLING_INFO "You use Shelling ability, it makes shoot in random ship"
#define SHELLING_NOTHING_TO_HIT "All Ships were destroyed!"
#define SHELLING_NAME "Shelling ability"

class Shelling: public Interface
{
    public:
        Shelling(std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions  = std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>());
        void Use_Ability();
        void Print_Ability_Info();
        void Put_Map_Data(bool* multiplier, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions);
        void Put_Coords(int x, int y);
        void Print();
        bool Is_Inputable();
        enum ABILITY Get_Type();
    private:
        std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions;
        bool* multiplier;
};
#endif //__SHELLING_CLASS_H__