#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Dva vstupní soubory obsahují seřazené posloupnosti znaků. Sluč je do třetího vý-
// stupního souboru tak, aby v něm byly všechny znaky také seřazeny.
void slouceniSerazenych(FILE *f1, FILE *f2, FILE *vystup){
    int x, y;
    bool out = false;
    fscanf(f1, "%c", &x);
    fscanf(f2, "%c", &y);
    while(1){
        if(x < y){
            fprintf(vystup, "%c ", x);
            if(fscanf(f1, "%c", &x) != 1)
                if(x == INT32_MAX) return;
                else x = INT32_MAX;
        } else {
            fprintf(vystup, "%c ", y);
            if(fscanf(f2, "%c", &y) != 1)
                if(y == INT32_MAX) return;
                else y = INT32_MAX;
        }
    }
}

// Dva vstupní soubory obsahují znaky. Sluč je do třetího výstupního souboru tak,
// aby v něm byly znaky seřazeny po dvojicích.
void slouceniDvojice(FILE *f1, FILE *f2, FILE *vystup){
    int x, y;
    bool out = false;
    fscanf(f1, "%c", &x);
    fscanf(f2, "%c", &y);
    while(fscanf(f1, "%c", &x) == 1 && fscanf(f2, "%c", &y) == 1){
        if (x < y) fprintf(vystup, "%c %c ", x, y);
        else fprintf(vystup, "%c %c ", y, x);
    }
    while(fscanf(f1, "%c", &x) == 1){
        if(fscanf(f1, "%c", &y) != 1){
            fprintf(vystup, "%c ", x);
            return;
        }
        if (x < y) fprintf(vystup, "%c %c ", x, y);
        else fprintf(vystup, "%c %c ", y, x);
    }
    while(fscanf(f2, "%c", &x) == 1){
        if(fscanf(f2, "%c", &y) != 1){
            fprintf(vystup, "%c ", x);
            return;
        }
        if (x < y) fprintf(vystup, "%c %c ", x, y);
        else fprintf(vystup, "%c %c ", y, x);
    }
}

// Vstupní soubor obsahuje posloupnost znaků. Rozděl je po N-ticích do dvou vý-
// stupních souborů (N je parametr).
void Ntice(FILE *f1, FILE *vystup1, FILE *vystup2, int N){
    FILE *vystup[2];
    vystup[0] = vystup1;
    vystup[1] = vystup2;
    int x, counter = 0;
    while(fscanf(f1, "%c", &x) == 1){
        fprintf(vystup[(counter/N) % 2], "%c", x);
        counter++;
    }
}

int main(){

    FILE *vstup1 = fopen("vstup1.txt", "r");
    FILE *vstup2 = fopen("vystup1.txt", "w");
    FILE *vystup = fopen("vystup2.txt", "w");
    if(vstup1 == NULL || vstup2 == NULL || vystup == NULL) return 1;

    Ntice(vstup1, vstup2, vystup, 3);

    return 0;
}