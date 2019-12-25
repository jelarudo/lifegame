#include "Vector2.h"

Vector2::Vector2()
{
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2 Vector2::operator + (const Vector2& v)
{
    Vector2 result = Vector2();
    result.x = this->x + v.x;
    result.y = this->y + v.y;
    return result;
}

Vector2 Vector2::operator - (const Vector2& v)
{
    Vector2 result = Vector2();
    result.x = this->x - v.x;
    result.y = this->y - v.y;
    return result;
}

Vector2& Vector2::operator += (const Vector2& v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector2& Vector2::operator -= (const Vector2& v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

bool Vector2::operator==(const Vector2& v)
{
    return this->x == v.x && this->y == v.y;
}

bool Vector2::operator!=(const Vector2& v)
{
    return this->x != v.x && this->y != v.y;
}
