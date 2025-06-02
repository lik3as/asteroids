#include "Game.hpp"

RenderWindow Game::window = RenderWindow("ASTEROIDS V.0", WINDOW_WIDTH, WINDOW_HEIGHT);
std::vector<Entity*> Game::entities = {};

bool Game::gameIsRunning = true;

Game::Game()
{	
	entities.push_back(
		new Player(0, 0, window.loadTexture("res/gfx/spaceship.png"))//already an rvalue!
	);

	auto asteroid = new Asteroid(0,0, window.loadTexture("res/gfx/asteroid.png"));
	asteroid->setPos(Vector2<float>(WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2));
	entities.push_back(
			std::move(asteroid)
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

			for (Entity* e : this->entities) {
				ICollider* col = dynamic_cast<ICollider*>(e); //upcasting
				if (col){
					handleCollisions(*col);
				}
				e->update(dt);
			}
			accumulator -= TIME_STEP;
		}

		window.clear();

		char buf[7];
		gcvt(dt, 5, buf);
		window.debug(buf, 10.0f, 10.0f);

		for (Entity* e : this->entities) {
			if(e->rotation != 0.0f) {
				window.render(*e, e->rotation); //using SDL_RenderTextureRotated -> more cpu
			} else {
				window.render(*e); //less cpu usage SDL_RenderTexture
			}
			char bufX[20];
			char bufY[20];
			bufX[0] = 'X';
			bufX[1] = ':';
			bufX[2] = ' ';
			gcvt(e->getPos().x, 7, &bufX[3]);
			bufY[0] = 'Y';
			bufY[1] = ':';
			bufY[2] = ' ';
			gcvt(e->getPos().y, 7, &bufY[3]);
			window.debug(bufX, 10.0f,20.0f);
			window.debug(bufY, 10.0f,30.0f);
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

void Game::handleCollisions(ICollider& col) {
	for (Entity* e : entities) {
		ICollider* colB = dynamic_cast<ICollider*>(e);
		if (colB && &col != colB) {
			col.AABB(*e);
		}
	}
}

void Game::handleEvents() {
	while(SDL_PollEvent(&ev)) {
		if (ev.type == SDL_EVENT_QUIT) {
			gameIsRunning = false;
		}
	}

	const bool* kEvent = SDL_GetKeyboardState(NULL);
	for (Entity* e : this->entities) {
		e->reactToEvent(kEvent);
	}
}

Game::~Game() {
	for (Entity* e : this->entities) {
		delete e;
	}
}
