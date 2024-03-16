// 3번 201811163 김세영 Windows
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

int main() // run time error로 수행이 멈추는 것을 확인
{   
    printf("3번 팩토리얼-Recursion run time error\n");  
    // recursion
    for(int i  = 1; i <= 5000; i++)
        printf("recursion(%d) : %d\n", i, factorial(i));
    return 0;   
}