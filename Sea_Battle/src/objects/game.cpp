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
void Game::Start_Game()
{
    this->try_number = 1;
    std::cout<<START_GAME_MSG<<std::endl;
    std::cout<<MAP_SIZE_SETTING<<std::endl;
    std::cin>>this->x>>this->y;

    Player_Map = new Map(this->x, this->y);

    this->Temp_Ship_manager = new Ship_manager(0,{});
    std::cout<<SHIPS_ADDITION_MSG<<std::endl;
    int ships_count = 0;
    std::string ship_type;
    std::cin>>ships_count;
    while(ships_count > 0)
    {
        std::cin>>ship_type;
        if(!ship_type.compare("BOAT"))
            this->Temp_Ship_manager->Add_Ships(1, {BOAT});
        else if(!ship_type.compare("CORVETTE"))
            this->Temp_Ship_manager->Add_Ships(1, {CORVETTE});
        else if(!ship_type.compare("FRIGATE"))
            this->Temp_Ship_manager->Add_Ships(1, {FRIGATE});
        else if(!ship_type.compare("BATTLESHIP"))
            this->Temp_Ship_manager->Add_Ships(1, {BATTLE_SHIP});
        else
        {
            ships_count++;
            std::cout<<INVALID_SHIP_LENGTH<<std::endl;
            std::cout<<"Make another try!"<<std::endl;
        }
        ships_count--;
    }
    this->Player_Ship_manager = new Ship_manager(*this->Temp_Ship_manager);
    this->Player_Map->Add_Ships(Player_Ship_manager->Get_Ships());
    this->Player_Map->Place_Ships();
    this->Player_Ability_manager = new Abilities_manager();
    Abilities_manager* Computer_Ability_manager = new Abilities_manager();
    while(!Player_Ship_manager->All_Destroyed())
    {
        std::cout<<"Your map:"<<std::endl;
        this->Player_Map->Print_Map();
        std::cout<<"Try number: "<<try_number<<std::endl;
        this->Computer_Map = new Map(x, y);
        this->Computer_Ship_manager = new Ship_manager(*this->Temp_Ship_manager);
        this->Player_Map->Add_Abilities(Computer_Ability_manager->Get_Abilities());
        this->Computer_Map->Add_Abilities(Player_Ability_manager->Get_Abilities());
        this->Computer_Map->Add_Ships(Computer_Ship_manager->Get_Ships());
        this->Computer_Map->Auto_Place_Ships();
        this->Try();
        this->try_number++;
    }
}
void Game::Try()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1,1000);
    this->step = 1;
    std::string s;
    int x, y;
    this->Computer_Map->Print_Fog_Of_War();
    while(!Player_Ship_manager->All_Destroyed() && !Computer_Ship_manager->All_Destroyed())
    {
        this->Save_State();
        if(step)
        {
            bool ability_flag = false;
            std::cout<<"Your turn:"<<std::endl;
            std::cout<<"If you want shoot input [shoot] and then input coordinates or if you want use ability input [ability] if you want save input [save], if you want exit input [exit]"<<std::endl;
            while(true)
            {
                std::cin>>s;
                if(!s.compare("ability") && !ability_flag)
                {
                    Computer_Map->Use_Ability();
                    this->Computer_Map->Print_Fog_Of_War();
                    ability_flag = true;
                    std::cout<<"You used ability, you can make shoot!"<<std::endl;
                }
                else if(!s.compare("ability") && ability_flag)
                {
                    std::cout<<"You have already used one ability!"<<std::endl;
                }
                else if(!s.compare("shoot"))
                {
                    std::cout<<"Input shoot coords like [x y]"<<std::endl;
                    while(true)
                    {
                        std::cin>>x>>y;
                        if(x > this->x || x <= 0 || y > this->y || y <= 0)
                        {
                            std::cout<<x<<" "<<this->x<<" "<<y<<" "<<this->y<<std::endl;
                            std::cout<<SHOOT_ERROR<<std::endl;
                        }
                        else
                        {
                            this->Computer_Map->Make_Shoot(x, y);
                            this->Computer_Map->Print_Fog_Of_War();
                            break;
                        }
                    }
                    break;
                }
                else if(!s.compare("save"))
                {
                    this->Save_Game();
                    std::cout<<"Game saving"<<std::endl;
                }
                else if(!s.compare("exit"))
                {
                    exit(1);
                }
                else
                {
                    std::cout<<"command error, make another try!"<<std::endl;
                }
            }
            step = 0;
        }
        else
        {
            x = (dist(rng) % this->x) + 1;
            y = (dist(rng) % this->y) + 1;
            std::cout<<x<<" "<<y<<std::endl;
            std::cout<<"Computer turn:"<<std::endl;
            this->Player_Map->Make_Shoot(x, y);
            step = 1;
        }
    }
    if(this->Player_Ship_manager->All_Destroyed())
    {
        std::cout<<"Game over!"<<std::endl;
    }
    else
    {
        std::cout<<"You win!"<<std::endl;
    }
}
void Game::Load_Game()
{
    this->Load_State();
    std::cout<<"Your map:"<<std::endl;
    this->Player_Map->Print_Map();
    if(this->step != -1)
    {
        std::cout<<"Try number: "<<try_number<<std::endl;
        this->Try();
        this->try_number++;
    }
    while(!Player_Ship_manager->All_Destroyed())
    {
        std::cout<<"Your map:"<<std::endl;
        this->Player_Map->Print_Map();
        std::cout<<"Try number: "<<try_number<<std::endl;
        this->Computer_Map = new Map(x, y);
        this->Computer_Ship_manager = new Ship_manager(*this->Temp_Ship_manager);
        this->Player_Ability_manager = new Abilities_manager();
        Abilities_manager* Computer_Ability_manager = new Abilities_manager();
        this->Player_Map->Add_Abilities(Computer_Ability_manager->Get_Abilities());
        this->Computer_Map->Add_Abilities(Player_Ability_manager->Get_Abilities());
        this->Computer_Map->Add_Ships(Computer_Ship_manager->Get_Ships());
        this->Computer_Map->Auto_Place_Ships();
        this->Try();
        this->try_number++;
    }
}
void Game::Save_Game()
{
    /*
    this->Save_State();
    std::ofstream fou2("saves/input.txt");
    fou2<<this->state;
    fou2.close();*/
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
    /*
    std::ifstream fin1("saves/input.txt");
    Game_State test_state;
    fin1>>test_state;
    fin1.close();
    std::ofstream fou1("saves/output.txt");
    fou1<<test_state;
    fou1.close();*/
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