typedef struct {
  float *data;
  int r, c, n;
  enum { col_major, row_major } order;
} mat;

void  mat_alloc(mat *m, int r, int c);
void  mat_free(mat *m);
void  mat_print(mat *m);
float mat_cmp(mat *a, mat *b, int print);
float mat_norm(mat *a);
float mat_min(mat *a);
float mat_max(mat *a);
float mat_avg(mat *a);
void  mat_zero(mat *a);
void  mat_dump(mat *a, const char *fn);
void  mat_read_txt(mat *m, const char *fn);
void  mmul0(mat *c, const mat *a, const mat *b, int, int);
void  mmul1(mat *c, const mat *a, const mat *b, int, int);
