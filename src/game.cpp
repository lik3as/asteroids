#include "Game.hpp"

RenderWindow Game::window = RenderWindow("ASTEROIDS V.0", WINDOW_WIDTH, WINDOW_HEIGHT);
std::vector<Entity*> Game::entities = {};

bool Game::gameIsRunning = true;

Game::Game()
{	
	entities.push_back(
		new Player(Vector2<int>(15, 0), window.loadTexture("res/gfx/spaceship.png")) //already an rvalue!!!
	);
}

void Game::run() {
	float accumulator = 0.0f;
	Uint64 prevTicks = SDL_GetTicks();

	std::cout << "calling Game::run()" << std::endl;
	while (gameIsRunning) {
		Uint64 lastTicks = SDL_GetTicks();
		float dt = (float) ((lastTicks / 1000.0f) - (prevTicks / 1000.0f));

		//std::cout << (float) (lastTicks / 1000.0f) - (float) prevTicks/  1000.0f  << std::endl;
		accumulator += dt;
		prevTicks = SDL_GetTicks();
		
		while(accumulator >= TIME_STEP) {
			handleEvents();
			for (Entity* e : this-> entities) {
				e->update(dt);
			}
			accumulator -= TIME_STEP;
		}

		window.clear();
		for (Entity* e : this->entities) {
			window.render(*e);
		}
		window.display();
		
		int minimum = 1000 / window.getRefreshRate(); //milliseconds
		int fTicks = SDL_GetTicks() - lastTicks;
		if (fTicks < minimum) {
			SDL_Delay(minimum - fTicks);
		}
	}
	
	std::cout << "game Is Not Running!!" << std::endl;
	window.cleanUp();
	SDL_Quit();
}

void Game::handleEvents() {
	while(SDL_PollEvent(&ev)) {
		if (ev.type == SDL_EVENT_QUIT) {
			gameIsRunning = false;
		}
	}

	const bool* kEvent = SDL_GetKeyboardState(NULL);
	for (Entity* e : this->entities) {
		e->reactTo(kEvent);
	}
}

Game::~Game() {
	for (Entity* e : this->entities) {
		delete e;
	}
}
