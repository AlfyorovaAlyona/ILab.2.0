//
// Created by alena on 11.11.17.
//

#include "list.h"
#include <stdio.h>
List* create_list()
{
    List* lst = (List*)calloc(1, sizeof(List));
    lst->first = lst->last = NULL;
    return lst;
}


void delete_list(List* lst)
{
    ListElement* tmp = lst->first;

    while(tmp)
    {
        ListElement* cur = tmp->next;
        free(tmp);
        tmp = cur;
    }
    free(lst);
}


void push_back(List* lst, int value)
{
    ListElement* tmp = (ListElement*)calloc(1, sizeof(ListElement));
    tmp->value = value;
    tmp->next = NULL;

    if(lst->last)
    {
        lst->last->next = tmp;
        lst->last = tmp;
    }
    else
    {
        lst->last = lst->first = tmp;
    }
}


int Find(List* lst, int value)
{
    ListElement* current = lst->first;

    while(current)
    {
        if(current->value == value)
            return 1;
        current = current->next;
    }
    return 0;
}


void print_list(List* lst)
{
    ListElement* current = lst->first;

    while(current)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void dumpList(List* lst)
{
    FILE* f;
    f = fopen("list-dot.txt", "wt");

    if(f != NULL)
    {
        fprintf(f, "%s\n", "digraph G {");
        fprintf(f, "%s\n", "rankdir=LR;\n"
                " node[color=\"red\",fontsize=14];\n"
                " edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n");
        ListElement* current = lst->first;
        fprintf(f, "%d", current->value);
        while(current->next)
        {
            fprintf(f, "->");
            current = current->next;
            fprintf(f, " %d ", current->value);
        }
        fprintf(f, ";\n");
        fprintf(f, "}");
    }
    else
    {
        printf("Not found\n");
    }

    system("dot list-dot.txt -Tjpg -O");
}
