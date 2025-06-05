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
		template <typename T>
		void setVelocity(T x, T y);
		const Vector2<float>& getVelocity() const;

		void update(float dt) override;
		void reactToEvent(const bool* kEvent) override;
		void AABB(const Entity&) override;

		~Player();
	private:
		void updateBB() override;
		void updateSprite(const bool* kvent);

		Vector2<float> velocity;
};

#endif
