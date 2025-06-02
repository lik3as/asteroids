#ifndef PLAYER
#define PLAYER

#include <cmath>

#include "Entity.hpp"
#include "Math.hpp"
#include "Collider.hpp"

class Player : public Entity, public ICollider {
	public:
		using Entity::Entity;
		bool shooting = false;
		void setVelocity(Vector2<float>&& vec);
		const Vector2<float>& getVelocity() const;
		void update(float dt) override;
		void reactToEvent(const bool* kEvent) override;
		bool checkAABB(const Entity&) const override;

		~Player();
	private:
		void updateBB() override;

		Vector2<float> velocity;
};

#endif
