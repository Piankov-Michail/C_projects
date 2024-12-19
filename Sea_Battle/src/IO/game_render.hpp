#ifndef __GAME_RENDER__
#define __GAME_RENDER__

#include "game_print.hpp"
#include "print_maps.hpp"

class Game_Render
{
    public:
        Game_Render();
        Game_Render(Game* game);
        void Render(enum TRACKING action);
    private:
        Game* game;
        Print_Maps* printer;
};

#endif //__GAME_RENDER__