//
// Created by alena on 05.12.17.
//

#include "tree.h"
#include <stdio.h>

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
    if(!root)
        return;
    printf(" ");
    printf("(");
    printf(" ");
    printf("%d", root->value);
    print_node(root->left);
    print_node(root->right);
    printf(" ");
    printf(")");
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
        fprintf(f, "%d%s\n", root->value, "[style=bold, shape = rectangle ,style=filled];");
        fprintf(f, "%d", root->value);
        Node* current = root;
        while(root->left)
        {
            fprintf(f, "->");
            root = root->left;
            fprintf(f, " %d ", root->value);
        }
        fprintf(f, "\n");
        fprintf(f, "%d", current->value);

        while(current->right)
        {
            fprintf(f, "->");
            current = current->right;
            fprintf(f, " %d ", current->value);
        }
        fprintf(f, ";\n");
        fprintf(f, "}");
    }
    else
    {
        printf("Not found\n");
    }

    //system("dot tree-dot.txt -Tjpg -O");
}
