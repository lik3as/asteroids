#ifndef MATH
#define MATH

#include <iostream>

template <typename T>
class Vector2 {
	public:
		T x, y;
		Vector2<T>()
		: x(0.0f), y(0.0f){}
		Vector2<T>(T x, T y)
		: x(x), y(y){}
		Vector2<T>(const Vector2<T>& vec)
		: x(vec.x), y(vec.y) {}
		
		Vector2<T> operator+(const Vector2<T>& vec) {
			Vector2<T> res;
			res.x = x + vec.x;
			res.y = y + vec.y;
			return res;
		}

		Vector2<T> operator*(int&& scalar) {
			Vector2<T> res;
			res.x = x * scalar;
			res.y = y * scalar;
			return res;
		}

		Vector2<T> operator/(int&& scalar) {
			Vector2<T> res;
			res.x = x / scalar;
			res.y = y / scalar;
			return res;
		}

		Vector2<T>& operator=(Vector2<T>&& vec) {
			this->x = vec.x;
			this->y = vec.y;

			return *this;
		}

		bool operator==(const Vector2<T>& vec) {
			return (this->x == vec.x && this->y == vec.y);
		}

		void print() {
			std::cout << x << ", " << y << std::endl;
		}
		
};

#endif
