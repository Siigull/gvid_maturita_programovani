#include <stdio.h>
#include <stdlib.h>

#define N 100
//načti řetězec ze vstupu (maximálně N znaků)
void nactiNznaku(char pole[N], char* vstup){
    for(int i=0; i<N; i++){
        pole[i] = vstup[i];
        if(vstup[i] == '\0') break;
    }
}

//vrať počet číslic v řetězci
int pocetCislic(char pole[N]){
    int counter = 0;
    for(int i=0; i<N; i++){
        if(pole[i] == '\0') break;
        if(pole[i] > 47 && pole[i] < 58) counter++;
    }
    return counter;
}

//vrať indexy první a poslední nalezené číslice v řetězci (přes parametry)
int* indexyCislic(char pole[N]){
    int* vysledky = malloc(2 * sizeof(int));
    vysledky[0] = 0; vysledky[1] = 0;

    int strLen = 0;
    for(int i=0; i<N; i++){
        if(pole[i] == '\0') break;
        if(pole[i] > 47 && pole[i] < 58) vysledky[0] = i;
        strLen++;
    }

    for(int i=strLen; i>=0; i--){
        if(pole[i] > 47 && pole[i] < 58){
            vysledky[1] = i;
            break;
        }
    }
    return vysledky;
}

//nahraď v řetězci každý výskyt znaku x znakem y (x a y jsou parametry funkce)
void nahradVyskyt(char x, char y, char pole[N]){
    for(int i=0; i<N; i++){
        if(pole[i] == '\0') break;
        if(pole[i] == x) pole[i] = y;
    }
}

void nahradCislice(char* pole){
    char result[N];
    int j=0;
    for(int i=0; i<N; i++){
        if(pole[i] > 47 && pole[i] < 58){
            i++;
            while((pole[i] > 47 && pole[i] < 58) || pole[i] == '.') i++;
            i--;
            result[j] = '#';
        } else{
            result[j] = pole[i];
        }
        if(pole[i] == '\0') break;
        printf("%c", pole[j]);
        j++;
    }
}

int main(int argc, char **argv){
    
    char* vstupniRetezec = argv[argc-1];
    // char nahrazeny, nahraditel;

    // if(argc == 4){
    //     nahrazeny = argv[1];
    //     nahraditel = argv[2];
    // }

    return 0;
}