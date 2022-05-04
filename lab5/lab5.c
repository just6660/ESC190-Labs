#include "lab5.h"

char **plan_route(Graph *gr, char *start, char *dest)
{
    // getting index of destination vertex
    int starting_index = -1;
    int destination_index = -1;
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(start, gr->adj_list[i]->station) == 0)
        {
            starting_index = i;
        }
        if (strcmp(dest, gr->adj_list[i]->station) == 0)
        {
            destination_index = i;
        }
    }

    // check if start and dest exist
    if (starting_index == -1 || destination_index == -1)
    {
        return NULL;
    }

    // initialize all the vnode costs to "infinity" and visited to 0 (false)
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, start) == 0)
        {
            gr->adj_list[i]->cost = 0;
            gr->adj_list[i]->visited = 1;
        }
        else
        {
            gr->adj_list[i]->cost = 25001;
            gr->adj_list[i]->visited = 0;
        }
    }

    int shortest_path_length = 1;
    // while loop until the destination vertex is visited
    while (gr->adj_list[destination_index]->visited != 1)
    {

        // find the vnode with the lowest potential cost
        int min_cost = 25001;
        int min_cost_start_index;
        int min_cost_destination_index = -1;
        int min_weight;

        // loop through every vnode
        for (int i = 0; i < gr->count; i++)
        {
            // if vnode is not visited then continue
            if (gr->adj_list[i]->visited != 1)
            {
                continue;
            }

            Enode *curr_enode = gr->adj_list[i]->edges;
            while (curr_enode != NULL)
            {
                // if edgenode vertex is visited then continue
                int test_vnode_index;

                for (int j = 0; j < gr->count; j++)
                {
                    if (strcmp(curr_enode->vertex, gr->adj_list[j]->station) == 0)
                    {
                        test_vnode_index = j;
                    }
                }
                if (gr->adj_list[test_vnode_index]->visited == 1)
                {
                    curr_enode = curr_enode->next;
                    continue;
                }

                // check each enode to find the minimum cost path
                if (min_cost > gr->adj_list[i]->cost + curr_enode->weight)
                {
                    min_cost = gr->adj_list[i]->cost + curr_enode->weight;
                    min_cost_start_index = i;
                    min_cost_destination_index = test_vnode_index;
                    min_weight = curr_enode->weight;
                }
                curr_enode = curr_enode->next;
            }
        }

        // no path
        if (min_cost_destination_index == -1)
        {
            return NULL;
        }

        // adjust cost of vnode
        gr->adj_list[min_cost_destination_index]->cost = gr->adj_list[min_cost_start_index]->cost + min_weight;
        // adjust prev vnode pointer
        gr->adj_list[min_cost_destination_index]->prev = gr->adj_list[min_cost_start_index];

        gr->adj_list[min_cost_destination_index]->visited = 1;
        shortest_path_length++;
    }

    // make list of shortest path
    char **shortest_route = (char **)malloc(sizeof(char *) * shortest_path_length);

    Vnode *curr_vnode = gr->adj_list[destination_index];
    int count = 0;
    // starts from destination vnode and records shortest path in a char* array using prev pointer
    while (curr_vnode != NULL)
    {
        shortest_route[count] = (char *)malloc(sizeof(char) * (MAX_LEN + 1));
        strcpy(shortest_route[count], curr_vnode->station);
        count++;
        curr_vnode = curr_vnode->prev;
    }
    return shortest_route;
}

void add(Graph *gr, char *station)
{
    // check if station already exists
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            return;
        }
    }

    // initialize new vnode station
    Vnode *new_station = (Vnode *)malloc(sizeof(Vnode));
    strcpy(new_station->station, station);
    new_station->edges = NULL;
    new_station->prev = NULL;

    // add new vnode station to graph

    // if adj_list is null then create adj_list
    if (gr->adj_list == NULL)
    {
        gr->adj_list = (Vnode **)malloc(sizeof(Vnode *));
    }
    // realloc space for new station vnode
    else
    {
        gr->adj_list = (Vnode **)realloc(gr->adj_list, sizeof(Vnode *) * (gr->count + 1));
    }
    gr->adj_list[gr->count] = new_station;
    gr->count++;
}
void update(Graph *gr, char *start, char *dest, int weight)
{

    // get index of starting station and destination station
    int starting_index = -1;
    int destination_index = -1;
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, start) == 0)
        {
            starting_index = i;
        }
        if (strcmp(gr->adj_list[i]->station, dest) == 0)
        {
            destination_index = i;
        }
    }

    // if weight is 0 remove edge from graph
    if (weight == 0)
    {
        // if vnode doesn't exist then do nothing
        if (starting_index == -1 || destination_index == -1)
        {
            return;
        }

        // keep track of head enode
        Enode *head_enode = gr->adj_list[starting_index]->edges;

        // if enode doesn't exist then do nothing
        if (head_enode == NULL)
        {
            return;
        }

        // keep track of prev and curr enode;
        Enode *prev_enode = head_enode;
        Enode *curr_enode = head_enode->next;

        // if enode to be removed is head
        if (strcmp(head_enode->vertex, dest) == 0)
        {
            free(head_enode);
            gr->adj_list[starting_index]->edges = curr_enode;
            return;
        }

        // removing enode and rewiring nodes
        while (curr_enode != NULL)
        {
            if (strcmp(curr_enode->vertex, dest) == 0)
            {
                prev_enode->next = curr_enode->next;
                free(curr_enode);
                return;
            }
            prev_enode = prev_enode->next;
            curr_enode = curr_enode->next;
        }
    }

    // if weight isn't 0
    if (weight != 0)
    {
        // add start and dest vnodes if they don't already exist
        add(gr, start);
        add(gr, dest);

        // get index of starting station and destination station
        for (int i = 0; i < gr->count; i++)
        {
            if (strcmp(gr->adj_list[i]->station, start) == 0)
            {
                starting_index = i;
            }
            if (strcmp(gr->adj_list[i]->station, dest) == 0)
            {
                destination_index = i;
            }
        }

        // keep track of current enode
        Enode *curr_enode = gr->adj_list[starting_index]->edges;

        // enode exists already modify the enode
        while (curr_enode != NULL)
        {
            if (strcmp(curr_enode->vertex, dest) == 0)
            {
                curr_enode->weight = weight;
                return;
            }
            curr_enode = curr_enode->next;
        }

        // enode doesn't exist add the enode to the end of linked list
        Enode *new_enode = (Enode *)malloc(sizeof(Enode));
        curr_enode = gr->adj_list[starting_index]->edges;

        // if there are no existing enodes
        if (curr_enode == NULL)
        {
            strcpy(new_enode->vertex, dest);
            new_enode->weight = weight;
            new_enode->next = NULL;
            gr->adj_list[starting_index]->edges = new_enode;
        }
        // add new enode to end of linked list
        else
        {
            while (curr_enode != NULL)
            {
                if (curr_enode->next == NULL)
                {
                    strcpy(new_enode->vertex, dest);
                    new_enode->weight = weight;
                    new_enode->next = NULL;
                    curr_enode->next = new_enode;
                    return;
                }
                curr_enode = curr_enode->next;
            }
        }
    }
}

void disrupt(Graph *gr, char *station)
{

    // remove all enodes pointing to targeted vnode
    for (int i = 0; i < gr->count; i++)
    {
        update(gr, gr->adj_list[i]->station, station, 0);
    }

    // finding the targeted vnode
    Vnode *temp_vnode;
    int temp_vnode_index = -1;
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, station) == 0)
        {
            temp_vnode = gr->adj_list[i];
            temp_vnode_index = i;
        }
    }

    // if targeted vnode is not in adj_list
    if (temp_vnode_index == -1)
    {
        return;
    }

    // freeing all the enodes of the targeted vnode
    Enode *curr_enode = temp_vnode->edges;
    Enode *temp_enode = temp_vnode->edges;
    while (curr_enode != NULL)
    {
        curr_enode = curr_enode->next;
        free(temp_enode);
        temp_enode = curr_enode;
    }

    // move all the array elements after the freed vnode down one
    for (int i = temp_vnode_index; i < gr->count - 1; i++)
    {
        gr->adj_list[i] = gr->adj_list[i + 1];
    }

    // set last element to null
    gr->adj_list[gr->count - 1] = NULL;

    // free the targeted vnode
    free(temp_vnode);

    // lower count
    gr->count--;

    // if adj_list is empty free it and set it to NULL
    if (gr->count == 0)
    {
        free(gr->adj_list);
        gr->adj_list = NULL;
    }
}
