#ifndef VECT2_HPP
#define VECT2_HPP

#include <ostream>

class   vect2{
    private :
        int x ,y;
    public :
        vect2();
        vect2(int x , int y);
        vect2(const vect2 &other);
        ~vect2();
        vect2&  operator=(const vect2 &other);

        int&    operator[](int index);
        const int&    operator[](int index)const;

        vect2&  operator++();
        vect2&  operator--();
        vect2  operator++(int);
        vect2  operator--(int);

        vect2&   operator+=(const vect2& other);
        vect2&  operator-=(const vect2& other);
        vect2&   operator*=(int t);
        vect2   operator+(const vect2& other)const;
        vect2   operator-(const vect2& other)const;
        vect2   operator*(int t)const;
        vect2   operator-()const;

        bool    operator==(const vect2& other)const;
        bool    operator!=(const vect2& other)const;

        friend  vect2   operator*(int t , const vect2& other);
        friend  std::ostream&   operator<<(std::ostream& o , const vect2& other);
};







#endif