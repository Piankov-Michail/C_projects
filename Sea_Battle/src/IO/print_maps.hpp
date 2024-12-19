#ifndef __PRINT_MAPS_CLASS__
#define __PRINT_MAPS_CLASS__

#include "../objects/game.hpp"

class Print_Maps
{
    public:
        Print_Maps(Game_State* game_state);
        void Print_Map();
        void Print_Fog_of_War();
    private:
        Game_State* game_state;
};

#endif //__USER_OUTPUT_CLASS__