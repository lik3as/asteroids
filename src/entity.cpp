#include "Entity.hpp"

Entity::Entity(int cropX, int cropY, SDL_Texture* tex)
:tex(tex){
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
	frame.x = cropX;
	frame.y = cropY;
	frame.w = 16;
	frame.h = 16;
	bb.min = Point<float>(getPos().x,getPos().y);
	bb.max = Point<float>(getPos().x + getSFrame().w, getPos().y + getSFrame().h);
}

void Entity::setPos(Vector2<float>&& pos) {
	this->pos = std::move(pos);
	updateBB();
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

SDL_FRect Entity::getFrame() const {
	return frame;
}

SDL_FRect Entity::getSFrame() const {
	SDL_FRect rect = frame;
	rect.w *= PIXEL_SCALE;
	rect.h *= PIXEL_SCALE;
	return rect;
}

void Entity::updateBB() {	
	bb.min = Point<float>(
			getPos().x,
			getPos().y
			);
	bb.max = Point<float>(
			getPos().x + getSFrame().w,
			getPos().y + getSFrame().h
			);
}

Entity::~Entity() {}
