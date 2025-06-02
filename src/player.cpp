#include "Player.hpp"

void Player::setVelocity(Vector2<float>&& p_vec) {
	this->velocity = std::move(p_vec);
	
	p_vec.x = 0;
	p_vec.y = 0;
	
	int x = 0;
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
	
	if ((this->getPos().x) + this->getSFrame().w > WINDOW_WIDTH) {
		this->setPos(
			Vector2<float>(WINDOW_WIDTH - this->getSFrame().w, this->getPos().y)
		);
	}
	if ((this->getPos().y) + this->getSFrame().h > WINDOW_HEIGHT) {
		this->setPos(
			Vector2<float>(this->getPos().x, (WINDOW_HEIGHT) - this->getSFrame().h)
		);
	}	
}

void Player::reactToEvent(const bool* kEvent) {
	this->shooting = kEvent[SDL_SCANCODE_SPACE];
	this->setVelocity(
		Vector2<float>(
			(100.0f * (kEvent[SDL_SCANCODE_D] - kEvent[SDL_SCANCODE_A])),
			(-100.0f * (kEvent[SDL_SCANCODE_W] - kEvent[SDL_SCANCODE_S]))
		)
	);	
}

void Player::AABB(const Entity& e) {
	if (
			this->bb.min.x < e.bb.max.x //true
			&& this->bb.max.x > e.bb.min.x //false!!
			&& this->bb.min.y < e.bb.max.y
			&& this->bb.max.y > e.bb.min.y
	) {
		if (this->bb.min.x < e.bb.min.x) {
			std::cout << "collision from left" << std::endl;
			this->setVelocity(
				Vector2<float>(
					- fabs(this->getVelocity().x * 1.5),
					this->getVelocity().y
				)
			);
		}
		else {
			this->setVelocity(
				Vector2<float>(
					+ fabs(this->getVelocity().x * 1.5),
					this->getVelocity().y
				)
			);

		}
		if (this->bb.max.y < e.bb.max.y) {
			this->setVelocity(
				Vector2<float>(
					this->getVelocity().x,
					- fabs(this->getVelocity().y * 1.5)
				)
			);
		}
		else {
			this->setVelocity(
				Vector2<float>(
					this->getVelocity().x,
					+ fabs(this->getVelocity().y * 1.5)
				)
			);

		}
	}

}

Player::~Player() {
	std::cout << "Destroying Player!" << std::endl;
}

void Player::updateBB() {
	auto& vel = this->velocity;
	auto resetBB = [&] () -> void {
		this->bb.min = Point<float>(this->getPos().x, this->getPos().y);
		this->bb.max = Point<float>(
				this->getPos().x + this->getSFrame().w,
				this->getPos().y + this->getSFrame().h
				);
	};

	if (vel.tendingTo(UP)) {
		this->bb.min = Point<float>(
				this->getPos().x,
				this->getPos().y + (7 * PIXEL_SCALE)
				);
		this->bb.max = Point<float>(
				this->getPos().x + this->getSFrame().w,
				this->getPos().y + this->getSFrame().h
				);
	}
	if (vel.tendingTo(RIGHT)) {
		this->bb.min = Point<float>(this->getPos().x, this->getPos().y);
		this->bb.max = Point<float>(
				this->getPos().x + this->getSFrame().w - (7 * PIXEL_SCALE),
				this->getPos().y + this->getSFrame().h
				);
	}
	if (vel.tendingTo(RIGHT) && vel.tendingTo(UP)) {
		resetBB();
	}
	if (vel.tendingTo(LEFT)) {
		this->bb.min = Point<float>(
				this->getPos().x + (7 * PIXEL_SCALE),
				this->getPos().y
				);
		this->bb.max = Point<float>(
				this->getPos().x + this->getSFrame().w,
				this->getPos().y + this->getSFrame().h
				);
	}
	if (vel.tendingTo(LEFT) && vel.tendingTo(UP)) {
		resetBB();
	}
	if (vel.tendingTo(DOWN)) {
		this->bb.min = Point<float>(this->getPos().x, this->getPos().y);
		this->bb.max = Point<float>(
				this->getPos().x + this->getSFrame().w,
				this->getPos().y + this->getSFrame().h - (7 * PIXEL_SCALE)
				);
	}
	if (vel.tendingTo(DOWN) && vel.tendingTo(LEFT)) {
		resetBB();
	}
	if (vel.tendingTo(DOWN) && vel.tendingTo(RIGHT)) {
		resetBB();
	}
	
}
