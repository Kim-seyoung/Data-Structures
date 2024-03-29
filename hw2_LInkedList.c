// 201811163 / 김세영 / Windows
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

typedef struct ListNode {
	int data;
	struct ListNode* next;
} ListNode;

int ListLength(struct ListNode* h) 
{
	struct ListNode* current = h;
	int count = 0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

int Traverse(struct ListNode* h, int index)
{
	struct ListNode* current = h;
	int position = 0;
	while((current != NULL) && (position < index)) {
		current = current->next;
		position++;
	}
	return current->data;
}

void InsertInLinkedList(struct ListNode** h, int data, int position)
{
	int k = 0;
	struct ListNode* p, * q, * newNode;
	newNode = (ListNode*)malloc(sizeof(struct ListNode));
	if (!newNode) { // 항상 메모리 에러를 확인해야 한다.
		printf("Memory Error");
		return;
	}
	newNode->data = data;
	p = *h; q = NULL;
	if (position == 0 || *h == NULL) // 가장 처음에 노드를 추가한다.  빈 List일때도
	{
		newNode->next = p;
		*h = newNode;
	}
	else // p는 position + 1 까지, q는 position 까지 진행한다. (position : 3 = index : 3 = 4번째)
	{
		while ((p != NULL) && (k < position)) {
			k++;
			q = p;
			p = p->next;
		}
		if (p == NULL) { // 가장 끝에 노드를 추가한다.
			q->next = newNode;
			newNode->next = NULL;
		}
		else { // 중간에 노드를 추가한다.
			newNode->next = p;
			q->next = newNode;
		}
	}
}

void DeleteNodeFromLinkedList(struct ListNode** h, int position)
{
	int k = 0;
	struct ListNode *p, *q;
	if (*h == NULL) {
		printf("List Empty");
		return;
	}
	p = *h; q = NULL;
	if (position == 0) { // 리스트 가장 맨 앞의 노드를 삭제하는 경우
		*h = p->next;
		free(p);
		return;
	}
	else { // 삭제할 위치까지 리스트 탐색하기
		while ((p != NULL) && (k < position)) { // (p != NULL) 없으면?? = 삭제할 리스트 자체가 없다
			k++;
			q = p;
			p = p->next;
		}
		if (p == NULL) // 리스트에 없는 항목을 삭제하는 경우
			printf("Position does not exist.");
		else { // 리스트 중간 또는 맨끝을 삭제하는 경우
			q->next = p->next;
			free(p);
		}
	}
}

void DeleteLinkedList(struct ListNode** h) { // LinkedList 전체 삭제
	struct ListNode *nextNode, *iterator;
	iterator = *h;
	while (iterator) {
		nextNode = iterator->next;
		free(iterator);
		iterator = nextNode;
	}
	*h = NULL; // Caller 함수의 'head'포인터를 update해 주기 위해
}

int main(void) {
	ListNode* head = NULL;

	clock_t start;
	clock_t end;
	
	unsigned long long i;

	int sum = 0, index;
	srand(time(NULL));

	// 1 - (1) : Insert 측정
	start = clock();

	for (int i = 0; i < SIZE; i++) {
		InsertInLinkedList(&head, i, i);
	}
	
	end = clock();
	printf("Insertion Time(LinkedList): %d millisec\n\n\n", end - start);

	// 1 - (2) : Random access for read	
	start = clock();

	for (int i = 0; i < SIZE; i++) {
		index = rand() * 10 % SIZE; // 0 ~ 99999
		sum += Traverse(head, index);
	}

	end = clock();
	printf("Random access for read Time(LinkedList): %d millisec\n", end - start);
	printf("sum = %d\n\n\n", sum);

	// 1 - (3) : Random access for deletion
	start = clock();

	for (int i = 0; i < SIZE; i++) {
		index = rand() * 10 % (SIZE - i); // index 갯수가 하나씩 줄어듦.
		DeleteNodeFromLinkedList(&head, index);
	}

	end = clock();
	printf("Random access for deletion Time(LinkedList): %d millisec\n", end - start);

	DeleteLinkedList(&head);
	return 0;
}
