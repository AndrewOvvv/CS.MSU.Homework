#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {DIFF_SIZES = 4};

long long trand()
{
    return rand() - RAND_MAX / 2;
}


void gen_inc(long long* array, int size)
{
    array[0] = trand();
    for (int i = 1; i < size; i++)
        array[i] = array[i - 1] + rand();
}


void gen_dec(long long* array, int size)
{
    array[0] = trand();
    for (int i = 1; i < size; i++)
        array[i] = array[i - 1] - rand();
}


void gen_rnd(long long* array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = trand();
}


void fprintf_array(FILE* fout, long long* array, int size)
{
    for (int i = 0; i < size; i++)
        fprintf(fout, "%lld ", array[i]);
    fprintf(fout, "\n");
}


int main(void )
{
    FILE* fout = fopen("data.txt", "w");
    int sizes[DIFF_SIZES] = {10, 100, 1000, 10000};

    for (int i = 0; i < DIFF_SIZES; i++)
    {
        int current_size = sizes[i];
        fprintf(fout, "%i\n", current_size);

        long long* array = malloc(current_size * sizeof(long long));

        gen_inc(array, current_size);
        fprintf_array(fout, array, current_size);

        gen_dec(array, current_size);
        fprintf_array(fout, array, current_size);

        gen_rnd(array, current_size);
        fprintf_array(fout, array, current_size);

        gen_rnd(array, current_size);
        fprintf_array(fout, array, current_size);
    }

    fclose(fout);
    return 0;
}
