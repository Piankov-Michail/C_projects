#include "game_tracking.hpp"

Game_Tracking::Game_Tracking()
{

}

Game_Tracking::Game_Tracking(Game_State game_state)
{
    this->last_game_state = game_state;
}

enum TRACKING Game_Tracking::Update(Game_State game_state)
{
    for(int i = 0; i < game_state.computer_fog_of_war.size(); i++)
    {
        for(int j = 0; j < game_state.computer_fog_of_war[i].size(); j++)
        {
            if(game_state.computer_fog_of_war[i][j] != this->last_game_state.computer_fog_of_war[i][j])
            {
                this->last_game_state = game_state;
                return PRINT_FOG_ACTION;
            }
                
        }
    }
    
    for(int i = 0; i < game_state.player_game_map.size(); i++)
    {
        for(int j = 0; j < game_state.player_game_map[i].size(); j++)
        {
            if(game_state.player_game_map[i][j] != this->last_game_state.player_game_map[i][j])
            {
                this->last_game_state = game_state;
                return PRINT_MAP_ACTION;
            }
                
        }
    }
    return NO_CHANGES;
}

