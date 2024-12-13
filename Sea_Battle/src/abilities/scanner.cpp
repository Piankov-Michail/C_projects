#include "scanner.hpp"
#include <iostream>

Scanner::Scanner(int x, int y): x(x), y(y)
{
    this->ship_positions = std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>();
}
void Scanner::Use_Ability()
{
    std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>> :: iterator i;
    for(i = this->ship_positions.begin(); i != this->ship_positions.end(); i++)
    {
        if((i->second.second == HORZ && (i->first.second > y + 1 || i->first.second < y)) ||\
         (i->second.second == VERT && (i->first.first > x + 1 || i->first.first < x)))
            continue;
        for(int j = 0; j < i->second.first->Get_Length(); j++)
        {
            if((i->second.second == HORZ && (i->first.first + j == x || i->first.first + j == x + 1)) ||\
             (i->second.second == VERT && (i->first.second + j == y || i->first.second + j == y + 1)))
            {
                if(i->second.first->Get_Cell_Health(j) != DESTROYED)
                {
                    std::cout<<SCANNER_TRUE_FIND<<std::endl;
                    return;
                }
                else
                    continue;
            }
        }
    }
    std::cout<<SCANNER_FALSE_FIND<<std::endl;
    return;
}
void Scanner::Print_Ability_Info()
{
    std::cout<<SCANNER_INFO<<std::endl;
}
void Scanner::Put_Coords(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Scanner::Put_Map_Data(bool* multiplier, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions)
{
    this->ship_positions = ship_positions;
}
enum ABILITY Scanner::Get_Type()
{
    return SCANNER;
}
void Scanner::Print(){std::cout<<SCANNER_NAME<<std::endl;}
bool Scanner::Is_Inputable(){return true;}
inline int x, y;
inline std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions;
inline bool inputable;