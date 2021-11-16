#include "Vec2.h"
#include "Math.h"

Vec2::Vec2() : x(0.0f), y(0.0f)
{
}

Vec2::Vec2(const Vec2& other)
{
    x = other.x;
    y = other.y;
}

Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

float Vec2::GetMagnitude()
{
    return Vec2::GetDistance({ 0.0f, 0.0f }, *this);
}

void Vec2::operator=(const Vec2& other)
{
    x = other.x;
    y = other.y;
}

bool Vec2::operator==(const Vec2& other)
{
    return x == other.x && y == other.y;
}

bool Vec2::operator!=(const Vec2& other)
{
    return !operator==(other);
}

Vec2 Vec2::Add(const Vec2& vec1, const Vec2& vec2)
{
    Vec2 result(vec1);
    result.x += vec2.x;
    result.y += vec2.y;
    return result;
}

Vec2 Vec2::Add(const Vec2& vec1, float value)
{
    Vec2 result(vec1);
    result.x += value;
    result.y += value;
    return result;
}

Vec2 Vec2::Subtract(const Vec2& vec1, const Vec2& vec2)
{
    Vec2 result(vec1);
    result.x -= vec2.x;
    result.y -= vec2.y;
    return result;
}

Vec2 Vec2::Subtract(const Vec2& vec1, float value)
{
    Vec2 result(vec1);
    result.x -= value;
    result.y -= value;
    return result;
}

Vec2 Vec2::Multiply(const Vec2& vec1, const Vec2& vec2)
{
    Vec2 result(vec1);
    result.x *= vec2.x;
    result.y *= vec2.y;
    return result;
}

Vec2 Vec2::Multiply(const Vec2& vec1, float value)
{
    Vec2 result(vec1);
    result.x *= value;
    result.y *= value;
    return result;
}

Vec2 Vec2::Divide(const Vec2& vec1, const Vec2& vec2)
{
    Vec2 result(vec1);
    result.x /= vec2.x;
    result.y /= vec2.y;
    return result;
}

Vec2 Vec2::Divide(const Vec2& vec1, float value)
{
    Vec2 result(vec1);
    result.x /= value;
    result.y /= value;
    return result;
}

float Vec2::GetDistance(const Vec2& vec1, const Vec2& vec2)
{
    return Math::Sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y));
}

Vec2 Vec2::operator+(const Vec2& other)
{
    return Add(*this, other);
}

Vec2 Vec2::operator+(float value)
{
    return Add(*this, value);
}

Vec2 Vec2::operator-(const Vec2& other)
{
    return Subtract(*this, other);
}

Vec2 Vec2::operator-(float value)
{
    return Subtract(*this, value);
}

Vec2 Vec2::operator*(const Vec2& other)
{
    return Multiply(*this, other);
}

Vec2 Vec2::operator*(float value)
{
    return Multiply(*this, value);
}

Vec2 Vec2::operator/(const Vec2& other)
{
    return Divide(*this, other);
}

Vec2 Vec2::operator/(float value)
{
    return Divide(*this, value);
}

void Vec2::operator+=(const Vec2& other)
{
    *this = Add(*this, other);
}

void Vec2::operator+=(float value)
{
    *this = Add(*this, value);
}

void Vec2::operator-=(const Vec2& other)
{
    *this = Subtract(*this, other);
}

void Vec2::operator-=(float value)
{
    *this = Subtract(*this, value);
}

void Vec2::operator*=(const Vec2& other)
{
    *this = Multiply(*this, other);
}

void Vec2::operator*=(float value)
{
    *this = Multiply(*this, value);
}

void Vec2::operator/=(const Vec2& other)
{
    *this = Divide(*this, other);
}

void Vec2::operator/=(float value)
{
    *this = Divide(*this, value);
}
