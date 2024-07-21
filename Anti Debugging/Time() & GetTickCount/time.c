#include <stdio.h>
#include <time.h>
#include <windows.h>

int* AllocateMemory(unsigned numbers_len)
{
	int *numbers = malloc(numbers_len * sizeof(int));
	return numbers;
}

int GeneratePseudoRandomNumbers(int range)
{
	return (rand() % range);
}

void PrintNumbers(int *array, int array_len)
{
	for (int i = 0; i < array_len; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
}

void BubbleSort(int *numbers, int numbers_len)
{
	for (int i = 0; i < numbers_len; i++)
	{
		for (int j = 0; j < numbers_len-1 - i; j++)
		{
			if (numbers[j] > numbers[j+1])
			{
				int temp = numbers[j];
				numbers[j] = numbers[j+1];
				numbers[j+1] = temp;
			}
		}
	}
}

int main()
{
	int numbers_len = 50000;

	int *numbers = AllocateMemory(numbers_len);

	if (numbers == NULL)
	{
		printf("Memory allocation error.\n");
		return 0;
	}

	srand(time(0));

	for(int i=0; i<numbers_len; i++)
	{
		int rnd = GeneratePseudoRandomNumbers(numbers_len);
		numbers[i] = rnd;
	}

	printf("Array before sorting: \n");
	PrintNumbers(numbers, numbers_len);
	printf("\n");

	// Get the seconds since 1. January 1970
	unsigned long seconds_1 = time(NULL); //GetTickCount();

	printf("Sorting has been started...\n\n");
	BubbleSort(numbers, numbers_len);

	unsigned long seconds_2 = time(NULL); //GetTickCount();

	if (seconds_1 < seconds_2 - 8)
	{
		printf("seconds 1: %lu\n", seconds_1);
		printf("seconds 2: %lu\n\n", seconds_2);

		printf("Time difference: %lu - %lu = %lu seconds\n\n", seconds_2, seconds_1, (seconds_2 - seconds_1) );

		printf("Debugger detected\n");
		getchar();
	}

	printf("Array after sorting: \n");
	PrintNumbers(numbers, numbers_len);
	printf("\n");

	printf("seconds 1: %lu\n", seconds_1);
	printf("seconds 2: %lu\n\n", seconds_2);

	getchar();
	return 0;
}



