#include "lab1.h"
#include <math.h>
#include <string.h>
double split_bill(double base_amount, double tax_rate, double tip_rate, int num_people)
{
    return (base_amount + base_amount * tax_rate + (base_amount + base_amount * tax_rate) * tip_rate) / num_people + 0.005;
}

double adjust_price(double original_price)
{
    return 10 * (pow(original_price, 0.5));
}

int sandy_eats(char menu_item[])
{
    int count;
    for (int i = 0; i < strlen(menu_item); i++)
    {
        if (menu_item[i] != ' ')
        {
            count++;
        }

        if (menu_item[i] == 'J' || menu_item[i] == 'K' || menu_item[i] == 'L' || menu_item[i] == 'j' || menu_item[i] == 'k' || menu_item[i] == 'l')
        {
            return 0;
        }
    }
    if (strstr(menu_item, "fish") != NULL)
    {
        return 0;
    }

    if (count % 2 == 1)
    {
        return 0;
    }

    return 1;
}

void imagine_fish(char thing[])
{
    char fish_str[] = "fish";
    strcat(thing, fish_str);
}