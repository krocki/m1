enum CBLAS_ORDER      {CblasRowMajor=101, CblasColMajor=102};
enum CBLAS_TRANSPOSE  {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113};

void cblas_sgemm(
  const enum CBLAS_ORDER Order,
  const enum CBLAS_TRANSPOSE TransA,
  const enum CBLAS_TRANSPOSE TransB,
  const int M, const int N, const int K,
  const float alpha, const float *A,
  const int lda, const float *B, const int ldb,
  const float beta, float *C, const int ldc);

// blas-like raw calls
void _mmul0(int M, int N, int K, float * restrict c, const float * restrict a, const float * restrict b, int transA, int transB);
void _mmul1(int M, int N, int K, float * restrict c, const float * restrict a, const float * restrict b, int transA, int transB);

// using mat struct wrapper
//void mmul1(mat * mc, const mat * ma, const mat * mb, int transA, int transB);

