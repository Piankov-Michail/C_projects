#ifndef __SHIP_MANAGER_CLASS_H__
#define __SHIP_MANAGER_CLASS_H__

#include "ship.hpp"

#include<map>
#include<iostream>
#include<vector>

class Ship_manager
{
    public:
        Ship_manager(int ships_count, std::initializer_list<enum LENGTH> arr);
        Ship_manager(Ship_manager& other);
        Ship_manager(std::vector<Ship*>ship_data);
        void Add_Ships(int ships_count, std::initializer_list<enum LENGTH> arr);
        void Print_Ships();
        std::vector<Ship*> Get_Ships();
        ~Ship_manager();
        bool All_Destroyed();
    private:
        int ships_count;
        std::vector<Ship*>ship_data;
};

#endif //__SHIP_MANAGER_CLASS_H__