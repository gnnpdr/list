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
    char* input_file_name = (char*)calloc(80, sizeof(char));
    char output_file_name[80] = {};

    if (enter_cnt == 0)
    {
        printf("enter name of input dot file (please)\n");
        scanf("%s", input_file_name);
    }

    strcpy(output_file_name, input_file_name);
    sprintf(input_file_name, "%s%d.dot", input_file_name, enter_cnt);
    
    sprintf(output_file_name, "%s%d.png", output_file_name, enter_cnt);


    char input_file_data[INPUT_FILE_SIZE] = {};

    sprintf(input_file_data, "%sdigraph G\n{\n\trankdir=LR;\n\tnode [shape = Mrecord; fillcolor = \"#9FDFDA\";];\n",\
     input_file_data);

    for (int i = 0; i < LIST_SIZE; i++)
        sprintf(input_file_data, "%s\tnode%d [style = filled; label = \"node = %d  | data = %d | next = %d | prev = %d\"];\n",\
         input_file_data, i, i, data[i], next[i], prev[i]);

    sprintf(input_file_data, "%s\n", input_file_data);

    sprintf(input_file_data, "%s\tnode_free [fillcolor = \"#16CABD\"; label = \"free = %d\"];\n\n",\
                               input_file_data, my_list->free);

    for (int i = 0; i < LIST_SIZE - 1; i++)
        sprintf(input_file_data, "%s\tnode%d -> node%d [weight = bold; color = white;];\n",\
        input_file_data, i, i + 1);
    
    sprintf(input_file_data, "%s\n", input_file_data);

    for (int i = 0; i < LIST_SIZE; i++)
    {
        if (next_copy[i] != next[i])
            sprintf(input_file_data, "%s\tnode%d -> node%d [weight = 0.15; color = \"#1D638B\"; constraint = false;];\n",\
             input_file_data, next_copy[i], next[i]);
    }

    sprintf(input_file_data, "%s\n", input_file_data);

    sprintf(input_file_data, "%s\tnode_free -> node%d [weight = 0.15; color = \"#16476E\"; constraint = false;];\n\n}",\
     input_file_data, my_list->free);

    printf("NAME\n\n%s\n\n", input_file_name);
    printf("%s\n\n\n---------------------------------------------------\n", input_file_data);

    FILE* input_file;
    input_file = fopen(input_file_name, "w");

    fwrite(input_file_data, sizeof(char), INPUT_FILE_SIZE, input_file);
    fclose(input_file);

    graph(input_file_name, output_file_name);

    enter_cnt++;

    free(input_file_name);
}

void graph (char* input_file_name, char* out_file_name)   //у меня не получилось разложить по папкам. отказано в доступе и разрешения для всех пользователей не меняются
{
    char cmd[80] = {};
    sprintf(cmd, "dot %s -Tpng -o %s", input_file_name, out_file_name);
    system(cmd);
}
