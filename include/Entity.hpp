#ifndef ENTITY
#define ENTITY

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include "Constants.hpp"
#include "Math.hpp"

typedef struct {
	Point<float> min;
	Point<float> max;
} BoundingBox;

class Entity {
	public:
		Entity(int cropX, int cropY, SDL_Texture* tex);
		virtual void update(float dt) = 0;
		virtual void reactToEvent(const bool* kEvent) = 0;

		void setPos(Vector2<float>&& pos);
		Vector2<float> getPos() const;
		SDL_Texture* const getTexture() const;
		SDL_FRect getFrame() const;
		SDL_FRect getSFrame() const;

		BoundingBox bb;
		double rotation = 0.0f;

		virtual ~Entity();
	protected:
		virtual void updateBB();
		void setSprite(int x, int y);
	private:
		SDL_FRect frame;
		Vector2<float> pos;
		SDL_Texture* tex;
		
};

#endif
