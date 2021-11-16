#pragma once

struct Vec2
{
	Vec2();
	Vec2(const Vec2& other);
	Vec2(float x, float y);

	float GetMagnitude();

	void operator=(const Vec2& other);
	bool operator==(const Vec2& other);
	bool operator!=(const Vec2& other);

	static Vec2 Add(const Vec2& vec1, const Vec2& vec2);
	static Vec2 Add(const Vec2& vec1, float value);
	static Vec2 Subtract(const Vec2& vec1, const Vec2& vec2);
	static Vec2 Subtract(const Vec2& vec1, float value);
	static Vec2 Multiply(const Vec2& vec1, const Vec2& vec2);
	static Vec2 Multiply(const Vec2& vec1, float value);
	static Vec2 Divide(const Vec2& vec1, const Vec2& vec2);
	static Vec2 Divide(const Vec2& vec1, float value);

	static float GetDistance(const Vec2& vec1, const Vec2& vec2);

	Vec2 operator+(const Vec2& other);
	Vec2 operator+(float value);

	Vec2 operator-(const Vec2& other);
	Vec2 operator-(float value);

	Vec2 operator*(const Vec2& other);
	Vec2 operator*(float value);

	Vec2 operator/(const Vec2& other);
	Vec2 operator/(float value);

	void operator+=(const Vec2& other);
	void operator+=(float value);

	void operator-=(const Vec2& other);
	void operator-=(float value);

	void operator*=(const Vec2& other);
	void operator*=(float value);

	void operator/=(const Vec2& other);
	void operator/=(float value);

	float x, y;
};

