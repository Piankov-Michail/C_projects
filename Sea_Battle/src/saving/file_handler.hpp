#ifndef __FILE_HANDLER__
#define __FILE_HANDLER__

#include "../objects/ship.hpp"
#include "../objects/ship_manager.hpp"
#include "../objects/map.hpp"
#include "../abilities/interface.hpp"
#include "../abilities/double_damage.hpp"
#include "../abilities/scanner.hpp"
#include "../abilities/shelling.hpp"
#include "../abilities/ability_manager.hpp"

#include "game_state.hpp"
#include "serialization.hpp"

#include <fstream>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

class File_Writer
{
    public:
        explicit File_Writer(const std::string& filename);
        ~File_Writer();
        void write(const std::string& content);
    private:
        std::ofstream m_file;
};

class File_Reader
{
    public:
        explicit File_Reader(const std::string& filename);
        ~File_Reader();
        std::string readAll();
    private:
        std::ifstream m_file;
};

class Game_Saver
{
    public:
        static void save(std::string filename, Game_State state)
        {
            try
            {
                File_Writer writer(filename);
                json j;
                to_json(j, state);
                writer.write(j.dump(4));
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error saving game state: "<< e.what() << std::endl;
            }
        }
        static Game_State load(std::string filename)
        {
            try {
                File_Reader reader(filename);
                std::string content = reader.readAll();
                json j = json::parse(content);
                Game_State state;
                from_json(j, state);
                return state;
            } catch (const std::exception& e) {
                std::cerr << "Error loading game state: "<< e.what() << std::endl;
                return {};
            }
        }
};

#endif //__FILE_HANDLER__