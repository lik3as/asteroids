#ifndef MATH
#define MATH

#include <iostream>

typedef enum Direction {
	REST,
	UP,
	DOWN,
	RIGHT,
	LEFT,
} Direction;

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

		bool tendingTo(Direction d) {
			switch (d) {
				case REST:
					return this->x == 0 && this->y == 0;
				case UP:
					return this->y < 0;
				case DOWN:
					return this->y > 0;
				case LEFT:
					return this->x < 0;
				case RIGHT:
					return this->x > 0;
			}
		}
		
		Vector2<T> operator+(const Vector2<T>& vec) {
			Vector2<T> res;
			res.x = x + vec.x;
			res.y = y + vec.y;
			return res;
		}

		Vector2<T> operator*(int&& scalar) {
			Vector2<T> res;
			res.x = (T) x * scalar;
			res.y = (T) y * scalar;
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

template <typename T>
class Point  {
	public:
		T x, y;
		Point<T>()
		: x(0), y(0){}
		Point<T>(T x, T y)
		: x(x), y(y){}
		Point<T>(const Point<T>& point)
		: x(point.x), y(point.y) {}
		
		Point<T>& operator=(Point<T>&& vec) {
			this->x = vec.x;
			this->y = vec.y;

			return *this;
		}

		bool operator==(const Point<T>& point) {
			return (this->x == point.x && this->y == point.y);
		}

		void print() {
			std::cout << x << ", " << y << std::endl;
		}
		
};

#endif
