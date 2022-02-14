#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {DIFF_SIZES = 4, DIFF_TYPES = 4};

int cnt_swaps, cnt_compares;


long long mabs(long long x) // function my_abs, i can't create function abs, because it has already defined in stdio.h
{
    if (x < 0)
        return -x;
    return x;
}


void shell_sort(long long *array, int size) // function which realize shell sort of array (i read about shell sort in the internet)
{
    for (int s = size / 2; s > 0; s /= 2)
    {
        for (int i = s; i < size; ++i)
        {
            int j;
            for (j = i - s; j >= 0 && mabs(array[j]) > mabs(array[j + s]); j -= s)
            {
                cnt_swaps++; cnt_compares++; // increase cnt_swaps because the next step is swap and compares, because in cycle we compare elements
                long long temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
            if (j >= 0 && mabs(array[j]) <= mabs(array[j + s]))
                cnt_compares++;
        }
    }
}


void quicksort(int* array, int size){
    int i, j, pivot;
    long long temp;
    int first = 0, last = size;

    if (first < last)
    {
        pivot = rand() % size; // choose pivot
        i = first;
        j = last;

        while (i < j)
        {
            while (abs(array[i]) <= abs(array[pivot]) && i < last)
            {
                i++;
                cnt_compares++; // increase cnt_compares because we compare elements
            }
            while (abs(array[j]) > abs(array[pivot]))
            {
                j--;
                cnt_compares++; // increase cnt_compares because we compare elements
            }
            if (i < j)
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                cnt_swaps++; // increase cnt_swaps because we swap two elements
            }
        }

        temp = array[pivot];
        array[pivot] = array[j];
        array[j] = temp;
        cnt_swaps++; // increase cnt_swaps because we swap two elements
        quicksort(array + first, (j - 1) - first); // recursively running the function from the left side
        quicksort(array + (j + 1), last - (j + 1)); // recursively running the function from the right side
    }
}



void fill_null()
{
    cnt_swaps = 0;
    cnt_compares = 0;
}


void fscanf_array(FILE* fin, long long* array, int size) // funtion read arrays from file
{
    for (int i = 0; i < size; i++)
        fscanf(fin, "%i", &array[i]);
}


int main(void )
{
    srand(time(NULL));
    FILE* fin = fopen("data.txt", "r"); // open file for reading

    for (int i = 0; i < DIFF_SIZES; i++) // cycle in different sizes
    {
        int current_size;
        fscanf(fin, "%i\n", &current_size); //read current size of array

        // reserve memory for arrays for shell sort and quick sort
        long long* array_shell = malloc(current_size * sizeof(long long));
        long long* array_qsort = malloc(current_size * sizeof(long long));
        printf("size of array: %i\n", current_size);

        // start cycle for different types of arrays (increasing, decreasing, random, random)
        for (int j = 0; j < DIFF_TYPES; j++)
        {
            fscanf_array(fin, array_shell, current_size); // read array from file
            memcpy(array_qsort, array_shell, current_size * sizeof(long long)); // copy array

            fill_null(); // assignes constants cnt_swaps and cnt_compares the value 0
            shell_sort(array_shell, current_size); // start shell sort for array array_shell
            printf("Shell, type %i array: %i (swaps), %i (comps)\n", j + 1, cnt_swaps, cnt_compares); // print the result of shell sort

            fill_null(); // assignes constants cnt_swaps and cnt_compares the value 0
            quicksort(array_qsort, current_size); // start quick sort for array array_qsort
            printf("Qsort, type %i array: %i (swaps), %i (comps)\n", j + 1, cnt_swaps, cnt_compares); // print the result of quick sort
        }
        printf("\n");
    }

    fclose(fin); // close file
    return 0;
}

