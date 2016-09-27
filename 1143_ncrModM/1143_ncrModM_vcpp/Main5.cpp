#include <iostream>
#include <math.h>
using namespace std;

uint64_t ncrModM(uint64_t n, uint64_t r, uint64_t m);
uint64_t ncrmodp(uint64_t n, uint64_t r, uint64_t p);
void doSieve();

int main() {
	uint64_t numProbs, n, r, m;
	uint64_t result;
	doSieve();
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

const uint64_t maxN = 1000000000Ui64;
const uint64_t maxPrime = 100;
bool C[maxPrime + 1];

void doSieve() {
	memset(C, false, sizeof(C));
	for (uint64_t p = 2; p < 10; p++) {
		if (!C[p]) {
			uint64_t n = p*p;
			for (; n <= maxPrime; n += p)
				C[n] = true;
		}
	}
}

uint64_t ncrModM(uint64_t n, uint64_t r, uint64_t m) {
	uint64_t ncrModM = 1;
	uint64_t curP, curBin;
	for (uint64_t p = 2; p <= maxPrime; p++) {
		if (!C[p] && (m % p) == 0) {
			curBin = 1;
			curBin *= ncrmodp(n, m, p);
			ncrModM *= (curBin % m);
			ncrModM %= m;
			if (ncrModM <= 0) break;
		}
	}
	return ncrModM;
}

uint64_t ncrmodp(uint64_t n, uint64_t r, uint64_t p) {
	if (r == 0) return 1;
	int ni = n%p, ri = r%p;
	return (ncrmodp(n / p, r / p, p) * // Last digits of n and r
		ncrmodp(ni, ri, p)) % p;  // Remaining digits
}
