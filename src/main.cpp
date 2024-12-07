#include <iostream>
#include <vector>

#include "game/game.hpp"

// remember to add inline parameters of the subroutine main else SDL2 will not work
int main(int argc, char* argv[]) {
    Game& game = Game::get_instance();
    game.init();
    game.run();
    game.destroy();

    return 0;
}