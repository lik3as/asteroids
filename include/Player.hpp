#ifndef PLAYER
#define PLAYER

#include <cmath>

#include "Constants.hpp"
#include "Entity.hpp"
#include "Math.hpp"

class Player : public Entity {
	public:
		using Entity::Entity;
		bool shooting = false;
		void setVelocity(Vector2<float>&& vec);
		const Vector2<float>& getVelocity() const;
		void update(float dt) override;
		void reactTo(const bool* kEvent) override;

		~Player();
	private:
		Vector2<float> velocity;
};

#endif
