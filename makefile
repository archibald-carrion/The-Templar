CC=g++
STD=-std=c++17
CFLAGS=-Wall $(GAME_FLAG)
INC_PATH=$(shell find ./libs -type d -exec echo -I{} \;)
SRC=src/main.cpp \
	src/game/game.cpp \
	src/game/Pseudo3DGame.cpp \
	src/ECS/*.cpp \
	src/assets_manager/assets_manager.cpp \
	src/controller_manager/*.cpp \
	src/scene_manager/*.cpp \
	src/audio_manager/*.cpp \
	src/animation_manager/*.cpp
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 -ltinyxml2
EXEC=game_engine

# Default GAME_FLAG (set to -DGAME if not specified)
GAME_FLAG ?= -DGAME


build:
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SRC) $(LFLAGS) -o $(EXEC)

run:
	./$(EXEC)

clean:
	rm $(EXEC)