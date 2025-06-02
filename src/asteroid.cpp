#include "Asteroid.hpp"

void Asteroid::update(float dt) {
}

void Asteroid::reactToEvent(const bool* kEvent) {

}

bool Asteroid::checkAABB(const Entity& e) const {
		//std::cout << "maxBY: " << e.getPos().y << " minAY: " << this->getPos().y - this->getSFrame().h << std::endl;
	if (
			this->bb.min.x < e.bb.max.x //true
			&& this->bb.max.x > e.bb.min.x //false!!
			&& this->bb.min.y < e.bb.max.y
			&& this->bb.max.y > e.bb.min.y
	) {
		//std::cout << "asteroid: " << bb.min.x << ", " << bb.max.x << std::endl;
		//std::cout << "player: " << e.bb.min.x << ", " << e.bb.max.x << std::endl;
		std::cout << "collision" << std::endl;
		return true;
	}
	return false;
}
