// https://projecteuler.net/problem=28
/*
Number spiral diagonals

Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101 = 21+7+1+3+13+25+9+5+17.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?

Solution:
Let diagonal sum from bottom left to top right = S
S = 1 + [3*3 + 5*5 + 7*7 + ... + (2n+1)*(2n+1)] + [2*2+1 + 4*4+1 + 6*6+1 + ... + (2n)*(2n)+1]
  = 1*1 + 2*2 + 3*3 + 4*4 + ... + (2n)*(2n) + (2n+1)*(2n+1) + (n/2)
  = n*(n+1)*(2n+1)/6 + n/2

Let diagonal sum from top left to mid(exclusive) = Stl
Stl = (2*2+1+3*3)/2 + (4*4+1+5*5)/2 + ... + ((2n)*(2n)+1+(2n+1)*(2n+1))/2 
	= (S-1)/2

Let diagonal sum from mid(exclusive) to bottom right = Sbr
Sbr = (2*2+1+1*1)/2 + (4*4+1+3*3)/2 + ... + ((2n)*(2n)+1+(2n-1)*(2n-1))/2 
	= (S-(2n+1)*(2n+1))/2

Stl + Sbr = S - (1+(2n+1)*(2n+1))/2
Total sum = 2*S - (1+(2n+1)*(2n+1))/2
*/

#include <iostream>
using namespace std;
typedef unsigned long long natural;

#define Modulus 1000000007ULL
#define modADD(x, y) (((x) + (y)) % Modulus)
#define modSUB(x, y) (((x) + Modulus - (y)) % Modulus)
#define modMUL(x, y) (((x) * (y)) % Modulus)

int main() {
	int t;
	cin >> t;
	while (t--) {
		natural n, t;
		cin >> n;
		natural s = 2 * (n / 2);
		n %= Modulus;
		t = modMUL(n, n + 1);
		t = modMUL(t, 2 * n + 1);
		t = modMUL(t, 333333336);
		s = modADD(s, t);
		t = modMUL(n, n);
		t = modADD(t, 1);
		t = modMUL(t, 500000004);
		s = modSUB(s, t);
		cout << s << endl;
	}
}