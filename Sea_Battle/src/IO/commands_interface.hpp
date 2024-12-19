#ifndef __COMMAND_INTERFACE_CLASS__
#define __COMMAND_INTERFACE_CLASS__

#include "enum_command.hpp"

struct Commands_Data
{
    int x = -1;
    int y = -1;
    int orientation = -1;
};

class Command_Interface
{
    public:
        virtual enum COMMAND Get_Type() = 0;
        virtual Commands_Data Get_Data() = 0;
        virtual ~Command_Interface() = 0;
};

#endif //__COMMAND_INTERFACE_CLASS__