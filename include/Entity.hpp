#ifndef ENTITY
#define ENTITY

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "Math.hpp"

class Entity {
	public:
		Entity(const Vector2<int>&& cut, SDL_Texture* tex);
		virtual void update(float dt) = 0;
		virtual void reactTo(const bool* kEvent) = 0;

		void setPos(Vector2<float>&& pos);
		Vector2<float> getPos() const;
		SDL_Texture* const getTexture() const;
		const SDL_FRect& getFrame() const;

		virtual ~Entity();
	protected:
		void setSprite(int x, int y);
	private:
		SDL_FRect frame;
		Vector2<float> pos;
		SDL_Texture* tex;
		
};

#endif
