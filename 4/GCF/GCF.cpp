#include "GCF.hpp"
#include <cmath>

int GCF1(int A, int B){
    if(A != B){
        if(A > B) {
            A -= B;
            GCF1(A,B);
        }
        else
        if(B > A) {
            B -= A;
            GCF1(A,B);
        }
    }
    else
    return A;
}

int GCF2(int A, int B){
    int nod = 1;
    int min = A > B ? A : B;
    for (int i = min; i > 1; --i)
        if(A % i == 0 && B % i == 0){
            nod = i;
            break;
        }
    return nod;
}