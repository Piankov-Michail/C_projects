#include "commands.hpp"

Short_Command::Short_Command(enum COMMAND command_type)
{
    this->command_type = command_type;
}
enum COMMAND Short_Command::Get_Type()
{
    return this->command_type;
}
Commands_Data Short_Command::Get_Data(){return {-1,-1,-1};}

Position_Command::Position_Command(enum COMMAND command_type, int x, int y)
{
    this->command_type = command_type;
    this->data = {x, y, -1};
}
enum COMMAND Position_Command::Get_Type()
{
    return this->command_type;
}
Commands_Data Position_Command::Get_Data()
{
    return this->data;
}

Ship_Position_Command::Ship_Position_Command(enum COMMAND command_type, int x, int y, int o)
{
    this->command_type = command_type;
    this->data = {x, y, o};
}
enum COMMAND Ship_Position_Command::Get_Type()
{
    return this->command_type;
}
Commands_Data Ship_Position_Command::Get_Data()
{
    return this->data;
}

Count_Command::Count_Command(enum COMMAND command_type, int x)
{
    this->command_type = command_type;
    this->data = {x, -1, -1};
}
enum COMMAND Count_Command::Get_Type()
{
    return this->command_type;
}
Commands_Data Count_Command::Get_Data()
{
    return this->data;
}