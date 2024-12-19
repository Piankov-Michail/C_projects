#include "map.hpp"
#include<algorithm>

Map::Map(int x, int y) : x(0), y(0)
{
    this->abilities = nullptr;
    this->x = x;
    this->y = y;
    for(int i = 0; i < x; i++)
    {
        std::vector<char>str(y, '~');
        this->game_map.push_back(str);
        this->fog_of_war.push_back(str);
    }
    this->multiplier = false;
    this->destroyed_ships_count = 0;
}
Map::Map(const Map& other) : x(other.x), y(other.y), multiplier(other.multiplier), destroyed_ships_count(destroyed_ships_count)
{
    this->ship_data = std::vector<Ship*>();
    for(auto i : other.ship_data)
        this->ship_data.push_back(i);
    this->abilities = other.abilities;
    this->game_map = std::vector<std::vector<char>>(x);
    for(int i = 0; i < x; i++)
    {
        for(auto j : other.game_map[i])
            this->game_map[i].push_back(j);
    }
    this->fog_of_war = std::vector<std::vector<char>>(x);
    for(int i = 0; i < x; i++)
    {
        for(auto j : other.fog_of_war[i])
            this->fog_of_war[i].push_back(j);
    }
    this->ship_positions = std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>();
    for(auto i : other.ship_positions)
        this->ship_positions.push_back(i);
    this->fill_area = std::map< std::pair<int, int>, bool >();
    for(auto i : other.fill_area)
        this->fill_area.insert(i);
    //std::cout<<"COPY MADE"<<std::endl;
}
Map& Map::operator = (const Map& other)
{
    if(this == &other)
        return *this;
    Map temp(other);
    std::swap(this->x, temp.x);
    std::swap(this->y, temp.y); 
    std::swap(this->ship_data, temp.ship_data);
    std::swap(this->abilities, temp.abilities);
    std::swap(this->game_map, temp.game_map);
    std::swap(this->fog_of_war, temp.fog_of_war);
    std::swap(this->ship_positions, temp.ship_positions);
    std::swap(this->fill_area, temp.fill_area);
    std::swap(this->multiplier, temp.multiplier);
    std::swap(this->destroyed_ships_count, temp.destroyed_ships_count);
    return *this;
}
Map::Map(Map&& move)noexcept : x(move.x), y(move.y)
{
    //std::cout<<"MOVE MADE"<<std::endl;
    this->ship_data = move.ship_data;
    this->game_map = move.game_map;
    this->fog_of_war = move.fog_of_war;
    this->fill_area = move.fill_area;
    this->ship_positions = move.ship_positions;
    this->multiplier = move.multiplier;
    this->abilities = move.abilities;
    this->destroyed_ships_count = move.destroyed_ships_count;
    move.ship_data.clear();
    move.ship_data = std::vector<Ship*>();
    move.abilities = nullptr;
    move.game_map.clear();
    move.game_map = std::vector<std::vector<char>>();
    move.fog_of_war.clear();
    move.fog_of_war = std::vector<std::vector<char>>();
    move.ship_positions.clear();
    move.ship_positions = std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>();
    move.fill_area.clear();
    move.fill_area = std::map< std::pair<int, int>, bool >();
    move.x = 0;
    move.y = 0;
    move.multiplier = 1;
    move.destroyed_ships_count = 0;
}
Map& Map::operator = (Map&& move)
{
    if(this == &move)
        return *this;
    this->ship_data.clear();
    this->ship_data = std::vector<Ship*>();
    this->abilities = nullptr;
    this->game_map.clear();
    this->game_map = std::vector<std::vector<char>>();
    this->fog_of_war.clear();
    this->fog_of_war = std::vector<std::vector<char>>();
    this->ship_positions.clear();
    this->ship_positions = std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>();
    this->fill_area.clear();
    this->fill_area = std::map< std::pair<int, int>, bool >();
    this->x = 0;
    this->y = 0;
    this->multiplier = 1;
    this->destroyed_ships_count = 0;
    return *this;
}
void Map::Print_Map()
{
    if(this->x == 0 && this->y == 0)
    {
        std::cout<<NOTHING_IMG<<std::endl;
        return;
    }
    this->Display_Ships();
    for(int i = this->y - 1; i > -1; i--)
    {
        std::cout<<std::setw(2)<<i+1<<" | ";
        for(int j = 0; j < this->x; j++)
        std::cout<<std::setw(2)<<this->game_map[j][i]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::setw(2)<<"      ";
    for(int i = 1; i <= this->x; i++)
    std::cout<<std::setw(2)<<"―"<<std::setw(2)<<" ";
    std::cout<<std::endl;
    std::cout<<std::setw(2)<<"     ";
    for(int i = 1; i <= this->x; i++)
    std::cout<<std::setw(2)<<i<<" ";
    std::cout<<std::endl;
}
void Map::Print_Fog_Of_War()
{
    if(this->x == 0 && this->y == 0)
    {
        std::cout<<NOTHING_IMG<<std::endl;
        return;
    }
    this->Display_Ships();
    for(int i = this->y - 1; i > -1; i--)
    {
        std::cout<<std::setw(2)<<i+1<<" | ";
        for(int j = 0; j < this->x; j++)
        std::cout<<std::setw(2)<<this->fog_of_war[j][i]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::setw(2)<<"     ";
    for(int i = 1; i <= this->x; i++)
    std::cout<<std::setw(2)<<"-"<<" ";
    std::cout<<std::endl;
    std::cout<<std::setw(2)<<"     ";
    for(int i = 1; i <= this->x; i++)
    std::cout<<std::setw(2)<<i<<" ";
    std::cout<<std::endl;
    std::cout<<std::endl;
}
int Map::Make_Shoot(int x_coord, int y_coord)
{
    x_coord -= 1;
    y_coord -= 1;
    if(x_coord < 0 || x_coord >= this->x || y_coord < 0 || y_coord >= this->y)
    {
        throw(Coordinates_Error(SHOOT_ERROR, x_coord, y_coord));
    }
    std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>> :: iterator i;
    for(i = this->ship_positions.begin(); i != this->ship_positions.end(); i++)
    {
        if((i->second.second == HORZ && i->first.second != y_coord) || (i->second.second == VERT && i->first.first != x_coord))
            continue;
        for(int j = 0; j < i->second.first->Get_Length(); j++)
        {
            if((i->second.second == HORZ && i->first.first + j == x_coord) || (i->second.second == VERT && i->first.second + j == y_coord))
            {   
                bool flag = true;
                if(i->second.first->Is_Defeat())
                    flag = false;
                i->second.first->User_Hit(j, multiplier);
                this->multiplier = false;
                if(i->second.first->Is_Defeat() && flag)
                    this->Give_New_Ability();
                this->Display_Ships();
                return 1;
            }
        }
    }
    std::cout<<MISS<<std::endl;
    this->multiplier = false;
    this->fog_of_war[x_coord][y_coord] = '.';
    this->Display_Ships();
    return 0;
}
void Map::Add_Ships(std::vector<Ship*> ship_data)
{
    for(auto i: ship_data)
        this->ship_data.push_back(i);
}
void Map::Add_Abilities(std::queue<Interface*>*abilities)
{
    this->abilities = abilities;
}
void Map::Use_Ability(int x, int y)
{
    if(this->abilities == nullptr || this->abilities->empty() ||  this->abilities->size() == 0)
    {
        throw(Ability_Error(ABILITY_ERROR));
    }
    Interface* current_ability = this->abilities->front();
    if(current_ability->Get_Type() != SCANNER)
        current_ability->Print_Ability_Info();
    if(current_ability->Is_Inputable())
    {
        x --; y --;
        if(x < 0 || x > this->x || y < 0 || y > this->y)
        {
            throw(Coordinates_Error(ABILITY_COORD_ERROR, x, y));
        }
        current_ability->Put_Coords(x, y);
    }
    current_ability->Put_Map_Data(&multiplier, this->ship_positions);
    current_ability->Use_Ability();
    this->abilities->pop();
    int new_destroyed_ships_count = 0;
    for(auto i: ship_data)
    {
        if(i->Is_Defeat())
            new_destroyed_ships_count++;
    }
    if(this->destroyed_ships_count != new_destroyed_ships_count)
    {
        this->Give_New_Ability();
        this->destroyed_ships_count = new_destroyed_ships_count;
    }
    this->Display_Ships();
}
Map::~Map()
{
    //std::cout<<"MAP DELETE MADE"<<std::endl;
    this->ship_data.clear();
    this->ship_data = std::vector<Ship*>();
    this->abilities = nullptr;
    this->game_map.clear();
    this->game_map = std::vector<std::vector<char>>();
    this->fog_of_war.clear();
    this->fog_of_war = std::vector<std::vector<char>>();
    this->ship_positions.clear();
    this->ship_positions = std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>();
    this->fill_area.clear();
    this->fill_area = std::map< std::pair<int, int>, bool >();
}
void Map::Place_Ship(int x, int y, int ort)
{
    int i = this->ship_positions.size();
    if(x <= 0 || x > this->x || y <= 0 || y > this->y)
    {
        throw(Coordinates_Error(SHIP_COORD_ERROR, x, y));
    }
    else
    {
        if(ort == 0)
        {
            if(Valid_Coords(x, y, ship_data[i]->Get_Length(), HORZ))
            {
                this->ship_positions.push_back({std::make_pair(x-1, y-1), std::make_pair(ship_data[i], HORZ)});
                Fill_Area(x, y, ship_data[i]->Get_Length(), HORZ);
                i++;
            }
            else
            {
                throw(Orientation_Error(SHIP_PLACE_ERROR, x, y, HORZ));
            }
        }  
        else if(ort == 1)
        {
            if(Valid_Coords(x, y, ship_data[i]->Get_Length(), VERT))
            {
                this->ship_positions.push_back({std::make_pair(x-1, y-1), std::make_pair(ship_data[i], VERT)});
                Fill_Area(x, y, ship_data[i]->Get_Length(), VERT);
                i++;
            }
            else
            {
                throw(Orientation_Error(SHIP_PLACE_ERROR, x, y, VERT));
            }
        }
        else
        {
            throw(Orientation_Error(SHIP_ORIENTATION_ERROR, x, y, WRONG));
        }
    }
    this->Display_Ships();
}
void Map::Auto_Place_Ships()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1,1000);
    int x, y;
    int ort;
    while(true)
    {
        int i = 0;
        int cnt = 0;
        while(i != this->ship_data.size())
        {
            x = (dist(rng) % this->x) + 1;
            y = (dist(rng) % this->y) + 1;
            ort = dist(rng) % 2;
            if(ort == 0)
            {
                if(Valid_Coords(x, y, ship_data[i]->Get_Length(), HORZ))
                {
                    this->ship_positions.push_back({std::make_pair(x-1, y-1), std::make_pair(ship_data[i], HORZ)});
                    Fill_Area(x, y, ship_data[i]->Get_Length(), HORZ);
                    i++;
                }
            }  
            else if(ort == 1)
            {
                if(Valid_Coords(x, y, ship_data[i]->Get_Length(), VERT))
                {
                    this->ship_positions.push_back({std::make_pair(x-1, y-1), std::make_pair(ship_data[i], VERT)});
                    Fill_Area(x, y, ship_data[i]->Get_Length(), VERT);
                    i++;
                }
            }
            cnt++;
            if(cnt > 100)
            {
                this->ship_positions.clear();
                this->fill_area.clear();
                break;
            }
        }
        if(i == ship_data.size())
            return;
    }
}
void Map::Give_New_Ability()
{
    try{
    if(this->abilities == nullptr)
    {
        throw(Ability_Error(ABILITY_ERROR));
    }
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0,10000);
    enum ABILITY ability = static_cast<enum ABILITY>(dist(rng) % 3 + 1);
    Interface* obj;
    if(ability == DOUBLE_DAMAGE)
        obj = new Double_Damage;
    else if(ability == SCANNER)
        obj = new Scanner;
    else if(ability == SHELLING)
        obj = new Shelling;
    this->abilities->push(obj);}
    catch(Ability_Error error)
    {
        std::cerr<<error.what()<<std::endl;
    }
}
bool Map::Valid_Coords(int x, int y, enum LENGTH length, enum ORIENTATION orinetation)
{
    int len = static_cast<int>(length);
    if((orinetation == HORZ && ((x + len - 1) > this->x)) || (orinetation == VERT && ((y + len - 1) > this->y)))
        return false;
    for(int i = 0; i < len; i++)
    {
        if(orinetation == HORZ && fill_area.find({x+i, y}) != fill_area.end())
            return false;
        else if(orinetation == VERT && fill_area.find({x, y+i}) != fill_area.end())
            return false;
    }
    return true;
}
void Map::Fill_Area(int x, int y, enum LENGTH length, enum ORIENTATION orinetation)
{
    for(int i = -1; i != static_cast<int>(length) + 1; i++)
    {
        for(int j = -1; j != 2; j++)
        {
            if(orinetation == HORZ)
                fill_area.insert({{i + x, j + y}, true});
            else if(orinetation == VERT)
                fill_area.insert({{j + x, i + y}, true});
        }   
    }
}
void Map::Display_Ships()
{
    std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>> :: iterator i;
    for(i = this->ship_positions.begin(); i != this->ship_positions.end(); i++)
    {
        if(i->second.first->Is_Defeat())
        {
            for(int k = -1; k != i->second.first->Get_Length() + 1; k++)
            {
                for(int l = -1; l != 2; l++)
                {
                    if(i->second.second == HORZ && k + i->first.first >= 0 && k + i->first.first < this->x && l + i->first.second >=0 && l + i->first.second< this->y)
                        this->fog_of_war[k + i->first.first][l + i->first.second] = NOTHING;
                    else if(i->second.second == VERT && k + i->first.second >= 0 && k + i->first.second < this->y && l + i->first.first >=0 && l + i->first.first< this->x)
                        this->fog_of_war[l + i->first.first][k + i->first.second] = NOTHING;
                }
            }
        }
        for(int j = 0; j < i->second.first->Get_Length(); j++)
        {
            if(i->second.first->Get_Cell_Health(j) == FULL)
            {
                if(i->second.second == HORZ)
                    this->game_map[i->first.first + j][i->first.second] = ALL_HEALTH + '0';
                else
                    this->game_map[i->first.first][i->first.second + j] = ALL_HEALTH + '0';
            }
            else if(i->second.first->Get_Cell_Health(j) == HALF)
            {
                if(i->second.second == HORZ)
                {
                    this->game_map[i->first.first + j][i->first.second] = HALF_HEALTH + '0';
                    if(i->second.first->Get_Cell_Action(j))
                        this->fog_of_war[i->first.first + j][i->first.second] = HALF_HEALTH + '0';
                }
                else
                {
                    this->game_map[i->first.first][i->first.second + j] = HALF_HEALTH + '0';
                    if(i->second.first->Get_Cell_Action(j))
                        this->fog_of_war[i->first.first][i->first.second + j] = HALF_HEALTH + '0';
                }
            }
            else
            {
                if(i->second.second == HORZ)
                {
                    this->game_map[i->first.first + j][i->first.second] = DESTROYED_SEG + '0';
                    if(i->second.first->Get_Cell_Action(j))
                        this->fog_of_war[i->first.first + j][i->first.second] = DESTROYED_SEG + '0';
                }
                else
                {
                    this->game_map[i->first.first][i->first.second + j] = DESTROYED_SEG + '0';
                    if(i->second.first->Get_Cell_Action(j))
                        this->fog_of_war[i->first.first][i->first.second + j] = DESTROYED_SEG + '0';
                }
            }
        }
    }
}
void Map::Clear_All()
{
    for(int i = 0; i < this->x; i++)
    {
        std::vector<char>str(this->y, '~');
        this->game_map.push_back(str);
        this->fog_of_war.push_back(str);
    }
}
void Map::Set_Map_Data(Map_Data map_data)
{
    this->game_map = map_data.game_map;
    this->fog_of_war = map_data.fog_of_war;
    this->fill_area = map_data.fill_area;
    this->ship_positions = map_data.ship_positions;
    this->destroyed_ships_count = map_data.destroyed_ships_count;
    this->multiplier = map_data.multiplier;
}
Map_Data Map::Get_Map_Data()
{
    Map_Data map_data;
    map_data.game_map = this->game_map;
    map_data.fog_of_war = this->fog_of_war;
    map_data.fill_area = this->fill_area;
    map_data.multiplier = this->multiplier;
    map_data.ship_positions = this->ship_positions;
    map_data.destroyed_ships_count = this->destroyed_ships_count;
    return map_data;
}
inline std::vector<std::vector<char>>game_map;
inline std::vector<std::vector<char>>fog_of_war;
inline std::vector<Ship*>ship_data;
inline std::vector<std::pair<std::pair<int, int>, std::pair<Ship*, enum ORIENTATION>>>ship_positions;
inline std::map< std::pair<int, int>, bool >fill_area;
inline int x,y;
inline bool multiplier;
inline std::queue<Interface*>*abilities;
inline int destroyed_ships_count;