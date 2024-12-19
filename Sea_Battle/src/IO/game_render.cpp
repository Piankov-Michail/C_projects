#include "game_render.hpp"

Game_Render::Game_Render()
{
    this->game = nullptr;
}
Game_Render::Game_Render(Game* game)
{
    this->game = game;
}
void Game_Render::Render(enum TRACKING action)
{
    this->printer = new Print_Maps(game->Get_Game_State());
    if(action == PRINT_MAP_ACTION)
        printer->Print_Map();
    else if(action == PRINT_FOG_ACTION)
        printer->Print_Fog_of_War();
}
inline Game* game;
inline Print_Maps* printer;