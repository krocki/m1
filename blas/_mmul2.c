#include "_mmul2.h"

#define __mmul2(M, N, K) \
void _mmul2_ ##M ##_ ##N ##_ ##K ##_NN ( \

float * restrict c, const float * restrict a, const float * restrict b) { \
    for (int i=0; i<M; i++) \
    for (int j=0; j<N; j++) \
    for (int k=0; k<K; k++) \
      c[i*N+j] +=           \
      a[i*K+k] * b[j+N*k];  }

__mmul2( 4, 4, 4)
__mmul2( 8, 8, 8)
__mmul2(16,16,16)
__mmul2(32,32,32)
