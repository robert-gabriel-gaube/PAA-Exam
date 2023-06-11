#include <stdio.h>
#include <stdlib.h>
#define INF __INT_MAX__
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

typedef struct elem {
    int nod, distanta_nod;
}ELEM;

int distances[100];
int cmp(const void *a, const void *b) {
    return (*(ELEM*)a).distanta_nod - (*(ELEM*)b).distanta_nod;
}

ELEM make_elem(int nod, int distanta_nod) {
    ELEM elem;
    elem.nod = nod;
    elem.distanta_nod = distanta_nod;
    return elem;
}

// Pentru ca folosesc quick sort la fiecare pas

// O(N^2 * log N)
void dijkstra() {
    for(int i = 1; i <= N; ++i) {
        distances[i] = INF;
    }
    ELEM elemente[100];
    distances[1] = -1;
    int start = 0, end = 0;
    elemente[0] = make_elem(1, 0);

    while(start <= end) {
        qsort(elemente + start, end - start + 1, sizeof(ELEM), cmp);
        ELEM current = elemente[start++];
        int current_node = current.nod;
        int current_distance = current.distanta_nod;

        for(int nod = 1; nod <= N; ++nod) {
            int distance = graf[current_node][nod];
            if(distance) {
                if(current_distance + distance < distances[nod]) {
                    distances[nod] = current_distance + distance;
                    elemente[++end] = make_elem(nod, distances[nod]);
                }
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        printf("%d (%d) ", i, distances[i]);
    }
    puts("");
}

int main() {
    init_graph();
    dijkstra();
    return 0;
}