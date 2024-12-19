#ifndef __ABILITY_MANAGER_CLASS_H__
#define __ABILITY_MANAGER_CLASS_H__

#include "interface.hpp"
#include "double_damage.hpp"
#include "scanner.hpp"
#include "shelling.hpp"
#include<vector>
#include<queue>
#include<random>
#include<algorithm>

class Abilities_manager
{
    public:
        Abilities_manager(std::vector<enum ABILITY> arr = std::vector<enum ABILITY>(), bool loading_flag = false);
        Abilities_manager(std::queue<Interface*>abilities);
        void Add_Abilities(std::vector<enum ABILITY> arr);
        void Print_Abilities();
        std::queue<Interface*>* Get_Abilities();
        std::vector<enum ABILITY> Get_Load_Buffer();
        ~Abilities_manager();
    private:
        int abilities_count;
        std::queue<Interface*>abilities;
};

#endif //__ABILITY_MANAGER_CLASS_H__