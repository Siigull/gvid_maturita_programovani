#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct bod{
    float x;
    float y;
}Tbod;

typedef struct matice{
    float prvek[2][3];
    int vyska;
    int sirka;
}Tmatice;

void nejvetsiKoeficient(Tmatice *m, int sloupec){
    int index = 0;
    for(int i = 1; i<m->vyska; i++)
        if(fabs(m->prvek[i][sloupec]) > fabs(m->prvek[index][sloupec]))
            index = i;

    float temp[3];
    for(int i=0; i<3; i++)
        temp[i] = m->prvek[0][i];

    for(int i=0; i<3; i++)
        m->prvek[0][i] = m->prvek[index][i];

    for(int i=0; i<3; i++)
        m->prvek[index][i] = temp[i];
}

void odectiRadek(Tmatice *m, int radek, int sloupec){
    if(m->prvek[radek][sloupec] == 0) return;
    float temp = m->prvek[radek][sloupec] / m->prvek[sloupec][sloupec];
    for(int i=sloupec; i<m->sirka; i++)
        m->prvek[radek][i] = m->prvek[radek][i] - temp * m->prvek[sloupec][i];
}

void zpetnyChod(Tmatice* m){
    const char vysledkyJmena[] = {'a', 'b'};

    for(int i=m->vyska-1; i>=0; i--){
        for(int j=i+1; j<m->vyska; j++)
            m->prvek[i][m->vyska] -= m->prvek[j][m->vyska] * m->prvek[i][j];
        m->prvek[i][m->vyska] /= m->prvek[i][i];
    }
    for(int i=0; i<m->vyska; i++)
        printf("%c: %f\n", vysledkyJmena[i], m->prvek[i][m->vyska]);
}

void GEM(Tmatice* m){
    for(int a=1; a<m->vyska; a++){
        nejvetsiKoeficient(m, a-1);
        for(int b=a; b<m->vyska; b++){
            odectiRadek(m, b, a-1);
        }
    }
}

Tbod* nactiBody(int* n){
    printf("Zadej počet bodů:");
    scanf("%d", n);
    Tbod* body = malloc(sizeof(Tbod) * (*n));
    if(body == NULL) return NULL;
    for(int i=0; i < *n; i++){
        printf("Zadej bod:");
        scanf("%f%f", &body[i].x, &body[i].y);
    }
    return body;
}

void nejmensiCtverce(Tbod body[], int n){
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for(int i=0; i<n; i++){
        sumX  += body[i].x;
        sumY  += body[i].y;
        sumX2 += body[i].x * body[i].x;
        sumXY += body[i].x * body[i].y;
    }

    Tmatice m = {.prvek = {{sumX2, sumX, sumXY}, {sumX, n, sumY},}, .sirka = 3, .vyska = 2};

    GEM(&m);

    zpetnyChod(&m);
}

int main(){
    int n;
    Tbod* body = nactiBody(&n);

    nejmensiCtverce(body, n);
    
    return 0;
}