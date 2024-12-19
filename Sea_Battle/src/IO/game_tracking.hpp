#ifndef __GAME_TRACKING_CLASS__
#define __GAME_TRACKING_CLASS__

#include "../objects/game.hpp"
#include "enum_tracking.hpp"

class Game_Tracking
{
    public:
        Game_Tracking();
        Game_Tracking(Game_State game_state);
        enum TRACKING Update(Game_State game_state);
    private:
        Game_State last_game_state;
};

#endif //__GAME_TRACKING_CLASS__