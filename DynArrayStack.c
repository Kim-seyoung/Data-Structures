// 201811163 / 김세영 / Windows
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define COUNT 10000000

struct DynArrayStack {
	int top;
	int capacity; // 최대크기
	int* array;
};

struct DynArrayStack* CreateStack(int cap) {
	struct DynArrayStack* S = (struct DynArrayStack*)malloc(sizeof(struct DynArrayStack));
	if (!S) return NULL;
	S->capacity = cap;
	S->top = -1;
	S->array = (int*)malloc(S->capacity * sizeof(int));
	if (!S->array) {
		return NULL;
	}
	return S;
}

int IsEmptyStack(struct DynArrayStack* S) {
	return (S->top == -1);
	// 이 조건이 참이면 1이 리턴되고 아니면 0이 리턴된다. (C++에서는 bool타입 반환)
}

int IsFullStack(struct DynArrayStack* S) {
	return (S->top == S->capacity - 1);
	// 이 조건이 참이면 1이 리턴되고 아니면 0이 리턴된다. (C++에서는 bool타입 반환)
}

void DoubleStack(struct DynArrayStack* S) {
	S->capacity *= 2;
	S->array = (int*)realloc(S->array, S->capacity * sizeof(int));
}

void Push(struct DynArrayStack* S, int data) {
	// 동적배열 방식으로 오버플로우가 발생하지 않음
	if (IsFullStack(S)) 
		DoubleStack(S);
	S->array[++S->top] = data; // top를 1증가한 후에 데이터입력
}

int Pop(struct DynArrayStack* S) {
	if (IsEmptyStack(S)) {
		printf("Stack is Empty");
		return INT_MIN;
	}
	return (S->array[(S->top)--]);
}

void DeleteStack(struct DynArrayStack* S) {
	if (S) {
		if (S->array)
			free(S->array);
		free(S);
	}
}

int Size(struct DynArrayStack* S) {
	return S->top + 1;
}

int Top(struct DynArrayStack* S) {
	if (IsEmptyStack(S))
		return INT_MIN;
	return S->array[S->top];
}

void PrintStack(struct DynArrayStack* S) { // 맨 위의 데이터부터 출력
	for (int i = S->top; i >= 0; i--) {
		printf("%d  ", S->array[i]);
	}
	printf("\n");
}

int main()
{
	struct DynArrayStack* mystk = CreateStack(1);
	clock_t start;
	clock_t end;
	unsigned long long i;

	start = clock();
	/* 시간을 측정하고자 하는 코드 시작 */
	/*for (i = 0; i < COUNT; i++) // 1번 문제
		Push(mystk, i);
	for (i = 0; i < COUNT; i++)
		Pop(mystk, i);*/

	//Push(mystk, COUNT); // 2번 문제 설계용
	//Pop(mystk);

	/*for (i = 0; i < COUNT; i++) { // 3번 문제
		start = clock();
		Push(mystk, i);
		if ((i >= (1 << 23) - 10) && (i <= (1 << 23) + 10))
		{
			end = clock();
			printf("Time: %d millisec\n", end - start);
			continue;
		}
		end = clock();
	}*/

	for (i = 0; i < COUNT; i++) { // 4번 문제
		Push(mystk, i);
		Pop(mystk);
	}
	/* 시간을 측정하고자 하는 코드 끝 */
	end = clock();
	printf("Time: %d millisec\n", end - start);

	DeleteStack(mystk);
	return 0;
}