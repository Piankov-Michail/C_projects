#include "ship_manager.hpp"
#include "ship.hpp"

Ship_manager::Ship_manager(int ships_count, std::initializer_list<enum LENGTH> arr)
{
    this->ships_count = ships_count == arr.size() ? ships_count : arr.size();
    for(auto i : arr)
        this->ship_data.push_back(new Ship(i));
}
Ship_manager::Ship_manager(Ship_manager& other)
{
    std::vector<Ship*>this_ship_data;
    for(auto i: other.ship_data)
        this_ship_data.push_back(new Ship(i->Get_Length()));
    this->ship_data = this_ship_data;
    this->ships_count = other.ships_count;
}
Ship_manager::Ship_manager(std::vector<Ship*>ship_data)
{
    this->ship_data = ship_data;
    this->ships_count = ship_data.size();
}
void Ship_manager::Add_Ships(int ships_count, std::initializer_list<enum LENGTH> arr)
{
    this->ships_count += ships_count == arr.size() ? ships_count : arr.size();
    for(auto i : arr)
        this->ship_data.push_back(new Ship(i));
}
void Ship_manager::Print_Ships()
{
    for(auto i : this->ship_data)
    {
        std::cout<<i->Get_Length()<<" Segments: ";
        for(int j = 0; j < i->Get_Length(); j++)
            std::cout<<i->Get_Cell_Health(j)<<" ";
        std::cout<<std::endl;
    }
}  
std::vector<Ship*> Ship_manager::Get_Ships()
{
    return this->ship_data;
}
Ship_manager::~Ship_manager()
{
    this->ships_count = 0;
    for(auto i : ship_data)
        delete i;
    this->ship_data.clear();
    this->ship_data = std::vector<Ship*>();
    //std::cout<<"SHIP_MANAGER DELETE MADE"<<std::endl;
}
bool Ship_manager::All_Destroyed()
{
    for(auto i: ship_data)
    {
        if(!i->Is_Defeat())
            return false;
    }
    return true;
}
inline int ships_count;
inline std::vector<Ship*>ship_data;