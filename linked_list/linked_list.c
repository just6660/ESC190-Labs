#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int cargo;
    struct ListNode *next;
} ListNode;

void print_ll(ListNode *head)
{
    ListNode *curr = head;
    while (curr != NULL)
    {
        printf("%d ", curr->cargo);
        curr = curr->next;
    }
}

ListNode *create_ll(int *arr, int n)
{
    ListNode *head = (ListNode *)malloc(sizeof(ListNode));

    head->cargo = arr[0];
    head->next = NULL;

    ListNode *prev = head;
    ListNode *curr = NULL;

    for (int i = 1; i < n; i++)
    {
        ListNode *curr = (ListNode *)malloc(sizeof(ListNode));
        curr->cargo = arr[i];
        curr->next = NULL;

        prev->next = curr;
        prev = curr;
    }
    return head;
}

int main()
{
    ListNode *ln;
    int arr[] = {1, 2, 3};
    ln = create_ll(arr, 3);
    print_ll(ln);
}