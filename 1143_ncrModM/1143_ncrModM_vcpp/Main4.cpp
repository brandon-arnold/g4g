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
const uint64_t BLOCKSIZE = 1 << 20; 
const uint64_t sqrtMaxN = 31622L;
const uint64_t numPrimes = 50847534L;
bool C[BLOCKSIZE]; 
uint64_t Primes[numPrimes];
uint64_t First[numPrimes];
uint64_t NP = 0;

void doSieve() {
	memset(C, false, sizeof(C));
	for (uint64_t p = 2; p <= sqrtMaxN; ++p)
		if (!C[p]) {
			Primes[NP] = p;
			uint64_t n = p*p;
			for (; n < BLOCKSIZE; n += p)
				C[n] = 1;
			First[NP] = n - BLOCKSIZE;
			NP++;
		}
	for (uint64_t p = sqrtMaxN + 1; p < BLOCKSIZE; ++p)
		if (!C[p]) {
			Primes[NP] = p;
			First[NP] = p*p - BLOCKSIZE;
			NP++;
		}
	for (uint64_t B = BLOCKSIZE; B <= maxN; B += BLOCKSIZE) {
		memset(C, false, sizeof(C));
		for (uint64_t k = 0; k < NP; ++k) {
			uint64_t p = Primes[k];
			uint64_t t = First[k];
			for (; t < BLOCKSIZE; t += p)
				C[t] = 1;
			First[k] = t - BLOCKSIZE;
		}
		for (uint64_t c = 0; (c < BLOCKSIZE) && ((c + B) <= maxN); c++) {
			if (!C[c]) {
				uint64_t p = B + c;
				Primes[NP] = p;
				First[NP] = p*p;
				NP++;
				for (uint64_t n = p*p; n <= BLOCKSIZE; n += p)
					C[n] = 1;
			}
		}
	}
}

uint64_t ncrModM(uint64_t n, uint64_t r, uint64_t m) {
	uint64_t ncrModM = 1;
	uint64_t p;
	uint64_t nfPower;
	for (uint64_t i = 0; (i < numPrimes && Primes[i] <= n); i++) {
		p = Primes[i];
		if (p < 1) break;
		nfPower = pFactorsInNFactorial(n, p);
		nfPower -= pFactorsInNFactorial(r, p);
		nfPower -= pFactorsInNFactorial(n - r, p);
		if (nfPower == 0) continue;
		p = (uint64_t)pow(p, nfPower);
		ncrModM *= p % m;
		ncrModM %= m;
		if (ncrModM <= 0) break;
		if (nfPower < 0) break;
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
