#include <SDL3/SDL.h>
#include <iostream>

#include "Game.hpp"

#define TIME_STEP 0.017f

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << SDL_GetError() << std::endl;
	}

	Game engine;
	engine.run();
	
	return 0;
}
