#ifndef ASTEROID
#define ASTEROID

#include "Entity.hpp"
#include "Collider.hpp"
#include "Constants.hpp"

class Asteroid : public Entity, public ICollider {
	public:
		using Entity::Entity;
		void update(float dt) override;
		void reactToEvent(const bool* kEvent) override;
		bool checkAABB(const Entity&) const override;
		~Asteroid(){}
};

#endif
