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
    N %= sizeof(u_int16_t)*8;
    if(N < 0) return (x << -N) | (x >> (sizeof(u_int16_t)*8 + N));
    else return (x >> N) | (x << (sizeof(u_int16_t)*8 - N));
}

//asi nevim co je aritmeticky soucet f

void vypisDvojkova(u_int16_t x){
    printf("%d\n", x);
    for(u_int16_t i=sizeof(u_int16_t)*8; i>0; i--){
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