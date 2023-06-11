#include <stdio.h>
#include <stdlib.h>
int graf[100][100];
int N = 8;

/*     1    10
    A -- B ----- C
 3/   10/       /  \8
D  -----\    4/ |   H
 4\      3\  /  5\  /11
    E ----  F ---- G
        5       9
*/

void init_graph() {
  graf[1][2] = graf[2][1] = 1;
  graf[1][4] = graf[4][1] = 3;

  graf[2][4] = graf[4][2] = 10;
  graf[2][3] = graf[3][2] = 10;
  graf[2][6] = graf[6][2] = 3;

  graf[3][8] = graf[8][3] = 8;
  graf[3][6] = graf[6][3] = 4;
  graf[3][7] = graf[7][3] = 5;

  graf[8][7] = graf[7][8] = 11;

  graf[7][6] = graf[6][7] = 9;

  graf[6][5] = graf[5][6] = 5;

  graf[5][4] = graf[4][5] = 4;
}

int visited[100];

typedef struct edge {
    int x, y, val;
}EDGE;

EDGE create_edge(int x, int y, int val) {
    EDGE edge;
    edge.x = x;
    edge.y = y;
    edge.val = val;
    return edge;
}
int cmp(const void* a, const void *b) {
    return (*(EDGE*)a).val - (*(EDGE*)b).val;
}
// O(N^2 + V*logV)
void create_MST() {
    visited[1] = 1;
    EDGE edges[100];
    int no_edges = 0;
    // O(N^2)
    for(int i = 1; i < N; ++i) {
        for(int j = i + 1; j <= N; ++j) {
            if(graf[i][j]) {
                edges[no_edges++] = create_edge(i, j, graf[i][j]);
                edges[no_edges++] = create_edge(j, i, graf[i][j]);
            }
        }
    }
    // O(V * log V)
    qsort(edges, sizeof(EDGE), no_edges, cmp);
    // O(V)
    for(int i = 0; i < no_edges; ++i) {
        if(visited[edges[i].x] ^ visited[edges[i].y]) {
            printf("%d %d (%d)\n", edges[i].x, edges[i].y, edges[i].val);
            visited[edges[i].x] = visited[edges[i].y] = 1;
        }
    }
}
int main() {
    init_graph();
    create_MST();
}