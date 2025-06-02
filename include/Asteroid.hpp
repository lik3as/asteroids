#ifndef ASTEROID
#define ASTEROID

#include <Entity.hpp>

class Asteroid : public Entity {
	public:
		using Entity::Entity;
		void update(float dt) override;
		void reactToEvent(const bool* kEvent) override;
};

#endif
