#include <iostream>
#include <math.h>
using namespace std;

uint64_t ncrModM1(uint64_t n, uint64_t r, uint64_t m);
uint64_t ncrModM2(uint64_t n, uint64_t r, uint64_t m);
uint64_t ncrModM3(uint64_t n, uint64_t r, uint64_t m);
uint64_t pFactorsInNFactorial(uint64_t n, uint64_t p);
uint64_t pFactorsAlt(uint64_t n, uint64_t p);
void doSieve();
void doSegSieve();

const uint64_t maxN = 1000000000L;
const uint64_t BLOCKSIZE = 1 << 24;
const uint64_t sqrtMaxN = 31622L;
const uint64_t numPrimes = 50847534L;
bool CSeg[BLOCKSIZE];
uint64_t Primes[numPrimes];
uint64_t First[numPrimes];
uint64_t NP = 0;
bool C[maxN];

int main() {
	uint64_t numProbs, n, r, m;
	uint64_t result1, result2;
	doSieve();
	doSegSieve();
	//uint64_t curP = 0;
	//for (uint64_t i = 2; i < maxN; i++) {
	//	if (!C[i]) {
	//		if (Primes[curP] != i) {
	//			cout << "difference found!" << endl;
	//		}
	//		curP++;
	//	}
	//}
	cin >> numProbs;
	while (numProbs--) {
		cin >> n;
		cin >> r;
		cin >> m;
		result1 = ncrModM3(n, r, m);
		cout << result1 << endl;
	}
	return 0;
}


void doSegSieve() {
	for (uint64_t j = 0; j < BLOCKSIZE; j++)
		CSeg[j] = 0L;
	for (uint64_t p = 2; p <= sqrtMaxN; ++p)
		if (!CSeg[p]) {
			Primes[NP] = p;
			uint64_t n = p*p;
			for (; n < BLOCKSIZE; n += p)
				CSeg[n] = 1;
			First[NP] = n - BLOCKSIZE;
			NP++;
		}
	for (uint64_t p = sqrtMaxN + 1; p < BLOCKSIZE; ++p)
		if (!CSeg[p]) {
			Primes[NP] = p;
			First[NP] = p*p - BLOCKSIZE;
			NP++;
		}
	for (uint64_t B = BLOCKSIZE; B <= maxN; B += BLOCKSIZE) {
		for (uint64_t j = 0; j < BLOCKSIZE; j++)
			CSeg[j] = 0;
		for (uint64_t k = 0; k < NP; ++k) {
			uint64_t p = Primes[k];
			uint64_t t = First[k];
			for (; t < BLOCKSIZE; t += p)
				CSeg[t] = 1;
			First[k] = t - BLOCKSIZE;
		}
		for (uint64_t c = 0; (c < BLOCKSIZE) && ((c + B) <= maxN); c++) {
			if (!CSeg[c]) {
				uint64_t p = B + c;
				Primes[NP] = p;
				First[NP] = p*p;
				NP++;
				for (uint64_t n = p*p; n <= BLOCKSIZE; n += p)
					CSeg[n] = 1;
			}
		}
	}
}

uint64_t ncrModM1(uint64_t n, uint64_t r, uint64_t m) {
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
uint64_t ncrModM3(uint64_t n, uint64_t r, uint64_t m) {
	uint64_t ncrModM1 = 1, ncrModM2 = 1;
	uint64_t p2 = 0, p2i = 0;
	uint64_t nfPower1, nfPower2;
	for (uint64_t p = 2; p <= n; p++) {
		if (!C[p]) {
			p2 = Primes[p2i++];
			if (p2 != p) {
				cout << "Difference found!" << endl;
			}
			nfPower1 = pFactorsInNFactorial(n, p);
			nfPower1 -= pFactorsInNFactorial(r, p);
			nfPower1 -= pFactorsInNFactorial(n - r, p);
			nfPower2 = pFactorsInNFactorial(n, p2);
			nfPower2 -= pFactorsInNFactorial(r, p2);
			nfPower2 -= pFactorsInNFactorial(n - r, p2);
			if (nfPower1 != nfPower2) {
				cout << "Difference found!" << endl;
			}
			if (nfPower1 == 0) continue;
			if (nfPower2 == 0) continue;
			p = (uint64_t)pow(p, nfPower1);
			ncrModM1 *= p % m;
			ncrModM1 %= m;
			p2 = (uint64_t)pow(p2, nfPower2);
			ncrModM2 *= p % m;
			ncrModM2 %= m;
			if (ncrModM1 != ncrModM2) {
				cout << "Difference found!" << endl;
			}
			if (ncrModM1 <= 0) break;
			if (ncrModM2 <= 0) break;
			if (nfPower1 < 0) break;
			if (nfPower2 < 0) break;
		}
	}
	return ncrModM1;
}

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

uint64_t ncrModM2(uint64_t n, uint64_t r, uint64_t m) {
	uint64_t ncrModM = 1;
	uint64_t nfPower;
	for (uint64_t p = 2; p <= n; p++) {
		if (!C[p]) {
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

uint64_t pFactorsAlt(uint64_t n, uint64_t p) {
	uint64_t baseNRemainder = n,
		maxPow = (uint64_t)(log(n) / log(p)),
		sumExp = 0;
	while (baseNRemainder > 0) {
		uint64_t curPPow = (uint64_t)pow(p, maxPow--);
		uint64_t curCoeff = baseNRemainder / curPPow;
		sumExp += curCoeff;
		baseNRemainder -= curCoeff * curPPow;
	}
	return (n - sumExp) / (p - 1);
}
