#include <stdio.h>

int factorial(int n, int total)
{
    if (n == 1)
        return total;
    else
        return factorial(n - 1, n * total);
}

int main()
{
    // tail recursion
    printf("tail recursion: %d\n", factorial(10, 1));
    
    return 0;
}