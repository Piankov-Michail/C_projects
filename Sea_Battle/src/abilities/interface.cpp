#include "interface.hpp"

void Interface::Use_Ability(){}
void Interface::Print_Ability_Info(){std::cout<<"Interface info"<<std::endl;}
void Interface::Print(){std::cout<<"Interface"<<std::endl;}
void Interface::Put_Map_Data(bool* multiplier, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions){}
void Interface::Put_Coords(int x, int y){}
bool Interface::Is_Inputable(){return false;}
Interface::~Interface(){}