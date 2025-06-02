#ifndef COLLIDER
#define COLLIDER

#include "Entity.hpp"

class ICollider {
	public:
		virtual bool checkAABB(const Entity&) const = 0;
		virtual ~ICollider() {};
};

#endif
