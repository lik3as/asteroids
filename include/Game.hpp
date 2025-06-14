#ifndef ENGINE
#define ENGINE

#include <SDL3/SDL.h>
#include <vector>

#include "Constants.hpp"
#include "RenderWindow.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Asteroid.hpp"
#include "Collider.hpp"

class Game {
	public:
		Game();
		void run();
		~Game();
	private:
		SDL_Event ev;
		static std::vector<Entity*> entities;
		static RenderWindow window;
		static bool gameIsRunning;

		void handleCollisions(ICollider&);
		void handleEvents();
};

#endif
