#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {DIFF_SIZES = 4, DIFF_TYPES = 4};

int cnt_swaps, cnt_compares;


void fill_null()
{
    cnt_swaps = 0;
    cnt_compares = 0;
}


long long mabs(long long x) // function my_abs, i can't create function abs, because it has already defined in stdio.h
{
    if (x < 0)
        return -x;
    return x;
}


void fscanf_array(FILE* fin, long long* array, int size) // funtion read arrays from file
{
    for (int i = 0; i < size; i++)
        fscanf(fin, "%lld", &array[i]);
}


void check_correctness(long long* array, int size)
{
    for (int i = 1; i < size; i++)
        if (mabs(array[i - 1]) > mabs(array[i]))
        {
            printf("Incorrect!!!!!!!!!!!!!!!!!!!!\n");
            return;
        }
}


void printf_array(long long* array, int size) //function outputs an array of size 'size' to a file
{
    for (int i = 0; i < size; i++)
        printf("%lld ", array[i]);
    printf("\n");
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


int split_and_split(long long* array, int size) // choose pivot element and after push lesser elemnts at the left segment and greater elements at the right segment
{
    int real_index = rand() % size; // choose random pivot index
    long long pivot = array[real_index], tmp;
    int index_of_pivot = -1;
    for (int i = 0; i < size; i++) // calculate size of left segment (elements lesser than pivot)
    {
        if (mabs(array[i]) <= mabs(pivot))
            index_of_pivot++;
        cnt_compares++;
    }

    if (real_index != index_of_pivot) // put pivot on correct position
    {
        tmp = array[real_index];
        array[real_index] = array[index_of_pivot];
        array[index_of_pivot] = tmp;
        cnt_swaps++;
    }

    int less = 0, great = size - 1;
    while(less < index_of_pivot && index_of_pivot < great) // swap elements while all elements which lesser than pivot will be at the left seg. and all elements which greater than pivot will be at the right seg.
    {
        cnt_compares++;
        while (mabs(array[less]) <= mabs(pivot)) // find greater element at the left part
        {
            less++;
            cnt_compares++;
        }
        cnt_compares++;
        while (mabs(array[great]) > mabs(pivot)) // find lesser element at the right part
        {
            great--;
            cnt_compares++;
        }
        if (less < index_of_pivot && index_of_pivot < great) // swap them
        {
            tmp = array[less];
            array[less] = array[great];
            array[great] = tmp;
            cnt_swaps++;
            less++;
            great--;
        }
    }
    return index_of_pivot; // return size of left part
}


void quicksort(long long* array, int size)
{
    if (size < 2)
        return;
    int m = split_and_split(array, size);
    quicksort(array, m); // sort left part
    quicksort(array + m + 1, size - m - 1); // sort right part
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

            //printf("\n");
            //printf("Before sorting:\n");
            //printf_array(array_shell, current_size);

            shell_sort(array_shell, current_size); // start shell sort for array array_shell
            //printf("After sorting:\n");
            check_correctness(array_shell, current_size);
            //printf_array(array_shell, current_size);
            printf("Shell, type %i array: %i (swaps), %i (comps)\n", j + 1, cnt_swaps, cnt_compares); // print the result of shell sort
            //printf("\n");

            fill_null(); // assignes constants cnt_swaps and cnt_compares the value 0

            //printf("\n");
            //printf("Before sorting:\n");
            //printf_array(array_qsort, current_size);

            quicksort(array_qsort, current_size); // start quick sort for array array_qsort
            check_correctness(array_qsort, current_size);
            //printf_array(array_qsort, current_size);
            printf("Qsort, type %i array: %i (swaps), %i (comps)\n", j + 1, cnt_swaps, cnt_compares); // print the result of quick sort
            //printf("\n");
        }

        free(array_shell); // free memory
        free(array_qsort); // free memory

        printf("\n");
    }

    fclose(fin); // close file
    return 0;
}
