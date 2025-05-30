#include "Entity.hpp"

Entity::Entity(const Vector2<int>&& cut, SDL_Texture* tex)
:tex(tex){
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
	frame.x = cut.x;
	frame.y = cut.y;
	frame.w = 16;
	frame.h = 16;
}

void Entity::setPos(Vector2<float>&& pos) {
	this->pos = std::move(pos);
}

void Entity::setSprite(int x, int y) {
	this->frame.x = x;
	this->frame.y = y;
}

SDL_Texture* const Entity::getTexture() const {
	return tex;
}

Vector2<float> Entity::getPos() const {
	return pos;
}

const SDL_FRect& Entity::getFrame() const {
	return frame;
}

Entity::~Entity() {}
