#include "shelling.hpp"

Shelling::Shelling(std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions): ship_positions(ship_positions){}
void Shelling::Use_Ability()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0,10000);
    int random_ship_iterator_number = dist(rng) % this->ship_positions.size();
    
    std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>> :: iterator i = ship_positions.begin();

    while(i != ship_positions.end() && random_ship_iterator_number > 0)
    {
        random_ship_iterator_number--;
        i++;
    }
    if(i->second.first->Is_Defeat())
    {
        while(i != ship_positions.end() && i->second.first->Is_Defeat())
            i++;
        if((i != ship_positions.end() && i->second.first->Is_Defeat()) || (i == ship_positions.end()))
            i = ship_positions.begin();
        while(i != ship_positions.end() && i->second.first->Is_Defeat())
            i++;
        if(i == ship_positions.end() || i->second.first->Is_Defeat())
        {
            std::cout<<SHELLING_NOTHING_TO_HIT<<std::endl;
            return;
        }
    }
    int random_segment_number = dist(rd) % (i->second.first->Get_Length());

    if(i->second.first->Get_Cell_Health(random_segment_number) == DESTROYED)
    {
        while (random_segment_number < i->second.first->Get_Length() && i->second.first->Get_Cell_Health(random_segment_number) == DESTROYED)
            random_segment_number++;
        if(random_segment_number == i->second.first->Get_Length())
            random_segment_number = 0;
        while (random_segment_number < i->second.first->Get_Length() && i->second.first->Get_Cell_Health(random_segment_number) == DESTROYED)
            random_segment_number++;
    }
    i->second.first->Ability_Hit(random_segment_number, *multiplier);
}
void Shelling::Print_Ability_Info()
{
    std::cout<<SHELLING_INFO<<std::endl;
}
void Shelling::Put_Map_Data(bool* multiplier, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions)
{
    this->ship_positions = ship_positions;
    this->multiplier = multiplier;
}
enum ABILITY Shelling::Get_Type()
{
    return SHELLING;
}
void Shelling::Put_Coords(int x, int y){}
void Shelling::Print(){std::cout<<SHELLING_NAME<<std::endl;}
bool Shelling::Is_Inputable(){return false;}
inline std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>> ship_positions;
inline bool* multiplier;