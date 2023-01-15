#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct pole
{
  float **prvek;
  int vyska;
  int delka;
}Tmatice;

Tmatice * vytvorM(int vyska,int delka){
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

void vypisM (Tmatice *m){
    printf("\n");
    printf("%d %d\n",m->vyska, m->delka);
    for(int i=0; i<m->vyska; i++){
        for(int j=0; j<m->delka; j++){
            printf("%.2f ", m->prvek[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void nejvetsiKoeficient(Tmatice *m, int sloupec){
    int index = 0;
    for(int i = 1; i<m->vyska; i++){
        if(m->prvek[i][sloupec] > m->prvek[index][sloupec]){
            index = i;
        }
    }
    float *temp = m->prvek[0];
    m->prvek[0] = m->prvek[index];
    m->prvek[index] = temp;
}

void odectiRadek(Tmatice *m, int radek, int sloupec){
    if(m->prvek[radek][sloupec] == 0) return;
    float temp[m->delka];
    for(int i=0; i<m->delka; i++){
        temp[i] = m->prvek[radek][i] / m->prvek[sloupec][sloupec];
    }
    for(int i=sloupec; i<m->delka; i++){
        m->prvek[radek][i] = temp[i] * m->prvek[sloupec][i] - m->prvek[radek][i];
    }
}

void GJEM(Tmatice* m){
    for(int a=0; a<m->vyska; a++){
        nejvetsiKoeficient(m, a);
        for(int b=0; b<m->vyska; b++){
            if(a == b) continue;
            odectiRadek(m, b, a);
        }
    }
}

// kontrolu, zda je matice koeficientů po přímém chodu Gauss-Jordanovy metody
bool jePoPrimem(Tmatice *m){
    for(int i=0; i<m->vyska; i++){
        for(int j=0; j<m->vyska; j++){
            if(i == j) continue;
            if(m->prvek[i][j]) return false;
        }
    }
    return true;
}

//provedení zpětného chodu Gauss-Jordanovy metody
void zpetnyChod(Tmatice* m){
    
    for(int i=0; i<m->vyska; i++)
        m->prvek[i][m->vyska] /= m->prvek[i][i];

    for(int i=0; i<m->vyska; i++)
        printf("x%d: %f\n", i+1, m->prvek[i][m->vyska]);
}

//3 4 23 4 5 3 3 4 5 3 2 4 5 63
int main(void)
{
    Tmatice *matice = nactiM();

    vypisM(matice);
    GJEM(matice);
    vypisM(matice);

    zpetnyChod(matice);

    smazM(matice);
    return 0;
}
