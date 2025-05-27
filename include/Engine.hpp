#ifndef ENGINE
#define ENGINE

#include <SDL3/SDL.h>

#include "RenderWindow.hpp"
#include "Player.hpp"
#include "Math.hpp"

#define TIME_STEP 0.017f
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

class Engine {
	public:
		Engine(const char* title);
		void run();
	private:
		Player player;
		SDL_Event ev;
		RenderWindow window;
		bool gameIsRunning;
		void handleEvents();
		void update(float dt);
};

#endif
