#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {DIFF_SIZES = 4, DIFF_TYPES = 4};

int cnt_swaps, cnt_compares;


long long mabs(long long x)
{
    if (x < 0)
        return -x;
    return x;
}


void shell_sort(long long *array, int size)
{
    for (int s = size / 2; s > 0; s /= 2)
    {
        for (int i = s; i < size; ++i)
        {
            int j;
            for (j = i - s; j >= 0 && mabs(array[j]) > mabs(array[j + s]); j -= s)
            {
                cnt_swaps++; cnt_compares++;
                long long temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
            if (j >= 0 && mabs(array[j]) <= mabs(array[j + s]))
                cnt_compares++;
        }
    }
}


void quicksort(int* array, int size)
{
    int i, j, pivot;
    long long temp;
    int first = 0, last = size;

    if (first < last)
    {
        pivot = rand() % size;
        i = first;
        j = last;

        while (i < j)
        {
            while (abs(array[i]) <= abs(array[pivot]) && i < last)
            {
                i++;
                cnt_compares++;
            }
            while (abs(array[j]) > abs(array[pivot]))
            {
                j--;
                cnt_compares++;
            }
            if (i < j)
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                cnt_swaps++;
            }
        }

        temp = array[pivot];
        array[pivot] = array[j];
        array[j] = temp;
        cnt_swaps++;
        quicksort(array + first, (j - 1) - first);
        quicksort(array + (j + 1), last - (j + 1));
    }
}



void fill_null()
{
    cnt_swaps = 0;
    cnt_compares = 0;
}


void fscanf_array(FILE* fin, long long* array, int size)
{
    for (int i = 0; i < size; i++)
        fscanf(fin, "%i", &array[i]);
}


int main(void )
{
    FILE* fin = fopen("data.txt", "r");

    for (int i = 0; i < DIFF_SIZES; i++)
    {
        int current_size;
        fscanf(fin, "%i\n", &current_size);

        long long* array_shell = malloc(current_size * sizeof(long long));
        long long* array_qsort = malloc(current_size * sizeof(long long));
        printf("size of array: %i\n", current_size);
        for (int j = 0; j < DIFF_TYPES; j++)
        {
            fscanf_array(fin, array_shell, current_size);
            memcpy(array_qsort, array_shell, current_size * sizeof(long long));

            fill_null();
            shell_sort(array_shell, current_size);
            printf("Shell, type %i array: %i (swaps), %i (comps)\n", j + 1, cnt_swaps, cnt_compares);

            fill_null();
            quicksort(array_qsort, current_size);
            printf("Qsort, type %i array: %i (swaps), %i (comps)\n", j + 1, cnt_swaps, cnt_compares);
        }
        printf("\n");
    }

    fclose(fin);
    return 0;
}
