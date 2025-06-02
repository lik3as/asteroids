#ifndef COLLIDER
#define COLLIDER

#include "Entity.hpp"

class ICollider {
	public:
		virtual void AABB(const Entity&) = 0;
		virtual ~ICollider() {};
};

#endif
