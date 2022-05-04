#include <stdio.h>
int main()
{
    int x = 0;
    int y = x;

    int *ptr_x = &x;
    int *ptr_y = &y;
    int **pptr_x = &ptr_x;
    int **pptr_y = &ptr_y;

    fprintf(stdout, "x contains the value %d at location %p\n", *ptr_x, ptr_x);
    fprintf(stdout, "y contains the value %d at location %p\n", *ptr_y, ptr_y);
    printf("%p\n", pptr_x);
    printf("%p", pptr_y);

    return 0;
}
