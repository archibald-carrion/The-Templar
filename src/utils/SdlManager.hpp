#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP

#include <iostream>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @brief The SDLManager class
 * The SDLManager class is a class for managing SDL.
 */
class SDLManager {
	bool _validState = true; // Valid state of SDL

public:

	/**
	 * @brief Get the instance of the SDLManager
	 * @return The instance of the SDLManager
	 */
	static SDLManager& getInstance() {
		static SDLManager instance;
		return instance;
	}

	SDLManager(const SDLManager&) = delete; // Delete copy constructor
	SDLManager& operator=(const SDLManager&) = delete; // Delete copy assignment

	[[nodiscard]] bool isValid() const { return _validState; } // Check if SDL is valid

private:

	/**
	 * @brief Construct a new SDLManager object
	 */
	SDLManager() {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0
			|| IMG_Init(SDL_INIT_VIDEO) != 0
			|| TTF_Init() != 0
			|| Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
			_validState = false;
		}
	}

    /**
	 * @brief Destroy the SDLManager object
	 */
	~SDLManager() {
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		Mix_CloseAudio();
	}
};

#endif //SDLMANAGER_HPP
