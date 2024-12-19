#include "game.hpp"

#include<iostream>
#include<vector>
#include<map>

int main()
{
    Game A = Game();
    std::cout<<"Чтобы начать игру введите [start], чтобы загрузиться введите [load]"<<std::endl;
    std::string s;
    while(true)
    {
        std::cin>>s;
        if(!s.compare("load"))
        {
            A.Load_Game();
            break;
        }
        else if(!s.compare("start"))
        {
            A.Start_Game();
            break;
        }
        else
        {
            std::cout<<"Ошибка в команде!"<<std::endl;
        }
    }
}