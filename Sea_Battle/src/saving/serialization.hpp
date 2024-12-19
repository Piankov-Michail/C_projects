#ifndef __SERIALIZATION_CLASS__
#define __SERIALIZATION_CLASS__

#include "../objects/ship.hpp"
#include "../objects/ship_manager.hpp"
#include "../objects/map.hpp"
#include "../abilities/interface.hpp"
#include "../abilities/double_damage.hpp"
#include "../abilities/scanner.hpp"
#include "../abilities/shelling.hpp"
#include "../abilities/ability_manager.hpp"

#include "json.hpp"

using json = nlohmann::json;

#include "game_state.hpp"

//Ship*
void to_json(json& j, Ship* ship);
void from_json(json &j, Ship* &ship);

//Ship_manager
void to_json(json &j, std::vector<Ship*> ship_data);
void from_json(json &j, std::vector<Ship*>& ship_data);

//Ability
void to_json(json& j, enum ABILITY ability);
void from_json(json& j, enum ABILITY& ability);

//Ability_manager
void to_json(json &j, std::vector<enum ABILITY> ability_data);
void from_json(json &j, std::vector<enum ABILITY>& ability_data);

// Map
// game_map & fog_of_war
void to_json(json &j, std::vector<std::vector<char>>game_map, std::vector<std::vector<char>>fog_of_war);
void from_json(json &j, std::vector<std::vector<char>>&game_map, std::vector<std::vector<char>>&fog_of_war);

//ship_positions
void to_json(json &j, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions);
void from_json(json &j, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>&ship_positions, std::vector<Ship*>ship_data);

//fill_area
void to_json(json &j, std::map< std::pair<int, int>, bool >fill_area);
void from_json(json &j, std::map< std::pair<int, int>, bool >&fill_area);

//Game_State
void to_json(json &j, Game_State game_state);
void from_json(json &j, Game_State& game_state);

#endif //__SERIALIZATION_CLASS__