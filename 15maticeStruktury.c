#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct pole
{
  float **prvek;
  int vyska;
  int delka;
}Tmatice;

Tmatice * vytvorM(int vyska, int delka){
    Tmatice *m = malloc(sizeof(Tmatice));
    if(m == NULL) return NULL;
    m->vyska = vyska;
    m->delka = delka;

    //alokace samotné matice
    m->prvek = malloc(m->vyska * sizeof(float*));
    if(m->prvek == NULL) return NULL;
    for(int i=0; i<m->vyska; i++){
        //alokace řádku
        m->prvek[i] = malloc(m->delka * sizeof(float));
        if(m->prvek[i] == NULL) return NULL;
    }
    return m;
}

void smazM(Tmatice* m){
    for(int i=0; i<m->vyska; i++) free(m->prvek[i]);
    free(m->prvek);
    free(m);
}

//Načti ze vstupu matici koeficientů o rozměrech m×n.
Tmatice* nactiM(){
    int vyska, delka;
    scanf("%d %d", &vyska, &delka);
    if(vyska+1 != delka) return NULL;

    Tmatice *m = vytvorM(vyska,delka);
    if(m == NULL) return NULL;

    for (int i=0; i<vyska; i++){
        for(int j=0; j<delka; j++){
            float prvek;
            scanf("%f", &prvek);
            m->prvek[i][j] = prvek;
        }
    }
    return m;
}

// Ověř, zda načtená matice může být maticí koeficientů soustavy lineárních rovnic
// (stačí rozměry).
bool jeSoustava(Tmatice* m){
    if(m->vyska+1 == m->delka) return false;
    return true;
}

// Ověř, zda je matice ostře diagonálně dominantní.
// --------------------------------------------------------------------------
// Ověř, zda řešení pomocí Jacobiho nebo Gauss-Seidelovy iterační metody bude
// nad touto maticí koeficientů konvergovat.
bool jeDominantni(Tmatice* m){
    for(int i=0; i<m->vyska; i++){
        float soucet = 0;
        for(int j=0; i<m->vyska; i++){
            if(i == j) continue;
            soucet += fabs(m->prvek[i][j]);
        }
        if(fabs(m->prvek[i][i]) <= soucet) return false;
    }
    return true;
}

int main(){
    Tmatice* m = nactiM();

    smazM(m);
    return 0;
}
