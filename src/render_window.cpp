#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int w, int h)
: w(w), h(h) {
	window = SDL_CreateWindow(title, w, h, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer || !window)
		throw SDL_GetError();
}

SDL_Texture* RenderWindow::loadTexture(const char* filepath) {
	SDL_Texture* tex = IMG_LoadTexture(renderer, filepath);

	if (!tex) 
		throw SDL_GetError();

	return tex;
}

void RenderWindow::render(const Entity& e) {
	SDL_FRect src;
	src = e.getFrame();

	SDL_FRect dst;
	dst.x = e.getPos().x * 8;
	dst.y = e.getPos().y * 8;
	dst.w = e.getFrame().w * 8;
	dst.h = e.getFrame().h * 8;
	SDL_RenderTexture(renderer, e.getTexture(), &src, &dst);
}

void RenderWindow::cleanUp() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

int RenderWindow::getRefreshRate() {
	int displayID = SDL_GetDisplayForWindow(window);
	const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(displayID);

	return mode->refresh_rate;
}
