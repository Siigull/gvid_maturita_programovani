#include <stdio.h>

u_int16_t soucin(u_int16_t x, u_int16_t y){
    return x & y;
}

u_int16_t soucet(u_int16_t x, u_int16_t y){
    return x | y;
}

u_int16_t xor(u_int16_t x, u_int16_t y){
    return x ^ y;
}

u_int16_t bitPosun(u_int16_t x, u_int16_t N){
    if(N < 0) return x << -N;
    else return x >> N;
}

u_int16_t bitRotace(u_int16_t x, u_int16_t N){
    N %= 16;
    if(N < 0) return (x << -N) | (x >> (16 + N));
    else return (x >> N) | (x << (16 - N));
}

//asi nevim co je aritmeticky soucet f

void vypisDvojkova(u_int16_t x){
    printf("%d\n", x);
    for(int i=16; i>0; i--){
        printf("%d", x >> (i-1) & 1);
    }
    printf("\n");
}

int main(){
    int x, y;
    printf("Zadej prvni hodnotu pro bitovou operaci: ");
    scanf("%d", &x);
    printf("Zadej druhou hodnotu pro bitovou operaci: ");
    scanf("%d", &y);

    return 0;
}