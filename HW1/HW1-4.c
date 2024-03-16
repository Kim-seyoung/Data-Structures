// 4번 201811163 김세영 Windows
#include <stdio.h>

int main()
{
    int result = 1;

    printf("4번 팩토리얼-iteration\n");  

    for (int n = 1; n <= 5000; n++) {
        // iteration
        result *= n;
        printf("iteration(%d) : %d\n", n, result);
    }

    return 0;
}