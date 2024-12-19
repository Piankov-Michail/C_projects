#include "serialization.hpp"

//Ship*
void to_json(json& j, Ship* ship)
{
    j["length"] = static_cast<int>(ship->Get_Length());
    j["cells"] = json::array();

    for (const auto &c : ship->Get_Cells())
    {
        json cell_json;
        cell_json["segment"] = static_cast<int>(c.segment);
        cell_json["user_action"] = c.user_action;
        j["cells"].push_back(cell_json);
    }
}

void from_json(json &j, Ship* &ship)
{
    enum LENGTH length = static_cast<LENGTH>(j.at("length").get<int>());
    std::vector<cell>cells;
    for (auto &cell_json : j.at("cells"))
    {
        cell new_cell;
        new_cell.segment = static_cast<SEGMENT>(cell_json.at("segment").get<int>());
        new_cell.user_action = cell_json.at("user_action").get<bool>();
        cells.push_back(new_cell);
    }
    ship = new Ship(length, cells);
}

//Ship_manager
void to_json(json &j, std::vector<Ship*> ship_data)
{
    j["ship_data"] = json::array();

    for (Ship *ship : ship_data)
    {
        json ship_json;
        to_json(ship_json, ship);
        j["ship_data"].push_back(ship_json);
    }
}

void from_json(json &j, std::vector<Ship*>& ship_data)
{
    ship_data.clear();

    for (auto &ship_json : j.at("ship_data"))
    {
        Ship* ship = NULL;
        from_json(ship_json, ship);
        ship_data.push_back(ship);
    }
}

//Ability
void to_json(json& j, enum ABILITY ability)
{
    j["ability"] = static_cast<int>(ability);
}

void from_json(json& j, enum ABILITY& ability)
{
    ability = static_cast<enum ABILITY>(j.at("ability").get<int>());
}

//Ability_manager
void to_json(json &j, std::vector<enum ABILITY> ability_data)
{
    j["ability_data"] = json::array();

    for(auto i: ability_data)
    {
        json ability_json;
        to_json(ability_json, i);
        j["ability_data"].push_back(ability_json);
    }
}

void from_json(json &j, std::vector<enum ABILITY>& ability_data)
{
    ability_data.clear();

    for(auto &ability_json: j.at("ability_data"))
    {
        enum ABILITY ability;
        from_json(ability_json, ability);
        ability_data.push_back(ability);
    }
}

// Map
// game_map & fog_of_war
void to_json(json &j, std::vector<std::vector<char>>game_map, std::vector<std::vector<char>>fog_of_war)
{
    j["game_map"] = json::array();
    for(auto i: game_map)
    {
        json char_vec = json::array();
        for(auto j: i)
        {
            char_vec.push_back(j);
        }
        j["game_map"].push_back(char_vec);
    }

    j["fog_of_war"] = json::array();
    for(auto i: fog_of_war)
    {
        json char_vec = json::array();
        for(auto j: i)
        {
            char_vec.push_back(j);
        }
        j["fog_of_war"].push_back(char_vec);
    }
}

void from_json(json &j, std::vector<std::vector<char>>&game_map, std::vector<std::vector<char>>&fog_of_war)
{
    for(auto i: game_map)
        i.clear();
    game_map.clear();
    for(auto i: fog_of_war)
        i.clear();
    fog_of_war.clear();

    for(std::vector<char> i: j.at("game_map"))
    {
        std::vector<char>string;
        for(char j: i)
            string.push_back(j);
        game_map.push_back(string);
    }

    for(std::vector<char> i: j.at("fog_of_war"))
    {
        std::vector<char>string;
        for(char j: i)
            string.push_back(j);
        fog_of_war.push_back(string);
    }
}

//ship_positions
void to_json(json &j, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions)
{

    j["ship_positions"] = json::array();
    std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>> :: iterator i;
    for(i = ship_positions.begin(); i != ship_positions.end(); i++)
    {
        json ship_position = {
            {"x", i->first.first},
            {"y", i->first.second},
            {"orientation", static_cast<int>(i->second.second)}
        };
        j["ship_positions"].push_back(ship_position);
    }
}

void from_json(json &j, std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>&ship_positions, std::vector<Ship*>ship_data)
{
    ship_positions.clear();
    int x, y;
    int k = 0;
    enum ORIENTATION orientation;
    for(json i: j.at("ship_positions"))
    {
        i.at("x").get_to<int>(x);
        i.at("y").get_to<int>(y);
        orientation = static_cast<enum ORIENTATION>(i.at("orientation"));
        ship_positions.push_back({std::make_pair(x, y), std::make_pair(ship_data[k], orientation)});
        k++;
    }
}

//fill_area
void to_json(json &j, std::map< std::pair<int, int>, bool >fill_area)
{
    j["fill_area"] = json::array();
    std::map< std::pair<int, int>, bool > :: iterator i;
    for(i = fill_area.begin(); i != fill_area.end(); i++)
    {
        json str = {
            {"x", i->first.first},
            {"y", i->first.second},
            {"using", i->second}
        };
        j["fill_area"].push_back(str);
    }
}

void from_json(json &j, std::map< std::pair<int, int>, bool >&fill_area)
{
    bool usable;
    fill_area.clear();
    for(json str: j.at("fill_area"))
        fill_area.insert({{str.at("x"), str.at("y")}, static_cast<bool>(str.at("using"))});
}

//Game_State
void to_json(json &j, Game_State game_state)
{
    json computer_ship_data_json;
    to_json(computer_ship_data_json, game_state.computer_ship_data);
    json player_ship_data_json;
    to_json(player_ship_data_json, game_state.player_ship_data);
    json temp_ship_data_json;
    to_json(temp_ship_data_json, game_state.temp_ship_data);

    json computer_game_map_json;
    to_json(computer_game_map_json, game_state.computer_game_map);
    json computer_fog_of_war_json;
    to_json(computer_fog_of_war_json, game_state.computer_fog_of_war);
    json player_game_map_json;
    to_json(player_game_map_json, game_state.player_game_map);
    json player_fog_of_war_json;
    to_json(player_fog_of_war_json, game_state.player_fog_of_war);

    json computer_fill_area_json;
    to_json(computer_fill_area_json, game_state.computer_fill_area);
    json player_fill_area_json;
    to_json(player_fill_area_json, game_state.player_fill_area);

    json computer_ship_positions_json;
    to_json(computer_ship_positions_json, game_state.computer_ship_positions);
    json player_ship_positions_json;
    to_json(player_ship_positions_json, game_state.player_ship_positions);

    json player_abilities_json;
    to_json(player_abilities_json, game_state.player_abilities);

    j = 
    {
        {"x", (int)game_state.x},
        {"y", (int)game_state.y},
        {"step", (int)game_state.step},
        {"try_number", (int)game_state.try_number},
        {"computer_ship_data", computer_ship_data_json},
        {"player_ship_data", player_ship_data_json},
        {"temp_ship_data", temp_ship_data_json},
        {"computer_game_map", computer_game_map_json},
        {"player_game_map", player_game_map_json},
        {"computer_fog_of_war", computer_fog_of_war_json},
        {"player_fog_of_war", player_fog_of_war_json},
        {"computer_fill_area", computer_fill_area_json},
        {"player_fill_area", player_fill_area_json},
        {"computer_ship_positions", computer_ship_positions_json},
        {"player_ship_positions", player_ship_positions_json},
        {"player_multiplier", game_state.player_multiplier},
        {"player_destroyed_ships_count", game_state.player_destroyed_ships_count},
        {"player_abilities", player_abilities_json}
    };
}

void from_json(json &j, Game_State& game_state)
{
    j.at("x").get_to<int>(game_state.x);
    j.at("y").get_to<int>(game_state.y);
    j.at("step").get_to<int>(game_state.step);
    j.at("try_number").get_to<int>(game_state.try_number);

    json computer_ship_data_json = j.at("computer_ship_data");
    from_json(computer_ship_data_json, game_state.computer_ship_data);
    json player_ship_data_json = j.at("player_ship_data");
    from_json(player_ship_data_json, game_state.player_ship_data);
    json temp_ship_data_json = j.at("temp_ship_data");
    from_json(temp_ship_data_json, game_state.temp_ship_data);

    json computer_game_map_json = j.at("computer_game_map");
    from_json(computer_game_map_json, game_state.computer_game_map);
    json computer_fog_of_war_json = j.at("computer_fog_of_war");
    from_json(computer_fog_of_war_json, game_state.computer_fog_of_war);
    json player_game_map_json = j.at("player_game_map");
    from_json(player_game_map_json, game_state.player_game_map);
    json player_fog_of_war_json = j.at("player_fog_of_war");
    from_json(player_fog_of_war_json, game_state.player_fog_of_war);

    json computer_fill_area_json = j.at("computer_fill_area");
    from_json(computer_fill_area_json, game_state.computer_fill_area);
    json player_fill_area_json = j.at("player_fill_area");
    from_json(player_fill_area_json, game_state.player_fill_area);

    json computer_ship_positions_json = j.at("computer_ship_positions");
    from_json(computer_ship_positions_json, game_state.computer_ship_positions, game_state.computer_ship_data);
    json player_ship_positions_json = j.at("player_ship_positions");
    from_json(player_ship_positions_json, game_state.player_ship_positions, game_state.player_ship_data);

    json player_abilities_json = j.at("player_abilities");
    from_json(player_abilities_json, game_state.player_abilities);
}