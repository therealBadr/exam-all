#include "bigint.hpp"

static  std::string add_str(const std::string &a , const std::string &b)
{
    std::string res;
    int i = a.size() -1;
    int j = b.size() -1;
    int carry = 0;
    while(i >= 0 || j >=0 || carry)
    {
        int sum = carry;
        if(i >= 0)
            sum+=a[i--] -'0';
        if(j >= 0)
            sum+=b[j--] -'0';
        res.push_back(sum % 10 +'0');
        carry = sum /10;
    }
    std::reverse(res.begin() , res.end());

    return res;
}
bigint::bigint() : str("0") {

}
bigint::bigint(int n) :  str(std::to_string(n)) {

}

bigint::bigint(const std::string &s) : str(s)  {

}
bigint& bigint::operator=(const bigint& o){
    if(this != &o)
    {
        str = o.str;
    }
    return *this;
}
bigint  bigint::operator+(const bigint& o) const {

    return (bigint(add_str(str , o.str)));
}
bigint  bigint::operator+(int n)const{
    return *this + bigint(n);
}

bigint&  bigint::operator+=(const bigint &o){

    str = add_str(str , o.str);
    return *this;
}
bigint& bigint::operator++(){
    *this+=1;
    return *this;
}

bigint bigint::operator++(int){
    bigint tmp = *this;
    ++(*this);
    return tmp;
}
bigint  bigint::operator<<(int n){

    if(str == "0")
        return *this;
    std::string res = str;
    for(int i = 0 ; i < n ; i++)
        res+="0";
    return bigint(res);
}
bigint& bigint::operator<<=(int n)
{
    if(str != "0")
    {
        for(int i = 0; i < n ; i++)
            str+="0";
    }
    return *this;
}
bigint& bigint::operator>>=(const bigint &o){
    int n = std::stoi(o.str);
    if((int)str.size() <= n)
        str ="0";
    else
        str = str.substr(0 , str.size() -n);
    return *this;
}

bool    bigint::operator<(const bigint& o)const{
    if(str.size() != o.str.size())
        return str.size() < o.str.size();
    return str < o.str;
}
bool    bigint::operator>(const bigint& o)const{
        return o < *this;
}
bool    bigint::operator==(const bigint &o)const{
    return str == o.str;
}
bool    bigint::operator!=(const bigint &o)const{
    return !(o == *this);
}
bool bigint::operator<=(const bigint& o)const{
    return !(*this > o);
}
bool    bigint::operator>=(const bigint &o)const{
    return !(*this < o);
}
std::ostream&   operator<<( std::ostream& o , const bigint& obj)
{
    o << obj.str;
    return o;
}


