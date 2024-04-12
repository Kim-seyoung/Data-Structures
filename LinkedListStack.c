// 201811163 / �輼�� / Windows
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
	// �� ������ ���̸� 1�� ���ϵǰ� �ƴϸ� 0�� ���ϵȴ�. (C++������ boolŸ�� ��ȯ)
}

void Push(struct Stack* S, int data) {
	struct ListNode* temp;
	temp = (struct ListNode*)malloc(sizeof(struct ListNode));
	if (!temp) // heap ������ �� ���� Push���� ���� ��츦 ����ó��
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

void PrintStack(struct Stack* S) { // Top�����͸� �־ �� ���� �����ͺ��� ��µȴ�.
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
	/* �ð��� �����ϰ��� �ϴ� �ڵ� ���� */
	/*for (i = 0; i < COUNT; i++) // 1�� ����
		Push(mystk, i);
	for (i = 0; i < COUNT; i++)
		Pop(mystk, i);*/

	//Push(mystk, COUNT); // 2�� ���� �����
	//Pop(mystk);

	for (i = 0; i < COUNT; i++) { // 4�� ����
		Push(mystk, i);
		Pop(mystk);
	}
	/* �ð��� �����ϰ��� �ϴ� �ڵ� �� */
	end = clock();
	printf("Time: %d millisec\n", end - start);

	DeleteStack(mystk);
	return 0;
}