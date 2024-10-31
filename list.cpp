#include <stdio.h>

#include "list.h"

void list_ctor (List* my_list)  //оостались вопросы с инициализацией, куда положить ноль?
{
    int free = 0;
    int list[LIST_SIZE];
    int next[LIST_SIZE];
    int prev[LIST_SIZE];

    list[0] = POISON;
    next[0] = 0;
    prev[0] = 0;
    my_list->tail = 0;
    my_list->head = 0;  //вот с этим вопросы, что такое head, он в next, но куда он показывает?

    for (int i = 1; i < LIST_SIZE; i++)
    {
        list[i] = POISON;
        next[i] = i;
        prev[i] = START_VALUE;
    }

    free = next[1];  //тоже вопрос, короче, уточнить надо
    
    my_list->data = list;

    for (int i = 1; i < LIST_SIZE; i++)
    {
        my_list->next[i] = next[i];
        my_list->prev[i] = prev[i];
    }

    my_list->free = free;
}
//в этом случае якорное значение указывает на предыдущий элемент к тому, куда будут добавлять
Errors list_push (List* my_list, int anchor_value, int new_element) //в какой буфер, после какого элемента, что записать
{
    int free = my_list->free;
    int tail = my_list->tail;

    int* next = my_list->next;
    int* prev = my_list->prev;

    if (free == 0)
    {
        printf("no free space\n");
        return NO_FREE;
    } 

    my_list->data[free] = new_element;

    if (tail == LIST_SIZE - 1) //точно - 1? Вроде да, но проверь меня, дружище
    {
        printf("no space\n");  //надо ли делать проверку, если по факту все прудыдущая решает?
        return NO_FREE;
    }

    prev[tail + 1] = prev[tail];
    prev[tail] = prev[next[anchor_value]];
    prev[next[anchor_value]] = free;

    int new_free = next[free];
    next[free] = next[anchor_value];
    next[anchor_value] = free;  //пофигу же, можно обратно не возвращать адреса массивов в структуру, они не копируются

    my_list->tail++;
    my_list->free = new_free;

    return ALL_RIGHT;
}
//а здесь якорное значение - непосредственно то место, откуда элемент удалят
Errors list_pop (List* my_list, int anchor_value)  //нужно ли, чтобы возвращал значение, которое забрал из списка?
{

    if (anchor_value > LIST_SIZE - 1 || anchor_value == 0)
    {
        printf("out of acceptable values\n");
        return BAD_ANC;
    }

    int* next = my_list->next;
    int* prev = my_list->prev;

    my_list->data[anchor_value] = POISON;  //потом это значение будет заполнено след push, а так tail не меняется

    next[prev[anchor_value]] = next[anchor_value];
    next[anchor_value] = anchor_value;  //это нужно для free. Мне кажется, я чего-то не догоняю, но это просто бессмысленно

    prev[anchor_value] = START_VALUE;

    my_list->free = anchor_value;

    return ALL_RIGHT;
}