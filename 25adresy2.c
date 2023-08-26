#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

bool is_number(char* ip, int len) {
    for(int i=0; i<len; i++) 
        if(!isdigit(ip[i])) return false;

    if(atoi(ip) > 255) return false;

    return true;
}

bool is_ip(char* ip) {
    int i=0;
    for(; i < 4; i++) {
        int x = strcspn(ip, ".\0");

        if(!is_number(ip, x)) return false; 

        ip += x + 1;

        if(ip[-1] == '\0') break;
    }

    if(i != 3 || ip[-2] == '.') return false;

    return true;
}

int main(){
    return 0;
}
