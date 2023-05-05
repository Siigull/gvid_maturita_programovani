#include <stdio.h>
#include <stdbool.h>

#define maxArr 100

//načti m×n prvků do 2D pole ze standardního vstupu, ze souboru
void nactiPoleSoubor(FILE *f, int pole[][maxArr]){
    int x, y;
    fscanf(f,"%d %d", &x, &y);
    int temp;

    for(int i=0; i<x; i++)
        for(int j=0; j<y; j++)
            fscanf(f, "%d", &pole[i][j]);
}

void nactiPoleVstup(int pole[][maxArr]){
    int x, y;
    scanf("%d %d", &x, &y);

    for(int i=0; i<x; i++)
        for(int j=0; j<y; j++)
            scanf("%d", &pole[i][j]);
}

//vypiš výsledné pole na standardní výstup, do souboru
void vypisPole(int pole[maxArr][maxArr], int x, int y){
    printf("\n");
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            printf("%d ", pole[i][j]);
        }
        printf("\n");
    }
}

void vypisPoleSoubor(FILE *f, int pole[][maxArr], int x, int y){
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            fprintf(f, "%d ", pole[i][j]);
        }
        fprintf(f, "\n");
    }
}

//zjisti počet sudých prvků v každém sloupci a zapiš jej do posledního řádku v tomto sloupci
void pocetSudych(int pole[][maxArr], int x, int y){
    for(int i=0; i<x; i++){
        int counter=0;
        for(int j=0; j<y; j++){
            if(!pole[j][i] % 2)
                counter++;
        }
        pole[x][i] = counter;
    }
}

//zjisti součet všech prvků na obvodu matice a pak všech prvků kromě obvodových
int soucetObvodovych(int pole[][maxArr], int x, int y){
    int soucet=0;
    for(int i=0; i<x; i++){
        soucet += pole[i][0];
        soucet += pole[i][y-1];
    }
    for(int i=1; i<y-1; i++){
        soucet += pole[0][i];
        soucet += pole[x-1][i];
    }
    return soucet;
}

int soucetNeobvodovych(int pole[][maxArr], int x, int y){
    int soucet=0;
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            soucet += pole[i][j];
        }
    }
    return soucet - soucetObvodovych(pole, x, y);
}

//zjisti součet prvků ve čtvrtinách matice, když každý rozměr rozdělíš celočíselným dělením 2
int* soucetCtvrtin(int pole[][maxArr], int x, int y){
    int *vysledky = malloc(sizeof(int) * 4);
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if(i < x/2){
                if(j < y/2) vysledky[0] += pole[i][j];
                else vysledky[1] += pole[i][j];
            } else {
                if(j < y/2) vysledky[3] += pole[i][j];
                else vysledky[4] += pole[i][j];
            }
        }
    }
    return vysledky;
}

//zjisti, zda je matice vertikálně, či horizontálně symetrická
bool jeHorizontalneSymetricka(int pole[][maxArr], int x, int y){
    for(int i=0; i<x/2; i++){
        for(int j=0; j<y; j++){
            if(pole[i][j] != pole[x-i-1][j]) return false;
        }
    }
    return true;
}

bool jeVertikalneSymetricka(int pole[][maxArr], int x, int y){
    for(int i=0; i<y/2; i++){
        for(int j=0; j<x; j++){
            if(pole[j][i] != pole[j][y-i-1]) return false;
        }
    }
    return true;
}

//vytvoř transponovanou matici
void transposeMatrix(int pole[][maxArr], int x, int y){
    for(int i=0; i<x; i++){
        for(int j=0; j<i; j++){
            int temp = pole[i][j];
            pole[i][j] = pole[j][i];
            pole[j][i] = temp; 
        }
    }
}

//vytvoř matici otočenou o 90, 180, 270 stupňů (zadej počet otočení o 90 stupňů parametrem)
void rotateMatrix(int pole[][maxArr], int x, int y, int degrees){
    for(int i=0; i<degrees/90; i++){
        transposeMatrix(pole, x, y);
        for(int i=0; i<y/2; i++){
            for(int j=0; j<x; j++){
                int temp = pole[j][i];
                pole[j][i] = pole[j][y-i-1];
                pole[j][y-i-1] = temp;
            }
        }
    }
}

int main(){
    return 0;
}