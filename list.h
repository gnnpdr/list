#ifndef _LIST_H_
#define _LIST_H_

#include "check.h"

void list_ctor (List* my_list);
Errors list_push (List* my_list, int anchor_value, int new_element);
Errors list_pop (List* my_list, int anchor_value);

#endif //_LIST_H_