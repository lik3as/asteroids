#include "Asteroid.hpp"

Asteroid::Asteroid(int cropX, int cropY, SDL_Texture* tex)
: Entity(cropX, cropY, tex){
	std::cout << bb.min.x << std::endl;
}

void Asteroid::update(float dt) {
}

void Asteroid::updateBB() {	
	bb.min = Point<float>(
			getPos().x,
			getPos().y
			);
	bb.max = Point<float>(
			getPos().x + getSFrame().w,
			getPos().y + getSFrame().h
			);

	bb.min = Point<float>(bb.min.x + 2 * PIXEL_SCALE, bb.min.y + 2 * PIXEL_SCALE);
	bb.max = Point<float>(bb.max.x - 2 * PIXEL_SCALE, bb.max.y - 2 * PIXEL_SCALE);
	bb.min = Point<float>(bb.min.x + 2 * PIXEL_SCALE, bb.min.y + 2 * PIXEL_SCALE);
	bb.max = Point<float>(bb.max.x - 2 * PIXEL_SCALE, bb.max.y - 2 * PIXEL_SCALE);
}

void Asteroid::reactToEvent(const bool* kEvent) {

}

void Asteroid::AABB(const Entity& e) {
		//std::cout << "maxBY: " << e.getPos().y << " minAY: " << this->getPos().y - this->getSFrame().h << std::endl;
	if (
			this->bb.min.x < e.bb.max.x //true
			&& this->bb.max.x > e.bb.min.x //false!!
			&& this->bb.min.y < e.bb.max.y
			&& this->bb.max.y > e.bb.min.y
	) {
		std::cout << bb.min.x << std::endl;
		//std::cout << "asteroid: " << bb.min.x << ", " << bb.max.x << std::endl;
		//std::cout << "player: " << e.bb.min.x << ", " << e.bb.max.x << std::endl;
	}
}
