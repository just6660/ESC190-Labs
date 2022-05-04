#include "lab3.h"
// Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta)
{

    if (strcmp(item, "IDE") != 0)
    {
        // create new_request party_node
        struct party_node *new_request = malloc(sizeof(struct party_node));

        // allocate memory for string
        new_request->item = (char *)malloc(sizeof(char) * (strlen(item) + 1));
        new_request->ta = (char *)malloc(sizeof(char) * (strlen(ta) + 1));

        // set new_request data
        strcpy(new_request->item, item);
        strcpy(new_request->ta, ta);
        new_request->price = price;

        // Rewiring the nodes
        new_request->next = *head;
        *head = new_request;

        return 0;
    }
    return -1;
}

// Remove the last item added
void remove_request(struct party_node **head)
{
    if (!*head)
    {
        return;
    }
    struct party_node *curr = *head;
    *head = (*head)->next;
    free(curr->item);
    free(curr->ta);
    free(curr);
}

// splits the list into two halves with *front being the pointer at the front of the list and *mid being the pointer at the middle of the list
void SplitList(struct party_node *head, struct party_node **front, struct party_node **mid)
{
    struct party_node *ptr_1;
    struct party_node *ptr_2;

    ptr_1 = head;
    ptr_2 = head->next;
    while (ptr_2)
    {
        ptr_2 = ptr_2->next;
        if (ptr_2)
        {
            ptr_1 = ptr_1->next;
            ptr_2 = ptr_2->next;
        }
    }
    *front = head;
    *mid = ptr_1->next;
    ptr_1->next = NULL;
}

// recursively merges 2 sorted lists into 1 sorted list
struct party_node *SortedMerge(struct party_node *a, struct party_node *b)
{
    struct party_node *result = NULL;
    if (a == NULL)
    {
        return b;
    }
    if (b == NULL)
    {
        return a;
    }

    if (a->price > b->price)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

// recursively sorts a list using merge sort
void make_sorted(struct party_node **head)
{
    // front of split list
    struct party_node *a;

    // middle of split list
    struct party_node *b;

    // reference to head of lists
    struct party_node *headRef = *head;

    // base case
    if ((headRef == NULL) || ((headRef)->next == NULL))
    {
        return;
    }

    // splits the list into two parts
    SplitList(headRef, &a, &b);

    // recursively splits the lists and then merges them once the base case is reached
    make_sorted(&a);
    make_sorted(&b);
    *head = SortedMerge(a, b);
}

// Trim list to fit the budget
double finalize_list(struct party_node **head, double budget)
{
    struct party_node *prev = *head;
    struct party_node *curr = (*head)->next;
    int on_head = 1;
    while (curr)
    {
        if (budget < (*head)->price && on_head)
        {
            remove_request(head);
            prev = *head;
            curr = (*head)->next;
        }
        else if (budget < (curr)->price)
        {
            prev->next = curr->next;
            remove_request(&curr);
        }
        else
        {
            if (on_head)
            {
                budget -= (*head)->price;
                on_head = 0;
            }
            else
            {
                budget -= curr->price;
                prev = prev->next;
                curr = curr->next;
            }
        }
    }
    return budget;
}

// Print the current list - hope this is helpful!
void print_list(struct party_node *head)
{
    int count = 1;
    printf("The current list contains:\n");
    while (head != NULL)
    {
        printf("Item %d: %s, %.2lf, requested by %s\n",
               count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}