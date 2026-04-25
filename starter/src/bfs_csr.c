
#include <stdlib.h>
#include "graph.h"

int bfs_csr(CSRGraph* g, int source, int* dist) {
  if(!g || !dist || source < 0) {
    return 0;
  }
  
  int n = g->num_vertices;

  if(n <= 0 || source >= n) {
    return 0;
  }
    
  for (int i = 0; i < n; i++) {
    dist[i] = -1;
  }

  int *arr = (int *)malloc((n)*sizeof(int));

  if(!arr) {
    return 0;
  }

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
      int next_nd = g->col_idx[i];
            
      if (dist[next_nd] == -1) {
        dist[next_nd] = dist[nd] + 1;
        arr[end] = next_nd;
        end++;
        visited++;
      }
    }
  }

  free(arr);
  return visited;
}
