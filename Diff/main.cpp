#include "node.h"
#include "differ.h"

int main()
{
    Node* root = new Node(FUNC, PLUS);
    Node* diffroot;

    root->add_left(VARS, X_FLAG);
    root->add_right(VARS, X_FLAG);

    Differentiator differ;
    diffroot = differ.Diff(root);

    return 0;
}







