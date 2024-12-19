#ifndef __GAME_PRINT__
#define __GAME_PRINT__

#include "../objects/game.hpp"
#include "enum_tracking.hpp"

template<typename Render>
class Game_Print
{
    public:
        Game_Print();
        Game_Print(Game* game);
        void Use(enum TRACKING action);
    private:
        Game* game;
        Render* render;
};

#endif //__GAME_PRINT__