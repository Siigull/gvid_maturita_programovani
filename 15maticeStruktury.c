#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define ODCHYLKA 0.001

typedef struct pole
{
  float **prvek;
  int vyska;
  int sirka;
}Tmatice;

Tmatice * vytvorM(int vyska, int sirka){
    Tmatice *m = malloc(sizeof(Tmatice));
    if(m == NULL) return NULL;
    m->vyska = vyska;
    m->sirka = sirka;

    //alokace samotné matice
    m->prvek = malloc(m->vyska * sizeof(float*));
    if(m->prvek == NULL) return NULL;
    for(int i=0; i<m->vyska; i++){
        //alokace řádku
        m->prvek[i] = malloc(m->sirka * sizeof(float));
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
    int vyska, sirka;
    scanf("%d %d", &vyska, &sirka);
    if(vyska+1 != sirka) return NULL;

    Tmatice *m = vytvorM(vyska,sirka);
    if(m == NULL) return NULL;

    for (int i=0; i<vyska; i++){
        for(int j=0; j<sirka; j++){
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
    if(m->vyska+1 != m->sirka) return false;
    return true;
}

// Ověř, zda je matice ostře diagonálně dominantní.
// --------------------------------------------------------------------------
// Ověř, zda řešení pomocí Jacobiho nebo Gauss-Seidelovy iterační metody bude
// nad touto maticí koeficientů konvergovat.
bool jeDominantni(Tmatice* m){
    for(int i=0; i<m->vyska; i++){
        float soucet = 0;
        for(int j=0; j<m->vyska; j++){
            if(i == j) continue;
            soucet += fabs(m->prvek[i][j]);
        }
        if(fabs(m->prvek[i][i]) <= soucet) return false;
    }
    return true;
}

bool vynuluj(Tmatice *m){
    for(int i=0; i<m->vyska; i++){
        for(int j=0; j<m->sirka; j++){
            if(i == j) continue;
            m->prvek[i][j] /= m->prvek[i][i];
        }
        m->prvek[i][i] = 0;
    }
    return 1;
}

bool odchylka(float res[][2], int n){
    for(int i=0; i<n; i++)
        if(fabs(fabs(res[i][0]) - fabs(res[i][1])) > ODCHYLKA) return false;

    return true;
}

void Jacob(Tmatice *m){
    float res[m->vyska][2];
    for(int i=0; i<m->vyska; i++){ res[i][0] = 0; res[i][1] = 0; }

    if(!jeDominantni(m)) return;

    vynuluj(m);

    //prubeh metody
    do {
        //prekopirovani vysledku z druheho do prvniho pole
        for(int i=0; i<m->vyska; i++)
            res[i][0] = res[i][1];

        for(int i=0; i<m->vyska; i++){
            float b = m->prvek[i][m->vyska];

            for(int j=0; j<m->vyska; j++)
                b -= m->prvek[i][j] * res[j][0];

            res[i][1] = b;
        }
    } while(!odchylka(res, m->vyska));

    //vysledky
    printf("\n");
    for (size_t i=0; i<m->vyska; i++)
        printf("%zu.x: %f\n", i, res[i][1]);
}

int main(){
    Tmatice* m = nactiM();

    Jacob(m);

    smazM(m);
    return 0;
}
