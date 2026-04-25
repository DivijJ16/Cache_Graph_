#include <stdlib.h>
#include "graph.h"

CSRGraph *convert_to_csr(Graph *g) {
  if (!g) {
    return NULL;
  }

  int n = g->num_vertices;

  if(n<=0) {
    return NULL;
  }

  int m = 0; // cnt edges
  for (int i = 0; i < n; i++) {
    Edge *curredge = g->vertices[i].head;
    while (curredge) {
      m++;
      curredge = curredge->next;
    }
  }

  CSRGraph *csr = (CSRGraph *)malloc(sizeof(CSRGraph));

  if(!csr) {
    return NULL;
  }

  csr->num_vertices = n;
  csr->num_edges = m;
  csr->row_ptr = (int *)malloc((n+1)*sizeof(int));

  if(!csr->row_ptr) {
    free(csr);
    return NULL;
  }

  if(m>0) {
    csr->col_idx = (int *)malloc((m)*sizeof(int));

    if(!csr->col_idx) {
      free_csr(csr);
      return NULL;
    }
  } else {
    csr->col_idx = NULL;
  }

  int curr_idx = 0;
  for (int i = 0; i < n; i++) {
    csr->row_ptr[i] = curr_idx; // start of edges of ith node
    Edge *curredge = g->vertices[i].head;
    while (curredge) {
      csr->col_idx[curr_idx] = curredge->dst;
      curredge = curredge->next;
      curr_idx++;
    }
  }

  csr->row_ptr[n] = m;
  return csr;
}


void free_csr(CSRGraph *g) {
  if (!g) {
    return;
  }

  free(g->row_ptr);
  free(g->col_idx);
  free(g);
}

