// 1번 201811163 김세영 Windows
#include <stdio.h>

int factorial(int n)
{
    if(n == 0)
        return 1;
    else if(n == 1)
        return 1;
    else
        return n*factorial(n-1);
}

int main()
{   
    int result = 1;

    printf("1번 팩토리얼 함수\n");

    for(int i = 1; i <= 10; i++){
        // recursion
        printf("recursion(%d) : %d\t\t", i, factorial(i));

        // iteration
        result *= i;
        printf("iteration(%d) : %d\n", i, result);
    }

    return 0;
}