#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <sstream>

class bigint{
    private :
        std::string str;

    public :
        // ------------------------------------------------------------------
        // CONSTRUCTION & ASSIGNMENT
        // ------------------------------------------------------------------
        bigint();
        bigint(int n);
        bigint(const std::string &s);
        bigint& operator=(const bigint& o);

        // ------------------------------------------------------------------
        // COMPARISONS — operator< and operator== do the real work;
        // everything below each one is derived straight from it.
        // ------------------------------------------------------------------
        bool    operator<(const bigint& o)const;
        bool    operator>(const bigint& o)const;   // = o < *this
        bool    operator<=(const bigint& o)const;  // = !(*this > o)
        bool    operator>=(const bigint& o)const;  // = !(*this < o)

        bool    operator==(const bigint& o)const;
        bool    operator!=(const bigint& o)const;  // = !(*this == o)

        // ------------------------------------------------------------------
        // ARITHMETIC — mutate (+=) then pure (+), then ++ built on +=
        // ------------------------------------------------------------------
        bigint& operator+=(const bigint &o);
        bigint  operator+(const bigint &o)const;
        bigint  operator+(int)const;               // wraps int -> bigint, calls the above

        bigint&  operator++();                     // prefix : *this += 1
        bigint  operator++(int);                    // postfix: copy, ++prefix, return copy

        // ------------------------------------------------------------------
        // DIGIT SHIFTS — same base-10 idea as ARITHMETIC's +=/+ pair,
        // pure (<<) then mutate (<<=, >>=)
        // ------------------------------------------------------------------
        bigint  operator<<(int) const;              // NOTE: digit-shift, not stream output
        bigint&  operator<<=(int);
        bigint&  operator>>=(const bigint& o);

        // ------------------------------------------------------------------
        // STREAM OUTPUT — different operator<< overload entirely: left
        // operand is std::ostream, so it can't be a member -> friend.
        // ------------------------------------------------------------------
        friend  std::ostream&   operator<<( std::ostream& o , const bigint& obj);
};

#endif
