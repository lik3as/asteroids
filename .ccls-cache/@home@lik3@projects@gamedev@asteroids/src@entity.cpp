#include "Entity.hpp"

Entity::Entity(SDL_Texture* tex)
:tex(tex){
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 16;
	currentFrame.h = 16;
}

SDL_Texture* Entity::getTexture() const {
	return tex;
}
