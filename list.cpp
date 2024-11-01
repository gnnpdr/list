#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void list_ctor (List* my_list)  //оостались вопросы с инициализацией, куда положить ноль?
{
    int free = 0;
    int list[LIST_SIZE];
    int next[LIST_SIZE];
    int prev[LIST_SIZE];

    my_list->data = (int*)calloc(LIST_SIZE, sizeof(int));
    my_list->next = (int*)calloc(LIST_SIZE, sizeof(int));
    my_list->prev = (int*)calloc(LIST_SIZE, sizeof(int));

    list[0] = 0;
    next[0] = 0;
    prev[0] = 0;

    for (int i = 1; i < LIST_SIZE; i++)
    {
        list[i] = POISON;
        next[i] = i + 1;
        prev[i] = START_VALUE;
    }

    free = 1;  //тоже вопрос, короче, уточнить надо

    for (int i = 1; i < LIST_SIZE; i++)
    {
        my_list->data[i] = list[i];
        my_list->next[i] = next[i];
        my_list->prev[i] = prev[i];
    }

    my_list->free = free;
}

//в этом случае якорное значение указывает на предыдущий элемент к тому, куда будет вставка
Errors list_push (List* my_list, int anchor_value, int new_element)
{
    int free = my_list->free;

    int* next = my_list->next;
    int* prev = my_list->prev;

    my_list->data[free] = new_element;

    prev[free] = anchor_value;

    if (prev[next[anchor_value]] != 0)
        prev[next[anchor_value]] = free;

    int new_free = next[free];

    next[free] = next[anchor_value];
    next[anchor_value] = free;
    
    my_list->free = new_free;

    Errors error = verificator(my_list);
    if (error != ALL_RIGHT)
        return error;

    return ALL_RIGHT;
}

//а здесь якорное значение - непосредственно то место, откуда элемент удалят
Errors list_pop (List* my_list, int anchor_value)
{
    if (anchor_value > LIST_SIZE - 1 || anchor_value == 0)
    {
        printf("out of acceptable values\n");
        return BAD_ANC;
    }

    int* next = my_list->next;
    int* prev = my_list->prev;
   
    next[prev[anchor_value]] = next[anchor_value];
    prev[next[anchor_value]] = prev[anchor_value];

    next[anchor_value] = anchor_value;
    my_list->free = next[anchor_value];

    prev[anchor_value] = START_VALUE;
    
    my_list->data[anchor_value] = POISON;

    Errors error = verificator(my_list);
    if (error != ALL_RIGHT)
        return error;

    return ALL_RIGHT;
}

void list_dtor(List* my_list)
{
    free(my_list->data);
    free(my_list->next);
    free(my_list->prev);
}