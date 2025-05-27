#ifndef RENDERWINDOW
#define RENDERWINDOW

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <Entity.hpp>

class RenderWindow {
	public:
		RenderWindow(const char* title, int w, int h);
		SDL_Texture* loadTexture(const char* filepath);
		void render(const Entity& e);
		void cleanUp();
		void clear();
		void display();
	private:
		int w, h;
		SDL_Window *window;
		SDL_Renderer *renderer;
};

#endif
