// 201811163 / �輼�� / Windows
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
	if (!newNode) { // �׻� �޸� ������ Ȯ���ؾ� �Ѵ�.
		printf("Memory Error");
		return;
	}
	newNode->data = data;
	p = *h; q = NULL;
	if (position == 0 || *h == NULL) // ���� ó���� ��带 �߰��Ѵ�.  �� List�϶���
	{
		newNode->next = p;
		*h = newNode;
	}
	else // p�� position + 1 ����, q�� position ���� �����Ѵ�. (position : 3 = index : 3 = 4��°)
	{
		while ((p != NULL) && (k < position)) {
			k++;
			q = p;
			p = p->next;
		}
		if (p == NULL) { // ���� ���� ��带 �߰��Ѵ�.
			q->next = newNode;
			newNode->next = NULL;
		}
		else { // �߰��� ��带 �߰��Ѵ�.
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
	if (position == 0) { // ����Ʈ ���� �� ���� ��带 �����ϴ� ���
		*h = p->next;
		free(p);
		return;
	}
	else { // ������ ��ġ���� ����Ʈ Ž���ϱ�
		while ((p != NULL) && (k < position)) { // (p != NULL) ������?? = ������ ����Ʈ ��ü�� ����
			k++;
			q = p;
			p = p->next;
		}
		if (p == NULL) // ����Ʈ�� ���� �׸��� �����ϴ� ���
			printf("Position does not exist.");
		else { // ����Ʈ �߰� �Ǵ� �ǳ��� �����ϴ� ���
			q->next = p->next;
			free(p);
		}
	}
}

void DeleteLinkedList(struct ListNode** h) { // LinkedList ��ü ����
	struct ListNode *nextNode, *iterator;
	iterator = *h;
	while (iterator) {
		nextNode = iterator->next;
		free(iterator);
		iterator = nextNode;
	}
	*h = NULL; // Caller �Լ��� 'head'�����͸� update�� �ֱ� ����
}

int main(void) {
	ListNode* head = NULL;

	clock_t start;
	clock_t end;
	
	unsigned long long i;

	int sum = 0, index;
	srand(time(NULL));

	// 1 - (1) : Insert ����
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

	// 1 - (4) : Random access for deletion
	start = clock();

	for (int i = 0; i < SIZE; i++) {
		index = rand() * 10 % (SIZE - i); // index ������ �ϳ��� �پ��.
		DeleteNodeFromLinkedList(&head, index);
	}

	end = clock();
	printf("Random access for deletion Time(LinkedList): %d millisec\n", end - start);

	DeleteLinkedList(&head);
	return 0;
}