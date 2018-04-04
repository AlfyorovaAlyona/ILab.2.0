//
// Created by alena on 25.03.18.
//

void Tex ::printpreambula(FILE *f)
{
    assert(f);
    if (f)
    {
        fprintf(f, "\\documentclass[12pt]{article} % тип документа\n"
                "\n"
                "% report, book\n"
                "\n"
                "%  Русский язык\n"
                "\n"
                "\\usepackage[T2A]{fontenc}\t\t\t% кодировка\n"
                "\\usepackage[utf8]{inputenc}\t\t\t% кодировка исходного текста\n"
                "\\usepackage[english,russian]{babel}\t% локализация и переносы\n"
                "\\usepackage{graphicx}\n"
                "\\usepackage{wrapfig}\n"
                "\\usepackage{floatrow}\n"
                "% Математика\n"
                "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools} \n"
                "\n"
                "\\usepackage[left=20mm, top=20mm, right=20mm, bottom=20mm]{geometry}\n"
                "\\usepackage{wasysym}\n"
                "\\newcommand{\\hm}[1]{#1\\nobreak\\discretionary{}{\\hbox{\\ensuremath{#1}}}{}}\n"
                "\n"
                "%Заговолок\n"
                "\\author{Алфёрова Алёна}\n"
                "\\title{Дифференциатор в \\LaTeX{}}\n"
                "\\date{\\today}\n"
                "\n"
                "\\begin{document}\n"
                "\\section*{Дифференциатор 2.0}\n");
    }
}

void Tex :: print_in_tex(FILE* f, Node* root)
{
    assert(root);
    assert(f);
    if (f)
    {
        fprintf(f,"\n");
        fprintf(f, "%s", " \\[ ");
        print_node_in_tex(f, root);
        fprintf(f, "%s\n", " \\] \\\\");
    }
    else
    {
        printf("file is not found\n");
    }
}


void Tex :: print_node_in_tex(FILE* f, Node* root)
{
    assert(root);
    assert(f);
    if (root && root->value != PART)
    {
        if (root->value == SIN || root->value == COS || root->value == LN)
            fprintf(f, "\\left(");

        if (root->left) {
            if (root->value == PLUS || root->value == MINUS || root->value == LN)
            {
                fprintf(f, "\\left(");
            }
            print_node_in_tex(f, root->left);
        }
        switch (root->flag) {
            case FUNC: {
                func_tex(f, root);
                break;
            }
            case VARS: {
                vars_tex(f, root);
                break;
            }
            case NUM: {
                num_tex(f, root);
                break;
            }
            default:
                printf("Wrong flag\n");
        }
        if (root->right)
        {
            print_node_in_tex(f, root->right);

            if(root->value == PLUS || root->value == MINUS || root->value == COS || root->value == LN || root->value == SIN)
            {
                fprintf(f, "\\right)");
            }
        }
    }

    if (root && root->value == PART)
    {
        fprintf(f, "\\frac{");
        if (root->left)
        {
            print_node_in_tex(f, root->left);
            fprintf(f, "}");
        }
        if (root->right)
        {
            fprintf(f, "{");
            print_node_in_tex(f, root->right);
            fprintf(f, "}");
        }
    }


}


void Tex :: func_tex(FILE* f, Node* root)
{
    assert(root);
    assert(f);
    switch(root->value)
    {
        case PLUS: {
            fprintf(f, " + ");
            break;
        }
        case MINUS: {
            fprintf(f, " - ");
            break;
        }
        case PROD: {
            fprintf(f, " \\cdot ");
            break;
        }
        case SIN:
        {
            fprintf(f, " \\sin ");
            break;
        }
        case COS:
        {
            fprintf(f, " \\cos ");
            break;
        }
        case LN:
        {
            fprintf(f, " \\ln ");
            break;
        }
        default:
            printf("Wrong func\n");
    }
}


void Tex :: vars_tex(FILE* f, Node* root)
{
    assert(root);
    assert(f);
    switch(root->value)
    {
        case X_FLAG:
            fprintf(f, " x ");
            break;
        case Y_FLAG:
            fprintf(f, " y ");
            break;
        default:
            printf("Wrong var\n");
    }
}


void Tex :: num_tex(FILE* f, Node* root)
{
    assert(root);
    assert(f);
    fprintf(f, "%d", root->value);
}


void Tex :: rule(FILE* f, Node* root)
{
    assert(root);
    assert(f);
    if (root)
    {
        if (root->flag == FUNC)
        {
            switch(root->value)
            {
                case PLUS:
                {
                    fprintf(f, "Как известно каждому, $ (f_1 + g_1)' = f_1' + g_1' \\Rightarrow  ");
                    if (root->left) {
                        fprintf(f, "g_1 = ");
                        print_node_in_tex(f, root->left);
                    }
                    if (root->right) {
                        fprintf(f, ", f_1 = ");
                        print_node_in_tex(f, root->right);
                    }
                    fprintf(f, "\\Rightarrow ");
                    fprintf(f, "(");
                    print_node_in_tex(f, root);
                    fprintf(f, ")' =  (");
                    if (root->left) {
                        print_node_in_tex(f, root->left);
                        fprintf(f, ")' + (");
                    }
                    if (root->right) {
                        print_node_in_tex(f, root->right);
                        fprintf(f, ")' \\Rightarrow $ \\\\ \n");
                    }
                    break;
                }
                case MINUS:
                {
                    fprintf(f, "Как известно всем, $ (f_2 - g_2)' = f_2' - g_2' \\Rightarrow  ");
                    if (root->left) {
                        fprintf(f, "f_2 = ");
                        print_node_in_tex(f, root->left);
                    }
                    if (root->right) {
                        fprintf(f, ", g_2 = ");
                        print_node_in_tex(f, root->right);
                    }
                    fprintf(f, " \\Rightarrow (");
                    print_node_in_tex(f, root);
                    fprintf(f, ")' =  (");
                    print_node_in_tex(f, root->left);
                    fprintf(f,")' - (");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")' \\Rightarrow $ \\\\ \n");
                    break;
                }
                case PROD:
                {
                    fprintf(f, "Немногие помнят, но $ (f_3 \\cdot g_3)' = f_3' g_3 + f_3 g_3' \\Rightarrow ");
                    if (root->left) {
                        fprintf(f, "f_3 = ");
                        print_node_in_tex(f, root->left);
                    }
                    if (root->right) {
                        fprintf(f, ", g_3 = ");
                        print_node_in_tex(f, root->right);
                    }
                    fprintf(f, "\\Rightarrow \\left(");
                    print_node_in_tex(f, root);
                    fprintf(f, "\\right)' =  (");
                    print_node_in_tex(f, root->left);
                    fprintf(f,")' (");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ") + (");
                    print_node_in_tex(f, root->left);
                    fprintf(f, ")  (");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")' \\Rightarrow $ \\\\ \n");
                    break;
                }
                case PART:
                {
                    fprintf(f, "Мало тех, кто поймёт, но $ \\left(\\frac{f_4}{g_4}\\right)' = \\frac{f_4'g_4 - f_4 g_4'}{g_4^2} "
                            "\\Rightarrow ");
                    if (root->left) {
                        fprintf(f, "f_4 = ");
                        print_node_in_tex(f, root->left);
                    }
                    if (root->right) {
                        fprintf(f, ",\\ g_4 = ");
                        print_node_in_tex(f, root->right);
                    }
                    fprintf(f, "\\Rightarrow \\left( ");
                    print_node_in_tex(f, root);
                    fprintf(f, "\\right)' =  \\frac{(");
                    print_node_in_tex(f, root->left);
                    fprintf(f,")' (");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ") - (");
                    print_node_in_tex(f, root->left);
                    fprintf(f, ")  (");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")'}{(");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")^2} \\Rightarrow $ \\\\ \n");
                    break;
                }
                case SIN:
                {
                    fprintf(f, "Знают все, что $ (\\sin f(x))' = f'(x) \\cdot \\cos f(x) \\Rightarrow");
                    fprintf(f, "(");
                    print_node_in_tex(f, root);
                    fprintf(f, ")' = ");
                    fprintf(f, "(");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")' \\cdot \\cos (");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ") \\Rightarrow $ \\\\ \n");
                    break;
                }
                case COS:
                {
                    fprintf(f, "Знают все, что $ (\\cos f(x))' = f'(x) \\cdot (-\\sin f(x)) \\Rightarrow");
                    fprintf(f, "(");
                    print_node_in_tex(f, root);
                    fprintf(f, ")' = ");
                    fprintf(f, "(");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")' \\cdot (-\\sin (");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")) \\Rightarrow $ \\\\ \n");
                    break;
                }
                case LN:
                {
                    fprintf(f, "Сосед сказал мне, что $ (\\ln f(x))' = f'(x) \\cdot \\frac{1}{f(x)} \\Rightarrow");
                    fprintf(f, "(");
                    print_node_in_tex(f, root);
                    fprintf(f, ")' = \\left(");
                    fprintf(f, "\\frac{(");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")'}{(");
                    print_node_in_tex(f, root->right);
                    fprintf(f, ")}\\right) \\Rightarrow $ \\\\ \n");
                    break;
                }
            }
        }
        if (root->flag == VARS)
        {
            switch (root->value)
            {
                case X_FLAG:
                {
                    fprintf(f, "Даже в учебнике по литературе написано $ x' = 1 \\Rightarrow");
                    fprintf(f, "(");
                    print_node_in_tex(f, root);
                    fprintf(f, ")' = 1 $ \\\\");
                    break;
                }
                case Y_FLAG:
                {
                    fprintf(f, "Если считать y константой, то $ y' = 1 \\Rightarrow");
                    fprintf(f, "(");
                    print_node_in_tex(f, root);
                    fprintf(f, ")' = 1 $ \\\\");
                    break;
                }
            }
        }
        if (root->flag == NUM)
        {
            fprintf(f, "Капитан очевидность говорит $ C' = 0 \\Rightarrow");
            fprintf(f, "(");
            print_node_in_tex(f, root);
            fprintf(f, ")' = 0 $ \\\\");
        }

    }
}













