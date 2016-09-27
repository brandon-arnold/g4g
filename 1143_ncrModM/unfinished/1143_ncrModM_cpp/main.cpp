#include <iostream>
#include <math.h>
using namespace std;

unsigned ncrModM(unsigned n, unsigned r, unsigned m);
unsigned pFactorsInNFactorial(unsigned n, unsigned p);
unsigned pFactorsAlt(unsigned n, unsigned p);
void doSieve();
const unsigned maxN = 1000000000;

int main() {
  unsigned numProbs, n, r, m;
  unsigned result;
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

const int BLOCKSIZE =1<<16;
const unsigned sqrtMaxN = 31622;
bool C[BLOCKSIZE];
unsigned Primes[50847534];   // primes to use in the sieve
unsigned First[50847534];   // next integer divisible by p (delta form block start)
unsigned NP = 0;

void doSieve(){
  for(unsigned p = 2; p <= sqrtMaxN; ++p)
    if( !C[p] ) {
      Primes[NP] = p;
      First[NP] = p*p;
      NP++;
      for(unsigned n = p*p; n <= BLOCKSIZE; n+=p)
        C[n] = 1;
    }
  for(unsigned B = sqrtMaxN + 1; B < maxN; B+=BLOCKSIZE) {
    for(int j = 0; j < BLOCKSIZE; j++) {
      C[j] = 0;
    }
    for(unsigned k = 0; k < NP; ++k) {
      unsigned p = Primes[k];
      unsigned t = First[k];
      for( ; t < BLOCKSIZE; t+=p )
        C[t] = 1;
      First[k] = t-BLOCKSIZE;
    }
    for(unsigned c = 0; c < BLOCKSIZE; c++) {
      if( !C[c] ) {
        unsigned p = B + c;
        Primes[NP] = p;
        First[NP] = p*p;
        if(NP == 3402) {
          cout << NP;
          cout << " ";
          cout << p << endl;
        }
        NP++;
        for(unsigned n = p*p; p <= BLOCKSIZE; n+=p)
          C[n] = 1;
      }
    }
  }
}

unsigned ncrModM(unsigned n, unsigned r, unsigned m) {
  unsigned ncrModM = 1;
  unsigned p;
  unsigned nfPower;
  for(unsigned i = 0; (i < 50847534 && Primes[i] <= n); i++) {
    p = Primes[i];
    cout << p;
    if(p < 1) break;
    nfPower = pFactorsInNFactorial(n, p);
    nfPower -= pFactorsInNFactorial(r, p);
    nfPower -= pFactorsInNFactorial(n - r, p);
    if(nfPower == 0) continue;
    p = (int)pow(p, nfPower);
    cout << ' ';
    cout << p;
    cout << ' ';
    cout << ncrModM;
    ncrModM *= p % m;
    ncrModM %= m;
    cout << ' ';
    cout << ncrModM;
    cout << ' ';
    cout << m << endl;
    if(ncrModM <= 0) break;
    if(nfPower < 0) break;
  }
  return ncrModM;
}

unsigned pFactorsInNFactorial(unsigned n, unsigned p) {
  unsigned sum = 0, curP = p;
  for(unsigned i = 1; curP <= n; i++) {
    sum += n / curP;
    curP *= p;
  }
  return sum;
}

unsigned pFactorsAlt(unsigned n, unsigned p) {
  unsigned baseNRemainder = n,
    maxPow = (unsigned)(log(n)/log(p)),
    sumExp = 0;
  while(baseNRemainder > 0) {
    unsigned curPPow = (unsigned)pow(p, maxPow--);
    unsigned curCoeff = baseNRemainder / curPPow;
    sumExp += curCoeff;
    baseNRemainder -= curCoeff * curPPow;
  }
  return (n - sumExp) /(p - 1);
}
