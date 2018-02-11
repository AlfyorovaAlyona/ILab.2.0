//
// Created by alena on 04.12.17.
//

#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    struct Node* left;
    struct Node* right;
    int value;
}Node;

Node* create_node_dynamic(int value);
void add_left(Node* root, int value);
void delete_subtree(Node* root);
void print_node(Node* root);
void add_right(Node* root, int value);
void dotTree(Node* root);
void print_dot(FILE* f, Node* root);