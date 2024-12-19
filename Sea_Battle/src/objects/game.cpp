#include "game.hpp"

std::ostream& operator<<(std::ostream& os, Game_State& state)
{
    int length;
    os<<"x:"<<std::endl<<state.x<<std::endl;
    os<<"y:"<<std::endl<<state.y<<std::endl;
    os<<"step:"<<std::endl<<state.step<<std::endl;
    os<<"try_number:"<<std::endl<<state.try_number<<std::endl;

    os<<"Computer_ships:"<<std::endl;
    os<<state.computer_ship_data.size()<<std::endl;
    for (auto ship : state.computer_ship_data)
    {
        length = static_cast<int>(ship->Get_Length());
        os<<length<<std::endl;
        for(int i = 0; i < length; i++)
        {
            os<<static_cast<int>(ship->Get_Cell_Health(i))<<" "<<(int)ship->Get_Cell_Action(i)<<std::endl;
        }
    }

    os<<"Player_ships:"<<std::endl;
    os<<state.player_ship_data.size()<<std::endl;
    for (auto ship : state.player_ship_data)
    {
        length = static_cast<int>(ship->Get_Length());
        os<<length<<std::endl;
        for(int i = 0; i < length; i++)
        {
            os<<static_cast<int>(ship->Get_Cell_Health(i))<<" "<<(int)ship->Get_Cell_Action(i)<<std::endl;
        }
    }

    os<<"Temp_ships: "<<std::endl;
    os<<state.temp_ship_data.size()<<std::endl;
    for (auto ship : state.temp_ship_data)
    {
        length = static_cast<int>(ship->Get_Length());
        os<<length<<std::endl;
        for(int i = 0; i < length; i++)
        {
            os<<static_cast<int>(ship->Get_Cell_Health(i))<<" "<<(int)ship->Get_Cell_Action(i)<<std::endl;
        }
    }

    os<<"Player_game_map:"<<std::endl;
    for (auto row : state.player_game_map)
    {
        for (char symbol : row)
        {
            os<<symbol;
        }
        os<<std::endl;
    }
    os<<"Player_fog_of_war:"<<std::endl;
    for (auto row : state.player_fog_of_war)
    {
        for (char symbol : row)
        {
            os<<symbol;
        }
        os<<std::endl;
    }

    os<<"Computer_game_map:"<<std::endl;
    for (auto row : state.computer_game_map)
    {
        for (char symbol : row)
        {
            os<<symbol;
        }
        os<<std::endl;
    }
    os<<"Computer_fog_of_war:"<<std::endl;
    for (auto row : state.computer_fog_of_war)
    {
        for (char symbol : row)
        {
            os<<symbol;
        }
        os<<std::endl;
    }

    os<<"Player_fill_area:"<<std::endl;
    os<<state.player_fill_area.size()<<std::endl;
    for(auto i: state.player_fill_area)
        os<<i.first.first<<" "<<i.first.second<<" "<<i.second<<std::endl;
    os<<"Computer_fill_area:"<<std::endl;
    os<<state.computer_fill_area.size()<<std::endl;
    for(auto i: state.computer_fill_area)
        os<<i.first.first<<" "<<i.first.second<<" "<<i.second<<std::endl;

    os<<"Player_ship_positions:"<<std::endl;
    os<<state.player_ship_positions.size()<<std::endl;
    for(auto i: state.player_ship_positions)
        os<<i.first.first<<" "<<i.first.second<<" "<<i.second.first->Get_Length()<<" "<<static_cast<int>(i.second.second)<<std::endl;
    os<<"Computer_ship_positions:"<<std::endl;
    os<<state.computer_ship_positions.size()<<std::endl;
    for(auto i: state.computer_ship_positions)
        os<<i.first.first<<" "<<i.first.second<<" "<<i.second.first->Get_Length()<<" "<<static_cast<int>(i.second.second)<<std::endl;

    os<<"Player_multiplier:"<<std::endl<<(state.player_multiplier ? "true" : "false")<<std::endl;
    os<<"Player_destroyed_ships_count:"<<std::endl<<state.player_destroyed_ships_count<<std::endl;

    os<<"Player_abilities:"<<std::endl;
    os<<state.player_abilities.size()<<std::endl;
    for (auto ability : state.player_abilities)
    {
        switch (ability)
        {
            case DOUBLE_DAMAGE:
                os<<1<<std::endl;
                break;
            case SCANNER:
                os<<2<<std::endl;
                break;
            case SHELLING:
                os<<3<<std::endl;
                break;
            default:
                os<<0<<std::endl;
                break;
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, Game_State& state)
{
    std::string s;
    int first_length;
    int second_length;
    is>>s;
    is>>state.x;
    is>>s;
    is>>state.y;
    is>>s;
    is>>state.step;
    is>>s;
    is>>state.try_number;

    //ship_managers
    state.player_ship_data.clear();
    state.computer_ship_data.clear();
    state.temp_ship_data.clear();
    int ship_length;
    int segment_health;
    int used;
    std::vector<cell>cell_data;

    is>>s;
    is>>first_length;

    for(int i = 0; i < first_length; i++)
    {
        is>>ship_length;
        cell_data.clear();
        for(int j = 0; j < ship_length; j++)
        {
            is>>segment_health>>used;
            cell_data.push_back({static_cast<enum SEGMENT>(segment_health), (bool)used});
        }
        Ship* ship = new Ship(static_cast<enum LENGTH>(ship_length), cell_data);
        state.player_ship_data.push_back(ship);
    }

    is>>s;
    is>>first_length;
    state.computer_ship_data.clear();

    for(int i = 0; i < first_length; i++)
    {
        is>>ship_length;
        cell_data.clear();
        for(int j = 0; j < ship_length; j++)
        {
            is>>segment_health>>used;
            cell_data.push_back({static_cast<enum SEGMENT>(segment_health), (bool)used});
        }
        Ship* ship = new Ship(static_cast<enum LENGTH>(ship_length), cell_data);
        state.computer_ship_data.push_back(ship);
    }

    is>>s;
    is>>first_length;
    state.temp_ship_data.clear();

    for(int i = 0; i < first_length; i++)
    {
        is>>ship_length;
        cell_data.clear();
        for(int j = 0; j < ship_length; j++)
        {
            is>>segment_health>>used;
            cell_data.push_back({static_cast<enum SEGMENT>(segment_health), (bool)used});
        }
        Ship* ship = new Ship(static_cast<enum LENGTH>(ship_length), cell_data);
        state.temp_ship_data.push_back(ship);
    }

    //maps
    state.player_game_map.clear();
    state.player_fog_of_war.clear();
    state.computer_game_map.clear();
    state.computer_fog_of_war.clear();
    std::vector<std::vector<char>> char_darray;
    std::vector<char> char_array;
    char symbol;

    is>>s;

    for(int i = 0; i < state.x; i++)
    {
        char_array.clear();
        for(int j = 0; j < state.y; j++)
        {
            is>>symbol;
            char_array.push_back(symbol);
        }
        char_darray.push_back(char_array);
    }
    state.player_game_map = char_darray;

    is>>s;

    char_darray.clear();
    for(int i = 0; i < state.x; i++)
    {
        char_array.clear();
        for(int j = 0; j < state.y; j++)
        {
            is>>symbol;
            char_array.push_back(symbol);
        }
        char_darray.push_back(char_array);
    }
    state.player_fog_of_war = char_darray;

    is>>s;

    char_darray.clear();
    for(int i = 0; i < state.x; i++)
    {
        char_array.clear();
        for(int j = 0; j < state.y; j++)
        {
            is>>symbol;
            char_array.push_back(symbol);
        }
        char_darray.push_back(char_array);
    }
    state.computer_game_map = char_darray;

    is>>s;

    char_darray.clear();
    for(int i = 0; i < state.x; i++)
    {
        char_array.clear();
        for(int j = 0; j < state.y; j++)
        {
            is>>symbol;
            char_array.push_back(symbol);
        }
        char_darray.push_back(char_array);
    }
    state.computer_fog_of_war = char_darray;

    //fill_areas
    state.player_fill_area.clear();
    state.computer_fill_area.clear();
    int x, y;
    
    is>>s;
    
    is>>first_length;
    for(int i = 0; i < first_length; i++)
    {
        is>>x>>y>>used;
        state.player_fill_area.insert({std::make_pair(x, y), (bool)used});
    }

    is>>s;
    
    is>>first_length;
    for(int i = 0; i < first_length; i++)
    {
        is>>x>>y>>used;
        state.computer_fill_area.insert({std::make_pair(x, y), (bool)used});
    }

    //ship_positions
    state.player_ship_positions.clear();
    state.computer_ship_positions.clear();
    int orientation;

    is>>s;
    
    is>>first_length;
    for(int i = 0; i < first_length; i++)
    {
        is>>x>>y>>ship_length>>orientation;
        state.player_ship_positions.push_back({std::make_pair(x, y), std::make_pair(state.player_ship_data[i], static_cast<enum ORIENTATION>(orientation))});
    }

    is>>s;
    
    is>>first_length;
    for(int i = 0; i < first_length; i++)
    {
        is>>x>>y>>ship_length>>orientation;
        state.computer_ship_positions.push_back({std::make_pair(x, y), std::make_pair(state.computer_ship_data[i], static_cast<enum ORIENTATION>(orientation))});
    }

    int mlp;
    is>>s;
    is>>mlp;
    state.player_multiplier = static_cast<bool>(mlp);

    is>>s;
    int destroyed_ships_count;
    is>>destroyed_ships_count;
    state.player_destroyed_ships_count = destroyed_ships_count;

    //abilities
    is>>s;
    state.player_abilities.clear();
    int abilities_size = 0;
    is>>abilities_size;
    int ability;
    for(int i = 0; i < abilities_size; i++)
    {
        is>>ability;
        enum ABILITY temp_ability = static_cast<enum ABILITY>(ability);
        state.player_abilities.push_back(temp_ability);
    }
    return is;
}

Game::Game()
{
    this->step = -1;
}
void Game::Start_Game(int x, int y)
{
    this->try_number = 0;
    this->x = x;
    this->y = y;
    this->Player_Map = new Map(this->x, this->y);
    this->Temp_Ship_manager = new Ship_manager(1, {BOAT});
    this->Player_Ship_manager = new Ship_manager(*this->Temp_Ship_manager);
    this->Player_Map->Add_Ships(this->Player_Ship_manager->Get_Ships());
    this->Computer_Map = new Map(x, y);
    this->Player_Ability_manager = new Abilities_manager();
    this->Computer_Map->Add_Abilities(Player_Ability_manager->Get_Abilities());
    this->Computer_Ship_manager = new Ship_manager(*this->Temp_Ship_manager);
    this->Save_State();
}
void Game::Place_Ship(int x , int y, int ort)
{
    this->Player_Map->Place_Ship(x, y, ort);
    this->Save_State();
}
int Game::Make_Shoot(int x, int y)
{
    int flag = this->Computer_Map->Make_Shoot(x, y);
    this->Save_State();
    return flag;
}
void Game::Make_Step()
{
    this->step++;
    this->Save_State();
}
void Game::Try()
{
    this->try_number++;
    this->Computer_Map = new Map(x, y);
    this->Computer_Ship_manager = new Ship_manager(*this->Temp_Ship_manager);
    this->Computer_Map->Add_Abilities(this->Player_Ability_manager->Get_Abilities());
    this->Computer_Map->Add_Ships(Computer_Ship_manager->Get_Ships());
    this->Computer_Map->Auto_Place_Ships();
    this->Save_State();
}
void Game::Computer_Step()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1,1000);
    int x_coord = (dist(rng) % this->x) + 1;
    int y_coord = (dist(rng) % this->y) + 1;
    std::cout<<"Computer turn:"<<std::endl;
    std::cout<<x_coord<<" "<<y_coord<<std::endl;
    this->Player_Map->Make_Shoot(x_coord, y_coord);
    //this->step++;
    this->Save_State();
}
bool Game::End()
{
    return this->Player_Ship_manager->All_Destroyed();
}
bool Game::Computer_Lose()
{
    return this->Computer_Ship_manager->All_Destroyed();
}
void Game::Use_Ability(int x, int y)
{
    Computer_Map->Use_Ability(x, y);
    this->Save_State();
}
void Game::Load_Game()
{
    this->Load_State();
}
void Game::Save_Game()
{
    this->game_saver.save("saves/save.json", state);
}
void Game::Save_State()
{
    Map_Data player_map_data = Player_Map->Get_Map_Data();
    Map_Data computer_map_data = Computer_Map->Get_Map_Data();

    this->state.x = this->x;
    this->state.y = this->y;
    this->state.try_number = this->try_number;
    this->state.step = this->step;
    this->state.computer_fog_of_war = computer_map_data.fog_of_war;
    this->state.player_fog_of_war = player_map_data.fog_of_war;
    this->state.computer_game_map = computer_map_data.game_map;
    this->state.player_game_map = player_map_data.game_map;
    this->state.computer_fill_area = computer_map_data.fill_area;
    this->state.player_fill_area = player_map_data.fill_area;
    this->state.computer_ship_data = Computer_Ship_manager->Get_Ships();
    this->state.player_ship_data = Player_Ship_manager->Get_Ships();
    this->state.temp_ship_data = Temp_Ship_manager->Get_Ships();
    this->state.computer_ship_positions = computer_map_data.ship_positions;
    this->state.player_ship_positions = player_map_data.ship_positions;
    this->state.player_abilities = Player_Ability_manager->Get_Load_Buffer();
    this->state.player_destroyed_ships_count = player_map_data.destroyed_ships_count;
    this->state.player_multiplier = player_map_data.multiplier;
}
void Game::Load_State()
{
    Game_State new_state = game_saver.load("saves/save.json");

    this->state = new_state;

    this->x = new_state.x;
    this->y = new_state.y;

    this->step = new_state.step;
    this->try_number = new_state.try_number;

    Map_Data new_player_map_data;
    Map_Data new_computer_map_data;

    this->Computer_Ship_manager = new Ship_manager(new_state.computer_ship_data);
    this->Player_Ship_manager = new Ship_manager(new_state.player_ship_data);
    this->Temp_Ship_manager = new Ship_manager(new_state.temp_ship_data);

    this->Player_Ability_manager = new Abilities_manager(new_state.player_abilities, true);

    new_player_map_data.destroyed_ships_count = new_state.player_destroyed_ships_count;
    new_player_map_data.multiplier = new_state.player_multiplier;
    new_player_map_data.fog_of_war = new_state.player_fog_of_war;
    new_player_map_data.game_map = new_state.player_game_map;
    new_player_map_data.fill_area = new_state.player_fill_area;
    new_player_map_data.ship_positions = new_state.player_ship_positions;

    new_computer_map_data.destroyed_ships_count = 0;
    new_computer_map_data.multiplier = 0;
    new_computer_map_data.fog_of_war = new_state.computer_fog_of_war;
    new_computer_map_data.game_map = new_state.computer_game_map;
    new_computer_map_data.fill_area = new_state.computer_fill_area;
    new_computer_map_data.ship_positions = new_state.computer_ship_positions;

    this->Player_Map = new Map(x, y);
    this->Player_Map->Set_Map_Data(new_player_map_data);
    this->Player_Map->Add_Ships(this->Player_Ship_manager->Get_Ships());
    Abilities_manager* Computer_Ability_manager = new Abilities_manager();
    this->Player_Map->Add_Abilities(Computer_Ability_manager->Get_Abilities());

    this->Computer_Map = new Map(x, y);
    this->Computer_Map->Set_Map_Data(new_computer_map_data);
    this->Computer_Map->Add_Ships(this->Computer_Ship_manager->Get_Ships());
    this->Computer_Map->Add_Abilities(this->Player_Ability_manager->Get_Abilities());
}
Game_State* Game::Get_Game_State()
{
    return &(this->state);
}
int Game::Get_Step()
{
    return this->step;
}
int Game::Get_Try()
{
    return this->try_number;
}
inline int x,y;
inline int step;
inline int try_number;
inline Ship_manager* Computer_Ship_manager;
inline Ship_manager* Player_Ship_manager;
inline Ship_manager* Temp_Ship_manager;
inline Map* Player_Map;
inline Map* Computer_Map;
inline Abilities_manager* Player_Ability_manager;
inline Game_State state;
inline Game_Saver game_saver;