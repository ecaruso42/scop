#include "Math/Matrix4.hpp"

Matrix4::Matrix4(){
	for(int i = 0; i < 16; i++)
        m[i] = 0;
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

float& Matrix4::at(int row, int col){
	return m[col * 4 + row];
}

const float& Matrix4::at(int row, int col) const
{
    return m[col * 4 + row];
}

Matrix4 Matrix4::operator*(const Matrix4 &other) const{
	Matrix4 result;

	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			result.at(row, col) = 0.0f;
			for(int k = 0; k < 4; k++){
				result.at(row, col) += at(row, k) * other.at(k, col);
			}
		}
	}
	return result;
}

Vector3 Matrix4::operator*(const Vector3& other) const
{
    Vector3 result;

    result.x = at(0,0) * other.x + at(0,1) * other.y + at(0,2) * other.z + at(0,3);

    result.y = at(1,0) * other.x + at(1,1) * other.y + at(1,2) * other.z + at(1,3);

    result.z = at(2,0) * other.x + at(2,1) * other.y + at(2,2) * other.z + at(2,3);

    return result;
}

Matrix4 Matrix4::translation(const Vector3 &position){
	Matrix4 result = Matrix4::identity();

	result.at(0,3) = position.x;
	result.at(1,3) = position.y;
	result.at(2,3) = position.z;

	return result;
}

Matrix4 Matrix4::scale(const Vector3 &position){
	Matrix4 result = Matrix4::identity();

	result.at(0,0) = position.x;
	result.at(1,1) = position.y;
	result.at(2,2) = position.z;

	return result;
}

Matrix4 Matrix4::rotationX(const float angle){
	Matrix4 result = Matrix4::identity();

	float c = cos(angle);
	float s = sin(angle);

	result.at(1,1) = c;
	result.at(1,2) = -s;

	result.at(2,1) = s;
	result.at(2,2) = c;

	return result;
}

Matrix4 Matrix4::rotationY(const float angle){
	Matrix4 result = Matrix4::identity();

	float c = cos(angle);
	float s = sin(angle);

	result.at(0,0) = c;
    result.at(0,2) = s;

    result.at(2,0) = -s;
    result.at(2,2) = c;

    return result;
}

Matrix4 Matrix4::rotationZ(const float angle){
	Matrix4 result = Matrix4::identity();

	float c = cos(angle);
	float s = sin(angle);

	result.at(0,0) = c;
    result.at(0,1) = -s;

    result.at(1,0) = s;
    result.at(1,1) = c;

    return result;
}

static Matrix4 perspective(float fov, float aspect, float near, float far){

}

static Matrix4 lookAt(const Vector3 &eye, const Vector3 &center, const Vector3 &up){
	
}