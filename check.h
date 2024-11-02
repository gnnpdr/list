#ifndef _CHECK_H_
#define _CHECK_H_

#include <stdlib.h>
#include <string.h>

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
static const int INPUT_FILE_SIZE = 5000;

struct List 
{
    int* data;

    int* next;
    int* prev;

    int* next_copy;

    int free;
};

#define FILE_CHECK(file)    do                                      \
                            {                                       \
                                if (file == nullptr)                \
                                {                                   \
                                    printf("file wasn't opened\n"); \
                                    return;                         \
                                }                                   \
                            }while(0);



Errors verificator (List* my_list);
Errors connection_check (List* my_list);
void   dump (List* my_list);
void graph (char* input_file, char* out_file) ;
void graph_dump (List* my_list);

#endif //_CHECK_H_