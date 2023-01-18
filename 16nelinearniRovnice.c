#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Vytvoř funkci pro vyčíslení zadaného polynomu v daném bodě x pomocí Horne-
// rova schématu.
float horner(float* pol, int n, float x){
    float res = pol[0];
    for(int i=1; i<n; i++)
        res = res*x + pol[i];

    return res;
}

// float secny(float* pol, int n, float eps, float a, float b){

//     float fa = horner(pol, n, a);
//     float fb = horner(pol, n, b);
//     float c = a + fa*(b-a) / (fa - fb);
//     float fc;

//     while(fabs(fc = horner(pol, n, c)) > eps){
//         fb = fa;
//         fa = fc;
//         b = a;
//         a = c;
//         c = a + fa*(b-a) / (fa - fb);
//     }
   
//     return c;
// }

float regulaFalsi(float* pol, int n, float eps, float a, float b){
    float fa = horner(pol, n, a);
    float fb = horner(pol, n, b);
    float c = a + fa*(b-a) / (fa - fb);
    float fc;

    while(fabs(fc = horner(pol, n, c)) > eps){
        if(fa * fc < 0){
            b = c;
            fb = fc;
        }else{
            a = c;
            fa = fc;
        }
        c = a + fa*(b-a) / (fa - fb);
    }
    return c;
}


float puleniIntervalu(float* pol, int n, float eps, float begin, float end){
    float stred = (begin + end) / 2.0;

    if(end - begin < eps) return stred;

    if(horner(pol, n, begin) * horner(pol, n, stred) < 0.0)
        return puleniIntervalu(pol, n, eps, begin, stred);
    else
        return puleniIntervalu(pol, n, eps, stred, end);
}

// Ověř funkčnost na polynomu <bude zadán> na intervalu <bude zadán>.
bool jeFunkcni(float* pol, int n, float begin, float end){
    if(horner(pol, n, begin) * horner(pol, n, end) > 0) return false;
    return true;
}

// Newtonovy metody (bude zadána derivace vyšetřované funkce)
float newton(float* pol, float* d, int n, float eps, float x){
    float fx;
    while(fabs(fx = horner(pol, n, x)) > eps)
        x = x - fx / horner(d, n-1, x);
    return x;
}

int main(){
    float f1[3] = {-5, 3.2, 7.5};
    float fd[2] = {-10, 3.2};
    int n = 3;
    printf("%f", newton(f1, fd, n, 0.0001, 2));
    return 0;
}