#include "game_print.hpp"

template<typename Render>
Game_Print<Render>::Game_Print()
{
    this->game = nullptr;
    this->render = nullptr;
}
template<typename Render>
Game_Print<Render>::Game_Print(Game* game)
{
    this->game = game;
    this->render = new Render(game);
}
template<typename Render>
void Game_Print<Render>::Use(enum TRACKING action)
{
    this->render->Render(action);
}