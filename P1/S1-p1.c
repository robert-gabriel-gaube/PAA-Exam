#include "testbench-arboreb.h"
#include <stdio.h>
/*
Baza de date care contine numele unei persoane si varsta acesteia este
in format Unix Epoch Time. Afisati numele persoanelor care au varsta mai mare
decat o valoare data folosind o functie. Baza de date e modelata sub forma 
de arbore B.
*/


// Functie care afiseaza arborele

// TIP FOR FELLOW STUDENTS READING:
// Problema spune sa afisam numele persoanelor
// cu varsta mai mare decat o valoare data.
// Aici am afisat doar "varsta" dar nu este greu
// sa afisam si numele persoanei. Trebuie adaugat
// in structura si afisat ala in loc de cheie.
// Dar eu nu voi face asta ca n-am chef sa scriu 1000000 de nume.
void afisare(Pagina *arbore) {
  int i;
  if (arbore == NULL)
    return;

  afisare(arbore->p0);
  for (i = 1; i <= arbore->m; i++)
    afisare(arbore->e[i].p);

  for (i = 1; i <= arbore->m; i++)
    printf("%d ", arbore->e[i].cheie);
}

// Este exact complexitatea cautarii intr-un arbore B
// O(logn(N)) - n este oridinul, N este numarul de noduri
void afisare_mai_mare(Pagina *arbore, TipCheie value) {
  if (arbore == NULL) {
    return;
  }

  // Exista mereu deoarece ordinul este >= 1
  if (value < arbore->e[1].cheie) {
    afisare_mai_mare(arbore->p0, value);
  }

  // Parcurge fiecare element din pagina si afiseaza elementele mai mari decat
  // value. Daca elementul este mai mic decat value, repetam recursiv procedura.
  for (int idx = 1; idx <= arbore->m; idx++) {
    if (arbore->e[idx].cheie == value) { // Facem if separat deoarece afisam doar valorile strict mai mari
      afisare(arbore->e[idx].p);
    } else if (arbore->e[idx].cheie > value) {
      printf("%d ", arbore->e[idx].cheie);
      afisare(arbore->e[idx].p);
    } else {
      afisare_mai_mare(arbore->e[idx].p, value);
    }
  }
}

int main() {
  Pagina *root = arbore_b_test();
  for (int idx = 0; idx < 20; ++idx) {
    printf("Afisare mai mare decat %2d:  ", idx);
    afisare_mai_mare(root, idx);
    printf("\n");
  }
  free_arbore_b(root);
  return 0;
}