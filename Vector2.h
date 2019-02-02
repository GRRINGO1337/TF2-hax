#pragma once
#include "Vector.h"

class Vector2
{
public:
	float x = 0, y = 0;
	Vector2() {}
	Vector2(float _x, float _y)
	{
		x = _x, y = _y;
	}

	float operator[](int i) const;
	float& operator[](int i);

	bool operator==(const Vector2& src) const;
	bool operator!=(const Vector2& src) const;

	__forceinline Vector2&	operator+=(float fl);
	__forceinline Vector2&	operator-=(float fl);

	__forceinline Vector2&	operator+=(const Vector2 &v);
	Vector2	operator+(const Vector2& v) const;

	Vector2& operator=(const Vector2 &vOther);
};

inline float Vector2::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
inline float& Vector2::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline bool Vector2::operator==(const Vector2& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y);
}
inline bool Vector2::operator!=(const Vector2& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y);
}

__forceinline Vector2&	Vector2::operator+=(float fl)
{
	x += fl;
	y += fl;
	CHECK_VALID(*this);
	return *this;
}

__forceinline  Vector2& Vector2::operator+=(const Vector2& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y;
	return *this;
}

inline Vector2 Vector2::operator+(const Vector2& v) const
{
	Vector2 res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}
//===============================================
__forceinline Vector2&	Vector2::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	CHECK_VALID(*this);
	return *this;
}

inline Vector2& Vector2::operator=(const Vector2 &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y;
	return *this;
}