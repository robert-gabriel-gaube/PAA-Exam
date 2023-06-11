#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MAX_N 100

typedef struct Nod { // Tine cate un employee
    char nume;
    int ID;    
    int parinte;     // In cazul nostru legatura cu boss ul direct
}NOD;

typedef struct Arbore {
    NOD noduri[MAX_N + 1];
    int size;       // Pozitia pana la care exista noduri valide
}ARBORE;


// Ne imaginam ca literele sunt nume

/*
            ArboreGen Test
                A1
            /   |   \
           B2   C3   D4
                |    |
                E5   G6
                    / \ 
                    H7 I8
                        \
                         J9                
*/

/*
            ArboreGen - Binary
                A1
              /
            B2
             \ 
              C3
              / \ 
            E5  D4
                /
               G6
              / 
            H7
             \ 
              I8
              /
             J9
*/

NOD make_nod(char nume, int ID, int parinte) {
    NOD nod;
    nod.nume = nume;
    nod.ID = ID;
    nod.parinte = parinte;
    return nod;
}

ARBORE test_arbore_gen_tablou() {
    ARBORE arbore;
    srand(time(NULL));
    arbore.noduri[1] = make_nod('A', rand(), -1);

    arbore.noduri[2] = make_nod('B', rand(), 1);
    arbore.noduri[3] = make_nod('C', rand(), 1);
    arbore.noduri[4] = make_nod('D', rand(), 1);

    arbore.noduri[5] = make_nod('E', rand(), 3);

    arbore.noduri[6] = make_nod('G', rand(), 4);

    arbore.noduri[7] = make_nod('H', rand(), 6);
    arbore.noduri[8] = make_nod('I', rand(), 6);

    arbore.noduri[9] = make_nod('J', rand(), 8);
    
    arbore.size = 9;
    return arbore;
}

int prim_fiu(ARBORE arbore, int parinte) {
    for(int idx = 1; idx <= arbore.size; ++idx) {
        if(arbore.noduri[idx].parinte == parinte) {
            return idx;
        }
    }
    return 0;
}
int next_fiu(ARBORE arbore, int parinte, int fiu) {
    for(int idx = fiu + 1; idx <= arbore.size; ++idx) {
        if(arbore.noduri[idx].parinte == parinte) {
            return idx;
        }
    }
    return 0;
}

void afisare_preordine(ARBORE arbore, int pozitie) {
    if(!pozitie) return;

    printf("%c ", arbore.noduri[pozitie].nume);
    int index_fiu = prim_fiu(arbore, pozitie);
    afisare_preordine(arbore, index_fiu);
    index_fiu = next_fiu(arbore, pozitie, index_fiu);
    while(index_fiu) {
        afisare_preordine(arbore, index_fiu);
        index_fiu = next_fiu(arbore, pozitie, index_fiu);
    }
}