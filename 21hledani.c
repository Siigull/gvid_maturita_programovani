#include <stdio.h>

int binarni(int* pole, int N, int x){
    int start = 0, end = N, stred = N/2;
    do{
        if(pole[stred] > x) end = stred;
        else start = stred;
        stred = (start + end) / 2;
        if(pole[stred] == x) return stred;
    }while(end - start > 1);
    return -1;
}

int sekvencniZarazka(int* pole, int N, int x){
    pole[N] = x;
    int i=0;
    while(1){
        if(pole[i++] == x) return i;
    }
}

int sekvencni(int* pole, int N, int x){
    for(int i=0; i<N; i++)
        if(pole[i] == x) return i;
    return -1;
}

// Ověř pomocí své funkce, zda je vstupní pole seřazeno. Vytvoř podprogram pro
// vyhledání v tomto poli algoritmem
int serazeno(int N){
    int pole[N+1], x;
    scanf("%d", &pole[0]);
    for(int i=1; i<N; i++){
        scanf("%d", &pole[i]);
        if(pole[i-1] > pole[i]) return -2;
    }
    scanf("%d", &x);

    sekvencni(&pole, N, x);

    return binarni(&pole, N, x);
}

int main(){
    int N;
    scanf("%d", &N);
    printf("%d",serazeno(N));
    return 0;
}