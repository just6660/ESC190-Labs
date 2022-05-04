#include <stdio.h>
#include "lab1.h"

int main()
{
    //Testing Part 1
    double test_p1 = split_bill(62.05, 0.15, 0.30, 4);
    printf("The split will be: $%.2f.\n", test_p1);
    //$32.50

    //Testing Part 2
    double test_p2 = adjust_price(25.00);
    printf("The adjusted price is: $%.2f.\n", test_p2);
    //$50.00

    //Testing Part 3
    char test_food[] = "Pepperoni Pizza";
    int test_p3 = sandy_eats(test_food);
    if (test_p3 == 0)
    {
        printf("Sandy would NOT eat '%s'.\n", test_food);
    }
    else
    {
        printf("Sandy would eat '%s'.\n", test_food);
    }
    //Sandy would eat 'Three Cheese Pizza'

    //Testing Part 4
    char test_p4[] = "zebra";
    imagine_fish(test_p4);
    printf("Justin imagine, a %s!\n", test_p4);
    // Just imagine, a zebrafish!

    //Add more tests here....

    return 0;
}