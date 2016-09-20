#include <iostream>
#include <math.h>
using namespace std;

uint32_t ncrModM(uint32_t n, uint32_t r, uint32_t m);
uint32_t pFactorsInNFactorial(uint32_t n, uint32_t p);
uint32_t pFactorsAlt(uint32_t n, uint32_t p);
void doSieve();

int main() {
	uint32_t numProbs, n, r, m;
	uint32_t result;
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

const uint32_t maxN = 1000000000L;
const uint32_t BLOCKSIZE = maxN; // 1 << 24;
const uint32_t sqrtMaxN = 31622L;
const uint32_t numPrimes = 50847534L;
bool C[BLOCKSIZE];
//uint32_t Primes[numPrimes];   // primes to use in the sieve
//uint32_t First[numPrimes];   // next integer divisible by p (delta form block start)
uint32_t NP = 0;

void doSieve() {
	uint32_t p;
	for (p = 2; p < sqrtMaxN + 1; ++p)
		if (!C[p]) {
			// Primes[NP] = p;
			uint64_t n = p*p;
			for (; n < BLOCKSIZE; n += p)
				C[n] = 1;
			// First[NP] = n - BLOCKSIZE;
			NP++;
		}
	for (p = sqrtMaxN + 1; p < maxN; ++p) {
		if (!C[p])
			NP++;
	}
	cout << NP << " " << numPrimes << endl;
}

//void doSieve() {
//	for (uint32_t p = 2; p < BLOCKSIZE; ++p)
//		if (!C[p]) {
//			Primes[NP] = p;
//			uint64_t n = p*p;
//			for (; n < BLOCKSIZE; n += p)
//				C[n] = 1;
//			First[NP] = n - BLOCKSIZE;
//			NP++;
//		}
//	for (uint32_t B = BLOCKSIZE; B <= maxN; B += BLOCKSIZE) {
//		for (uint32_t j = 0; j < BLOCKSIZE; j++)
//			C[j] = 0;
//		for (uint32_t k = 0; k < NP; ++k) {
//			uint32_t p = Primes[k];
//			uint32_t t = First[k];
//			for (; t < BLOCKSIZE; t += p)
//				C[t] = 1;
//			First[k] = t - BLOCKSIZE;
//		}
//		for (uint32_t c = 0; (c < BLOCKSIZE) && ((c + B) <= maxN); c++) {
//			if (!C[c]) {
//				uint32_t p = B + c;
//				Primes[NP] = p;
//				First[NP] = p*p;
//				NP++;
//				for (uint64_t n = p*p; n <= BLOCKSIZE; n += p)
//					C[n] = 1;
//			}
//		}
//	}
//	cout << NP << " " << numPrimes << endl;
//}

//uint32_t ncrModM(uint32_t n, uint32_t r, uint32_t m) {
//	uint32_t ncrModM = 1;
//	uint32_t p;
//	uint32_t nfPower;
//	for (uint32_t i = 0; (i < numPrimes && Primes[i] <= n); i++) {
//		p = Primes[i];
//		//cout << p;
//		if (p < 1) break;
//		nfPower = pFactorsInNFactorial(n, p);
//		nfPower -= pFactorsInNFactorial(r, p);
//		nfPower -= pFactorsInNFactorial(n - r, p);
//		if (nfPower == 0) continue;
//		p = (uint32_t)pow(p, nfPower);
//		//cout << ' ';
//		//cout << p;
//		//cout << ' ';
//		//cout << ncrModM;
//		//ncrModM *= p % m;
//		//ncrModM %= m;
//		//cout << ' ';
//		//cout << ncrModM;
//		//cout << ' ';
//		//cout << m << endl;
//		if (ncrModM <= 0) break;
//		if (nfPower < 0) break;
//	}
//	return ncrModM;
//}

uint32_t ncrModM(uint32_t n, uint32_t r, uint32_t m) {
	uint32_t ncrModM = 1;
	uint32_t p;
	uint32_t nfPower;
	for (uint32_t i = 2; i < maxN; i++) {
		if (!C[i]) {
			nfPower = pFactorsAlt(n, i);
			nfPower -= pFactorsAlt(r, i);
			nfPower -= pFactorsAlt(n - r, i);
			if (nfPower == 0) continue;
			i = (uint32_t)pow(i, nfPower);
			ncrModM *= i % m;
			ncrModM %= m;
			if (ncrModM <= 0) break;
			if (nfPower < 0) break;
		}
	}
	return ncrModM;
}

uint32_t pFactorsInNFactorial(uint32_t n, uint32_t p) {
	uint32_t sum = 0, curP = p;
	for (uint32_t i = 1; curP <= n; i++) {
		sum += n / curP;
		curP *= p;
	}
	return sum;
}

uint32_t pFactorsAlt(uint32_t n, uint32_t p) {
	uint32_t baseNRemainder = n,
		maxPow = (uint32_t)(log(n) / log(p)),
		sumExp = 0;
	while (baseNRemainder > 0) {
		uint32_t curPPow = (uint32_t)pow(p, maxPow--);
		uint32_t curCoeff = baseNRemainder / curPPow;
		sumExp += curCoeff;
		baseNRemainder -= curCoeff * curPPow;
	}
	return (n - sumExp) / (p - 1);
}
