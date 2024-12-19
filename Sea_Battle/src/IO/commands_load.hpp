#include "../saving/json.hpp"
#include "enum_command.hpp"
#include <fstream>
#include <iostream>
#include <map>
using json = nlohmann::json;

//Commands

void to_json(std::unordered_map<COMMAND, std::string> m) {
    json j;
    j["commands"] = json::array();
    for (auto i : m)
    {
        json elem = {
            {"first", static_cast<int>(i.first)},
            {"second", i.second}
        };
        j["commands"].push_back(elem);
    }
    try{
    std::ofstream file("./src/IO/commands.json");
    file << j;}
    catch (const std::exception& e)
    {
        std::cerr << "Error saving commands: "<< e.what() << std::endl;
    }
}

std::unordered_map<enum COMMAND, std::string> load_from_json()
{
    std::unordered_map<enum COMMAND, std::string> command_keys_default = {{START, "start"}, {SAVE, "save"}, {LOAD, "load"}, {ABIL, "ability"},\
     {PRINT_MAP, "print map"}, {PRINT_FOG, "print fog"}, {EXIT, "exit"}, {SHOOT, "shoot"}};
    std::unordered_map<enum COMMAND, std::string> command_keys;
    try{
    std::ifstream file("./src/IO/commands.json");
    json j = json::parse(file);
    for (auto elem : j.at("commands"))
    {
        command_keys[static_cast<enum COMMAND>(elem.at("first"))] = elem.at("second");
    }}
    catch (const std::exception& e)
    {
        std::cerr << "Error download commands: "<< e.what() << std::endl;
        return command_keys_default;
    }
    for(auto i: command_keys_default)
    {
        if(command_keys.find(i.first) != command_keys.end())
        {
            command_keys[i.first] = i.second;
        }
    }
    return command_keys;
}