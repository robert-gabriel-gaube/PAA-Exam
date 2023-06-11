#include "testbench-arboregen-tablou.h"
#include <stdio.h>

/*
Well damn ce sa zic problema asta cred ca am complicat o.
Nu cred ca e usor de inteles so spor who s reading this.
*/


typedef struct Nod_binar {
    char nume;
    int ID;
    struct Nod_binar *stanga;
    struct Nod_binar *dreapta;
}NOD_BINAR;

typedef struct Arbore_binar {
    NOD_BINAR* root;
}ARBORE_BINAR;


void show_preorder_recursive(NOD_BINAR const* node) {
    if(node) {
        printf("%c ", node->nume);
        show_preorder_recursive(node->stanga);
        show_preorder_recursive(node->dreapta);
    }
}

void print_ordered_preorder_binary_tree(ARBORE_BINAR binary_tree) {
    show_preorder_recursive(binary_tree.root);
    printf("\n");
}

void dealloc_bin_tree(NOD_BINAR* arbore) {
    if(arbore) {
        dealloc_bin_tree(arbore->stanga);
        dealloc_bin_tree(arbore->dreapta);
        free(arbore);
    } 
}  

// Returneaza adresa catre un pointer de tip nod_binar 
// Adica adresa unui nod din arbore care are valorile egale cu
// cele din nod. Am pus dupa nume aici ca sa vad eu daca merge
// dar in problema se cere dupa ID

// O(n) - n = numar total de noduri

NOD_BINAR** find_nod(NOD_BINAR** arbore_binar, NOD nod) {
    if((*arbore_binar) == NULL) return NULL;
    if((*arbore_binar)->nume == nod.nume) {
        return arbore_binar;
    } else {
        NOD_BINAR **stanga = find_nod(&((*arbore_binar)->stanga), nod);
        NOD_BINAR **dreapta = find_nod(&((*arbore_binar)->dreapta), nod);
        if(stanga) return stanga;
        if(dreapta) return dreapta;
        return NULL;
    }
}

// Insereaza in arbore binar. Nodul nod ca fiu al nodului parinte (exista deja in arbore)
// direction = 1 inseamna stanga si = 0 inseamna dreapta. Daca nu exista radacina inca
// va adauga nodul ca radacina si atat.

// O(log n)

void insert_binary_tree(ARBORE_BINAR *binary_tree, NOD nod, NOD parinte, int direction) {
    NOD_BINAR *new_node = (NOD_BINAR*)malloc(sizeof(NOD_BINAR));
    new_node->nume = nod.nume;
    new_node->ID = nod.ID;
    new_node->dreapta = NULL;
    new_node->stanga = NULL;

    if(binary_tree->root == NULL) {
        binary_tree->root = new_node;    
    } else {
        NOD_BINAR** adresa_parinte = find_nod(&(binary_tree->root), parinte);
        if(direction) (*adresa_parinte)->stanga = new_node;
        else (*adresa_parinte)->dreapta = new_node;
    }
}
/*
Ok well aici a fost mai greu pentru ca a spus dreq sa fie sub forma de tablou
So ideea e ca in laborator primul fiu al unui nod parinte devine fiul stang al
lui parinte si orice frate drept al primului fiu devine fiul drept al fiului 
anterior 
Ex: 
     A                       A
   / | \         ->        /
  B  C  D                 B
                            \
                             C
                               \
                                 D

So aici am facut exact asta.

O(n)
*/

ARBORE_BINAR transform_to_bt(ARBORE arbore) {
    ARBORE_BINAR binary_tree;
    binary_tree.root = NULL;
    // Prima data introducem radacina 
    insert_binary_tree(&binary_tree, arbore.noduri[1], arbore.noduri[1], 0);

    // Aici am decis sa fac o parcurgere in latime sa nu ma complic ( :) ). 
    // Cu o coada.
    int coada[100], inceput = 0, sfarsit = 0;
    coada[0] = 1;
    while(inceput <= sfarsit) {
        int parinte = coada[inceput];
        int index_prim_fiu = prim_fiu(arbore, parinte);
        if(index_prim_fiu) { // Daca exista prim fiu
            // Il adaugam ca fiu stang al nodului parinte
            insert_binary_tree(&binary_tree, arbore.noduri[index_prim_fiu], arbore.noduri[parinte], 1);
            // Si il bagam in coada
            coada[++sfarsit] = index_prim_fiu;
            // Ultimul fiu care l-am procesat e primul fiu 
            int last_fiu = index_prim_fiu;
            // Cautam urmatorul fiu
            int index_fiu = next_fiu(arbore, parinte, index_prim_fiu);
            while(index_fiu) { // Cat timp exista alti fii
                // Ii bagam in coada
                coada[++sfarsit] = index_fiu;
                // Si ii introducem in arbore ca fiu drept al ultimului fiu procesat
                insert_binary_tree(&binary_tree, arbore.noduri[index_fiu], arbore.noduri[last_fiu], 0);

                // Pasi de actualizare
                last_fiu = index_fiu;
                index_fiu = next_fiu(arbore, parinte, index_fiu);
            }
        }
        // Trecem la urmatorul
        inceput++;
    }

    return binary_tree;
}

 

int main() {
    ARBORE arbore = test_arbore_gen_tablou();
    afisare_preordine(arbore, 1); puts("");
    ARBORE_BINAR arboreBinar = transform_to_bt(arbore);
    print_ordered_preorder_binary_tree(arboreBinar);
    dealloc_bin_tree(arboreBinar.root);
    return 0;
}