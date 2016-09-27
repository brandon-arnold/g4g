#include <iostream>
#include <math.h>
using namespace std;

uint64_t ncrModM(uint64_t n, uint64_t r, uint64_t m);
uint64_t pFactorsInNFactorial(uint64_t n, uint64_t p);
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

const uint64_t maxN = 1000000000L;
const uint64_t BLOCKSIZE = 1 << 24;
const uint64_t sqrtMaxN = 31622L;
const uint64_t numPrimes = 50847534L;
bool C[maxN];
uint64_t Primes[numPrimes];
uint64_t First[numPrimes];
uint64_t NP = 0;

void doSieve() {
	for (uint64_t j = 0; j < maxN; j++) {
		C[j] = false;
	}
	for (uint64_t p = 2; p < sqrtMaxN + 1; p++) {
		if (!C[p]) {
			uint64_t n = p*p;
			for (; n < maxN; n += p)
				C[n] = true;
		}
	}
}

uint64_t ncrModM(uint64_t n, uint64_t r, uint64_t m) {
	uint64_t ncrModM = 1;
	uint64_t maxFact;
	uint64_t nfPower;
	for (uint64_t p = 2; p <= n; p++) {
		if (!C[p]) {
			nfPower = pFactorsInNFactorial(n, p);
			nfPower -= pFactorsInNFactorial(r, p);
			nfPower -= pFactorsInNFactorial(n - r, p);
			if (nfPower == 0) continue;
			maxFact = (uint64_t)pow(p, nfPower);
			ncrModM *= maxFact % m;
			ncrModM %= m;
			if (ncrModM <= 0) break;
			if (nfPower < 0) break;
		}
	}
	return ncrModM;
}

uint64_t pFactorsInNFactorial(uint64_t n, uint64_t p) {
	uint64_t sum = 0, curP = p;
	for (uint64_t i = 1; curP <= n; i++) {
		sum += n / curP;
		curP *= p;
	}
	return sum;
}

