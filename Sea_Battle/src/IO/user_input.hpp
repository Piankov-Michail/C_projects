#ifndef __USER_INPUT__
#define __USER_INPUT__

#include "../objects/game.hpp"
#include "commands.hpp"

#include <regex>

#define POS_EXP "^[1-9]+[0-9]* [1-9]+[0-9]*$"
#define SHIP_POS_EXP "^[1-9]+[0-9]* [1-9]+[0-9]* [01]$"
#define COUNT_EXP "^[1-9]+[0-9]*$"

class User_Input
{
    public:
        User_Input();
        User_Input(std::unordered_map<enum COMMAND, std::string> command_keys);
        Command_Interface* Parse_Input(std::string input);
    private:
        std::unordered_map<enum COMMAND, std::string> command_keys;
};

User_Input::User_Input()
{
    this->command_keys = std::unordered_map<enum COMMAND, std::string>();
}

User_Input::User_Input(std::unordered_map<enum COMMAND, std::string> command_keys)
{
    this->command_keys = command_keys;
}
Command_Interface* User_Input::Parse_Input(std::string input)
{
    int x, y, cnt, o;

    std::regex pos_exp(POS_EXP);
    std::regex ship_pos_exp(SHIP_POS_EXP);
    std::regex count_exp(COUNT_EXP);

    Command_Interface* command;
    if(!input.compare(command_keys[START]))
    {
        command = new Short_Command(START);
    }
    else if(!input.compare(command_keys[EXIT]))
    {
        command = new Short_Command(EXIT);
    }
    else if(!input.compare(command_keys[SAVE]))
    {
        command = new Short_Command(SAVE);
    }
    else if(!input.compare(command_keys[LOAD]))
    {
        command = new Short_Command(LOAD);
    }
    else if(!input.compare(command_keys[ABIL]))
    {
        command = new Short_Command(ABIL);
    }
    else if(!input.compare(command_keys[PRINT_MAP]))
    {
        command = new Short_Command(PRINT_MAP);
    }
    else if(!input.compare(command_keys[PRINT_FOG]))
    {
        command = new Short_Command(PRINT_FOG);
    }
    else if(!input.compare(command_keys[SHOOT]))
    {
        command = new Short_Command(SHOOT);
    }
    else if(std::regex_match(input, pos_exp))
    {
        sscanf(input.c_str(), "%d %d", &x, &y);
        command = new Position_Command(POS, x, y);
    }
    else if(std::regex_match(input, ship_pos_exp))
    {
        sscanf(input.c_str(), "%d %d %d", &x, &y, &o);
        command = new Ship_Position_Command(SHIP_POS, x, y, o);
    }
    else if(std::regex_match(input, count_exp))
    {
        sscanf(input.c_str(), "%d", &x);
        command = new Count_Command(COUNT, x);
    }
    else
    {
        throw Command_Error("Command error [uknown or argments error]!");
    }

    return command;
}

#endif //__USER_INPUT__