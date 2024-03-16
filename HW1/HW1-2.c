// 2번 201811163 김세영 Windows
#include <stdio.h>

int Fibonacci(int n)
{
    if(n == 1)
        return 1;
    else if(n == 2)
        return 1;
    else    
        return Fibonacci(n-1) + Fibonacci(n-2);
}

int main()
{
    int arr[10];

    printf("2번 피보나치수열\n");

    printf("recursion : ");
    for(int i = 1; i <= 10; i++){
        printf("%d  ", Fibonacci(i));
    }

    printf("\n");

    printf("iteration : ");
    for(int i = 0; i < 10; i++){
        if(i == 0)
            arr[i] = 1;
        else if(i == 1)
            arr[i] = 1;
        else
            arr[i] = arr[i-1]+arr[i-2];
    }

    for(int i = 0; i < 10; i++){
        printf("%d  ", arr[i]);
    }

    return 0;
}