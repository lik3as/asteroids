#include "Engine.hpp"

Engine::Engine(const char* title)
:window(title, WINDOW_WIDTH, WINDOW_HEIGHT), player(NULL){
	SDL_Texture* tex = window.loadTexture("res/gfx/spaceship.png");
	player = Player(tex);

	gameIsRunning = true;
}

void Engine::run() {
	float accumulator = 0.0f;
	Uint64 prevTicks = SDL_GetTicks();

	while (gameIsRunning) {
		Uint64 lastTicks = SDL_GetTicks();
		float dt = (float) (lastTicks - prevTicks) / 100.0f;

		prevTicks = SDL_GetTicks();
		accumulator += dt;
	
		while(accumulator >= TIME_STEP) {
			handleEvents();
			update(dt);
			accumulator -= TIME_STEP;
		}

		window.clear();
		window.render(player);
		window.display();
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
	player.speed = Vector2f(0.0f, 0.0f);

	if (kEvent[SDL_SCANCODE_UP] || kEvent[SDL_SCANCODE_W]) {
		player.speed = Vector2f(0.0f, -5.0f);
	}
	if (kEvent[SDL_SCANCODE_DOWN] || kEvent[SDL_SCANCODE_S]) {
		player.speed = Vector2f(0.0f, 5.0f);
	}
	if (kEvent[SDL_SCANCODE_LEFT] || kEvent[SDL_SCANCODE_A]) {
		player.speed = Vector2f(-5.0f, 0.0f);
	}
	if (kEvent[SDL_SCANCODE_RIGHT] || kEvent[SDL_SCANCODE_D]) {
		player.speed = Vector2f(5.0f, 0.0f);
	}
}

void Engine::update(float dt) {
	std::cout << dt << std::endl;
	player.currentFrame.x += (int) (10 * player.speed.x * dt);
	player.currentFrame.y += (int) (10 * player.speed.y * dt);

	if (player.currentFrame.x < 0) player.currentFrame.x = 0;
	if (player.currentFrame.y < 0) player.currentFrame.y = 0;
	
	if (player.currentFrame.x + player.currentFrame.w > WINDOW_WIDTH) {
		player.currentFrame.x = WINDOW_WIDTH - player.currentFrame.w;
	}
	if (player.currentFrame.y + player.currentFrame.h > WINDOW_HEIGHT) {
		player.currentFrame.y = WINDOW_HEIGHT - player.currentFrame.h;
	}

}
