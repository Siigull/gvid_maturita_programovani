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
    for(int i = 1; i<m->vyska; i++)
        if(fabs(m->prvek[i][sloupec]) > fabs(m->prvek[index][sloupec]))
            index = i;

    float *temp = m->prvek[0];
    m->prvek[0] = m->prvek[index];
    m->prvek[index] = temp;
}

void odectiRadek(Tmatice *m, int radek, int sloupec){
    if(m->prvek[radek][sloupec] == 0) return;
    
    float temp = m->prvek[radek][sloupec] / m->prvek[sloupec][sloupec];

    for(int i=sloupec; i<m->delka; i++)
        m->prvek[radek][i] = m->prvek[radek][i] - temp * m->prvek[sloupec][i];
}

void zpetnyChod(Tmatice* m){
    for(int i=m->vyska-1; i>=0; i--){
        for(int j=i+1; j<m->vyska; j++)
            m->prvek[i][m->vyska] -= m->prvek[j][m->vyska] * m->prvek[i][j];
        m->prvek[i][m->vyska] /= m->prvek[i][i];
    }
    for(int i=0; i<m->vyska; i++)
        printf("x%d: %f\n", i+1, m->prvek[i][m->vyska]);
}

// přímý chod Gaussovy metody
void GEM(Tmatice* m){
    for(int a=1; a<m->vyska; a++){
        nejvetsiKoeficient(m, a-1);
        for(int b=a; b<m->vyska; b++){
            odectiRadek(m, b, a-1);
        }
    }
}

// zjištění počtu řešení po přímém chodu Gaussovy metody 1=nekonecno 0=1
int pocetReseni(Tmatice *m){
    for(int i=0; i<m->vyska; i++) 
        if(!m->prvek[i][i]) return 0;

    return 1;
}

// kontrolu, zda je matice koeficientů ve tvaru po provedení přímého chodu Gaussovy metody
bool jePoPrimem(Tmatice *m){
    for(int i=0; i<m->vyska; i++)
        for(int j=i-1; j>=0; j--)
            if(m->prvek[i][j]) return false;

    return true;
}

// provedení zpětného chodu na i-tém řádku (předpokládá se, že na dalších řádcích
// již výpočet proběhl)
void zpetnyRadek(Tmatice* m, int i){
    for(int j=i+1; j<m->vyska; j++)
        m->prvek[i][m->vyska] -= m->prvek[j][m->vyska] * m->prvek[i][j];

    m->prvek[i][m->vyska] /= m->prvek[i][i];
}

//3 4 23 4 5 3 3 4 5 3 2 4 5 63
int main(void)
{
    Tmatice *matice = nactiM();

    vypisM(matice);
    GEM(matice);
    vypisM(matice);

    zpetnyChod(matice);

    smazM(matice);
    return 0;
}
