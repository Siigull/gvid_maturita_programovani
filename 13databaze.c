#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct element{
    u_int32_t id;
    char hodnota[3][100];
    int index;
    bool smazano;
}Telement;

typedef struct tabulka{
    Telement** arr;
    int delka;
    int maxDelka;
}Ttabulka;

Telement* vytvorElement(char* hodnota, int id){
    Telement* e = malloc(sizeof(Telement));
    if(e == NULL) return NULL;
    strcpy(e->hodnota[0], hodnota);
    e->id = id;
    e->smazano = 0;
    e->index = 1;
    return e;
}

Ttabulka* vytvorTabulku(){
    Ttabulka* t = malloc(sizeof(Ttabulka));
    if(t == NULL) return NULL;
    t->delka = 0;
    t->maxDelka = 4;
    t->arr = malloc(t->maxDelka * sizeof(Telement));
    return t;
}

void pridejElement(Ttabulka* t, u_int32_t id, char* hodnota){
    if(t->delka == t->maxDelka){
        t->maxDelka *= 2;
        Telement* temp = realloc(t->arr, t->maxDelka * sizeof(Telement));
        if(temp == NULL) {
            free(t->arr); t->arr = NULL; t->maxDelka = 0; return;
        }
        t->arr = temp;
    }
    if(t->arr[id] == NULL){
        t->delka++;
        Telement* e = vytvorElement(hodnota, id);
        t->arr[id] = e;
    } 
    else{
        strcpy(t->arr[id]->hodnota[t->arr[id]->index], hodnota);
        t->arr[id]->index++;
    }
}

void nactiDatabazi(Ttabulka *t, FILE *f){
    char hodnota[100];
    int id;
    while(fscanf(f,"%d %99s", &id, hodnota) == 2){
        pridejElement(t, id, hodnota);
    }
}

void vypisElement(Telement* e){
    printf("%d,%s,%s\n", e->id, e->hodnota[0], e->hodnota[1]);
}

// V textových souborech jsou textově uloženy dvě databázové tabulky. V první
// tabulce (souboru) jsou uloženy záznamy s atributy ID, jméno (10 znaků). Ve
// druhé tabulce (souboru) jsou uloženy záznamy s atributy ID_uživatele, e-mail
// (20 znaků). V první tabulce má ID charakter primárního klíče a ID_uživatele je
// cizí klíč odkazující do první tabulky. Napiš podprogram, který vypíše na řádky
// všechny emailové adresy uživatelů se zadaným jménem (parametr
// podprogramu). Na každém řádku výstupu budou tyto údaje ID, jméno, e-mail.
void najdiJmeno(Ttabulka* t, char* jmeno){
    printf("%d\n", t->delka);
    for(int i=0; i<t->delka; i++){
        if(!strcmp(t->arr[i]->hodnota[0], jmeno)) vypisElement(t->arr[i]);
    }
}

// V tabulce (souboru) jsou záznamy o sopkách s atributy název (20 znaků), výška
// (v metrech), zda je aktivní (ano/ne). Vytvoř podprogram pro výpis všech záznamů
// o nad/podprůměrně (parametr) vysokých ne/aktivních (parametr) sopkách.
// PŘESUNUL JSEM DO strukturovanySoubor.c

int main(){
    srand(time(NULL));
    Ttabulka* tab = vytvorTabulku();

    char cesta[100];
    // printf("Zadej prvni soubor: ");
    // scanf("%99s", cesta);
    FILE *vstup1 = fopen("databaz1.txt", "r");

    // printf("Zadej druhy soubor: ");
    // scanf("%99s", cesta);
    FILE *vstup2 = fopen("databaz2.txt", "r");

    if(vstup1 == NULL || vstup2 == NULL) return 1;

    nactiDatabazi(tab,vstup1);
    nactiDatabazi(tab,vstup2);

    najdiJmeno(tab, "lek");

    return 0;
}