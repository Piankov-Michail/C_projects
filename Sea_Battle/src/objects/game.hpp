#ifndef __GAME_CLASS__
#define __GAME_CLASS__

#include "ship.hpp"
#include "ship_manager.hpp"
#include "map.hpp"
#include "../abilities/interface.hpp"
#include "../abilities/double_damage.hpp"
#include "../abilities/scanner.hpp"
#include "../abilities/shelling.hpp"
#include "../abilities/ability_manager.hpp"

#include "../saving/game_state.hpp"
#include "../saving/serialization.hpp"
#include "../saving/file_handler.hpp"

#define START_GAME_MSG "You start game!"
#define MAP_SIZE_SETTING "Put game map size [x y]"
#define ROUND_START "Your round number: "
//#define SHIPS_ADDITION_MSG "Input ships count then input their type in [BOAT, FRIGATE, CORVETTE, BATTLESHIP]"
//#define INVALID_SHIP_LENGTH "Ship type error!"

class Game
{
    public:
        Game();
        void Start_Game(int x, int y);
        void Load_Game();
        void Save_Game();
        void Save_State();

        void Place_Ship(int x , int y, int ort);
        void Make_Step();
        void Try();
        void Computer_Step();
        int Make_Shoot(int x, int y);
        void Use_Ability(int x, int y);
        int Get_Step();
        int Get_Try();
        bool End();
        bool Computer_Lose();

        Game_State* Get_Game_State();
    private:
        void Load_State();
        int x, y;
        int step;
        int try_number;
        Ship_manager* Computer_Ship_manager;
        Ship_manager* Player_Ship_manager;
        Ship_manager* Temp_Ship_manager;
        Map* Player_Map;
        Map* Computer_Map;
        Abilities_manager* Player_Ability_manager;
        Game_State state;
        Game_Saver game_saver;
};

#endif //__GAME_CLASS__