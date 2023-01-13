#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//Načítej ze vstupu hodnoty zapsané v šestnáctkové soustavě a oddělené bílými
//znaky a vracej jejich vyčíslenou hodnotu. V případě chyby vrať zápornou hodnotu
//a ukonči program. Vyčíslené hodnoty zapisuj na výstup, každou na jeden řádek.
int nacti16(){
    int x;
    while(1){
        if(!scanf("%x", &x)) return -1;
        printf("%d\n", x);
    }
    return 0;
}

// Vytvoř podprogram, který zapíše zadanou hodnotu na výstup ve zvolené číselné
// soustavě. Základ číselné soustavy a hodnota budou parametry podprogramu
// a zjisti je od uživatele. Počítej se základy od 2 do 36.
void tiskCislice(int x){
    if(x > 9) printf("%c", x+87);
    else printf("%d", x);
}

void prevod(int soustava, int x){
    if(x<=0) return;
    int num = x%soustava;
    prevod(soustava, x/soustava);
    tiskCislice(num);
}

// Na vstupu jsou dvě celá čísla oddělená písmenem E, např. 124E-10. Načti je jako
// celá čísla a vrať desetinné číslo, které představují (předveď, že víš, co ten zápis
// představuje). V případě chyby vrať hodnotu NAN (Not A Number = 0.0/0.0). Ne-
// smíš je načítat jako desetinné číslo. Získanou hodnotu vytiskni s přesností na
// 3 desetinná místa v semilogaritmickém tvaru.
void sciNotation(){
    int exp, temp;
    scanf("%dE%d", &temp, &exp);
    float base = temp;
    while(1){
        if(base/10 < 1) break;
        base /= 10;
        exp++;
    }
    printf("%.3fe%d", base, exp);
}


int main(){
    sciNotation();
    return 0;
}