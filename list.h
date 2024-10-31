#ifndef _LIST_H_
#define _LIST_H_

enum Errors
{
    ALL_RIGHT,
    NO_FREE,
    BAD_ANC
};

static const int LIST_SIZE =  10;
static const int POISON   = -13;
static const int START_VALUE = -1;

struct List 
{
    int* data;

    int* next; //ну вот и все, от массива структур одни проблемы
    int* prev;

    int head;
    int tail;

    int free;
};

#endif //_LIST_H_