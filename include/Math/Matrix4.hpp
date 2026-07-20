#pragma once

#include "Vector3.hpp"

#include <cmath>

class Matrix4 {
	public:
		float m[16];

	private:
		void Matrix4();
		static Matrix4 identity();

		Matrix4 operator*(const Matrix4 &other) const;
		Vector3 operator*(const Vector3 &other) const;
};