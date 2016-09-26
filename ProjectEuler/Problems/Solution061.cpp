// https://projecteuler.net/problem=61
/*
Cyclical figurate numbers
Triangle, square, pentagonal, hexagonal, heptagonal, and octagonal numbers are all figurate (polygonal)
numbers and are generated by the following formulae:

Triangle	 	P3,n=n(n+1)/2	 	1, 3,  6, 10, 15, ...
Square	 		P4,n=n2	 			1, 4,  9, 16, 25, ...
Pentagonal	 	P5,n=n(3n-1)/2	 	1, 5, 12, 22, 35, ...
Hexagonal	 	P6,n=n(2n-1)	 	1, 6, 15, 28, 45, ...
Heptagonal	 	P7,n=n(5n-3)/2	 	1, 7, 18, 34, 55, ...
Octagonal	 	P8,n=n(3n-2)	 	1, 8, 21, 40, 65, ...
The ordered set of three 4-digit numbers: 8128, 2882, 8281, has three interesting properties.

The set is cyclic, in that the last two digits of each number is the first two digits of the next number
(including the last number with the first).
Each polygonal type: triangle (P3,127=8128), square (P4,91=8281), and pentagonal (P5,44=2882), is represented
by a different number in the set.
This is the only set of 4-digit numbers with this property.
Find the sum of the only ordered set of six cyclic 4-digit numbers for which each polygonal type: triangle,
square, pentagonal, hexagonal, heptagonal, and octagonal, is represented by a different number in the set.

Solution:
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
typedef unsigned long long natural;

vector<vector<int>> polyNumbers;
void pushPolygonalNumbers(int a, int b) {
	vector<int> set;
	int n = 1, i = a;
	while (n < 1000) {
		n += i;
		i += b;
	}
	while (n < 10000) {
		if ((n % 100) / 10) // second last digit should not be 0
			set.push_back(n);
		n += i;
		i += b;
	}
	polyNumbers.emplace_back(set);
}

inline void generateAll4DigitPolygonalNumbers() {
	pushPolygonalNumbers(2, 1);	// Triangle
	pushPolygonalNumbers(3, 2); // Square
	pushPolygonalNumbers(4, 3); // Pentagonal
	pushPolygonalNumbers(5, 4); // Hexagonal
	pushPolygonalNumbers(6, 5); // Heptagonal
	pushPolygonalNumbers(7, 6); // Octagonal
}

bool dfs(vector<int>& numbers, int matched) {
	if (numbers.size() == 6 && matched == 63 && numbers[0] / 100 == numbers[5] % 100)
		return true;
	int last2 = numbers.back() % 100;
	numbers.push_back(0);
	for (int i = 4; i >= 0; i--) {
		if (!(matched & (1 << i))) {
			int str = lower_bound(polyNumbers[i].begin(), polyNumbers[i].end(), last2 * 100) - polyNumbers[i].begin();
			int end = lower_bound(polyNumbers[i].begin(), polyNumbers[i].end(), (last2 + 1) * 100) - polyNumbers[i].begin();
			for (int j = str; j < end; j++) {
				numbers.back() = polyNumbers[i][j];
				if (dfs(numbers, matched | (1 << i)))
					return true;
			}
		}
	}
	numbers.pop_back();
	return false;
}

int main() {
	auto begin = chrono::high_resolution_clock::now();
	generateAll4DigitPolygonalNumbers();

	int str = lower_bound(polyNumbers[5].begin(), polyNumbers[5].end(), 1000) - polyNumbers[5].begin();
	vector<int> numbers = { 0 };
	for (int i = str, n = polyNumbers[5].size(); i < n; i++) {
		numbers[0] = polyNumbers[5][i];
		if (dfs(numbers, 1 << 5))
			break;
	}

	cout << "Done in " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - begin).count() / 1000000.0 << " miliseconds." << endl;
	int sum = 0;
	for (auto x : numbers) {
		cout << x << endl;
		sum += x;
	}
	cout << "sum = " << sum << endl;
}