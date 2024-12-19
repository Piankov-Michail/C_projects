#include "ability_manager.hpp"

Abilities_manager::Abilities_manager(std::vector<enum ABILITY> arr, bool loading_flag)
{
    if(arr.size() == 0 && !loading_flag)
    {
        std::mt19937 rng(std::random_device{}());
        arr  = {DOUBLE_DAMAGE, SCANNER, SHELLING};
        std::shuffle(arr.begin(), arr.end(), rng);
    }
    this->abilities_count = arr.size();
    for(auto i : arr)
    {
        Interface* obj;
        if(i == DOUBLE_DAMAGE)
            obj = new Double_Damage();
        else if(i == SCANNER)
            obj = new Scanner();
        else if(i == SHELLING)
            obj = new Shelling();
        this->abilities.push(obj);
    }
}
void Abilities_manager::Add_Abilities(std::vector<enum ABILITY> arr)
{
    this->abilities_count += arr.size();
    for(auto i : arr)
    {
        Interface* obj;
        if(i == DOUBLE_DAMAGE)
            obj = new Double_Damage();
        else if(i == SCANNER)
            obj = new Scanner();
        else if(i == SHELLING)
            obj = new Shelling();
        this->abilities.push(obj);
    }
}
void Abilities_manager::Print_Abilities()
{
    std::queue<Interface*>abilities_copy(abilities);
    while(!abilities_copy.empty())
    {
        abilities_copy.front()->Print();
        abilities_copy.pop();
    }
}
std::queue<Interface*>* Abilities_manager::Get_Abilities()
{
    return &(this->abilities);
}
std::vector<enum ABILITY> Abilities_manager::Get_Load_Buffer()
{
    std::vector<enum ABILITY>ability_buffer;
    std::queue<Interface*>abilities_copy(abilities);
    while(!abilities_copy.empty())
    {
        enum ABILITY ability = abilities_copy.front()->Get_Type();
        ability_buffer.push_back(ability);
        abilities_copy.pop();
    }
    return ability_buffer;
}
Abilities_manager::~Abilities_manager()
{
    this->abilities_count = 0;
    this->abilities = std::queue<Interface*>();
    //std::cout<<"ABILITIES_MANAGER DELETE MADE"<<std::endl;
}