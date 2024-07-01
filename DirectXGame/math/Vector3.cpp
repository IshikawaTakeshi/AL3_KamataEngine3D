#include "Vector3.h"
#include "MyMath/MyMath.h"


//===============================================================
//		二項演算子
//===============================================================

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	return MyMath::Add(v1, v2);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	return MyMath::Subtract(v1, v2);
}

Vector3 operator*(float s, const Vector3& v) {
	return MyMath::Multiply(s, v);
}

Vector3 operator*(const Vector3& v, float s) {
	return s * v;
}

Vector3 operator/(float s, const Vector3& v) {
	return MyMath::Multiply(1.0f / s, v);
}

Vector3 operator/(const Vector3& v, float s) {
	return s / v;
}

//===============================================================
//		複合代入演算子
//===============================================================

Vector3 Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 Vector3::operator*=(float s) {
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3 Vector3::operator/=(float s) {
	x /= s;
	y /= s;
	z /= s;
	return *this;
}