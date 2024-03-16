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

    for(int i = 1; i <= 10; i++){
        // recursion
        printf("recursion(%d) : %d\t\t", i, factorial(i));

        // iteration
        result *= i;
        printf("iteration(%d) : %d\n", i, result);
    }

    return 0;
}