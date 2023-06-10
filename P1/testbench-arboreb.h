#define N 2       // Ordin
#define NN 2 * N 
#include <stdlib.h>
#include <stdio.h>


// Am ales aceste structuri de date deoarece asa ne-au fost prezentate in laborator
typedef int TipCheie;

typedef struct Nod_B {
    TipCheie cheie;   // Informatia din nod
    struct Pagina *p; // Pagina cu chei mai mari decat cheia curenta
}Nod_B;

typedef struct Pagina {
    int m;              // Valori [n, nn]
    struct Pagina *p0;  // Pagina cu chei mai mici decat in pagina curenta
    Nod_B e[NN + 1];    // Cheile paginii curente si pointerii spre cele descendente
}Pagina;

/*                 
                Arbore B Test 

                    | 11 |
               /              \
       | 3 7 |                  | 14 17 |
     /    |    \               /    |     \
| 1 2 | 4 5 6 | 8 9 |    | 12 13 | 15 16 | 18 19 | 
*/
void afisare_arbore_b_test(Pagina *arbore, int nivel)
{
	int i;

	if (!arbore)
		return;
	afisare_arbore_b_test(arbore->p0, nivel + 1);
	for (i = 1; i <= arbore->m; i++)
		afisare_arbore_b_test(arbore->e[i].p, nivel + 1);

	printf("Nivel %d: ", nivel);
	for (i = 1; i <= arbore->m; i++)
		printf("%d ", arbore->e[i].cheie);
	printf("\n");
}

Pagina* arbore_b_test() {
    Pagina *root = (Pagina*)malloc(sizeof(Pagina));
    root->m = 1;
    root->e[1].cheie = 11;

    root->p0 = (Pagina*)malloc(sizeof(Pagina));
    root->p0->m = 2;
    root->p0->e[1].cheie = 3;
    root->p0->e[2].cheie = 7;

    root->e[1].p = (Pagina*)malloc(sizeof(Pagina));
    root->e[1].p->m = 2;
    root->e[1].p->e[1].cheie = 14;
    root->e[1].p->e[2].cheie = 17;

    root->e[1].p->p0 = (Pagina*)malloc(sizeof(Pagina));
    root->e[1].p->p0->m = 2;
    root->e[1].p->p0->e[1].cheie = 12;
    root->e[1].p->p0->e[2].cheie = 13;

    root->e[1].p->e[1].p = (Pagina*)malloc(sizeof(Pagina));
    root->e[1].p->e[1].p->m = 2;
    root->e[1].p->e[1].p->e[1].cheie = 15;
    root->e[1].p->e[1].p->e[2].cheie = 16;

    root->e[1].p->e[2].p = (Pagina*)malloc(sizeof(Pagina));
    root->e[1].p->e[2].p->m = 2;
    root->e[1].p->e[2].p->e[1].cheie = 18;
    root->e[1].p->e[2].p->e[2].cheie = 19;

    root->p0->p0 = (Pagina*)malloc(sizeof(Pagina));
    root->p0->p0->m = 2;
    root->p0->p0->e[1].cheie = 1;
    root->p0->p0->e[2].cheie = 2;

    root->p0->e[1].p = (Pagina*)malloc(sizeof(Pagina));
    root->p0->e[1].p->m = 3;
    root->p0->e[1].p->e[1].cheie = 4;
    root->p0->e[1].p->e[2].cheie = 5;
    root->p0->e[1].p->e[3].cheie = 6;

    root->p0->e[2].p = (Pagina*)malloc(sizeof(Pagina));
    root->p0->e[2].p->m = 2;
    root->p0->e[2].p->e[1].cheie = 8;
    root->p0->e[2].p->e[2].cheie = 9;

    return root;
}

void free_arbore_b(Pagina* root) {
    if (root == NULL) return;
    free_arbore_b(root->p0);
    for (int i = 1; i <= root->m; i++) {
        free_arbore_b(root->e[i].p);
    }
    free(root);
}
