#include "commands_interface.hpp"

enum COMMAND Command_Interface::Get_Type()
{
    return EMPTY_COMMAND;
}

Commands_Data Command_Interface::Get_Data()
{
    Commands_Data data = {-1, -1, -1};
    return data;
}

Command_Interface::~Command_Interface(){}