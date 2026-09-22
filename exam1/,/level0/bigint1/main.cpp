//	test 0
#include "bigint.hpp"

// int main() {
// 	const bigint a(10);
// 	bigint b(20);
// 	// bigint c;
// 	// bigint d(1337), e(d);
// 	// bigint j("0000009");
// 	// bigint k(1);
	
// 	std::cout << "a = " << a << std::endl;
// 	std::cout << "b = " << b << std::endl;

// 	std::cout << "(a + b) = " << a + b << std::endl;
// 	std::cout << "(b += a) = " << (b += a) << std::endl;
// 	std::cout << "b = " << b << std::endl;
// 	std::cout << "(++b) = " << ++b << std::endl;
// 	std::cout << "(b++) = " << b++ << std::endl;
// 		std::cout << "b = " << b << std::endl;

// 	std::cout << "((b << 10) = " << (b << 10)<< std::endl;
// 	std::cout << "(b >>= (const bigint)2) = " << (b >>= (const bigint)2) << std::endl;
// 	std::cout << "a = " << a << std::endl;
// 	std::cout << "b = " << b << std::endl;
// 	#include <stdio.h>
// 	std::cout << "(b < a) = " << (b < a) << std::endl;
// 	std::cout << "(b == a) = " << (b == a) << std::endl;
// 	std::cout << "(b != a) = " << (b != a) << std::endl;
// 	std::cout << "(b >= a) = " << (b >= a) << std::endl;
// 	std::cout << "(b <= a) = " << (b <= a) << std::endl;
// 	std::cout << "(b > a) = " << (b > a) << std::endl;

// 	return (0);
// }

// 	// test 1
int main() {
	const bigint a(42);
	bigint b(21), c, d(1337), e(d);

	std::cout << "(c <<= 10) = " << (c <<= 10) << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "a + b = " << a + b << std::endl;
	std::cout << "(c += a) = " << (c += a) << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "++b = " << ++b << std::endl;
	std::cout << "b++ = " << b++ << std::endl;
	std::cout << "(b << 10) + 42 = " << (b << 10) + 42 << std::endl;
	std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
	std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d < a) = " << (d < a) << std::endl;
	std::cout << "(d > a) = " << (d > a) << std::endl;
	std::cout << "(d == a) = " << (d == a) << std::endl;
	std::cout << "(d != a) = " << (d != a) << std::endl;
	std::cout << "(d <= a) = " << (d <= a) << std::endl;
	std::cout << "(d >= a) = " << (d >= a) << std::endl;
}
