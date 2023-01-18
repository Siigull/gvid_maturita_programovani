#include <stdio.h>
#include <stdbool.h>

// Ověř zda je zadaný textový řetězec validní MAC, IPv4, IPv6, e-mailovou adresou.
// Kontroluj oddělovače, přebytečné nuly, mezery atd.
bool isLetter(char x){
    if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) return 1;
    return 0;
}

bool jeMAC(char* vstup){
    for(int i=0; i<14; i+=3)
        if(!(isLetter(vstup[i]) && isLetter(vstup[i+1]) && vstup[i+2] == ':')) return 0;

    if(!(isLetter(vstup[15]) && isLetter(vstup[16]))) return 0;
    return 1;
}


int main(){
    return 0;
}