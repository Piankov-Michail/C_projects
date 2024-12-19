#include "game_direction.hpp"
#include "../IO/commands_load.hpp"

int main()
{
    Game* game = new Game();
    std::unordered_map<enum COMMAND, std::string>command_keys;
    command_keys = load_from_json();
    //to_json(command_keys);
    User_Input* input_handler = new User_Input(command_keys);
    Game_Print<Game_Render>* game_printer = new Game_Print<Game_Render>(game);
    Game_Direction<User_Input> game_director(game, input_handler, game_printer);
    game_director.Run();
}