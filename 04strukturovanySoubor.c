#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct sopka{
    char nazev[100];
    int vyska;
    bool aktivni;
}Tsopka;

typedef struct seznamSopek{
    Tsopka** sopky;
    int delka;
    int maxDelka;
}Tseznam;

Tseznam* vytvorSeznam(){
    Tseznam* sopky = malloc(sizeof(Tseznam));
    if(sopky == NULL) return NULL;
    sopky->delka = 0;
    sopky->maxDelka = 4;
    sopky->sopky = malloc(4 * sizeof(Tsopka));
    return sopky;
}

void pridejSopku(Tseznam *s, Tsopka *a){
    if(s->delka == s->maxDelka){
        s->maxDelka *= 2;
        Tsopka *temp = realloc(s->sopky, s->maxDelka * sizeof(Tsopka));
        if(temp == NULL) {
            free(s->sopky); s->sopky = NULL; s->maxDelka = 0; return;
        }
        s->sopky = temp;
    }
    s->sopky[s->delka] = a;
    s->delka++;
}

void nactiSoubor(Tseznam* sopky, FILE *f){
    char aktivni[4], jmeno[100];
    int vyska;
    while(fscanf(f,"%99s %d %3s", jmeno, &vyska, aktivni) == 3){
        fflush(stdout);
        Tsopka* temp = malloc(sizeof(Tsopka));
        strcpy(temp->nazev, jmeno);
        temp->vyska = vyska;
        if(aktivni[0] == 'A') temp->aktivni = 1;
        else temp->aktivni = 0; 
        pridejSopku(sopky, temp);
    }
}

//Vytvoř funkci vracející průměrnou výšku všech ne/aktivních sopek (vybere se pa-rametrem).
float prumerVysek(Tseznam *s, bool aktivni){
    int soucet=0, pocet=0;
    for(int i=0; i<s->delka; i++){
        if(s->sopky[i]->aktivni == aktivni){
            pocet++;
            soucet += s->sopky[i]->vyska;
        }
    }
    return soucet / (pocet * 1.0);
}

//Vypiš názvy všech sopek vyšších než hodnota zadaná parametrem. U každého
//názvu vypiš, zda je sopka aktivní, či ne.
void vypisSopku(Tsopka *s){
    if(s->aktivni) printf("%s je aktivni\n", s->nazev);
    else printf("%s neni aktivni\n", s->nazev);
}

void jeVyssi(Tseznam *s, int vyska){
    for(int i=0; i<s->delka; i++){
        if(s->sopky[i]->vyska > vyska) vypisSopku(s->sopky[i]);
    }
}

//Vytvoř jeden soubor se záznamy o aktivních a druhý se záznamy o neaktivních
//sopkách. Výstupní soubory musí zachovávat formát vstupního souboru.
void vypisSopkuSoubor(Tsopka *s, FILE *f){
    if(s->aktivni) fprintf(f ,"%s %d ANO\n", s->nazev, s->vyska);
    else fprintf(f, "%s %d NE\n", s->nazev, s->vyska);
}

void dvaSoubory(Tseznam *s){
    FILE *aktivni = fopen("aktivni.txt", "w");
    FILE *neaktivni = fopen("neaktivni.txt", "w");
    if(aktivni == NULL || neaktivni == NULL) return;
    for(int i=0; i<s->delka; i++){
        if(s->sopky[i]->aktivni) vypisSopkuSoubor(s->sopky[i], aktivni);
        else vypisSopkuSoubor(s->sopky[i], neaktivni);
    }
}

int main(){
    Tseznam* sopky = vytvorSeznam();
    char cesta[100];
    // scanf("%99s", cesta);
    FILE *f = fopen("sopky.txt", "r");
    if(f == NULL) return 1;
    nactiSoubor(sopky, f);
    return 0;
}