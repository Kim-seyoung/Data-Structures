// 201811163 / 김세영 / Windows
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

static void array_print(int arr[])
{
	for (int i = 0; i < SIZE; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

static void array_insert(int arr[], int index, int data)
{
	for (int i = 0; i < SIZE; i++) {
		if (i == index)
			arr[i] = data;
	}
}

static void array_delete(int arr[], int index)
{
	//printf("\n지우는 데이터는 %d입니다.\n", arr[index]);
	for (int i = index; i < SIZE; i++) {
		arr[i] = arr[i + 1];
	}
	//array_print(arr);
}

int main(void) {
	int* arr = (int*)calloc(SIZE, sizeof(int));;

	clock_t start;
	clock_t end;

	unsigned long long i;

	int sum = 0, index;
	srand(time(NULL));

	// 1 - (1) : Insert 측정
	start = clock();

	for (int i = 0; i < SIZE; i++) {
		array_insert(arr, i, i);
	}

	end = clock();
	printf("Insertion Time(Array): %d millisec\n\n\n", end - start);

	// 1 - (2) : Random access for read	
	start = clock();

	for (int i = 0; i < SIZE; i++) {
		index = rand() * 10 % SIZE; // 0 ~ 99999
		sum += arr[index];
	}

	end = clock();
	printf("Random access for read Time(Array): %d millisec\n", end - start);
	printf("sum = %d\n\n\n", sum);

	// 1 - (3) : Random access for deletion
	start = clock();

	for (int i = 0; i < SIZE; i++) {
		index = rand() * 10 % (SIZE - i); // index 갯수가 하나씩 줄어듦.
		array_delete(arr, index);
	}

	end = clock();
	printf("Random access for deletion Time(Array): %d millisec\n", end - start);

	free(arr);
	
	return 0;
}