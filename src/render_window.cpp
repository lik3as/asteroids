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
	dst.x = e.getPos().x * PIXEL_SCALE;
	dst.y = e.getPos().y * PIXEL_SCALE;
	dst.w = e.getFrame().w * PIXEL_SCALE;
	dst.h = e.getFrame().h * PIXEL_SCALE;
	SDL_RenderTexture(renderer, e.getTexture(), &src, &dst);
}

void RenderWindow::render(const Entity& e, const double& angle) {
	SDL_FRect src;
	src = e.getFrame();

	SDL_FRect dst;
	dst.x = e.getPos().x * PIXEL_SCALE;
	dst.y = e.getPos().y * PIXEL_SCALE;
	dst.w = e.getFrame().w * PIXEL_SCALE;
	dst.h = e.getFrame().h * PIXEL_SCALE;
	SDL_RenderTextureRotated(renderer, e.getTexture(), &src, &dst, angle, NULL, SDL_FLIP_NONE);
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

void RenderWindow::debug(const char* str, float x, float y) {
	SDL_SetRenderDrawColor(renderer, 255,0,0,255);
	if(!SDL_RenderDebugText(renderer, x, y, str)) {
		std::cout << "SDL Error while debugging: " << SDL_GetError() << std::endl;
	}
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);

}

int RenderWindow::getRefreshRate() {
	int displayID = SDL_GetDisplayForWindow(window);
	const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(displayID);

	return mode->refresh_rate;
}
