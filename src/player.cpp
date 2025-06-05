#include "Player.hpp"

void Player::setVelocity(Vector2<float>&& p_vec) {
	this->velocity = std::move(p_vec);
	
	p_vec.x = 0;
	p_vec.y = 0;	
}

template <typename T>
void Player::setVelocity(T x, T y) {
	this->velocity.x = x;
	this->velocity.y = y;
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
	
	//natural deceleration
	if (this->getVelocity().x > 0) {
		this->setVelocity<float>(
			this->getVelocity().x - 1.0f,
			this->getVelocity().y
		);
	} else if (this->getVelocity().x < 0){
		this->setVelocity<float>(
			this->getVelocity().x + 1.0f,
			this->getVelocity().y
		);
	}
	if (this->getVelocity().y > 0) {
		this->setVelocity<float>(
			this->getVelocity().x,
			this->getVelocity().y - 1.0f
		);

	} else if (this->getVelocity().y < 0) {
		this->setVelocity<float>(
			this->getVelocity().x,
			this->getVelocity().y + 1.0f
		);
	}

	//max velocity
	if (fabs(this->getVelocity().x) > MAX_SPEED) {
		if (this->getVelocity().x > 0) {
			this->setVelocity<float>(
				this->getVelocity().x - (fabs(this->getVelocity().x) - MAX_SPEED),
				this->getVelocity().y
			);
		}
		else {
			this->setVelocity<float>(
				this->getVelocity().x + (fabs(this->getVelocity().x) - MAX_SPEED),
				this->getVelocity().y
			);
		}
	}
	//max velocity
	if (fabs(this->getVelocity().y) > MAX_SPEED) {
		if (this->getVelocity().y > 0) {
			this->setVelocity<float>(
				this->getVelocity().x,
				this->getVelocity().y - (fabs(this->getVelocity().y) - MAX_SPEED)
			);
		}
		else {
			this->setVelocity<float>(
				this->getVelocity().x,
				this->getVelocity().y + (fabs(this->getVelocity().y) - MAX_SPEED)
			);
		}
	}
}

void Player::reactToEvent(const bool* kEvent) {
	this->shooting = kEvent[SDL_SCANCODE_SPACE];

	/** TODO FIND A WAY TO DECELERATE THE PLAYER **/

	this->setVelocity(
		Vector2<float>(
			this->getVelocity().x + (100.0f * (kEvent[SDL_SCANCODE_D] - kEvent[SDL_SCANCODE_A])),
			this->getVelocity().y + (-100.0f * (kEvent[SDL_SCANCODE_W] - kEvent[SDL_SCANCODE_S]))
		)
	);
	this->updateSprite(kEvent);
}

void Player::AABB(const Entity& e) {
	if (
			this->bb.min.x < e.bb.max.x //true
			&& this->bb.max.x > e.bb.min.x //false!!
			&& this->bb.min.y < e.bb.max.y
			&& this->bb.max.y > e.bb.min.y
	) {
		if (this->bb.min.x < e.bb.min.x) {
			//std::cout << "collision from left" << std::endl;
			this->setVelocity(
				Vector2<float>(
					- fabs(this->getVelocity().x),
					this->getVelocity().y
				)
			);
		}
		else {
			this->setVelocity(
				Vector2<float>(
					+ fabs(this->getVelocity().x),
					this->getVelocity().y
				)
			);

		}
		if (this->bb.max.y < e.bb.max.y) {
			this->setVelocity(
				Vector2<float>(
					this->getVelocity().x,
					- fabs(this->getVelocity().y)
				)
			);
		}
		else {
			this->setVelocity(
				Vector2<float>(
					this->getVelocity().x,
					+ fabs(this->getVelocity().y)
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

void Player::updateSprite(const bool* kEvent) {
	int x = 0;
	auto& vel = this->velocity;

	/** TODO: CREATE ANOTHER METHOD TO UPDATE THE SPRITE **/
	bool pressingWASD = kEvent[SDL_SCANCODE_W] || kEvent[SDL_SCANCODE_A]
		|| kEvent[SDL_SCANCODE_S] || kEvent[SDL_SCANCODE_D];

	if (kEvent[SDL_SCANCODE_W]) {
		rotation = 0.0f;
		x = 32;
	}
	if (kEvent[SDL_SCANCODE_A]) {
		rotation = -90.0f;
		x = 32;
	}
	if (kEvent[SDL_SCANCODE_S]) {
		x = 32;
		rotation = 180.0f;
	}
	if (kEvent[SDL_SCANCODE_D]) {
		rotation = 90.0f;
		x = 32;
	}
	if (kEvent[SDL_SCANCODE_A] && kEvent[SDL_SCANCODE_W]) {
		rotation = -45.0f;
	}
	if (kEvent[SDL_SCANCODE_D] && kEvent[SDL_SCANCODE_W]) {
		rotation = 45.0f;
	}
	if (kEvent[SDL_SCANCODE_S] && kEvent[SDL_SCANCODE_A]) {
		x = 32;
		rotation = 180.0f + 45.0f;
	}
	if (kEvent[SDL_SCANCODE_S] && kEvent[SDL_SCANCODE_D]) {
		x = 32;
		rotation = 180.0f - 45.0f;
	}
	/**
	if (!pressingWASD) {
		x = 0;
		rotation = 0;
	}
	**/

	x += (this->shooting * 16);
	this->setSprite(x, 0);

}
