#include <stdio.h>
#include "testbench-trie.h"

// Numara cate litere si cate cuvinte sunt in trie
// Parcurgem arborele in latime si pastram nodurile in coada
// impreuna cu nivelul lor in arbore. Daca un nod este 
// terminal (se termina un cuvant in el) atunci adaugam
// nivelul sau la numarul total de litere si incrementam
// numarul de cuvinte.

// O(n) - n = numarul de noduri in arbore
float average_word_size(NodArboreDeRegasire *trie) {
    NodArboreDeRegasire *coada[100];
    int nivele[100];
    int inceput = 0, sfarsit = 0;

    coada[sfarsit] = trie;
    nivele[sfarsit] = 0;

    float nr_cuvinte = 0, nr_litere = 0;
    while(inceput <= sfarsit) {
        NodArboreDeRegasire *nod = coada[inceput];
        if(nod->alfabet[char_to_index('[')] != NULL) {
            nr_cuvinte++;
            nr_litere += nivele[inceput];
        }
        for(int i = 0; i < 26; ++i) {
            if(nod->alfabet[i] != NULL) {
                sfarsit++;
                coada[sfarsit] = nod->alfabet[i];
                nivele[sfarsit] = nivele[inceput] + 1;
            }
        }
        inceput++;
    }
    return nr_litere / nr_cuvinte;
}

int main() {
    NodArboreDeRegasire *trie = test_arbore_trie();
    printf("%f\n", average_word_size(trie));
    free_trie(trie);
    return 0;
}