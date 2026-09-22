#ifndef BIGINT_HPP
#define BIGINT_HPP



#include <iostream>
#include <sstream>

class bigint{
    private :
        std::string str;
    public :
        bigint();
        bigint(int n);
        bigint(const std::string &s);
        bigint& operator=(const bigint& o);

        bigint  operator+(const bigint &o)const;
        bigint  operator+(int)const;
        bigint& operator+=(const bigint &o);

        bigint&  operator++();
        bigint  operator++(int);

        bigint  operator<<(int) const;
        bigint&  operator<<=(int);
        bigint&  operator>>=(const bigint& o);

        bool    operator<(const bigint& o)const;
        bool    operator>(const bigint& o)const;
        bool    operator==(const bigint& o)const;
        bool    operator!=(const bigint& o)const;
        bool    operator<=(const bigint& o)const;
        bool    operator>=(const bigint& o)const;

        friend  std::ostream&   operator<<( std::ostream& o , const bigint& obj);
};

#endif