typedef int Cursor;
typedef char TipCheie;
#define MAX_N 100

// Am ales aceste structuri de date deoarece asa ne-au fost prezentate in laborator
typedef struct Zona {
    TipCheie cheie;                  //cheia nodului
    Cursor primul_fiu, frate_drept;
}Zona;

typedef struct Arbore {
    Zona noduri[MAX_N + 1];
    Cursor radacina;                //pozitia radacinii
}Arbore;

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

Arbore arbore_gen_test() {
    Arbore arbore;
    arbore.radacina = 1;
    arbore.noduri[1].cheie = 'A';
    arbore.noduri[1].primul_fiu = 2;
    arbore.noduri[1].frate_drept = 0;

    arbore.noduri[2].cheie = 'B';
    arbore.noduri[2].primul_fiu = 0;
    arbore.noduri[2].frate_drept = 3;

    arbore.noduri[3].cheie = 'C';
    arbore.noduri[3].primul_fiu = 5;
    arbore.noduri[3].frate_drept = 4;

    arbore.noduri[4].cheie = 'D';
    arbore.noduri[4].primul_fiu = 6;
    arbore.noduri[4].frate_drept = 0;

    arbore.noduri[5].cheie = 'E';
    arbore.noduri[5].primul_fiu = 0;
    arbore.noduri[5].frate_drept = 0;

    arbore.noduri[6].cheie = 'G';
    arbore.noduri[6].primul_fiu = 7;
    arbore.noduri[6].frate_drept = 0;

    arbore.noduri[7].cheie = 'H';
    arbore.noduri[7].primul_fiu = 0;
    arbore.noduri[7].frate_drept = 8;

    arbore.noduri[8].cheie = 'I';
    arbore.noduri[8].primul_fiu = 9;
    arbore.noduri[8].frate_drept = 0;

    return arbore;
}