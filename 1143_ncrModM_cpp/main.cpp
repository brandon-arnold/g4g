#include <iostream>
#include <math.h>
using namespace std;

int ncrModM(int n, int r, int m);
int pFactorsInNFactorial(int n, int p);

int main() {
  int numProbs, n, r, m, result;
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

int ncrModM(int n, int r, int m) {
  int ncrModM = 1;
  int sqrtN = (int)sqrt(n);

  // perform sieve to sqrtN
  bool* sieve = new bool[n + 1];
  for(int i = 0; i < n + 1; i++) sieve[i] = true;
  for(int i = 2; i <= sqrtN; i++)
    if(sieve[i])
      for (int j = i; j <= n / i; j++)
        sieve[j * i] = false;

  // get integer to primes mapping
  int numPrimes = 0;
  for(int i = 2; i < n+1; i++)
    if(sieve[i]) numPrimes++;
  int* nthPrime = new int[numPrimes];
  int curPrime = 0;
  for(int i = 2; i < n + 1; i++)
    if(sieve[i])
      nthPrime[curPrime++] = i;

  // get prime factorization of n!/r!(n-r)!
  int* nFact = new int[numPrimes];
  for(int i = 0; i < numPrimes; i++) {
    //add factorization of n!
    nFact[i] = pFactorsInNFactorial(n, nthPrime[i]);

    //subtract factorization of r!
    nFact[i] -= pFactorsInNFactorial(r, nthPrime[i]);

    //subtract factorization of (n-r)!
    nFact[i] -= pFactorsInNFactorial(n - r, nthPrime[i]);
  }

  // perform mod of M by reduction technique
  for(int i = 0; i < numPrimes; i++)
    ncrModM = (ncrModM * (int)pow(nthPrime[i], nFact[i])) % m;

  delete [] sieve;
  delete [] nthPrime;
  delete [] nFact;
  return ncrModM;
}

int pFactorsInNFactorial(int n, int p) {
  int baseNRemainder = n,
    maxPow = (int)floor(log(n)/log(p)),
    sumExp = 0;
  while(baseNRemainder > 0) {
    int curPPow = (int)pow(p, maxPow--);
    int curCoeff = baseNRemainder / curPPow;
    sumExp += curCoeff;
    baseNRemainder -= curCoeff * curPPow;
  }
  return (n - sumExp) /(p - 1);
}
