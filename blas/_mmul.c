#include "_mmul.h"

void _mmul0(
    int M, int N, int K,
    float * restrict c,
    const float * restrict a,
    const float * restrict b,
    int transA, int transB) {

  enum CBLAS_TRANSPOSE at =
    (transA) ? CblasTrans : CblasNoTrans;
  enum CBLAS_TRANSPOSE bt =
    (transB) ? CblasTrans : CblasNoTrans;

  float alpha = 1.0f;
  float beta = 1.0f;

  int lda = transA ? M : K;
  int ldb = transB ? K : N;
  int ldc = N;

  cblas_sgemm(
     CblasRowMajor,
     at, bt, M, N, K,
     alpha,
     a, lda,
     b, ldb,
     beta,
     c, ldc );
}

void mmul1(
    int M, int N, int K,
    float * restrict c,
    const float * restrict a,
    const float * restrict b,
    int transA, int transB) {

  //NN
  if (0==transA && 0==transB) {
    for (int i=0; i<M; i++)
    for (int j=0; j<N; j++)
    for (int k=0; k<K; k++)
      c[i*N+j] += a[i*K+k] * b[j+N*k];
  }

  //TN
  if (1==transA && 0==transB) {
    for (int j=0; j<N; j++)
    for (int i=0; i<M; i++)
    for (int k=0; k<K; k++)
      c[i*N+j] += a[i+M*k] * b[j+N*k];
  }

  //NT
  if (0==transA && 1==transB) {
    for (int i=0; i<M; i++)
    for (int j=0; j<N; j++)
    for (int k=0; k<K; k++)
      c[i*N+j] += a[i*K+k] * b[j*N+k];
  }

  //TT
  if (1==transA && 1==transB) {
    for (int j=0; j<N; j++)
    for (int i=0; i<M; i++)
    for (int k=0; k<K; k++)
      c[i*N+j] += a[i+M*k] * b[j*N+k];
  }
}

