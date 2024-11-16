#include <iostream>
#include <vector>

#ifdef GAME
#include "game/game.hpp"
#elif PSEUDO_3D_GAME
#include"game/Pseudo3DGame.hpp"
#endif

// remember to add inline parameters of the subroutine main else SDL2 will not work
int main(int argc, char* argv[]) {

    #ifdef GAME
    Game& game = Game::get_instance();
    game.init();
    game.run();
    game.destroy();

    #elif PSEUDO_3D_GAME
    Pseudo3DGame& game = Pseudo3DGame::get_instance();
    game.init();
    game.run();
    game.destroy();
    #endif
    return 0;
}