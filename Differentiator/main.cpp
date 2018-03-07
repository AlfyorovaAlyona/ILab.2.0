#include "node.h"
#include "differ.h"

int main()
{
    Node* root = new Node(FUNC, PROD);
    Node* diffroot;

    root->add_left(VARS, X_FLAG);
    root->add_right(VARS, Y_FLAG);

    root->dot();

    Differentiator differ;
    diffroot = differ.Diff(root);

    diffroot->dot();

    return 0;
}







