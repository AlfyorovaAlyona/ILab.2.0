//
// Created by alena on 18.02.18.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef AKINATOR_AKI_H
#define AKINATOR_AKI_H

typedef struct Node
{
    struct Node* left;
    struct Node* right;
    char* value;
}Node;

Node* create_node_dynamic(char* value);
void add_left(Node* root, char* value);
void delete_subtree(Node* root);
void add_right(Node* root, char* value);

int isQuestion(Node* root);
void akinator(Node* root);

void dotTree(Node* root);
void print_dot(FILE* f, Node* root);

void print_node(Node* root);
void file_print(FILE* f, Node* root);


#endif //AKINATOR_AKI_H
