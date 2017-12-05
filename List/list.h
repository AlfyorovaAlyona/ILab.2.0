//
// Created by alena on 08.11.17.
//
#include <stdlib.h>

#pragma once

typedef struct list_element
{
    int value;
    struct list_element *next;
} ListElement;


typedef struct List
{
    ListElement* first;
    ListElement* last;
} List;

List* create_list();
int Find(List* lst, int value);
void print_list(List* lst);
void push_back(List*, int value);
void delete_list(List* lst);
void dumpList(List* lst);
