#include "tree.h"
#include <stdio.h>


int main() {
    int Roo, l, r;

    /*system("espeak Enter");
    system("espeak a");
    system("espeak root");*/

    scanf("%d", &Roo);
    Node* root = create_node_dynamic(Roo);
    Node* cur = root;
    for(int i = 1; i < 10; i++)
    {
        add_right(root, i);
        add_left(root, 10*i);
        root = root->right;
    }
    print_node(cur);
    dotTree(cur);
    return 0;
}