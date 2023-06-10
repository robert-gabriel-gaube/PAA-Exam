#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct NodArboreDeRegasire {
	struct NodArboreDeRegasire *alfabet[27]; //alfabetul A B ... Z [
}NodArboreDeRegasire;

/* Avem cuvintele calciu, carbon, heliu, hidrogen, oxigen
  
              ROOT
         /      |         \
         C      H         O 
         |     / \        |
         A    E   I       X
        / \   |   |       |
        R  L  L   D       I   
        |  |  |   |       |
        B  C  I   R       G
        |  |  |   |       |
        O  I  U   O       E
        |  |      |       |
        N  U      G       N 
           |      |       
           M      E       
                  |       
                  N       
*/

int char_to_index(char c) {
    return c - 'A';
}

NodArboreDeRegasire* new_nod() {
    NodArboreDeRegasire *nod = (NodArboreDeRegasire*)malloc(sizeof(NodArboreDeRegasire));
    for (int i = 0; i < 27; i++) {
        nod->alfabet[i] = NULL;
    }
    return nod;
}
NodArboreDeRegasire* test_arbore_trie() {
    NodArboreDeRegasire *root = (NodArboreDeRegasire*)malloc(sizeof(NodArboreDeRegasire));
    for (int i = 0; i < 27; i++) {
        root->alfabet[i] = NULL;
    }

    NodArboreDeRegasire* c = root -> alfabet[char_to_index('C')] = new_nod();
    NodArboreDeRegasire* h = root -> alfabet[char_to_index('H')] = new_nod();
    NodArboreDeRegasire* o = root -> alfabet[char_to_index('O')] = new_nod();

    NodArboreDeRegasire* ca = c -> alfabet[char_to_index('A')] = new_nod();
    NodArboreDeRegasire* he = h -> alfabet[char_to_index('E')] = new_nod();
    NodArboreDeRegasire* hi = h -> alfabet[char_to_index('I')] = new_nod();
    NodArboreDeRegasire* ox = o -> alfabet[char_to_index('X')] = new_nod();

    NodArboreDeRegasire* car = ca -> alfabet[char_to_index('R')] = new_nod();
    NodArboreDeRegasire* cal = ca -> alfabet[char_to_index('L')] = new_nod();
    NodArboreDeRegasire* hel = he -> alfabet[char_to_index('L')] = new_nod();
    NodArboreDeRegasire* hid = hi -> alfabet[char_to_index('D')] = new_nod();
    NodArboreDeRegasire* oxi = ox -> alfabet[char_to_index('I')] = new_nod();

    NodArboreDeRegasire* carb = car -> alfabet[char_to_index('B')] = new_nod(); 
    NodArboreDeRegasire* calc = cal -> alfabet[char_to_index('C')] = new_nod();
    NodArboreDeRegasire* heli = hel -> alfabet[char_to_index('I')] = new_nod();
    NodArboreDeRegasire* hidr = hid -> alfabet[char_to_index('R')] = new_nod();
    NodArboreDeRegasire* oxig = oxi -> alfabet[char_to_index('G')] = new_nod();

    NodArboreDeRegasire* carbo = carb -> alfabet[char_to_index('O')] = new_nod();
    NodArboreDeRegasire* calci = calc -> alfabet[char_to_index('I')] = new_nod();
    NodArboreDeRegasire* heliu = heli -> alfabet[char_to_index('U')] = new_nod();
    NodArboreDeRegasire* hidro = hidr -> alfabet[char_to_index('O')] = new_nod();
    NodArboreDeRegasire* oxige = oxig -> alfabet[char_to_index('E')] = new_nod();

    heliu -> alfabet[char_to_index('[')] = heliu;
    
    NodArboreDeRegasire* carbon = carbo -> alfabet[char_to_index('N')] = new_nod();
    NodArboreDeRegasire* calciu = calci -> alfabet[char_to_index('U')] = new_nod();
    NodArboreDeRegasire* hidrog = hidro -> alfabet[char_to_index('G')] = new_nod();
    NodArboreDeRegasire* oxigen = oxige -> alfabet[char_to_index('N')] = new_nod();

    carbon -> alfabet[char_to_index('[')] = carbon;
    calciu -> alfabet[char_to_index('[')] = calciu;
    oxigen -> alfabet[char_to_index('[')] = oxigen;

    NodArboreDeRegasire* hidroge = hidrog -> alfabet[char_to_index('E')] = new_nod();

    NodArboreDeRegasire* hidrogen = hidroge -> alfabet[char_to_index('N')] = new_nod();

    hidrogen -> alfabet[char_to_index('[')] = hidrogen;

    return root;
}
void show_trie(NodArboreDeRegasire* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (root->alfabet[i] != NULL) {
            printf("%c ", i + 'A');
            fflush(stdout);
            show_trie(root->alfabet[i]);
        
        }
    }
    if(root->alfabet[char_to_index('[')] != NULL) {
        printf("\n");
    }
}

void free_trie(NodArboreDeRegasire* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        free_trie(root->alfabet[i]);
    }
    free(root);
}