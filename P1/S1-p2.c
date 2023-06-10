#include "testbench-arboregen.h"
#include <stdio.h>

// Functia returneaza 1 + maximul dintre inaltimiile subarborilor
// care la randul lor sunt aflate recursiv. Drumul maxim este defapt
// inaltimea arborelui.
// O(n) - n este numarul de noduri
int inaltime_arbore(Arbore arbore, Cursor pozitie) {
    if (arbore.noduri[pozitie].primul_fiu == 0) {
        return 1;
    }
    int primul_fiu = arbore.noduri[pozitie].primul_fiu;
    int primul_fiu_drept = arbore.noduri[primul_fiu].frate_drept;
    int inaltime_fiu = inaltime_arbore(arbore, primul_fiu); // initializam cu inaltimea primul fiu

    while(primul_fiu_drept) { // Cat timp mai exista subarborii
        int inaltime_fiu_drept = inaltime_arbore(arbore, primul_fiu_drept);
        if (inaltime_fiu_drept > inaltime_fiu) { // Pastram inaltimea maxima
            inaltime_fiu = inaltime_fiu_drept;
        }
        primul_fiu_drept = arbore.noduri[primul_fiu_drept].frate_drept;
    }

    return 1 + inaltime_fiu; // 1 + inaltimea maxima a subarborilor deoarece ne aflam pe un nivel mai sus
}

int main() {
    Arbore arbore = arbore_gen_test();
    printf("%d", inaltime_arbore(arbore, 1));
    return 0;
}