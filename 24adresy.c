#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vytvoř podprogram, který ze vstupního řetězce (parametr) odstraní všechny zna-
// ky, které se nemohou vyskytovat v binárním vyjádření adresy. Výsledkem bude
// řetězec tvořený nesmazanými znaky.
void odstranZnaky(char* vstup){
    for(int i=0, j=0; vstup[i] != '\0'; i++)
        if(vstup[i] == '0' || vstup[i] == '1' || vstup[i] == '.') vstup[j++] = vstup[i]; 
}

// Vytvoř podprogram, který bude mít ve vstupním textovém řetězci (parametr) za-
// psanou hodnotu v šestnáctkové soustavě. Ověř, zda tato hodnota může být adre-
// sou v 8, 16, 32 nebo 64 bitovém operačním systému. Funkce bude vracet hodno-
// ty 0, 8, 16, 32 nebo 64. Nulu vracej v případě chyby, nebo příliš velké hodnoty.
int kolikBitu(char* vstup){
    int n = strlen(vstup);
    if(n > 16) return 0;
    return n * 4;
}


int main(){
    printf("%d", kolikBitu("4f"));
    return 0;
}