#include "tree.h"
#include <stdio.h>

const int N1 = 10;
const int N2 = 20;
int main() {
    int Roo, i;
    printf("Enter a root\n");
    /*system("espeak Enter");
    system("espeak a");
    system("espeak root");*/
    scanf("%d", &Roo);
    Node* root = create_node_dynamic(Roo);
    printf("CreateNodeDynamic: root = %d\n", root->value);
    Node* current1 = root;
    Node* current2 = root;

    for(i = 0; i < N1; i++)
    {
        add_left(root, i);
        root = root->left;
    }
    for(i = N1; i < N2; i++)
    {
        add_right(current1, i);
        current1 = current1->right;
    }

    print_node(current2);
    dotTree(current2);
    return 0;
}