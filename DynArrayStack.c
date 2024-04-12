// 201811163 / �輼�� / Windows
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define COUNT 10000000

struct DynArrayStack {
	int top;
	int capacity; // �ִ�ũ��
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
	// �� ������ ���̸� 1�� ���ϵǰ� �ƴϸ� 0�� ���ϵȴ�. (C++������ boolŸ�� ��ȯ)
}

int IsFullStack(struct DynArrayStack* S) {
	return (S->top == S->capacity - 1);
	// �� ������ ���̸� 1�� ���ϵǰ� �ƴϸ� 0�� ���ϵȴ�. (C++������ boolŸ�� ��ȯ)
}

void DoubleStack(struct DynArrayStack* S) {
	S->capacity *= 2;
	S->array = (int*)realloc(S->array, S->capacity * sizeof(int));
}

void Push(struct DynArrayStack* S, int data) {
	// �����迭 ������� �����÷ο찡 �߻����� ����
	if (IsFullStack(S)) 
		DoubleStack(S);
	S->array[++S->top] = data; // top�� 1������ �Ŀ� �������Է�
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

void PrintStack(struct DynArrayStack* S) { // �� ���� �����ͺ��� ���
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
	/* �ð��� �����ϰ��� �ϴ� �ڵ� ���� */
	/*for (i = 0; i < COUNT; i++) // 1�� ����
		Push(mystk, i);
	for (i = 0; i < COUNT; i++)
		Pop(mystk, i);*/

	//Push(mystk, COUNT); // 2�� ���� �����
	//Pop(mystk);

	/*for (i = 0; i < COUNT; i++) { // 3�� ����
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