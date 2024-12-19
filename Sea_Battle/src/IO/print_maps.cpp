#include "print_maps.hpp"

Print_Maps::Print_Maps(Game_State* game_state)
{
    this->game_state = game_state;
}
void Print_Maps::Print_Map()
{
    if(game_state->x == 0 && game_state->x == 0)
    {
        std::cout<<NOTHING_IMG<<std::endl;
        return;
    }
    for(int i = this->game_state->y - 1; i > -1; i--)
    {
        std::cout<<std::setw(2)<<i+1<<" | ";
        for(int j = 0; j < this->game_state->x; j++)
        std::cout<<std::setw(2)<<this->game_state->player_game_map[j][i]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::setw(2)<<"      ";
    for(int i = 1; i <= this->game_state->x; i++)
    std::cout<<std::setw(2)<<"―"<<std::setw(2)<<" ";
    std::cout<<std::endl;
    std::cout<<std::setw(2)<<"     ";
    for(int i = 1; i <= this->game_state->x; i++)
    std::cout<<std::setw(2)<<i<<" ";
    std::cout<<std::endl;
}
void Print_Maps::Print_Fog_of_War()
{
    if(game_state->x == 0 && game_state->x == 0)
    {
        std::cout<<NOTHING_IMG<<std::endl;
        return;
    }
    for(int i = this->game_state->y - 1; i > -1; i--)
    {
        std::cout<<std::setw(2)<<i+1<<" | ";
        for(int j = 0; j < this->game_state->x; j++)
        std::cout<<std::setw(2)<<this->game_state->computer_fog_of_war[j][i]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::setw(2)<<"      ";
    for(int i = 1; i <= this->game_state->x; i++)
    std::cout<<std::setw(2)<<"―"<<std::setw(2)<<" ";
    std::cout<<std::endl;
    std::cout<<std::setw(2)<<"     ";
    for(int i = 1; i <= this->game_state->x; i++)
    std::cout<<std::setw(2)<<i<<" ";
    std::cout<<std::endl;
}