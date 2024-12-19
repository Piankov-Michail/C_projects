#ifndef __EXCEPTION_CLASS_H__
#define __EXCEPTION_CLASS_H__

#include<iostream>
#include<string>
#include "../objects/ship.hpp"

class Exceptions: public std::invalid_argument
{
    public:
        Exceptions(std::string message): invalid_argument(message){};
};

class Coordinates_Error: public Exceptions
{
    public:
        Coordinates_Error(std::string message, int x, int y): Exceptions(message), x(x), y(y) {};
        int Get_x(){return this->x;};
        int Get_y(){return this->y;};
    private:
        int x, y;

};

class Orientation_Error: public Exceptions
{
    public:
        Orientation_Error(std::string message, int x, int y, enum ORIENTATION orientation): Exceptions(message), x(x), y(y), orientation(orientation) {};
        int Get_x(){return this->x;};
        int Get_y(){return this->y;};
        std::string Get_Orientation()
        {
            if(this->orientation == HORZ)
                return "Horizontal";
            else if(this->orientation == VERT)
                return "Vertical";
            else
                return "Invalid Value!";
        }
    private:
        int x,y;
        enum ORIENTATION orientation;

};

class Ability_Error: public Exceptions
{
    public:
        Ability_Error(std::string message): Exceptions(message) {};
};

class Command_Error: public Exceptions
{
    public:
        Command_Error(std::string message): Exceptions(message) {};
};

#endif //__EXCEPTION_CLASS_H__