#include <stdio.h>
int graf[100][100];
int N = 8;

/*
    1 -- 2 ----- 3
  /     /       /  \
4  -----        |   8
  \              \  /
    5 ----  6 ---- 7

*/

void init_graph() {
  graf[1][4] = graf[4][1] = 1;
  graf[1][2] = graf[2][1] = 1;

  graf[2][4] = graf[4][2] = 1;
  graf[2][3] = graf[3][2] = 1;

  graf[3][8] = graf[8][3] = 1;
  graf[3][7] = graf[7][3] = 1;

  graf[8][7] = graf[7][8] = 1;

  graf[7][6] = graf[6][7] = 1;

  graf[6][5] = graf[5][6] = 1;

  graf[5][4] = graf[4][5] = 1;
}
typedef enum state {NOT_STARTED, IN_PROGRESS, DONE} STATE;

STATE states[100];
int time[100], parent[100];

// Functioneaza in felul urmator: Initial toate nodurile sunt NOT_STARTED, nu 
// au inceput sa fie parcurse. In momentul in care se parcurg se pun in IN_PROGRESS
// In momentul in care s-a terminat parcurgerea acestuia si a celorlalti vecini ai
// lui se pune pe DONE. Daca intr-un moment avem un drum de la nodul curent la unul
// IN_PROGRESS inseamna ca am dat de un ciclu (inafara de cazul in care este parintele
// acestuia). De asemenea pastram intr-un vector time care este distanta de parcurgere
// de la nodul initial. Astfel putem afla distanta ciclului 
// time[nod_actual] - time[nod_incepere_ciclu] + 1.

// O(N + M) - N = numarul de noduri, M = numarul de arce


void cycles(int nod) {
  states[nod] = IN_PROGRESS;
  for(int idx = 1; idx <= N; ++idx) {
    if(graf[nod][idx]) {
      if(states[idx] == NOT_STARTED) { // Daca nu e started incepem parcurgerea lui
        parent[idx] = nod;
        time[idx] = time[nod] + 1;
        cycles(idx);
      } else if (states[idx] == IN_PROGRESS && time[nod] - time[idx] != 1) { // Daca e started si ciclul e cel putin de lungime 3 inseamna ca avem un ciclu valid
        printf("We have a cycle on %d of length %d\n", idx, time[nod] - time[idx] + 1);
        // Parte de afisare ciclu daca este nevoie.
        int copy = nod;
        printf("%d ", idx);
        while(copy != idx) {
          printf("%d ", copy);
          copy = parent[copy];
        }
        printf("%d \n", copy);
      }
    }
  }
  states[nod] = DONE;
}

int main() {
  init_graph();
  for(int idx = 1; idx <= N; ++idx) {
    states[idx] = NOT_STARTED;
  }
  parent[1] = 0;
  for(int idx = 1; idx <= N; ++idx) {
    if(states[idx] == NOT_STARTED) {
      cycles(idx);
    }
  }
}

