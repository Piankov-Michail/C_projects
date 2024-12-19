#include "ship.hpp"

Ship::Ship(enum LENGTH length) : length(EMPTY)
{
    this->length = length;
    this->cells = std::vector<cell>(length, cell{FULL, 0});
}
Ship::Ship(const Ship& other)
{
    this->cells = other.cells;
    this->length = other.length;
}
Ship::Ship(enum LENGTH length, std::vector<cell>cells)
{
    this->length = length;
    this->cells = cells;
}
bool Ship::Is_Defeat()
{
    for(int i = 0; i < this->length; i++)
    {
        if(this->cells[i].segment != DESTROYED)
            return 0;
    }
    return 1;
}
void Ship::Hit(int index, bool multiplier)
{
    if(this->cells[index].segment == DESTROYED)
    {
        std::cout<<ENOUGH_DAMAGE<<std::endl;
        return;
    }
    if(!multiplier)
    {
        if(this->cells[index].segment == FULL)
            this->cells[index].segment = HALF;
        else if(this->cells[index].segment == HALF)
            this->cells[index].segment = DESTROYED;
        std::cout<<SHIP_HIT<<std::endl;
    }
    else if(multiplier)
    {
        if(this->cells[index].segment == FULL || this->cells[index].segment == HALF)
            this->cells[index].segment = DESTROYED;
        std::cout<<SHIP_HIT<<std::endl;
    }
    if(Is_Defeat())
        std::cout<<SHIP_DEFEAT<<std::endl;
}
void Ship::Ability_Hit(int index, bool multiplier)
{
    this->Ship::Hit(index, multiplier);
}
void Ship::User_Hit(int index, bool multiplier)
{
    if(!this->cells[index].user_action)
        this->cells[index].user_action = 1;
    this->Ship::Hit(index, multiplier);
}
enum LENGTH Ship::Get_Length()
{
    return this->length;
}
enum SEGMENT Ship::Get_Cell_Health(int index)
{
    if(index < this->cells.size())
        return this->cells[index].segment;
    else
    {
        std::cout<<"Index error!"<<std::endl;
        return ERROR;
    }
}
bool Ship::Get_Cell_Action(int index)
{
    if(index < this->cells.size())
        return this->cells[index].user_action;
    else
    {
        std::cout<<"Index error!"<<std::endl;
        return ERROR;
    }
}
Ship::~Ship()
{
    this->length = EMPTY;
    this->cells.clear();
    this->cells = std::vector<cell>();
    //std::cout<<"SHIP DELETE MADE"<<std::endl;
}
std::vector<cell> Ship::Get_Cells()
{
    return this->cells;
}
void Ship::Set_Cells(std::vector<cell>cells)
{
    this->cells = cells;
}
void Ship::Set_Length(enum LENGTH length)
{
    this->length = length;
}
inline enum LENGTH length;
inline std::vector<cell>cells;