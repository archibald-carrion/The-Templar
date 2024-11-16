#ifndef COOLGAME_HPP
#define COOLGAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <memory>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAP_WIDTH = 8;
const int MAP_HEIGHT = 8;
const int TEXTURE_WIDTH = 64;
const int TEXTURE_HEIGHT = 64;


/** @brief Target frames per second for the game. */
const int FPS = 60;

/** @brief Number of milliseconds per frame based on the target FPS. */
const int MILLISECS_PER_FRAME = 1000 / FPS;

struct Player {
    double x, y;  // Player position
    double dirX, dirY;  // Direction vector
    double planeX, planeY;  // Camera plane
};

class Pseudo3DGame {
private:

    std::vector<SDL_Texture*> textures;
    // static const int TEXTURE_WIDTH = 64;
    // static const int TEXTURE_HEIGHT = 64;

    int mPreviousFrame = 0; /**< Time of the previous frame. */

    bool isRunning; /**< Flag to indicate if the game is running. */
    
    SDL_Window* window = nullptr; /**< Pointer to the SDL window. */
    SDL_Renderer* renderer = nullptr; /**< Pointer to the SDL renderer. */
    std::unique_ptr<Player> player;
    double movement_speed;
    bool checkCollision(double x, double y);

    SDL_Color wall_color = {100, 100, 100, SDL_ALPHA_OPAQUE}; // unused, need deleting later

    int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1},
        {1,0,2,0,0,1,0,1},
        {1,0,0,0,0,0,0,1},
        {1,1,1,0,0,0,0,2},
        {1,0,1,0,0,0,0,2},
        {1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1}
    };



    /**
     * @brief Processes user input events.
     */
    void processInput();

    /**
     * @brief Updates the game state.
     */
    void update();

    /**
     * @brief Renders the game state to the screen.
     */
    void render();

    /**
     * @brief 
     */
    void setup();

    /**
     * @brief Load the textures used in the game.
     */
    void load_textures();


public:
    Pseudo3DGame();
    ~Pseudo3DGame();
    void init();
    void destroy();
    int run();
    
    /**
     * @brief Returns the instance of the Game class.
     */
    static Pseudo3DGame& get_instance();

    /**
     * @brief Raycasting algorithm.
     * Algorithm to render the 3D world, partially based on https://lodev.org/cgtutor/raycasting.html
     */
    void raycasting();
    void drawVerticalLine(int start_point_X, int start_point_Y, int end_point_Y, uint8_t r, uint8_t g, uint8_t b);
};


#endif // COOLGAME_HPP