#ifndef ENTITY
#define ENTITY

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "Math.hpp"

class Entity {
	public:
		Entity(SDL_Texture* tex);
		SDL_Texture* getTexture() const;
		SDL_FRect currentFrame;
	private:
		SDL_Texture* tex;
};

#endif
