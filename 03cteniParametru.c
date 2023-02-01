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
    for(int i=0; i<N || pole[i] != '\0'; i++){
        if(pole[i] > 47 && pole[i] < 58) counter++;
    }
    return counter;
}

//vrať indexy první a poslední nalezené číslice v řetězci (přes parametry)
int* indexyCislic(char pole[N]){
    int* vysledky = malloc(2 * sizeof(int));
    vysledky[0] = 0; vysledky[1] = 0;

    int strLen = 0;
    for(int i=0; i<N || pole[i] != '\0'; i++){
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
    for(int i=0; i<N || pole[i] != '\0'; i++){
        if(pole[i] == x) pole[i] = y;
    }
}

//skryj v řetězci každé číslo přepsáním pomocí znaku #
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
        j++;
    }
}

//vrať počet slov v řetězci
int pocetSlov(char* pole){
    int pocet = 0;
    for(int i=0; i<N || pole[i] != '\0'; i++){
        if((pole[i] < 91 && pole[i] > 64) || (pole[i] < 123 && pole[i] > 96)){
            pocet++;
            while((pole[i] < 91 && pole[i] > 64) || (pole[i] < 123 && pole[i] > 96)) i++;
            i--;
        }
    }
    return pocet;
}

//nahraď v řetězci malá písmena za velká, nebo velká za malá
void nahradVelikost(char* pole){
    for(int i=0; i<N || pole[i] != '\0'; i++){
        if(pole[i] < 91 && pole[i] > 64) pole[i] -= 32;
        if(pole[i] < 123 && pole[i] > 96) pole[i] += 32;
    }
}

void prohod(char* x, char* y){
    char temp = *x;
    *x = *y;
    *y = temp;
}

void reverzeRekurze(char* pole, int zacatek, int konec){
    if(konec-zacatek < 1) return; 
    prohod(&pole[zacatek], &pole[konec]);
    reverzeRekurze(pole, zacatek+1, konec-1);
}

void reverzeALT(char* pole, int index){
    if(pole[index] = "\0") return;
    reverzeALT(pole, index+1);
    printf("%c", pole[index]);
}

void reverzeCyklus(char* pole, int n){
    for(int i=0; i<n/2; i++)
        prohod(&pole[i], &pole[n-i]);
}

int main(int argc, char **argv){
    
    // char* vstupniRetezec = argv[argc - 1];
    // char nahrazeny, nahraditel;

    // if(argc == 4){
    //     nahrazeny = argv[1];
    //     nahraditel = argv[2];
    // }

    char pole[] = {'a','b','c','d','e'};
    
    for(int i=0; i<5; i++) printf("%c", pole[i]);
    reverzeRekurze(pole, 0, 4);
    for(int i=0; i<5; i++) printf("%c", pole[i]);

    return 0;
}