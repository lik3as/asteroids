#include "Player.hpp"

void Player::setVelocity(Vector2<float>&& m_vec) {
	this->velocity = std::move(m_vec);
	
	m_vec.x = 0;
	m_vec.y = 0;
	
	int x = 0;
	auto& vel = this->velocity;	
	if (
		 vel == (Vector2<float>(fabs(vel.x), - fabs(vel.y)))
		|| vel == (Vector2<float>(- fabs(vel.x), - fabs(vel.y)))
		|| vel == (Vector2<float>(1.0f, - fabs(vel.y)))
	) {
		//std::cout << this->velocity.y << " up " << std::endl;
		x = 32;
	}
	if (
		vel == (Vector2<float>(0.0f, 0.0f))
		|| vel == (Vector2<float>(0.0f, fabs(vel.y)))
		|| vel == (Vector2<float>(fabs(vel.x), fabs(vel.y)))
		|| vel == (Vector2<float>(- fabs(vel.x), fabs(vel.y)))
	) {
		//std::cout << this->velocity.y << " down " << std::endl;
		x = 0;
	}
	x += (this->shooting * 16);
	this->setSprite(x, 0);
}

const Vector2<float>& Player::getVelocity() const {
	return this->velocity;
}

void Player::update(float dt) {
	this->setPos(this->getPos() + Vector2<float>(
		(float) (this->getVelocity().x * dt),
		(float) (this->getVelocity().y * dt)
	));

	if (this->getPos().x < 0) this->setPos(Vector2<float>(0, this->getPos().y));
	if (this->getPos().y < 0) this->setPos(Vector2<float>(this->getPos().x, 0));
	
	if ((this->getPos().x * 10) + this->getFrame().w > WINDOW_WIDTH) {
		this->setPos(Vector2<float>((WINDOW_WIDTH / 10) - this->getFrame().w, this->getPos().y));
	}
	if ((this->getPos().y * 10) + this->getFrame().h > WINDOW_HEIGHT) {
		this->setPos(Vector2<float>(this->getPos().x, (WINDOW_HEIGHT / 10) - this->getFrame().h));
	}	
}

void Player::reactTo(const bool* kEvent) {
	this->shooting = kEvent[SDL_SCANCODE_SPACE];
	this->setVelocity(
		Vector2<float>(
			(15.0f * (kEvent[SDL_SCANCODE_D] - kEvent[SDL_SCANCODE_A])),
			(-15.0f * (kEvent[SDL_SCANCODE_W] - kEvent[SDL_SCANCODE_S]))
		)
	);	
}

Player::~Player() {
	std::cout << "Destroying Player!" << std::endl;
}
