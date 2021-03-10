#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mat.h"

extern void mat_alloc(mat *m, int r, int c);

void mat_read_txt(mat *m, const char *fn) {

  FILE *f = fopen(fn, "r");
  if (!f) return;

  int res=fscanf(f, "%d %d", &(m->r), &(m->c));
  if (!res) fprintf(stderr, "fscanf err\n");

  int r=m->r, c=m->c;

  mat_alloc(m, r, c);

  for (int j=0; j<r; j++) {
    for (int i=0; i<c; i++) {
      res=fscanf(f, "%f", &(m->data[i*r+j]));
      if (!res) fprintf(stderr, "fscanf err\n");
      //printf("%12f", m->data[i*r+j]);
    }
    //printf("\n");
  }

  fclose(f);

}

void dump_arr_f(int n, float *m, const char *fn) {
  FILE *f = fopen(fn, "wb");
  if (!f) return;
  fwrite(m, n, sizeof(float), f);
  fclose(f);
}

void dump_arr_i(int n, int *m, const char *fn) {
  FILE *f = fopen(fn, "wb");
  if (!f) return;
  fwrite(m, n, sizeof(int), f);
  fclose(f);
}

void mat_dump(mat *m, const char *fn) {
  if (!m) return;
  size_t n = m->c * m->r;
  dump_arr_f(n, m->data, fn);
}

void mat_alloc(mat *m, int r, int c) {
  m->data = calloc(r * c, sizeof(float));
  m->r = r; m->c = c;
  m->n = r * c;
  m->order = row_major;
}

void mat_free(mat *m) {
  free(m->data); m->data = NULL;
  m->r = 0; m->c = 0;
}

int print_f(float *f) {
  if (fabs(*f)>1e-6) {
    printf("%6.3f", *f);
    return 1;
  }
  else {
    printf("  --- ");
    return 0;
  }
}

void mat_print(mat *m) {
  printf("===== %d %d %s =====\n",
  m->r, m->c,
  m->order == col_major ?
  "col_major" : "row_major");

  printf(" ");
  for (size_t i=0; i<m->c; i++)
    printf("%6zu ", i);
  printf("\n");

  int nnz = 0;
  for (size_t j=0; j<m->r; j++) {
    printf("%2zu ", j);
    for (int i=0; i<m->c; i++) {
      nnz+=print_f(&(m->data[j*m->c+i]));
      if (i==(m->c-1)) {
        printf("%s", nnz==0 ? "\r" : "\n");
        nnz = 0;
      }
      else printf(" ");
    }
  }
}

void mat_zero(mat *m) {
  int n = m->r * m->c;
  memset(m->data, 0, n * sizeof(float));
}
