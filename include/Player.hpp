#ifndef PLAYER
#define PLAYER

#include "Entity.hpp"
#include "Math.hpp"

class Player : public Entity {
	public:
		using Entity::Entity;
		bool shooting = false;
		void setVelocity(Vector2f&& vec);
		const Vector2f& getVelocity() const;
	private:
		Vector2f velocity;
};

#endif
