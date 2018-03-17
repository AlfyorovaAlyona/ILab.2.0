
#include "node.h"
#include "differ.h"

int main()
{
    FILE* ftex;
    FILE* fout;
    FILE* fin;
    ftex = fopen("file.tex", "at");
    fout = fopen("root.txt", "wt");
    fin = fopen("diffroot.txt", "wt");

    Node* root = new Node(FUNC, PROD);
    Node* diffroot;

    root->add_left(FUNC , PLUS);
    root->add_right(FUNC , PROD);
    root->left->add_left(NUM ,3000);
    root->left->add_right(NUM ,9000);
    root->right->add_left(VARS , X_FLAG);
    root->right->add_right(VARS , X_FLAG);

    root->dot(fout);

    root->print_in_tex(ftex);

    Differentiator differ;
    diffroot = differ.Diff(root);

    fprintf(ftex, "Результат:");

    diffroot->dot(fin);
    diffroot->print_in_tex(ftex);

    fprintf(ftex, "\\end{document}");
    fclose(ftex);
    return 0;
}







