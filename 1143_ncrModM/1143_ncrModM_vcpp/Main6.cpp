#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <stdexcept>
using namespace std;

uint64_t ncrModM(uint64_t n, uint64_t r, uint64_t m);

int main() {
	uint64_t numProbs, n, r, m;
	uint64_t result;
	cin >> numProbs;
	while (numProbs--) {
		cin >> n;
		cin >> r;
		cin >> m;
		result = ncrModM(n, r, m);
		cout << result << endl;
	}
	return 0;
}

uint64_t choose(uint64_t x, uint64_t y) {
	uint64_t** C = new uint64_t*[x + 1];
	for (uint64_t i = 0; i < x + 1; i++) {
		C[i] = new uint64_t[y + 1];
	}
	for (uint64_t i = 0; i <= x; i++) {
		for (uint64_t j = 0; j <= std::min(i, y); j++) {
			if (j == 0 || j == i)
				C[i][j] = 1;
			else
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
	uint64_t result = C[x][y];
	for (uint64_t i = 0; i < x + 1; i++) {
		delete C[i];
	}
	delete C;
	return result;
}

uint64_t ncrModMP(uint64_t n, uint64_t r, uint64_t m) {
	int maxPow = (int)(log(n) / log(m));
	uint64_t returned = 1;
	uint64_t ni, ri, niChooseRi, powm;
	for (int i = maxPow; i >= 0; i--) {
		powm = pow(m, i);
		ni = n / powm;
		n -= (ni * powm);
		ri = r / powm;
		r -= (ri * powm);
		if (ri > ni) return 0;
		niChooseRi = choose(ni, ri);
		returned *= (niChooseRi % m);
		returned = returned % m;
		if (returned == 0) return returned;
	}
	return returned;
}

//primes less than 50
const short numPrimes = 15;
uint64_t primes[numPrimes] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };

std::vector<uint64_t> getMPrimes(uint64_t m) {
	std::vector<uint64_t> mPrimes;
	for (int i = 0; i < numPrimes; i++) {
		if ((m % primes[i]) == 0) {
			mPrimes.push_back(primes[i]);
		}
	}
	return mPrimes;
}

// overflows
uint64_t modInv(uint64_t a, uint64_t b) {
	uint64_t b0 = b, t, q;
	uint64_t x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

/*
* getMRem:
* Returns the equivalent value modulo m for a
*  distribution of moduluses of m's prime factors
*
* Inputs:
* pm: array of m's primes
* mpm: array of the moduluses of pm
*/
uint64_t getMRem(uint64_t m, std::vector<uint64_t> pm, std::vector<uint64_t> mpm) {
	// uint64_t result = 0;
	// for(int i = 0; i < pm.size(); i++) {
	//   uint64_t pp = m / pm[i];
	//   if(mpm[i] != 0) {
	//     result += mpm[i] * modInv(pp, pm[i]) * pp;
	//   }
	// }
	// return result % m;
	for (uint64_t i = 0; i < m; i++) {
		int curP = pm.size() - 1;
		while (true) {
			if (mpm[curP] == (i % pm[curP])) {
				if (curP == 0) {
					return i;
				}
				curP--;
			}
			else { break; }
		}
	}
	throw std::runtime_error("Internal error: getMRem()");
}

uint64_t ncrModM(uint64_t n, uint64_t r, uint64_t m) {
	uint64_t result = 0;
	std::vector<uint64_t> mPrimes = getMPrimes(m);
	std::vector<uint64_t> mpModM;
	for (int i = 0; i < mPrimes.size(); i++) {
		uint64_t curModMP = ncrModMP(n, r, mPrimes[i]);
		mpModM.push_back(curModMP);
	}
	result = getMRem(m, mPrimes, mpModM);
	return result;
}