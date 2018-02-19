//
// Created by alena on 18.02.18.
//
#include "aki.h"
#include <stdio.h>
#include <stdlib.h>


Node* create_node_dynamic(char* value)
{
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    newNode->value = value;
    return newNode;
}


void add_left(Node* root, char* value)
{
    assert(root);
    Node* left = create_node_dynamic(value);
    if (root->left)
    {
        delete_subtree(root->left);
    }
    root->left = left;
}


void add_right(Node* root, char* value)
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
    fprintf(f, "%s\n", root->value);
    if(root->left != NULL)
    {
        fprintf(f,"%s%s%s\n", root->value, "->", root->left->value);
        print_dot(f, root->left);
    }

    if(root->right != NULL)
    {
        fprintf(f,"%s%s%s\n", root->value, "->", root->right->value);
        print_dot(f, root->right);
    }
}


void print_node(Node* root)
{
    FILE* f;
    f = fopen("Input.txt", "w");
    if (f)
    {
        file_print(f, root);
        fclose(f);
    }
    else
    {
        printf("Not found");
    }
    
}


void file_print(FILE* f, Node* root)
{
	if(!root)
		return;
	fprintf(f, "%s", " ");
    fprintf(f, "%s", "(");
    fprintf(f, "%s", " ");
    fprintf(f, "%s", root->value);
    file_print(f, root->left);
    file_print(f, root->right);
    fprintf(f, "%s", " ");
    fprintf(f, "%s", ")");
	
}











