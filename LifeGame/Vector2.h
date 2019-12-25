#pragma once

class Vector2
{
public:
    Vector2();
    Vector2(int x, int y);

    Vector2 operator + (const Vector2& v);
    Vector2 operator - (const Vector2& v);
    Vector2& operator += (const Vector2& v);
    Vector2& operator -= (const Vector2& v);

    bool operator==(const Vector2& v);
    bool operator!=(const Vector2& v);
public:
    int x;
    int y;
};

