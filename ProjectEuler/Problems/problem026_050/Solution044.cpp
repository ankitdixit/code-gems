// https://projecteuler.net/problem=44
/*
Pentagon numbers

Pentagonal numbers are generated by the formula, Pn=n(3n-1)/2.
The first ten pentagonal numbers are:

1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

It can be seen that P4 + P7 = 22 + 70 = 92 = P8.
However, their difference, 70 - 22 = 48, is not pentagonal.

Find the pair of pentagonal numbers, Pj and Pk, for which their sum and
difference are pentagonal and D = |Pk - Pj| is minimised;
what is the value of D?

Solution:

*/

#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

template <class T>
inline T pentagonal(const T x) {
	return x*(3 * x - 1) / 2;
}

template <class T>
T pentagonalIndex(T x) {
	x = 24 * x + 1;
	const T r = sqrt(x);
	if (r*r != x)
		return 0;
	return (r + 1) % 6 == 0 ? (r + 1) / 6 : 0;
}

using natural = unsigned;
constexpr natural limit = 3000;
natural compute() {
	natural d = 1;
	while (d < limit) {
		natural diff = pentagonal(d);
		natural k = d + 1;
		while (k < limit && 3 * k + 1 <= diff) {
			natural j = pentagonalIndex(pentagonal(k) - diff), s;
			if (j && (s = pentagonalIndex(pentagonal(k) + pentagonal(j)))) {
				//printf("%u - %u = %u, %u + %u = %u \n", k, j, d, k, j, s);
				return diff;
			}
			k++;
		}
		d++;
	}
	return 0;
}

#ifdef _MSC_VER
	template <class T>
	inline void DoNotOptimize(const T &value) {
		__asm { lea ebx, value }
	}
#else
	template <class T>
	__attribute__((always_inline)) inline void DoNotOptimize(const T &value) {
		asm volatile("" : "+m"(const_cast<T &>(value)));
	}
#endif

int main() {
	using namespace std;
	using namespace chrono;
	auto start = high_resolution_clock::now();
	auto result = compute();
	DoNotOptimize(result);
	cout << "Done in "
		<< duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() / 1e6
		<< " miliseconds." << endl;
	cout << result << endl;
}

