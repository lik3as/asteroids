#ifndef PLAYER
#define PLAYER

#include "Entity.hpp"
#include "Math.hpp"

class Player : public Entity {
	public:
		using Entity::Entity;
		Vector2f velocity;
	private:
};

#endif
