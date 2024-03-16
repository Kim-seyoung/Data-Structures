#include <stdio.h>

int main()
{
    int result = 1;

    for (int n = 1; n <= 5000; n++) {
        // iteration
        result *= n;
        printf("iteration(%d) : %d\n", n, result);
    }

    return 0;
}