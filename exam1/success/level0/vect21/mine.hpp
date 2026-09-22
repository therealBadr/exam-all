#ifndef MINE_HPP
#define MINE_HPP

#include <ostream>

class   vect2
{
    private:
        int x, y;
    public:
        // construct & assignement
        vect2();
        vect2(int x, int y);
        vect2(const vect2& other);
        ~vect2();
        vect2&  operator=(const vect2& other);


        // subscript []
        int&    operator[](int index);
        const int& operator[](int index) const;

        // increment and decrement
        vect2&  operator++();
        vect2&  operator++(int);

        vect2&  operator--();
        vect2&  operator--(int);

        // arithmetics
        vect2&  operator+=(const vect2& other);
        vect2&  operator+(const vect2& other) const;
        
        vect2& operator-=(const vect2& other);
        vect2& operator-(const vect2& other) const;
        vect2& operator-() const;

        vect2& operator*=(int t);
        vect2& operator*(int t) const;


        // comparison
        bool operator==(const vect2& other) const;
        bool operator!=(const vect2& other) const;

        // friend
        friend vect2    operator*(int t, const vect2& other);
        friend std::ostream& operator<<(std::ostream& o, const vect2& other);
};

#endif