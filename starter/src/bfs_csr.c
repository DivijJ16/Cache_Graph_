
#include <stdlib.h>
#include "graph.h"

int bfs_csr(CSRGraph* g, int source, int* dist) {
  if(!g) {
    return 0;
  }
  
  int n = g->num_vertices;
    
  for (int i = 0; i < n; i++) {
    dist[i] = -1;
  }

  int *arr = (int *)malloc(n*sizeof(int));

  int front = 0, end = 0;
  arr[end] = source;
  end++;
  dist[source] = 0;
  int visited = 1;

  while (end>front) {
    int nd = arr[front];
    front++;

    int start_idx = g->row_ptr[nd];
    int end_idx = g->row_ptr[nd + 1];

    for (int i = start_idx; i < end_idx; i++) {
      int child_nd = g->col_idx[i];
            
      if (dist[child_nd] == -1) {
        dist[child_nd] = dist[nd] + 1;
        arr[end] = child_nd;
        end++;
        visited++;
      }
    }
  }

  free(arr);
  return visited;
}
