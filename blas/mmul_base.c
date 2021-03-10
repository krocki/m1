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
      c[j*M+i] += a[k*M+i] * b[k+K*j];
  }

  //TN
  if (1==transA && 0==transB) {
    for (int j=0; j<N; j++)
    for (int i=0; i<M; i++)
    for (int k=0; k<K; k++)
      c[j*M+i] += a[k+K*i] * b[k+K*j];
  }

  //NT
  if (0==transA && 1==transB) {
    for (int i=0; i<M; i++)
    for (int j=0; j<N; j++)
    for (int k=0; k<K; k++)
      c[j*M+i] += a[k*M+i] * b[k*N+j];
  }

  //TT
  if (1==transA && 1==transB) {
    for (int j=0; j<N; j++)
    for (int i=0; i<M; i++)
    for (int k=0; k<K; k++)
      c[j*M+i] += a[k+K*i] * b[k*N+j];
  }
}
