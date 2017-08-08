#include "PubKey.h"

#include "NumUtils.h"
#include "Ring2Utils.h"
#include <NTL/BasicThreadPool.h>

PubKey::PubKey(Params& params, SecKey& secretKey) : axKeySwitch(), bxKeySwitch() {
    ZZX ex, sxsx;
    
    NumUtils::sampleUniform2(ax, params.N, params.logq);
    NumUtils::sampleGauss(ex, params.N, params.sigma);
    Ring2Utils::mult(bx, secretKey.sx, ax, params.q, params.N);
    Ring2Utils::sub(bx, ex, bx, params.q, params.N);
    
    //-----------------------------------------
    
    axKeySwitch = new ZZX[params.logNh];
    bxKeySwitch = new ZZX[params.logNh];
    
    
    for (long i = 0; i < params.logNh; ++i) {
        ZZX spow;
        long ipow = (1 << i);
        Ring2Utils::inpower(spow, secretKey.sx, params.rotGroup[params.logNh][ipow], params.q, params.N);
        Ring2Utils::leftShiftAndEqual(spow, params.logP, params.logPq, params.N);
        NumUtils::sampleUniform2(axKeySwitch[i], params.N, params.logPq);
        NumUtils::sampleGauss(ex, params.N, params.sigma);
        Ring2Utils::addAndEqual(ex, spow, params.Pq, params.N);
        Ring2Utils::mult(bxKeySwitch[i], secretKey.sx, axKeySwitch[i], params.Pq, params.N);
        Ring2Utils::sub(bxKeySwitch[i], ex, bxKeySwitch[i], params.Pq, params.N);
    }
    
    
    //-----------------------------------------
    
    Ring2Utils::mult(sxsx, secretKey.sx, secretKey.sx, params.q, params.N);
    Ring2Utils::leftShiftAndEqual(sxsx, params.logP, params.logPq, params.N);
    NumUtils::sampleUniform2(axStar, params.N, params.logPq);
    NumUtils::sampleGauss(ex, params.N, params.sigma);
    Ring2Utils::addAndEqual(ex, sxsx, params.Pq, params.N);
    Ring2Utils::mult(bxStar, secretKey.sx, axStar, params.Pq, params.N);
    Ring2Utils::sub(bxStar, ex, bxStar, params.Pq, params.N);
    
    //-----------------------------------------
}
