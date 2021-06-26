#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <Accelerate/Accelerate.h>
#else
#include <cblas.h>
#endif
#include "mat.h"

void mmul0(mat * restrict c, const mat * restrict a, const mat * restrict b, int transA, int transB);

double get_time() {
  struct timeval tv; gettimeofday(&tv, NULL);
  return (tv.tv_sec + tv.tv_usec * 1e-6);
}

float randf() {
  return rand() / (RAND_MAX + 1.0f);
}

float randn(float mean, float std) {
  float  x = randf(),
         y = randf(),
         z = sqrtf(-2 * logf(x)) * cos(2 * M_PI * y);
  return std*z + mean;
}

#define timeit(expr)  \
  do { double ts=get_time(); \
       (expr); \
       double te=get_time(); \
       printf("`" #expr "` took %f s\n",\
           te-ts); \
  } while (0)

int main(int argc, char **argv) {

  mat a, b, c;

  if (argc < 6) {
    printf("usage: %s M N K At Bt\n", argv[0]);
    return -1;
  }

  unsigned M = strtoul(argv[1], NULL, 10);
  unsigned N = strtoul(argv[2], NULL, 10);
  unsigned K = strtoul(argv[3], NULL, 10);

  unsigned TA = strtoul(argv[4], NULL, 10);
  unsigned TB = strtoul(argv[5], NULL, 10);

  mat_alloc(&a, M, K);
  mat_alloc(&b, K, N);
  mat_alloc(&c, M, N);

  mat_zero(&a); mat_zero(&b); mat_zero(&c);

  for (int i=0; i<a.r*a.c; i++)
    a.data[i] = randn(0, 1);
  for (int i=0; i<b.r*b.c; i++)
    b.data[i] = randn(0, 1);

  printf("M = %d, N = %d, K = %d, TA = %d, TB = %d\n", M, N, K, TA, TB);

  //timeit(mmul0(&c, &a, &b, TA, TB));
  timeit(mmul1(&c, &a, &b, TA, TB));

  mat_dump(&a, "a.bin");
  mat_dump(&b, "b.bin");
  mat_dump(&c, "c.bin");

  mat_print(&a);
  mat_print(&b);
  mat_print(&c);

  mat_free(&a);
  mat_free(&b);
  mat_free(&c);

  return 0;
}

void mmul0(mat * restrict c,
     const mat * restrict a,
     const mat * restrict b,
     int transA, int transB) {

  enum CBLAS_TRANSPOSE at =
    (transA) ? CblasTrans : CblasNoTrans;
  enum CBLAS_TRANSPOSE bt =
    (transB) ? CblasTrans : CblasNoTrans;

  int M = c->r, N = c->c;
  int K = transA ? a->r : a->c;

  float alpha = 1.0f;
  float beta = 1.0f;

  int lda = transA ? M : K;
  int ldb = transB ? K : N;
  int ldc = N;

  cblas_sgemm( CblasRowMajor, at, bt, M, N, K,
               alpha,
               a->data, lda,
               b->data, ldb,
               beta,
               c->data, ldc );

}

void mmul1(mat * mc,
     const mat * ma,
     const mat * mb,
     int transA, int transB) {

  int M = mc->r, N = mc->c;
  int K = transA ? ma->r : ma->c ;

  float * restrict c = mc->data;
  float * restrict a = ma->data;
  float * restrict b = mb->data;

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
