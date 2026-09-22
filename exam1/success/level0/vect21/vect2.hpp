#ifndef VECT2_HPP
#define VECT2_HPP

#include <ostream>

class   vect2{
    private :
        int x ,y;

    public :
        // ------------------------------------------------------------------
        // CONSTRUCTION & ASSIGNMENT
        // ------------------------------------------------------------------
        vect2();
        vect2(int x , int y);
        vect2(const vect2 &other);
        ~vect2();
        vect2&  operator=(const vect2 &other);

        // ------------------------------------------------------------------
        // SUBSCRIPT — two overloads, one pair: non-const gives a writable
        // reference, const gives a read-only one for const vect2 objects.
        // ------------------------------------------------------------------
        int&    operator[](int index);
        const int&    operator[](int index)const;

        // ------------------------------------------------------------------
        // INCREMENT / DECREMENT — each pair is prefix then its own postfix
        // ------------------------------------------------------------------
        vect2&  operator++();       // prefix ++ : mutate, return *this
        vect2  operator++(int);      // postfix++ : copy, ++prefix, return copy

        vect2&  operator--();       // prefix --
        vect2  operator--(int);      // postfix--

        // ------------------------------------------------------------------
        // ARITHMETIC — one mutate/pure pair per operation, side by side
        // ------------------------------------------------------------------
        vect2&   operator+=(const vect2& other);
        vect2   operator+(const vect2& other)const;

        vect2&  operator-=(const vect2& other);
        vect2   operator-(const vect2& other)const;
        vect2   operator-()const;              // unary negate, same family as -=/-

        vect2&   operator*=(int t);
        vect2   operator*(int t)const;

        // ------------------------------------------------------------------
        // COMPARISONS — no natural order for a 2D point, so only ==/!=
        // ------------------------------------------------------------------
        bool    operator==(const vect2& other)const;
        bool    operator!=(const vect2& other)const;   // = !(x==ox) || !(y==oy), NOT &&

        // ------------------------------------------------------------------
        // FRIENDS — left operand isn't a vect2, so these can't be members
        // ------------------------------------------------------------------
        friend  vect2   operator*(int t , const vect2& other);   // lets `3 * v` compile
        friend  std::ostream&   operator<<(std::ostream& o , const vect2& other);
};

#endif
