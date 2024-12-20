CC = g++
CFLAGS = -Wall -Werror
SRC = src/objects/main.cpp src/objects/ship.cpp src/objects/ship_manager.cpp src/objects/map.cpp src/abilities/interface.cpp src/abilities/double_damage.cpp src/abilities/scanner.cpp src/abilities/shelling.cpp src/abilities/ability_manager.cpp src/objects/game.cpp src/saving/serialization.cpp src/saving/file_handler.cpp src/IO/commands_interface.cpp src/IO/commands.cpp src/IO/game_render.cpp src/IO/game_print.cpp src/IO/print_maps.cpp src/IO/game_tracking.cpp
OBJS = $(SRC:.cpp=.o)

all: src/run.out

src/run.out: $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f src/run.out $(OBJS)
