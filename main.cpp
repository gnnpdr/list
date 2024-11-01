#include <stdio.h>

#include "check.h"
#include "list.h"

int main ()
{
    List my_list = {};
    list_ctor (&my_list);

    dump (&my_list);

    list_push (&my_list, 0, 10);
    dump (&my_list);

    list_push (&my_list, 1, 20);
    dump (&my_list);

    list_push (&my_list, 2, 30);
    dump (&my_list);

    list_push (&my_list, 1, 40);
    dump (&my_list);

    list_push (&my_list, 4,50);  //вот это мне немного не понятно, это правильно или нет. получается, мы вставляем как бы в середину или в конец?
    dump (&my_list);

    list_pop (&my_list, 1);
    dump (&my_list);
}