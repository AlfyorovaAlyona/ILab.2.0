
bool _OPTIMIZATION_ = true;
#include "node.h"
#include "TexOutput.h"
#include "differ.h"
#include "PGD.h"

int main()
{
    grammar Gramm;
    Gramm.str = "(30-x*x*x)/((40-x)*(10/x))";
    Node* root = Gramm.GetG();

    if (root)
    {
        FILE* ftex = fopen("file.tex", "at");
        FILE* fout = fopen("root.txt", "wt");
        FILE* fin = fopen("diffroot.txt", "wt");
        FILE* f = fopen("baddiffroot.txt", "wt");

        Tex texer;
        texer.printpreambula(ftex);
        Node* diffroot;
        root->dot(fout);

        fprintf(ftex, "Функция, которую необходимо продифференцировать: \\\\");
        texer.print_in_tex(ftex, root);
        texer.rule(ftex, root);

        Differentiator differ;
        diffroot = differ.Diff(root, ftex);

        diffroot->dot(f);

        fprintf(ftex, "Итого: \\\\");
        texer.print_in_tex(ftex, diffroot);

        while (_OPTIMIZATION_) {
            diffroot->opt_const();
            diffroot->opt_simple();
        }

        fprintf(ftex, "Итого, путём несложных математических преобразований: ");
        texer.print_in_tex(ftex, diffroot);

        diffroot->dot(fin);

        fprintf(ftex, "\\end{document}");
        fclose(ftex);
    }
    else
    {
        printf("Error FUNC in str\n");
    }
    return 0;
}








