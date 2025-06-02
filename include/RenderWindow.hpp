#ifndef RENDERWINDOW
#define RENDERWINDOW

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include "Constants.hpp"
#include "Entity.hpp"

class RenderWindow {
	public:
		RenderWindow(const char* title, int w, int h);
		SDL_Texture* loadTexture(const char* filepath);
		void render(const Entity& e);
		void render(const Entity& e, const double& angle);
		void cleanUp();
		void clear();
		void display();
		void debug(const char* str, float x, float y);
		int getRefreshRate();
	private:
		int w, h;
		SDL_Window *window;
		SDL_Renderer *renderer;
};

#endif
