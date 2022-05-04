#include <stdlib.h>
#include <stdio.h>
void append(int **x, int *n, int val)
{
    *x = realloc(*x, sizeof(int) * (*n + 1));

    (*x)[*n] = val;
    *n = *n + 1;
}
/*
int main()
{
    int *ptr = (int *)malloc(sizeof(int) * 3);
    ptr[0] = 1;
    ptr[1] = 2;
    ptr[2] = 3;
    int length = 3;
    for (int i = 0; i < length; i++)
    {
        printf("%d", ptr[i]);
    }
    printf("\n");

    append(&ptr, &length, 4);

    printf("%d\n", length);
    for (int i = 0; i < length; i++)
    {
        printf("%d", ptr[i]);
    }
}
*/