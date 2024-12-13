#ifndef __GAME_STATE_STRUCT__
#define __GAME_STATE_STRUCT__

#include "../objects/ship.hpp"
#include "../objects/ship_manager.hpp"
#include "../objects/map.hpp"
#include "../abilities/interface.hpp"
#include "../abilities/double_damage.hpp"
#include "../abilities/scanner.hpp"
#include "../abilities/shelling.hpp"
#include "../abilities/ability_manager.hpp"

#include <iomanip>
#include <iostream>
#include <string>

struct Game_State
{
    int x;
    int y;
    int step;
    int try_number;

    std::vector<Ship*>computer_ship_data;
    std::vector<Ship*>player_ship_data;
    std::vector<Ship*>temp_ship_data;

    std::vector<std::vector<char>>player_game_map;
    std::vector<std::vector<char>>player_fog_of_war;

    std::vector<std::vector<char>>computer_game_map;
    std::vector<std::vector<char>>computer_fog_of_war;

    std::map<std::pair<int, int>, bool>player_fill_area;
    std::map<std::pair<int, int>, bool>computer_fill_area;

    std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>player_ship_positions;
    std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>computer_ship_positions;

    bool player_multiplier;

    int player_destroyed_ships_count;

    std::vector<enum ABILITY> player_abilities;
};

#endif //__GAME_STATE_STRUCT__