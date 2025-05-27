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

		Vector2f operator+(const Vector2f& vec) {
			Vector2f res;
			res.x = x + vec.x;
			res.y = y + vec.y;
			return res;
		}
		
		void print() {
			std::cout << x << ", " << y << std::endl;
		}
		
};

#endif
