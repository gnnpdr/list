#include <stdio.h>

#include "check.h"

Errors verificator (List* my_list)
{
    Errors error = connection_check (my_list);
    
    if (error == CONNECTION_PROBLEM)
    {
        printf("connection_problem\n");
        return CONNECTION_PROBLEM;
    }
    else if (my_list->free == 0)
    {
        printf("no free space\n");
        return NO_FREE;
    } 

    return ALL_RIGHT;
}

Errors connection_check (List* my_list)
{
    int* data = my_list->data;
    int* next = my_list->next;
    int* prev = my_list->prev;

    for (int ind = 1; ind < LIST_SIZE; ind++)
    {
        if(data[ind] == POISON)
            break;

        if (ind != next[prev[ind]] && prev[next[ind]] != START_VALUE)
            return CONNECTION_PROBLEM;
    }

    return ALL_RIGHT;
}

void dump (List* my_list)
{
    int* next = my_list->next;
    int* data = my_list->data;
    int* prev = my_list->prev;

    printf("------------------------------------------------------------------------------------------------\n");

    printf("IND\n");
    for (int i = 0; i < LIST_SIZE; i++)
        printf("%d ", i);

    printf("\n");

    printf("DATA\n");
    for (int i = 0; i < LIST_SIZE; i++)
        printf("%d ", data[i]);

    printf("\n");
    printf("NEXT\n");
    for (int i = 0; i < LIST_SIZE; i++)
        printf("%d ", next[i]);

    printf("\n");
    printf("PREV\n");
    for (int i = 0; i < LIST_SIZE; i++)
        printf("%d ", prev[i]);

    printf("\n");
}
