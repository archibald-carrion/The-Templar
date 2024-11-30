MAKEFLAGS += -j$(shell nproc)

CC = g++
STD = -std=c++20
DEBUG_FLAGS = -g -Wall -pipe -O0
OPTIMIZATION_FLAGS = -O3 -pipe
GAME_FLAG ?= -DGAME

INC_PATH = $(shell find ./libs -type d -exec echo -I{} \;)
SRC = $(shell find src -name '*.cpp')
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 -ltinyxml2
ASAN_CFLAGS = -fsanitize=address -fno-omit-frame-pointer -pipe
ASAN_LFLAGS = -fsanitize=address
ASAN_OPTIONS=halt_on_error=1:detect_leaks=1 ./your_program

EXEC = build/game_engine

.PHONY: all build release asan clean run

all: build

build: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(DEBUG_FLAGS) $(GAME_FLAG) $(STD) $(INC_PATH) $(OBJ) $(LFLAGS) -o $(EXEC)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(DEBUG_FLAGS) $(GAME_FLAG) $(STD) $(INC_PATH) -c $< -o $@

asan: CFLAGS += $(ASAN_CFLAGS)
asan: LFLAGS += $(ASAN_LFLAGS)
asan: build

release: CFLAGS += $(OPTIMIZATION_FLAGS)
release: build

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf build
