// 201811163 / 김세영 / Windows
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define COUNT 10000000

typedef struct ListNode {
	int data;
	struct ListNode* next;
} ListNode;

struct Stack {
	struct ListNode* top;
	int size;
};

struct Stack* CreateStack() {
	struct Stack* S = (struct Stack*)malloc(sizeof(struct Stack));
	if (!S) return NULL;
	S->top = NULL;
	return S;
}

int IsEmptyStack(struct Stack* S) {
	return (S->top == NULL);
	// 이 조건이 참이면 1이 리턴되고 아니면 0이 리턴된다. (C++에서는 bool타입 반환)
}

void Push(struct Stack* S, int data) {
	struct ListNode* temp;
	temp = (struct ListNode*)malloc(sizeof(struct ListNode));
	if (!temp) // heap 공간이 꽉 차서 Push하지 못할 경우를 예외처리
		return;
	temp->data = data;
	temp->next = S->top;
	S->top = temp;
	S->size++;
}

int Pop(struct Stack* S) {
	int data;
	struct ListNode* temp;

	if (IsEmptyStack(S)) {
		printf("Stack is Empty");
		return INT_MIN;
	}

	temp = S->top;
	S->top = S->top->next;
	data = temp->data;
	free(temp);
	S->size--;
	return data;
}

void DeleteStack(struct Stack* S) {
	struct ListNode *temp, *p;
	p = S->top;
	while (p) {
		temp = p->next;
		free(p);
		p = temp;
	}
	if(S)
		free(S);
}

int Size(struct Stack* S) {
	return S->size;
}

int Top(struct Stack* S) {
	if (IsEmptyStack(S))
		return INT_MIN;
	return S->top->data;
}

void PrintStack(struct Stack* S) { // Top포인터만 있어서 맨 위의 데이터부터 출력된다.
	struct ListNode *temp;
	temp = S->top;
	while (temp) {
		printf("%d  ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main()
{
	struct Stack* mystk = CreateStack();
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