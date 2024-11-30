#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP

#include <iostream>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDLManager {
	bool _validState = true;

public:
	static SDLManager& getInstance() {
		static SDLManager instance;
		return instance;
	}

	SDLManager(const SDLManager&) = delete;
	SDLManager& operator=(const SDLManager&) = delete;

	[[nodiscard]] bool isValid() const { return _validState; }

private:
	SDLManager() {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0
			|| IMG_Init(SDL_INIT_VIDEO) != 0
			|| TTF_Init() != 0
			|| Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
			_validState = false;
		}
	}

	~SDLManager() {
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
		Mix_CloseAudio();
	}
};

#endif //SDLMANAGER_HPP
