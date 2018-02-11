//
// Created by alena on 05.12.17.
//

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

Node* create_node_dynamic(int value)
{
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    newNode->value = value;
    return newNode;
}


void add_left(Node* root, int value)
{
    assert(root);
    Node* left = create_node_dynamic(value);
    if (root->left)
    {
        delete_subtree(root->left);
    }
    root->left = left;
}


void add_right(Node* root, int value)
{
    assert(root);
    Node* right = create_node_dynamic(value);
    if (root->right)
    {
        delete_subtree(root->right);
    }
    else
    {
        root->right = right;
    }
}


void delete_subtree(Node* root)
{
    assert(root);
    if (root->left)
        delete_subtree(root->left);

    if (root->right)
        delete_subtree(root->right);
    free(root);
}


void print_node(Node* root)
{
    FILE* f;
    f = fopen("Input.txt", "w");
    if (f)
    {
        if (!root)
            return;
        fprintf(f, "%s", " ");
        fprintf(f, "%s", "(");
        fprintf(f, "%s", " ");
        fprintf(f, "%d", root->value);
        print_node(root->left);
        print_node(root->right);
        fprintf(f, "%s", " ");
        fprintf(f, "%s", ")");
        fclose(f);
    }
    else
    {
        printf("Not found");
    }
}


void dotTree(Node* root)
{
    FILE* f;
    f = fopen("tree-dot.txt", "wt");

    if(f != NULL)
    {
        fprintf(f, "%s\n", "digraph G {");
        fprintf(f, "%s\n", "node[color=\"red\",fontsize=14];\n"
                " edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n");
        print_dot(f, root);
        fprintf(f, "}");
    }
    else
    {
        printf("Not found\n");
    }
    fclose(f);
    //system("dot tree-dot.txt -Tjpg -O");
}

void print_dot(FILE* f, Node* root)
{
    fprintf(f, "%d\n", root->value);
    if(root->left != NULL)
    {
        fprintf(f,"%d%s%d\n", root->value, "->", root->left->value);
        print_dot(f, root->left);
    }

    if(root->right != NULL)
    {
        fprintf(f,"%d%s%d\n", root->value, "->", root->right->value);
        print_dot(f, root->right);
    }
}










