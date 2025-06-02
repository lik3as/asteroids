#include "Player.hpp"

void Player::setVelocity(Vector2<float>&& m_vec) {
	this->velocity = std::move(m_vec);
	
	m_vec.x = 0;
	m_vec.y = 0;
	
	int x = 0;
	double roatation = 0;
	auto& vel = this->velocity;

	if (vel.tendingTo(UP)) {
		rotation = 0.0f;
		x = 32;
	}
	if (vel.tendingTo(RIGHT)) {
		rotation = 90.0f;
		x = 32;
	}
	if (vel.tendingTo(RIGHT) && vel.tendingTo(UP)) {
		rotation = 45.0f;
	}
	if (vel.tendingTo(LEFT)) {
		rotation = -90.0f;
		x = 32;
	}
	if (vel.tendingTo(LEFT) && vel.tendingTo(UP)) {
		rotation = -45.0f;
	}
	if (vel.tendingTo(REST)) {
		x = 0;
		rotation = 0;
	}
	if (vel.tendingTo(DOWN)) {
		x = 32;
		rotation = 180.0f;
	}
	if (vel.tendingTo(DOWN) && vel.tendingTo(LEFT)) {
		x = 32;
		rotation = 180.0f + 45.0f;

	}
	if (vel.tendingTo(DOWN) && vel.tendingTo(RIGHT)) {
		x = 32;
		rotation = 180.0f - 45.0f;
	}

	x += (this->shooting * 16);
	this->setSprite(x, 0);
	this->rotation = rotation;
}

const Vector2<float>& Player::getVelocity() const {
	return this->velocity;
}

void Player::update(float dt) {
	this->setPos(this->getPos() + Vector2<float>(
		(float) (this->getVelocity().x * dt),
		(float) (this->getVelocity().y * dt)
	));

	//AABB collision!!!
	if (this->getPos().x < 0) {
		this->setPos(Vector2<float>(0, this->getPos().y));
	}
	if (this->getPos().y < 0) this->setPos(Vector2<float>(this->getPos().x, 0));
	
	if ((this->getPos().x) + this->getFrame().w > WINDOW_WIDTH / PIXEL_SCALE) {
		this->setPos(
			Vector2<float>((WINDOW_WIDTH / PIXEL_SCALE) - this->getFrame().w, this->getPos().y)
		);
	}
	if ((this->getPos().y) + this->getFrame().h > WINDOW_HEIGHT / PIXEL_SCALE) {
		this->setPos(
			Vector2<float>(this->getPos().x, (WINDOW_HEIGHT / PIXEL_SCALE) - this->getFrame().h)
		);
	}	
}

void Player::reactToEvent(const bool* kEvent) {
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
