// https://www.hackerrank.com/challenges/count-fox-sequences

#include <iostream>
#include <vector>
//#include <chrono>
//#include <type_traits>
using namespace std;

template<class T, T Modulus>
class Modular{
private:
	T value;

public:
	Modular(const T &init);
	Modular(const Modular& other);
	Modular& operator= (const Modular &other);
	Modular operator - () const;
	T Value() const;
	Modular inv() const;

	Modular& operator += (const Modular &a);
	Modular& operator -= (const Modular &a);
	Modular& operator *= (const Modular &a);
	Modular& operator /= (const Modular &a);
	
	template<class T1, T1 Modulus1>
	friend Modular<T1, Modulus1> operator + (const Modular<T1, Modulus1> &a, const Modular<T1, Modulus1> &b);

	template<class T1, T1 Modulus1>
	friend Modular<T1, Modulus1> operator - (const Modular<T1, Modulus1> &a, const Modular<T1, Modulus1> &b);
	
	template<class T1, T1 Modulus1>
	friend Modular<T1, Modulus1> operator * (const Modular<T1, Modulus1> &a, const Modular<T1, Modulus1> &b);

	template<class T1, T1 Modulus1>
	friend Modular<T1, Modulus1> operator / (const Modular<T1, Modulus1> &a, const Modular<T1, Modulus1> &b);
	
	template<class T1, T1 Modulus1>
	friend Modular<T1, Modulus1> pow(Modular<T1, Modulus1> i, T1 j);
	
};

// TODO: not allow 0 and 1 as Modulus
//template<class T>
//class Modular < T, std::integral_constant<T, 0>> {};

template<class T, T Modulus>
Modular<T, Modulus>::Modular(const T &init) : value(init % Modulus) { if (value < 0)value += Modulus; }

template<class T, T Modulus>
Modular<T, Modulus>::Modular(const Modular& other) : value(other.value) {}

template<class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator= (const Modular<T, Modulus> &other) { value = other.value; return *this; }

template<class T, T Modulus>
Modular<T, Modulus> Modular<T, Modulus>::operator - () const {
	if(value)
		return Modular(Modulus - value);
	return Modular(0);
}

template<class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator += (const Modular<T, Modulus> &a) {
	value += a.value;
	if (value >= Modulus)
		value -= Modulus;
	return *this;
}

template<class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator -= (const Modular<T, Modulus> &a) {
	value += Modulus - a.value;
	if (value >= Modulus)
		value -= Modulus;
	return *this;
}

template<class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator *= (const Modular<T, Modulus> &a) {
	value *= a.value;
	if (value >= Modulus)
		value %= Modulus;
	return *this;
}

template<class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator /= (const Modular<T, Modulus> &a) {
	*this *= a.inv();
	if (value >= Modulus)
		value %= Modulus;
	return *this;
}

template<class T, T Modulus>
T Modular<T, Modulus>::Value() const {
	return value;
}

template<class T, T Modulus>
Modular<T, Modulus> operator + (const Modular<T, Modulus> &a, const Modular<T, Modulus> &b) {
	Modular<T, Modulus> s(a.value);
	return s += b;
}

template<class T, T Modulus>
Modular<T, Modulus> operator - (const Modular<T, Modulus> &a, const Modular<T, Modulus> &b) {
	Modular<T, Modulus> s(a.value);
	return s -= b;
}

template<class T, T Modulus>
Modular<T, Modulus> operator * (const Modular<T, Modulus> &a, const Modular<T, Modulus> &b) {
	Modular<T, Modulus> s(a.value);
	return s *= b;
}

template<class T, T Modulus>
Modular<T, Modulus> operator / (const Modular<T, Modulus> &a, const Modular<T, Modulus> &b) {
	Modular<T, Modulus> s(a.value);
	return s /= b;
}

template<class T, T Modulus>
Modular<T, Modulus> pow(Modular<T, Modulus> i, T j) {
	if (!i.value)
		return Modular<T, Modulus>(0);
	
	if (i.value == T(1) || j == T(0))
		return Modular<T, Modulus>(1);

	Modular<T, Modulus> p(1);
	while (j) {
		if (j & 1)
			p *= i;
		i *= i;
		j >>= 1;
	}
	return p;
}

template<class T, T Modulus>
Modular<T, Modulus> Modular<T, Modulus>::inv() const {
	return pow<T, Modulus>(*this, Modulus - 2);
}

typedef unsigned long long natural;
constexpr natural Limit = 1000000007ULL;
typedef Modular<natural, Limit> modular;

vector<modular> factorialTableModulus = { 1 };
modular fact(size_t v) {
	auto n = factorialTableModulus.size();
	if (n > v)
		return factorialTableModulus[v];

	auto l = factorialTableModulus.back();
	while (n <= v) {
		l *= n;
		factorialTableModulus.push_back(l);
		n++;
	}
	return l;
}

modular nCr(size_t n, size_t r) {
	if (r > n)
		return 0;
	else if (r > n - r)
		r = n - r;

	if (n < 2 || r == 0)
		return 1;

	if (r == 1)
		return n;

	return fact(n) / (fact(r) * fact(n - r));
}

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--) {
		size_t n, lo, hi;
		cin >> n >> lo >> hi;
		
		auto d = hi - lo;
		if (d) {
			vector<modular> dCi;
			for (auto i = 0; i <= d; i++)
				dCi.push_back((i & 1) ? -nCr(d, i) : nCr(d, i));

			auto b = n + d - 1;
			modular res(0);
			for (auto k = 1; k <= n; k++)
				for (auto i = 0; i <= d; i++) {
					auto a = (i + 1) * k;
					if (b < a)
						break;
					res += dCi[i] * nCr(b - a, d - 1);
				}
			res *= modular(d + 1);
			cout << res.Value() << endl;
		}
		else
			cout << 1 << endl;
	}
	
	system("pause");
}

/*
6
3 1 4
2 1 1
2 1 3
3 1 2
4 4 5
10 2 4
*/