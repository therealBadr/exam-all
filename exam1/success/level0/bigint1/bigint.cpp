#include "bigint.hpp"
#include <algorithm>
#include <sstream>
#include <cstdlib>

// ============================================================================
// HELPERS — used by more than one operator below
// ============================================================================

// grade-school column addition, digit by digit, right to left
static std::string add_str(const std::string &a, const std::string &b)
{
    std::string res;
    int i = a.size() - 1;
    int j = b.size() - 1;
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

// C++98 has no std::to_string — build the string through a stream instead
static std::string int_to_str(int n)
{
    std::ostringstream ss;
    ss << n;
    return ss.str();
}

// ============================================================================
// CONSTRUCTION & ASSIGNMENT
// ============================================================================

bigint::bigint() : str("0") {
}

bigint::bigint(int n) : str(int_to_str(n)) {
}

bigint::bigint(const std::string &s) : str(s) {
}

bigint& bigint::operator=(const bigint& o){
    if (this != &o)
    {
        str = o.str;
    }
    return *this;
}

// ============================================================================
// COMPARISONS — build < and ==, derive the other four from them
// ============================================================================

bool bigint::operator<(const bigint& o) const {
    if (str.size() != o.str.size())        // no leading zeros, so fewer digits
        return str.size() < o.str.size();  // always means a smaller number
    return str < o.str;                    // same length -> plain lexicographic compare works
}

bool bigint::operator>(const bigint& o) const {
    return o < *this;                      // just flip the operands
}

bool bigint::operator<=(const bigint& o) const {
    return !(*this > o);
}

bool bigint::operator>=(const bigint &o) const {
    return !(*this < o);
}

bool bigint::operator==(const bigint &o) const {
    return str == o.str;
}

bool bigint::operator!=(const bigint &o) const {
    return !(o == *this);
}

// ============================================================================
// ARITHMETIC — += mutates, + builds a new bigint, ++ is built on +=
// ============================================================================

bigint& bigint::operator+=(const bigint &o){
    str = add_str(str, o.str);
    return *this;
}

bigint bigint::operator+(const bigint& o) const {
    return bigint(add_str(str, o.str));
}

bigint bigint::operator+(int n) const {
    return *this + bigint(n);              // reuse the bigint+bigint overload above
}

bigint& bigint::operator++(){              // prefix: mutate, return *this
    *this += 1;
    return *this;
}

bigint bigint::operator++(int){            // postfix: save old value, then prefix-increment
    bigint tmp = *this;
    ++(*this);
    return tmp;
}

// ============================================================================
// DIGIT SHIFTS — shift base-10 digits, not bits. << is pure, <<= and >>=
// mutate in place.
// ============================================================================

bigint bigint::operator<<(int n) const {
    if (str == "0")
        return *this;
    std::string res = str;
    for (int i = 0; i < n; i++)
        res += "0";
    return bigint(res);
}

bigint& bigint::operator<<=(int n)
{
    if (str != "0")
    {
        for (int i = 0; i < n; i++)
            str += "0";
    }
    return *this;
}

bigint& bigint::operator>>=(const bigint &o){
    int n = std::atoi(o.str.c_str());
    if ((int)str.size() <= n)
        str = "0";
    else
        str = str.substr(0, str.size() - n);
    return *this;
}

// ============================================================================
// STREAM OUTPUT
// ============================================================================

std::ostream& operator<<(std::ostream& o, const bigint& obj)
{
    o << obj.str;
    return o;
}
