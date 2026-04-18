
#include "graph.h"
#include <stdlib.h>

int bfs_pointer(Graph *g, int source, int *dist) {
  if(!g) {
    return 0;
  }
  
  int n = g->num_vertices;

  for (int i = 0; i < n; i++) {
    dist[i] = -1;
  }

  int *arr = (int *)malloc((n+1)*sizeof(int));
  
  int front = 0, end = 0; // idx of the 1st and last elements of the queue, insert happend at end and delete at front
  arr[end] = source;
  end++;
  dist[source] = 0;
  int visited = 1;

  while (end>front) {
    int nd = arr[front];
    front++;
    Edge *curredge = g->vertices[nd].head;
    while (curredge) {
      int child = curredge->dst;
      if (dist[child] == -1) {
        dist[child] = dist[nd] + 1;
        arr[end] = child;
        end++;
        visited++;
      }
      curredge = curredge->next;
    }
  }

  free(arr);

  return visited;
}
