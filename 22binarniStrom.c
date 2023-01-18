#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct prvek{
    int hodnota;
    struct prvek* levy;
    struct prvek* pravy;
}Tprvek;

Tprvek* vytvorPrvek(int hodnota){
    Tprvek* p = malloc(sizeof(Tprvek));
    if(p == NULL) return NULL;
    p->hodnota = hodnota;
    p->pravy = NULL;
    p->levy = NULL;
    return p;
}

void pridejHodnotu(Tprvek* p, int hodnota){
    if(hodnota < p->hodnota)
        if(p->levy == NULL) p->levy = vytvorPrvek(hodnota);
        else pridejHodnotu(p->levy, hodnota);
    else if(hodnota > p->hodnota)
        if(p->pravy == NULL) p->pravy = vytvorPrvek(hodnota);
        else pridejHodnotu(p->pravy, hodnota);
    else 
        printf("hodnota jiz existuje\n");
}

//přidání nového klíče do stromu
void vlozPrvek(Tprvek* p, Tprvek* vlozeny){
    if(p->levy == NULL) p->levy = vlozeny;
    else vlozPrvek(p->levy, vlozeny);
}

int smazHodnotu(Tprvek* p, int hodnota){
    if(p == NULL){ printf("hodnota neni\n"); return 1;}
    if(hodnota < p->hodnota){
        int x = smazHodnotu(p->levy, hodnota);
        if(x == -1) p->levy = NULL;
        else if(x == -2) p->levy = p->levy->levy;
        else if(x == -3) p->levy = p->levy->pravy;
    } else if(hodnota > p->hodnota){
        int x = smazHodnotu(p->pravy, hodnota);
        if(x == -1) p->pravy = NULL;
        else if(x == -2) p->pravy = p->pravy->levy;
        else if(x == -3) p->pravy = p->pravy->pravy;
    } else {
        if(p->pravy == NULL && p->levy == NULL) return -1;
        else if(p->pravy == NULL) return -2;
        else if(p->levy == NULL) return -3;
        else {
            vlozPrvek(p->pravy, p->levy);
            p = p->pravy;
        }
    }
    return 0;
}

//nalezení zadaného klíče
bool jeVeStrome(Tprvek* p, int hodnota){
    if(p == NULL) return 0;
    if(p->hodnota == hodnota) return 1;

    if(hodnota < p->hodnota) return jeVeStrome(p->levy, hodnota);
    else return jeVeStrome(p->pravy, hodnota);
}

// výpis klíčů seřazených vzestupně / sestupně
//vzestupně
void inorder(Tprvek *p){
    if(p == NULL) return;
    inorder(p->levy);
    printf("%d ", p->hodnota);
    inorder(p->pravy);
}

//sestupně
void sestupne(Tprvek *p){
    if(p == NULL) return;
    inorder(p->pravy);
    printf("%d ", p->hodnota);
    inorder(p->levy);
}

void preorder(Tprvek *p){
    if(p == NULL) return;
    printf("%d ", p->hodnota);
    preorder(p->levy);
    preorder(p->pravy);
}


void postorder(Tprvek *p){
    if(p == NULL) return;
    postorder(p->levy);
    postorder(p->pravy);
    printf("%d ", p->hodnota);
}

//nalezení minimálního / maximálního prvku ve stromu
int maxPrvek(Tprvek* p){
    if(p->pravy == NULL) return p->hodnota;
    maxPrvek(p->pravy);
}

int minPrvek(Tprvek* p){
    if(p->levy == NULL) return p->hodnota;
    maxPrvek(p->levy);
}

// zrušení celého stromu
// zrušení listu
void smazStrom(Tprvek* p){
    if(p == NULL) return;
    smazStrom(p->levy);
    smazStrom(p->pravy);
    free(p);
}

// výpočet váhy stromu (počtu prvků ve stromu)
int vahaStromu(Tprvek*p){
    if(p == NULL) return 0;
    int x = vahaStromu(p->levy);
    x += vahaStromu(p->pravy);
    return x;
}

// výpočet výšky stromu (největší vzdálenost kořen – list)
int vyskaStromu(Tprvek* p, int vyska){
    if(p == NULL) return vyska-1;
    int maxVyska = vyskaStromu(p->levy, vyska+1);
    return MAX(vyskaStromu(p->levy, vyska+1), maxVyska);
}

int main(){
    Tprvek* p = vytvorPrvek(14);
    int pole[] = {123,5,345,3,45,345,34,6346,345,23,423,5423,4,235,235,325};
    int n = 16;
    for(int i=0; i<n; i++){
        pridejHodnotu(p, pole[i]);
    }

    return 0;
}