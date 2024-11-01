#ifndef _CHECK_H_
#define _CHECK_H_

enum Errors
{
    OVERFLOW,
    CONNECTION_PROBLEM,
    ALL_RIGHT,
    NO_FREE,
    BAD_ANC
};

static const int LIST_SIZE   =  10;
static const int POISON      = -13;
static const int START_VALUE =  -1;

struct List 
{
    int* data;

    int* next;
    int* prev;

    int free;
};


Errors verificator (List* my_list);
Errors connection_check (List* my_list);
void   dump (List* my_list);

#endif //_CHECK_H_