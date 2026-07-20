#include "Matrix4.hpp"

void Matrix4::Matrix4(){
}

Matrix4 Matrix4::identity(){
	Matrix4 m;

	for(int i = 0; i < 16; i++){
		m.m[i] = 0.0f;
	}
	m.m[0] = 1.0f;
	m.m[5] = 1.0f;
	m.m[10] = 1.0f;
	m.m[15] = 1.0f;
	return m;
}

Matrix4 operator*(const Matrix4 &other) const{
	Matrix4 m;
	int result;

	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			result = 0;
			for(int k = 0; k < 4; k++){
				result += this->m[row * 4 + k] * other.m[k * 4 + col];
			}
			m.m[row * 4 + col] = result;
		}
	}
	return m;
}

Vector3 operator*(const Vector3 &other) const{
	Vector3 v;
	v.x = this->m[0] * other.x + this->m[1] * other.y + this->m[2] * other.z + this->m[3];
	v.y = this->m[4] * other.x + this->m[5] * other.y + this->m[6] * other.z + this->m[7];
	v.z = this->m[8] * other.x + this->m[9] * other.y + this->m[10] * other.z + this->m[11];
	return v;
}