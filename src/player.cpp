#include "Player.hpp"

void Player::setVelocity(Vector2f&& vec) {
	this->velocity = std::move(vec);

	vec.x = 0;
	vec.y = 0;
}

const Vector2f& Player::getVelocity() const {
	return this->velocity;
}
