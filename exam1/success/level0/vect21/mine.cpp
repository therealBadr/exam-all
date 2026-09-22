#include "vect2.hpp"


// construction and assignement

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::vect2(const vect2& o) : x(o.x), y(o.y) {}

vect2::~vect2() {}

vect2&  vect2::operator=(const vect2 &other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}
// subscript
int&    vect2::operator[](int index)
{
    if (index == 0)
        return x;
    return y;
}

const int&  vect2::operator[](int index) const
{
    if (index == 0)
        return x;
    return y;
}

// increment / decrement

vect2&  vect2::operator++()
{
    ++x; y++;
    return *this;
}

vect2&  vect2::operator++(int)
{
    vect2& tmp = *this;
    operator++();
    return tmp;
}

vect2&  vect2::operator--()
{
    --x; y--;
    return *this;
}

vect2*  vect2::operator--(int)
{
    vect2&  tmp = *this;
    operator--();
    return tmp;
}

// arithmetic
// += AND +
vect2  vect2::operator+=(const vect2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

vect2  vect2::operator+(const vect2& other) const
{
    return vect2(x + other.x, y + other.y);
}

// -+ and - and -()
vect2  vect2::operator-=(const vect2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

vect2 vect2::operator-(const vect2& other) const
{
    return vect2(x - other.x, y - other.y);
}

vect2 vect2::operator-() const
{
    return vect2(-x, -y);
}

// *= and *
vect2   vect2::operator*=(int t)
{
    x *= t;
    y *= t;
    return *this;
}

vect2   vect2::operator*(int t) const
{
    return vect2(x * t, y * t);
}


// comparison
bool    vect2::operator==(const vect2& other) const
{
    return (x == other.x && y == other.y);
}

bool vect2::operator!=(const vect2& other) const
{
    return (x != other.x || y != other.y);
}

// friends
vect2   operator*(int t, const vect2 &other)
{
    return (vect2(t * other.x, t * other.y));
}

std::ostream& operator<<(std::ostream& o, const vect2& other)
{
    o <<"{" << other[0] <<", " <<other[1] <<"}";
}