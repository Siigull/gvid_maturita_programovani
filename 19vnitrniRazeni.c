#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insertSort(int* pole, int n){
    for(int i=1; i<n; i++)
        for(int j=i; j>0 && pole[j-1] > pole[j]; j--)
            swap(&pole[j-1], &pole[j]);
}

void selectSort(int* pole, int n){
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if(pole[j] < pole[i]) swap(&pole[j], &pole[i]);
}

void bubbleSort(int* pole, int n){
    int posledni = 0;
    for(int i=0; i<n; i++){
        bool was = false;
        for(int j=posledni; j<n-1; j++){
            if(pole[j] > pole[j+1]){ 
                if(!was){
                    was = true;
                    posledni = max(j-1, 0);
                }
                swap(&pole[j], &pole[j+1]);
            }
        }
        if(!was) return;
    }
}

void mergeSort(int* pole, int n){
    if(n == 1) return;

    int n1 = n/2;
    mergeSort(pole, n1);
    
    int n2 = n - n1;
    mergeSort(pole + n1, n2);

    // ---------------------uloha---------------------
    int i=0, j=0, res[n];
    while(i < n1 && j < n2)
        if(pole[i] < pole[n1+j]) { res[i+j] = pole[i]; i++; }
        else { res[i+j] = pole[n1 + j]; j++; }

    for(; i<n1; i++) res[i+j] = pole[i];
    for(; j<n2; j++) res[i+j] = pole[n1+j];

    for(int a=0; a<n; a++) pole[a] = res[a];
    // ---------------------uloha---------------------
}

int main(){

    int pole[] = {4,6,3,7,3,5,234,6,5,4,324,3,5235,2,523,5,23,523,5,23,52,35,23,5235};

    mergeSort(pole, 24);

    for(int i=0; i<24; i++) printf("%d ", pole[i]);

    return 0;
}