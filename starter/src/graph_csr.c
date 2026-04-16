
#include <stdlib.h>
#include "graph.h"
CSRGraph *convert_to_csr(Graph *g) {
  if (!g) {
    return NULL;
  }
  int n = g->num_vertices;
  int m = 0; // cnt vertices
  for (int i = 0; i < n; i++) {
    Edge *curredge = g->vertices[i].head;
    while (curredge) {
      m++;
      curredge = curredge->next;
    }
  }
  int* row_ptr = (int*)malloc((n+1)*sizeof(int));
  int *col_idx = (int *)malloc(m * sizeof(int));

  CSRGraph *csr = (CSRGraph *)malloc(sizeof(CSRGraph));
  csr->num_vertices = n;
  csr->num_edges = m;
  csr->row_ptr = row_ptr;
  csr->col_idx = col_idx;

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    csr->row_ptr[i] = cnt; // start of edges of ith node
    Edge *curredge = g->vertices[i].head;
    while (curredge) {
      csr->col_idx[cnt] = curredge->dst;
      curredge = curredge->next;
      cnt++;
    }
  }
  csr->row_ptr[n] = m;
  return csr;
  
}


void free_csr(CSRGraph *g) {
  if (!g){
    return;
  }
  free(g->row_ptr);
  free(g->col_idx);
  free(g);
}

