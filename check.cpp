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

    FILE* log_file;
    log_file = fopen("log_file.txt", "a");  //это же так делается? Хочется, чтобы выходной файл был с битами
    FILE_CHECK(log_file)

    fprintf(log_file, "------------------------------------------------------------------------------------------------\n");

    fprintf(log_file, "IND\n");
    for (int i = 0; i < LIST_SIZE; i++)
        fprintf(log_file, "%d ", i);

    fprintf(log_file, "\n");

    fprintf(log_file, "DATA\n");
    for (int i = 0; i < LIST_SIZE; i++)
        fprintf(log_file, "%d ", data[i]);

    fprintf(log_file, "\n");
    fprintf(log_file, "NEXT\n");
    for (int i = 0; i < LIST_SIZE; i++)
        fprintf(log_file, "%d ", next[i]);

    fprintf(log_file, "\n");
    fprintf(log_file, "PREV\n");
    for (int i = 0; i < LIST_SIZE; i++)
        fprintf(log_file, "%d ", prev[i]);

    fprintf(log_file, "\n");

    fclose(log_file);
}

void graph_dump (List* my_list)
{   
    int* data = my_list->data;
    int* next = my_list->next;
    int* prev = my_list->prev;

    int* next_copy = my_list->next_copy;

    static int enter_cnt = 0;
    char input_file_name[80] = {};

    if (enter_cnt == 0)
    {
        printf("enter name of input dot file (please)\n");
        scanf("%s", input_file_name);
    }

    sprintf(input_file_name, "%d.dot", enter_cnt);

    char output_file_name[80] = {};
    sprintf(output_file_name, "%d.png", enter_cnt);


    char input_file_data[INPUT_FILE_SIZE] = {};

    sprintf(input_file_data, "digraph G\n{\n\trankdir=LR;\n \
    \tnode [shape = Mrecord; fillcolor = \"#9FDFDA\";];");

    for (int i = 0; i < LIST_SIZE; i++)
        sprintf(input_file_data, "\tnode%d [style = filled; label = \"node = %d  | data = %d \
                                | next = %d | prev = %d\"];\n", i, i, data[i], next[i], prev[i]);

    sprintf(input_file_data, "\tnode_free [fillcolor = \"#16CABD\"; label = \"free = %d\"];\n",\
                               my_list->free);

    for (int i = 0; i < LIST_SIZE - 1; i++)
        sprintf(input_file_data, "\tnode%d -> node%d [weight = bold; color = white;];\n",\
        i, i + 1);
    
    for (int i = 0; i < LIST_SIZE; i++)
    {
        if (next_copy[i] != next[i])
            sprintf(input_file_data, "\tnode%d -> node%d [weight = 0.15; color = \"#1D638B\";\
                                       constraint = false;];\n",next_copy[i], next[i]);
    }

    sprintf(input_file_data, "\tnode_free -> node%d [weight = 0.15; color = \"%0B3D59\"; \
                               constraint = false;];\n}", my_list->free);

    FILE* input_file;
    input_file = fopen(input_file_name, "w");

    fwrite(input_file_data, sizeof(char), INPUT_FILE_SIZE, input_file);

    graph(input_file_name, output_file_name);

    enter_cnt++;

    fclose(input_file);
}

void graph (char* input_file, char* out_file)   //у меня не получилось разложить по папкам. отказано в доступе и разрешения для всех пользователей не меняются
{
    char cmd[80] = {};
    sprintf(cmd, "dot -Tpng %s -o %s", input_file, out_file);
    system(cmd);
}
