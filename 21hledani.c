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

int sekvencni(int N){
    int pole[N];

    for(int i=0; i<N; i++)
        scanf("%d", &pole[i]);

    int x;
    scanf("%d", &x);

    for(int i=0; i<N; i++)
        if(pole[i] == x) return i;
    return -1;
}

int main(){
    int pole[] = {4,6,7,19,23,25,67,123,1525};
    printf("%d", binarni(pole, 9, 7));
    return 0;
}