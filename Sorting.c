#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

// bubble sort
void BubbleSort(int A[], int n) { 
	int swapped = 1;
	for (int end = n - 1; end > 0 && swapped; end--) {
		swapped = 0;
		for (int i = 0; i < end; i++) {
			if (A[i] > A[i + 1]) {
				// ������ �׸��� ��ȯ�Ѵ�
				int temp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = temp;
				swapped = 1;
			}
		}
	}
}

// selection sort
void SelectionSort(int A[], int n) { 
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (A[j] < A[min])
				min = j;
		}
		// �׸��� ��ȯ�Ѵ�
		temp = A[min];
		A[min] = A[i];
		A[i] = temp;
	}
}

// insertion sort
void InsertionSort(int A[], int n) {
	int i, j, key;
	for (i = 1; i <= n - 1; i++) {
		key = A[i];
		for (j = i - 1; j >= 0 && A[j] > key; j--) {
			A[j + 1] = A[j];
		}
		A[j + 1] = key;
	}
}

// merge sort
void Merge(int A[], int temp[], int left, int right, int right_end) {
	int i, j, left_end, size, temp_pos;
	left_end = right - 1;
	size = right_end - left + 1;
	i = left;
	j = right;
	temp_pos = left;
	while ((i <= left_end) && (j <= right_end)) {   // left�ʰ� right�ʿ��� ���� ������� temp[]�� copy
		if (A[i] <= A[j]) {
			temp[temp_pos] = A[i];
			temp_pos = temp_pos + 1;
			i = i + 1;
		}
		else {
			temp[temp_pos] = A[j];
			temp_pos = temp_pos + 1;
			j = j + 1;
		}
	}
	while (i <= left_end) {    // left���� �����ִٸ�
		temp[temp_pos] = A[i];
		temp_pos = temp_pos + 1;
		i = i + 1;
	}
	while (j <= right_end) {      // right���� �����ִٸ�
		temp[temp_pos] = A[j];
		temp_pos = temp_pos + 1;
		j = j + 1;
	}
	for (i = left; i <= right_end; i++) // temp[]���� A[]�� �ٽ� copy
		A[i] = temp[i];
}


void MergeSort(int A[], int temp[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		MergeSort(A, temp, left, mid);
		MergeSort(A, temp, mid + 1, right);
		Merge(A, temp, left, mid + 1, right);
	}
}

// quick sort
void swap(int A[], int low, int high) {
	int temp;
	temp = A[high];
	A[high] = A[low];
	A[low] = temp;
}

int Partition(int A[], int left, int right) {
	int low, high;  // ���� ���� ���� pivot���� ����
	int pivot_item = A[left];
	
	// Randomized Quick Sort�� ���� Random index�� �� �� A[0]�� swap -> ���ĵ� �迭�� ���, ������ ������
	/*int random_index = rand() % (right + 1);
	int pivot_item = A[random_index];*/

	low = left;
	high = right;
	while (low < high) {
		/* item <= pivot�� ���� ���������� �ű�� */
		while (low <= right && A[low] <= pivot_item)
			low++;
		/* item > pivot�� ���� dhls������ �ű�� */
		while (left <= right && A[high] > pivot_item)
			high--;
		if (low < high)
			swap(A, low, high); // swap�� ���� ����
	}
	/* high�� pivot�� ���� ��ġ�̴� */
	A[left] = A[high];
	A[high] = pivot_item;
	return high;
}

void QuickSort(int A[], int left, int right) {
	int pivot;
	if (left < right) {
		pivot = Partition(A, left, right);
		QuickSort(A, left, pivot - 1);
		QuickSort(A, pivot + 1, right);
	}
}

// heap sort
struct Heap {
	int* array;
	int count; // �� ���� �׸� ����
	int capacity; // ���� �뷮
	int heap_type; // min heap���� max heap����
};

struct Heap* CreateHeap(int capacity, int heap_type) {
	struct Heap* h = (struct Heap*)malloc(sizeof(struct Heap));
	if (h == NULL) {
		printf("Memory Error");
		return NULL;
	}
	h->heap_type = heap_type;
	h->count = 0;
	h->capacity = capacity;
	h->array = (int*)malloc(sizeof(int) * h->capacity);
	if (h->array == NULL) {
		printf("Memory Error");
		return NULL;
	}
	return h;
}

int Parent(struct Heap* h, int i) {
	if (i <= 0 || i >= h->count)
		return -1;
	return (i - 1) / 2;
}

int LeftChild(struct Heap* h, int i) {
	int left = 2 * i + 1;
	if ((i < 0) || (left >= h->count)) return -1;
	return left;
}

int RightChild(struct Heap* h, int i) {
	int right = 2 * i + 2;
	if ((i < 0) || (right >= h->count)) return  -1;
	return right;
}

void Heapify(struct Heap* h, int i) {
	int left, right, max, temp;
	left = LeftChild(h, i);
	right = RightChild(h, i);
	if (left != -1 && h->array[left] > h->array[i])   max = left;
	else   max = i;
	if (right != -1 && h->array[right] > h->array[max])   max = right;
	if (max != i) {
		//h->array[i]�� h->array[max]�� swap�ϱ�
		temp = h->array[i];
		h->array[i] = h->array[max];
		h->array[max] = temp;
		Heapify(h, max);
	}
}

void ResizeHeap(struct Heap* h) {    // realloc���� �����ϰ� ���� ����
	int* array_old = h->array;
	h->array = (int*)malloc(sizeof(int) * h->capacity * 2);
	if (h->array == NULL) {
		printf("Memory Error");
		return;
	}
	for (int i = 0; i < h->capacity; i++)
		h->array[i] = array_old[i];
	h->capacity *= 2;
	free(array_old);
}

void BuildHeap(struct Heap* h, int A[], int n) {
	int last_index;
	if (h == NULL)         return;
	while (n > h->capacity)
		ResizeHeap(h);
	for (int i = 0; i < n; i++) {
		h->array[i] = A[i];
	}
	h->count = n;
	last_index = n - 1;
	for (int i = Parent(h, last_index); i >= 0; i--) {
		Heapify(h, i);
	}
}

void DestroyHeap(struct Heap* h) {
	if (h == NULL)
		return;
	free(h->array);
	free(h);
}

void HeapSort(int A[], int n) {
	int i, temp;
	struct Heap* h = CreateHeap(n, 1);  // type 1�� max heap�̶�� ����
	BuildHeap(h, A, n);
	for (i = n - 1; i > 0; i--) {	// n-1���� 1���� �ݺ�	
		temp = h->array[0]; 	// h->array[0]�� ���� ū �׸��̴�
		h->array[0] = h->array[h->count - 1];
		h->array[h->count - 1] = temp;   // ��������: ���� ū �׸��� �� �ڷ� �ű��.
		h->count--;
		Heapify(h, 0);
	}
	for (i = 0; i < n; i++)
		A[i] = h->array[i];
	DestroyHeap(h);
}


void PrintArray(int A[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d  ", A[i]);
	printf("\n");
}

int main()
{
	srand((unsigned)time(NULL));

	int a[SIZE]; int temp[SIZE];
	for (int i = 0; i < SIZE; i++) {
		// a[i] = rand() % SIZE; // 1��
		a[i] = i; // 2��
	}

	clock_t start;
	clock_t end;
	unsigned long long i;

	start = clock();
	/* �ð��� �����ϰ��� �ϴ� �ڵ� ���� */
	
	//BubbleSort(a, SIZE);
	//SelectionSort(a, SIZE);
	//InsertionSort(a, SIZE);
	//MergeSort(a, temp, 0, SIZE - 1);
	QuickSort(a, 0, SIZE - 1);
	//HeapSort(a, SIZE);

	/* �ð��� �����ϰ��� �ϴ� �ڵ� �� */
	end = clock();
	printf("Time: %d millisec\n", end - start);

	return 0;
}