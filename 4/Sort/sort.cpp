#include "sort.hpp"
#include <cmath>

int * bubble_sort(int * arr, int n){
    for (int i = 0; i < n-1; ++i){
        for (int j = i+1; j < n; ++j){
            if (arr[i] > arr[j]){
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return arr;
}

int * hoar_sort_rec(int * a,int first, int last){

 
    int i = first, j = last;
    int tmp, x = a[(first + last) / 2];
 
    do {
        while (a[i] < x)
            i++;
        while (a[j] > x)
            j--;
 
    if (i <= j) 
    {
        if (i < j)
        {
            tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
        }
        i++;
        j--;
    }
    } while (i <= j);
 
    if (i < last)
        hoar_sort_rec(a, i, last);
    if (first < j)
        hoar_sort_rec(a, first,j);
    return a;
}

int * hoar_sort(int * arr, int n){
    int begin = 0;
    return hoar_sort_rec(arr,begin,n-1);
}