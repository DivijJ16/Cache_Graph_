
#include "graph.h"

int sz(int front, int end) { // since q contains elements from arrr[front->end-1], sie - end-front
  return end-front;
}
int bfs_pointer(Graph *g, int source, int *dist) {
  int n = g->num_vertices;
  for (int i = 0; i < n; i++) {
    dist[i] = -1;
  }
  // used array to implement a queue.
  int arr[n+1];
  int front = 0, end = 0; // idx of the 1st and last elements of the queue, insert happend at end and delete at front
  arr[end] = source;
  end++;
  dist[source] = 0;
  int visited = 1;
  while (sz(front,end) > 0) {
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
  return visited;
  }
