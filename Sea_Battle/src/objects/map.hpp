#ifndef __MAP_CLASS_H__
#define __MAP_CLASS_H__

#include "ship.hpp"
#include "ship_manager.hpp"
#include "../abilities/interface.hpp"
#include "../exceptions/exceptions.hpp"
#include "../abilities/ability_manager.hpp"

enum SEGMENTS_DISPLAY
{
    ALL_HEALTH = 2,
    HALF_HEALTH = 1,
    DESTROYED_SEG = 40
};

enum MAP_DISPLAY
{
    NOTHING = 46,
    FOG = 126
};

#include<iomanip>
#include<vector>
#include<iostream>
#include<queue>

#define NOTHING_IMG "Nothing to image!"
#define SHIP_COORD_ERROR "Ship coordinates error!"
#define SHOOT_ERROR "Shoot error!"
#define SHIP_ORIENTATION_ERROR "Ship orientation error!"
#define SHIP_PLACE_ERROR "Ship has coordinates or orientation error!"
#define TRY "Make another try!"
#define PLACING_SHIPS_MESSAGE "Start your ship replacement on map, ENTER: [x_coord y_coord orientation(0-HORIZONTAL / 1-VERTICAL)]\nto paste your left_down end of piece of ship!"
#define ABILITY_ERROR "You haven't any abilityes!"
#define ABILITY_COORD_ERROR "Wrong Coordinates for ability!"
#define SCANNER_INPUT "Put left down corner of square 2x2 coords like [x_coord y_coord]!"

struct Map_Data
{
    std::vector<std::vector<char>>game_map;
    std::vector<std::vector<char>>fog_of_war;
    std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions;
    std::map< std::pair<int, int>, bool >fill_area;
    bool multiplier;
    int destroyed_ships_count;
};

class Map
{
    public:
        Map(int x, int y);
        Map(const Map& other);
        Map& operator = (const Map& other);
        Map(Map&& move)noexcept;
        Map& operator = (Map&& move);
        void Print_Map();
        void Print_Fog_Of_War();
        int Make_Shoot(int x_coord, int y_coord);
        void Add_Ships(std::vector<Ship*> ship_data);
        void Add_Abilities(std::queue<Interface*>*abilities);
        void Place_Ship(int x, int y, int ort);
        void Auto_Place_Ships();
        void Use_Ability(int x, int y);
        void Set_Map_Data(Map_Data map_data);
        Map_Data Get_Map_Data();
        ~Map();
    private:
        void Give_New_Ability();
        bool Valid_Coords(int x, int y, enum LENGTH length, enum ORIENTATION orinetation);
        void Fill_Area(int x, int y, enum LENGTH length, enum ORIENTATION orinetation);
        void Display_Ships();
        void Clear_All();
        std::vector<std::vector<char>>game_map;
        std::vector<std::vector<char>>fog_of_war;
        std::vector<Ship*>ship_data;
        std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions;
        std::map< std::pair<int, int>, bool >fill_area;
        int x,y;
        bool multiplier;
        std::queue<Interface*>*abilities;
        int destroyed_ships_count;
};

#endif //__MAP_CLASS_H__