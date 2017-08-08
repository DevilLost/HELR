#include "Params.h"


Params::Params(long logN,  long logp, long logq, double sigma, double rho, long h) :
logN(logN),  logp(logp), logq(logq), sigma(sigma), rho(rho), h(h),  rotGroup(), rotGroupInv() {
    
    //-----------------------------------------
    
    N = 1 << logN;
    M = N << 1;
    Nh = N >> 1;
    logNh = logN - 1;

    //logq = logl + L;   // the largest modulus in the scheme
    logP = logq;
    logPq = logP + logq;
    power(p, 2, logp);
    power(q, 2, logq);
    power(Pq, 2, logPq);
    

    //qi = new ZZ[L];
    //Pqi = new ZZ[L];
    /*
    for (long i = 0; i < L; ++i) {
        long logql = logl + logp * (i + 1);
        power(qi[i], 2, logql);
        power(Pqi[i], 2, logql + logP);
    }*/


    rotGroup = new long*[logN];
    rotGroupInv = new long*[logN];
    
    for (long i = 0; i < logN; ++i) {
        long ipow = 1 << i;
        long ipow2 = ipow << 2;
        rotGroup[i] = new long[ipow];
        rotGroupInv[i] = new long[ipow];
        long val = 1;
        for (long j = 0; j < ipow; ++j) {
            rotGroup[i][j] = val;
            rotGroupInv[i][j] = ipow2 - val;
            val *= 3;
            val %= ipow2;
        }
    }
}

