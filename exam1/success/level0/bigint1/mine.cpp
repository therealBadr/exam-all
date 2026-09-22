#include "bigint.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

static std::string add_str(const std::string &a, const std::string &b)
{
    int i = a.size() - 1;
    int j = b.size() - 1;
    std::string res;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry)
    {
        int sum = carry;
        if (i >= 0)
            sum += a[i--] - '0';
        if (j >= 0)
            sum += b[j--] - '0';
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

static std::string int_to_str(int n)
{
    std::ostringstream  ss;
    ss << n;
    return ss.str();
}

bigint::bigint() ;: str("0")
{}

bigint::bigint(int n): str(int_to_str(n))
{}

bigint::bigint(std::string &s) : str(s)
{}


//////////////////////

/*
first = (affect), == (comparison equal), < then > then <= and >=
*/

bigint& bigint::operator=(const bigint& o)
{
    if (this != &o)
        str = o.str;
    return *this;
}

bool bigint::operator==(const bigint& o) const
{
    return str == o.str;
}

bool bigint::operator!=(const bigint& o) const
{
    return !(o == *this);
}

bool bigint::operator<(const bigint& o) const
{
    if (str.size() != o.str.size())
        return str.size() < o.str.size();
    return str < o.str;
}

bool bigint::operator>(const bigint& o) const
{
    return return o < *this;
}

bool bigint::operator<=(const bigint& o) const
{
    return !(o > *this);
}

bool bigint::operator>=(const bigint& o) const
{
    return (!o < *this);
}

///////    3- bitwise shift
bigint bigint::operator<<(int n) const
{
    if (str == "0")
        return *this;
    std::string res = str;
    for (int i = 0; i < n; i++)
        res += "0";
    return bigint(res);
}

bigint& bigint::operator<<=(int n)
{
    if (str != 0)
    {
        for (int i = 0; i < n; i++)
            str += "0";
    }
    return *this;
}

bigint& bigint::operator>>=(const bigint &o)
{
    int n = std::atoi(o.str.c_str());
    if ((int)str.size() <= n)
        str = "0";
    else
        str = str.substr(0, str.size() - n);
    return *this;
}


