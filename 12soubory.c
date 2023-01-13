#include <stdio.h>

// Vytvoř podprogram, který zpracuje vstupní soubor tak, že každý výskyt znaku
// # nahradí zadaným textovým řetězcem a výsledek zapíše do výstupního souboru.
void nahradHash(FILE *vstup, FILE *vystup, char* nahrazeni){
    char x;
    while(fscanf(vstup, "%c", &x) == 1){
        if(x == '#') fprintf(vystup, "%s", nahrazeni);
        else fprintf(vystup, "%c", x);
    }
}

// Vytvoř podprogram, který zkombinuje dva vstupní soubory tak, že bude do výstupního
// souboru zapisovat střídavě vždy jeden řádek z prvního a pak ze druhého souboru.
void souborStridave(FILE *vstup1, FILE *vstup2, FILE *vystup){
    char pole[100], pole2[100];
    while(fscanf(vstup1, "%99s", pole) == 1 && fscanf(vstup2, "%99s", pole2) == 1){
        fprintf(vystup, "%s\n%s\n", pole, pole2);
    }
}

// Vytvoř podprogram, který zjistí počet slov na každém řádku vstupního souboru
// a tyto počty zapíše na odpovídající řádky výstupního souboru.
void pocetSlov(FILE *vstup, FILE *vystup){
    char x;
    int pocet = 0;
    while(fscanf(vstup, "%c", &x) == 1){
        if((x > 64 && x < 91) || (x > 96 && x < 123)){
            pocet++;
            while((fscanf(vstup, "%c", &x) == 1) && ((x > 64 && x < 91) || (x > 96 && x < 123))) {}
        }
        if(x == '\n'){
            fprintf(vystup, "%d\n", pocet);
            pocet = 0;
        }
    }
}

// Vstupní soubor obsahuje textově zapsaná celá čísla větší než nula. Na začátku
// jsou data seřazená vzestupně na konci je oblast přeplnění. Seřazenou oblast
// a oblast přeplnění odděluje řádek s hodnotou 0. Vytvoř funkci, která v tomto sou-
// boru efektivně vyhledá zadanou hodnotu a bude brát v úvahu jak seřazenou ob-
// last, tak oblast přeplnění.
void efektivniHledani(){
    //Nepochopil jsem co znamená efektivní hledání, když je to sekvenční soubor
}


int main(){
    char cesta[100];
    printf("Zadej prvni soubor: ");
    scanf("%99s", cesta);
    FILE *vstup1 = fopen(cesta, "r");

    printf("Zadej druhy soubor: ");
    scanf("%99s", cesta);
    FILE *vstup2 = fopen(cesta, "r");

    FILE *vystup = fopen("vystup.txt", "w");
    if(vstup1 == NULL || vstup2 == NULL || vystup == NULL) return 1;

    return 0;
}