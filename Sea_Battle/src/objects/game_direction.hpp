#ifndef __GAME_DIRECTION_CLASS__
#define __GAME_DIRECTION_CLASS__

#include "game.hpp"
#include "../IO/user_input.hpp"
#include "../IO/game_print.cpp"
#include "../IO/game_render.hpp"
#include "../IO/game_tracking.hpp"

template<typename Input>
class Game_Direction
{
    public:
        Game_Direction(Game* game, Input* input_handler, Game_Print<Game_Render>* game_printer);
        void Run();
        void Start();
        void Load();
    private:
        void Step();
        Game* game;
        Game_Print<Game_Render> game_printer;
        enum TRACKING action;
        Input input_handler;
        Game_Tracking game_tracker;
};

template<typename Input>
Game_Direction<Input>::Game_Direction(Game* game, Input* input_handler, Game_Print<Game_Render>* game_printer)
{
    this->game = game;
    this->input_handler = *input_handler;
    this->game_printer = *game_printer;
    //action = NO_CHANGES;
}

template<typename Input>
void Game_Direction<Input>::Run()
{
    Command_Interface* command;
    
    std::string s;
    
    bool flag = true;
    
    std::cout<<"Чтобы начать игру введите [start], чтобы загрузиться введите [load]"<<std::endl;

    while(true)
    {
        std::getline(std::cin, s);
        try
        {
            command = input_handler.Parse_Input(s);
            if(command->Get_Type() != START && command->Get_Type() != LOAD)
                throw(Command_Error("Incorrect command, load or save need!"));
            break;
        }
        catch(Command_Error e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    if(command->Get_Type() == START)
        this->Start();
    else if(command->Get_Type() == LOAD)
        this->Load();
}

template<typename Input>
void Game_Direction<Input>::Step()
{
    std::string s;
    Command_Interface* command;
    int x, y;
    bool ability_flag;
    while(!game->End())
    {
        std::cout<<"Try number: "<<game->Get_Try()<<std::endl;
        while(!game->Computer_Lose() && !game->End())
        {
            std::cout<<"Your turn:"<<std::endl;
            ability_flag = false;
            game_printer.Use(PRINT_FOG_ACTION);
            std::cout<<"If you want shoot input [shoot] and then input coordinates or if you want use ability input [ability] if you want save input [save]"<<std::endl;
            std::cout<<"input [print fog] or [print map] to see enemy and your map!"<<std::endl;
            while(true)
            {
                while(true)
                {
                    std::getline(std::cin, s);
                    try
                    {
                        command = input_handler.Parse_Input(s);
                        if(command->Get_Type() != SHOOT && command->Get_Type() != SAVE && command->Get_Type() != ABIL &&\
                        command->Get_Type() != EXIT && command->Get_Type() != PRINT_FOG && command->Get_Type() != PRINT_MAP)
                            throw(Command_Error("Incorrect command, save or exit or shoot or ability or print fog or print map need!"));
                        break;
                    }
                    catch(Command_Error e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                if(command->Get_Type() == EXIT)
                    exit(0);
                else if(command->Get_Type() == SAVE)
                {
                    game->Save_Game();
                }
                else if(command->Get_Type() == ABIL)
                {
                    x = -1;
                    y = -1;
                    if(game->Get_Game_State()->player_abilities.size() != 0 and game->Get_Game_State()->player_abilities[0] == SCANNER)
                    {
                        std::cout<<SCANNER_INFO<<std::endl;
                        while(true)
                        {
                            try{
                            std::getline(std::cin, s);
                            command = input_handler.Parse_Input(s);
                            if(command->Get_Type() != POS)
                                throw(Command_Error("Incorrect command, x and y needed!"));
                            x = command->Get_Data().x;
                            y = command->Get_Data().y;
                            break;}
                            catch(Command_Error e)
                            {
                                std::cerr << e.what() << '\n';
                            }
                        }
                    }
                    if(!ability_flag)
                    {
                        try
                        {
                            game->Use_Ability(x, y);
                            ability_flag = true;
                        }
                        catch(Ability_Error error)
                        {
                            std::cerr<<error.what()<<std::endl;
                        }
                        catch(Coordinates_Error error)
                        {
                            std::cerr<<error.what()<<" On coords: x: "<<error.Get_x() + 1<<" y: "<<error.Get_y() + 1<<std::endl;
                        }
                    }
                    else
                        std::cout<<"You have already used ability!"<<std::endl;
                }
                else if(command->Get_Type() == PRINT_FOG)
                {
                    //action = this->game_tracker.Update(*game->Get_Game_State());
                    //std::cout<<static_cast<int>(action)<<std::endl;
                    //game_printer.Use(action);
                    game_printer.Use(PRINT_FOG_ACTION);
                }
                else if(command->Get_Type() == PRINT_MAP)
                {
                    //action = this->game_tracker.Update(*game->Get_Game_State());
                    //std::cout<<static_cast<int>(action)<<std::endl;
                    //game_printer.Use(action);
                    game_printer.Use(PRINT_MAP_ACTION);
                }
                else if(command->Get_Type() == SHOOT)
                {
                    while(true)
                    {
                        try
                        {
                            std::getline(std::cin, s);
                            command = input_handler.Parse_Input(s);
                            if(command->Get_Type() != POS)
                                throw(Command_Error("Incorrect command, load or save need!"));
                            x = command->Get_Data().x;
                            y = command->Get_Data().y;
                            game->Make_Shoot(x, y);
                            break;
                        }
                        catch(Coordinates_Error error)
                        {
                            std::cerr<<error.what()<<" On coords: "<<"x: "<<error.Get_x() + 1<<" "<<" y: "<<error.Get_y() + 1<<std::endl;
                        }
                        catch(Command_Error e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }
                    break;
                }
            }
            game->Computer_Step();
        }
        if(!game->End())
        {
            std::cout<<"You win!"<<std::endl;
            game->Try();
        }
    }
    std::cout<<"Game over!"<<std::endl;
}

template<typename Input>
void Game_Direction<Input>::Start()
{
    Command_Interface* command;
    
    std::string s;

    std::cout<<START_GAME_MSG<<std::endl;
    game->Start_Game(3, 3);
    game_printer.Use(PRINT_MAP_ACTION);
    std::cout<<START_GAME_MSG<<std::endl;
    std::cout<<PLACING_SHIPS_MESSAGE<<std::endl;
    int ships_count = 1;
    int x, y, ort;
    while(ships_count > 0)
    {
        std::getline(std::cin, s);
        try
        {
            command = input_handler.Parse_Input(s);
            if(command->Get_Type() != SHIP_POS)
                throw(Command_Error("Incorrect command, ship position need!"));
            x = command->Get_Data().x;
            y = command->Get_Data().y;
            ort = command->Get_Data().orientation;
            game->Place_Ship(x, y, ort);
            game_printer.Use(PRINT_MAP_ACTION);
            ships_count --;
        }
        catch(Command_Error e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(Coordinates_Error e)
        {
            std::cerr<<e.what()<<" On coords: x: "<<e.Get_x()<<" y: "<<e.Get_y()<<std::endl;
        }
        catch(Orientation_Error e)
        {
            std::cerr<<e.what()<<" On: x: "<<e.Get_x()<<" y: "<<e.Get_y()<<" orientation: "<<e.Get_Orientation()<<std::endl;
        }
    }
    std::cout<<"Ship replacement done!"<<std::endl;
    std::cout<<"Now we start rounds!"<<std::endl;
    this->game_tracker = Game_Tracking(*(this->game->Get_Game_State()));
    game->Try();
    this->Step();
}

template<typename Input>
void Game_Direction<Input>::Load()
{
    game->Load_Game();
    this->Step();
}

#endif //__GAME_DIRECTION_CLASS__