#include "node.h"
#include "differ.h"

int main()
{
    FILE* f;
    f = fopen("file.tex", "at");

    Node* root = new Node(FUNC, PLUS);
    Node* diffroot;

    root->add_left(FUNC, PROD);
    root->add_right(FUNC, MINUS);
    root->left->add_left(VARS,X_FLAG);
    root->left->add_right(VARS,X_FLAG);
    root->right->add_left(FUNC , PROD);
    root->right->add_right(FUNC , PLUS);
    root->right->left->add_left(VARS, X_FLAG);
    root->right->left->add_right(VARS, X_FLAG);
    root->right->right->add_right(VARS, X_FLAG);
    root->right->right->add_left(VARS, X_FLAG);

    root->print_in_tex(f);

    Differentiator differ;
    diffroot = differ.Diff(root);

    fprintf(f, "Результат:");

    diffroot->dot();
    diffroot->print_in_tex(f);

    fprintf(f, "\\end{document}");
    fclose(f);
    return 0;
}







