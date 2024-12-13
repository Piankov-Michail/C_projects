#ifndef __SCANNER_ABILITY_CLASS_H__
#define __SCANNER_ABILITY_CLASS_H__

#include "interface.hpp"
#include "../objects/map.hpp"
#define SCANNER_INFO "You use Scanner Ability, you can find enemy ships in 2x2 square!"
#define SCANNER_TRUE_FIND "Yep there is a ship"
#define SCANNER_FALSE_FIND "Nope there isn't any ship"
#define SCANNER_NAME "Scanner ability"

class Scanner: public Interface
{
    public:
        Scanner(int x = -1, int y =- 1);
        void Use_Ability();
        void Print_Ability_Info();
        void Put_Map_Data(bool* multiplier, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions);
        void Put_Coords(int x, int y);
        void Print();
        bool Is_Inputable();
        enum ABILITY Get_Type();
    private:
        int x, y;
        std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions;
};

#endif //__SCANNER_ABILITY_CLASS_H__