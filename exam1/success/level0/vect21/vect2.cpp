#include "vect2.hpp"

// ============================================================================
// CONSTRUCTION & ASSIGNMENT
// ============================================================================

vect2::vect2() : x(0) , y(0) {

}
vect2::vect2(int x ,int y) : x(x) , y(y) {

}
vect2::vect2(const vect2 &other) : x(other.x) , y(other.y) {

}
vect2::~vect2(){

}
vect2&  vect2::operator=(const vect2 &other){
    if(this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}

// ============================================================================
// SUBSCRIPT
// ============================================================================

int&    vect2::operator[](int index){          // non-const: v[i] = x must compile
    if(index == 0)
        return x;
    return y;
}

const int&    vect2::operator[](int index) const {   // const: read-only, works on const vect2&
    if(index == 0)
        return x;
    return y;
}

// ============================================================================
// INCREMENT / DECREMENT
// ============================================================================

vect2&  vect2::operator++(){
    ++x;
    y++;
    return *this;
}

vect2   vect2::operator++(int){
    vect2 tmp = *this;
    operator++();
    return tmp;
}

vect2&  vect2::operator--(){
    --x;
    y--;
    return *this;
}

vect2   vect2::operator--(int){
    vect2 tmp = *this;
    operator--();
    return tmp;
}

// ============================================================================
// ARITHMETIC — mutate/pure pairs, one operation at a time
// ============================================================================

vect2&  vect2::operator+=(const vect2&  other){
    x+=other.x;
    y+=other.y;
    return *this;
}
vect2   vect2::operator+(const vect2& other)const{
    return vect2(x + other.x , y +other.y);
}

vect2&  vect2::operator-=(const vect2&  other){
    x-=other.x;
    y-=other.y;
    return *this;
}
vect2   vect2::operator-(const vect2& other)const{
    return vect2(x - other.x , y - other.y);
}
vect2   vect2::operator-()const                 // unary negate
{
    return vect2(-x ,-y);
}

vect2&  vect2::operator*=(int t){
    x*=t;
    y*=t;
    return *this;
}
vect2   vect2::operator*(int t)const{
    return vect2(x * t , y *t);
}

// ============================================================================
// COMPARISONS
// ============================================================================

bool    vect2::operator==(const vect2&  other)const {
    return (x == other.x && y == other.y);
}
bool    vect2::operator!=(const vect2&  other)const {
    return (x != other.x || y != other.y);   // De Morgan: !(A && B) == !A || !B
}

// ============================================================================
// FRIENDS
// ============================================================================

vect2   operator*(int t , const vect2& other)   // left operand is int, not vect2
{
    return (vect2(t * other.x , t*other.y));
}

std::ostream&   operator<<(std::ostream& o , const vect2& other)
{
    o <<"{" << other[0] <<", " <<other[1] <<"}";
    return o;
}
