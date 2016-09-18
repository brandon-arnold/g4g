package io.bna.g2g.ncrmodm;

/**
 * Created by brand on 9/18/2016.
 */
public class NcrModMStrategy {

    public static void main (String[] args) {
        int numProbs = Integer.parseInt(args[0]),
            curProb = 0;
        while(curProb < numProbs) {
            int n = Integer.parseInt(args[curProb * 3 + 1]),
                r = Integer.parseInt(args[curProb * 3 + 2]),
                m = Integer.parseInt(args[curProb * 3 + 3]);
            int result = ncrModM(n, r, m);
            System.out.println(Integer.toString(result));
            curProb++;
        }
    }

    public static int ncrModM(int n, int r, int m) {
        int ncrModM = 1;
        int sqrtN = (int)Math.sqrt(n);

        // perform sieve to sqrtN
        boolean[] sieve = new boolean[n + 1];
        for(int i = 0; i < n + 1; i++) sieve[i] = true;
        for(int i = 2; i <= sqrtN; i++)
            if(sieve[i])
                for (int j = i; j <= n / i; j++)
                    sieve[j * i] = false;

        // get integer to primes mapping
        int numPrimes = 0;
        for(int i = 2; i < n+1; i++)
            if(sieve[i]) numPrimes++;
        int[] nthPrime = new int[numPrimes];
        int curPrime = 0;
        for(int i = 2; i < n + 1; i++)
            if(sieve[i])
                nthPrime[curPrime++] = i;

        // get prime factorization of n!/r!(n-r)!
        int[] nFact = new int[numPrimes];
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
            ncrModM = (ncrModM * (int)Math.pow(nthPrime[i], nFact[i])) % m;

        return ncrModM;
    }

    public static int pFactorsInNFactorial(int n, int p) {
        int baseNRemainder = n,
            maxPow = (int)(Math.log(n)/Math.log(p)),
            sumExp = 0;
        while(baseNRemainder > 0) {
            int curPPow = (int)Math.pow(p, maxPow--);
            int curCoeff = baseNRemainder / curPPow;
            sumExp += curCoeff;
            baseNRemainder -= curCoeff * curPPow;
        }
        return (n - sumExp) /(p - 1);
    }
}
