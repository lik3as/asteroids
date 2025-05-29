#ifndef ENTITY
#define ENTITY

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "Math.hpp"

class Entity {
	public:
		Entity(const Vector2f&& cut, SDL_Texture* tex);
		void setPos(Vector2f&& pos);
		void setSprite(int x, int y);
		SDL_Texture* const getTexture() const;
		Vector2f getPos() const;
		const SDL_FRect& getFrame() const;
	private:
		SDL_FRect frame;
		Vector2f pos;
		SDL_Texture* tex;
		
};

#endif
