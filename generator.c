#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {DIFF_SIZES = 4};


long long mabs(long long x)
{
    if (x < 0)
        return -x;
    return x;
}


void sort_inc(long long* array, int size) // sort sequence
{
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (mabs(array[i]) > mabs(array[j]))
            {
                long long tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
}


void sort_dec(long long* array, int size) // sort sequence
{
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (mabs(array[i]) < mabs(array[j]))
            {
                long long tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
}


long long trand() //function generates truely random nauber which can be lower than zero
{
    return rand() - RAND_MAX / 2;
}


void gen_rnd(long long* array, int size) // the function generates a random sequence of numbers
{
    for (int i = 0; i < size; i++)
        array[i] = trand();
}


void gen_inc(long long* array, int size) //function generates a strictly increasing sequence of numbers
{
    gen_rnd(array, size);
    sort_inc(array, size);
}


void gen_dec(long long* array, int size) // the function generates a strictly decreasing sequence of numbers
{
    gen_rnd(array, size);
    sort_dec(array, size);
}


void fprintf_array(FILE* fout, long long* array, int size) //function outputs an array of size 'size' to a file
{
    for (int i = 0; i < size; i++)
        fprintf(fout, "%lld ", array[i]);
    fprintf(fout, "\n");
}


int main(void )
{
    srand(time(NULL));
    FILE* fout = fopen("data.txt", "w"); //open file for writing
    int sizes[DIFF_SIZES] = {10, 100, 1000, 10000}; // fill array of sizes

    for (int i = 0; i < DIFF_SIZES; i++)
    {
        int current_size = sizes[i]; //save current size
        fprintf(fout, "%i\n", current_size);

        long long* array = malloc(current_size * sizeof(long long)); //reserve memory for array

        gen_inc(array, current_size); // gnerate increasing array
        fprintf_array(fout, array, current_size); // print increasing array

        gen_dec(array, current_size); // generate decreasing array
        fprintf_array(fout, array, current_size); // print decreasing array

        gen_rnd(array, current_size); // generate random array
        fprintf_array(fout, array, current_size); //print random array

        gen_rnd(array, current_size); // generate random array
        fprintf_array(fout, array, current_size); // print random array

        free(array); // free memory
    }

    fclose(fout); // close file
    return 0;
}
