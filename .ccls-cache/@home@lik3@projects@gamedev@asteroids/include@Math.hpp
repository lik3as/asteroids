#ifndef MATH
#define MATH

#include <iostream>

class Vector2f {
	public:
		float x, y;
		Vector2f()
		: x(0.0f), y(0.0f){}
		Vector2f(float x, float y)
		: x(x), y(y){}
		inline Vector2f& operator+=(const Vector2f& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}
		
		void print() {
			std::cout << x << ", " << y << std::endl;
		}
		
};

#endif
