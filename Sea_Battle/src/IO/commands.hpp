#ifndef __COMMANDS_CLASSES__
#define __COMMANDS_CLASSES__

#include "commands_interface.hpp"

class Position_Command: public Command_Interface
{
    public:
        Position_Command(enum COMMAND command_type, int x, int y);
        enum COMMAND Get_Type();
        Commands_Data Get_Data();
    private:
        enum COMMAND command_type;
        Commands_Data data;
};

class Ship_Position_Command: public Command_Interface
{
    public:
        Ship_Position_Command(enum COMMAND command_type, int x, int y, int o);
        enum COMMAND Get_Type();
        Commands_Data Get_Data();
    private:
        enum COMMAND command_type;
        Commands_Data data;
};

class Count_Command: public Command_Interface
{
    public:
        Count_Command(enum COMMAND command_type, int x);
        enum COMMAND Get_Type();
        Commands_Data Get_Data();
    private:
        enum COMMAND command_type;
        Commands_Data data;
};

class Short_Command: public Command_Interface
{
    public:
        Short_Command(enum COMMAND command_type);
        enum COMMAND Get_Type();
        Commands_Data Get_Data();
    private:
        enum COMMAND command_type;
};

#endif //__COMMANDS_CLASSES__