#include "Entity.hpp"

Entity::Entity(const Vector2f&& cut, SDL_Texture* tex)
:tex(tex){
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
	frame.x = 0;
	frame.y = 0;
	frame.w = 16;
	frame.h = 16;
}

void Entity::setPos(Vector2f pos) {
	this->pos = pos;
}

void Entity::setSprite(int x, int y) {
	this->frame.x = x;
	this->frame.y = y;
}

SDL_Texture* const Entity::getTexture() const {
	return tex;
}

Vector2f Entity::getPos() const {
	return pos;
}

const SDL_FRect& Entity::getFrame() const {
	return frame;
}
