#include <stdlib.h>
#include <stdio.h>
int main()
{
    int *p = (int *)malloc(sizeof(int));
    int *q = (int *)malloc(sizeof(int) * 2);
    *p = 1;
    *q = 10;
    fprintf(stdout, "Value stored at address %p: %d\n", p, *p);
    fprintf(stdout, "Value stored at address %p: %d\n", q, *q);

    q = p;

    fprintf(stdout, "Value stored at address %p: %d\n", q, *q);
    fprintf(stdout, "Value stored at address %p: %d\n", p, *p);
    free(q);
    free(p);
}
