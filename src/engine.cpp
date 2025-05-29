#include "Engine.hpp"

RenderWindow Engine::window = RenderWindow("ASTEROIDS V.0", WINDOW_WIDTH, WINDOW_HEIGHT);
bool Engine::gameIsRunning = true;

Engine::Engine()
:player(Vector2f(0.0f, 0.0f), window.loadTexture("res/gfx/spaceship.png")){}

void Engine::run() {
	float accumulator = 0.0f;
	Uint64 prevTicks = SDL_GetTicks();

	while (gameIsRunning) {
		Uint64 lastTicks = SDL_GetTicks();
		float dt = (float) ((lastTicks / 1000.0f) - (prevTicks / 1000.0f));

		//std::cout << (float) (lastTicks / 1000.0f) - (float) prevTicks/  1000.0f  << std::endl;
		accumulator += dt;
		prevTicks = SDL_GetTicks();
	
		while(accumulator >= TIME_STEP) {
			handleEvents();
			update(dt);
			accumulator -= TIME_STEP;
		}

		window.clear();
		window.render(player);
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

void Engine::handleEvents() {
	while(SDL_PollEvent(&ev)) {
		if (ev.type == SDL_EVENT_QUIT) {
			gameIsRunning = false;
		}
	}

	const bool* kEvent = SDL_GetKeyboardState(NULL);
	player.setVelocity(
		Vector2f(
			(15.0f * (kEvent[SDL_SCANCODE_D] - kEvent[SDL_SCANCODE_A])),
			(15.0f * (kEvent[SDL_SCANCODE_W] - kEvent[SDL_SCANCODE_S]) * -1)
		)
	);
}

void Engine::update(float dt) {
	player.setPos(player.getPos() + Vector2f(
		(float) (player.getVelocity().x * dt),
		(float) (player.getVelocity().y * dt)
	));

	if (player.getPos().x < 0) player.setPos(Vector2f(0, player.getPos().y));
	if (player.getPos().y < 0) player.setPos(Vector2f(player.getPos().x, 0));
	
	if ((player.getPos().x * 10) + player.getFrame().w > WINDOW_WIDTH) {
		player.setPos(Vector2f((WINDOW_WIDTH / 10) - player.getFrame().w, player.getPos().y));
	}
	if ((player.getPos().y * 10) + player.getFrame().h > WINDOW_HEIGHT) {
		player.setPos(Vector2f(player.getPos().x, (WINDOW_HEIGHT / 10) - player.getFrame().h));
	}

}
