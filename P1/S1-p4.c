#include <stdio.h>
#include "testbench-trie.h"

void afiseaza_invers(char litere[], int parinte[], int start) {
    if(parinte[start] != -1) {
        afiseaza_invers(litere, parinte, parinte[start]);
    }
    printf("%c", litere[start]);
}

// Parcurgem arborele in latime si pastram nodurile in coada
// impreuna cu indexul parintelui lor. Daca un nod este
// terminal (se termina un cuvant in el) atunci afisam
// drumul de la radacina la el. Deoarece am parcurs in latime
// drumul de la radacina la un nod terminal este cel mai scurt.

// O(n) - n = numarul de noduri in arbore
void afisare_short_word(NodArboreDeRegasire *trie) {
    NodArboreDeRegasire *coada[100];
    char litere[100]; // pastram litera corespunzatoare fiecarui nod
    int parinte[100]; // pastram index ul parintelui fiecarui nod
    int inceput = 0, sfarsit = 0;

    coada[sfarsit] = trie;
    parinte[sfarsit] = -1;
    litere[0] = '\0';

    while(inceput <= sfarsit) {
        NodArboreDeRegasire *nod = coada[inceput];
        if(nod->alfabet[char_to_index('[')] != NULL) { // cand dam de un final de word il afisam
            afiseaza_invers(litere, parinte, inceput); // afisam invers sa fie citibil
            puts("");
            return;
        }
        for(int i = 0; i < 26; ++i) {
            if(nod->alfabet[i] != NULL) {
                sfarsit++;
                litere[sfarsit] = i + 'A';
                coada[sfarsit] = nod->alfabet[i];
                parinte[sfarsit] = inceput;
            }
        }
        inceput++;
    }
}

int main() {
    NodArboreDeRegasire *trie = test_arbore_trie();
    afisare_short_word(trie);
    free_trie(trie);
    return 0;
}