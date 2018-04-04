//
// Created by alena on 06.03.18.
//

Node* Differentiator :: Diff(Node* root, FILE* f)
{
    assert(root);
    assert(f);
    Node* diffroot = NULL;
    switch(root->flag)
    {
        case FUNC:
            diffroot = FuncDiff(root,f);
            break;
        case VARS:
            diffroot = VarsDiff(root);
            break;
        case NUM:
            diffroot = NumDiff(root);
            break;
        default:
            printf("Error flag");
    }
    return diffroot;
}


Node* Differentiator :: FuncDiff(Node* root, FILE* f)
{
    assert(root);
    assert(f);
    Node* difun = NULL;
    switch(root->value)
    {
        case PLUS: {
            difun = diffplus(root, f);
            break;
        }

        case MINUS: {
            difun = diffres(root, f);
            break;
        }

        case PROD: {
            difun = diffmult(root, f);
            break;
        }

        case PART: {
            difun = diffpart(root, f);
            break;
        }

        case SIN:
        {
            difun = diffsin(root, f);
            break;
        }

        case COS:
        {
            difun = diffcos(root, f);
            break;
        }

        case LN:
        {
            difun = diffln(root, f);
            break;
        }

        default:
            printf("Error function\n");
    }
    return difun;
}


Node* Differentiator :: diffplus(Node* root, FILE* f)
{
    assert(root);
    assert(f);
    Tex texer;
    Node* diffsum = new Node(FUNC, PLUS);
    if (root->left)
    {
        texer.rule(f, root->left);
        fprintf(f, "Нетрудно понять, что производная $g_1 =");
        texer.print_node_in_tex(f, root->left);
        fprintf(f, ":$ \\\\");
        diffsum->left = Diff(root->left, f);
        fprintf(f, "\\[ g_1' = ");
        texer.print_node_in_tex(f, diffsum->left);
        fprintf(f, " \\]");
    }
    if (root->right)
    {
        texer.rule(f, root->right);
        fprintf(f, "Тогда производная $f_1 =");
        texer.print_node_in_tex(f, root->right);
        fprintf(f, ":$ \\\\");
        diffsum->right = Diff(root->right, f);
        fprintf(f, "\\[ f_1' = ");
        texer.print_node_in_tex(f, diffsum->right);
        fprintf(f, " \\]");
    }
    fprintf(f, "Равна сумме: ");
    texer.print_in_tex(f, diffsum);
    return diffsum;
}


Node* Differentiator :: diffres(Node* root, FILE* f)
{
    assert(root);
    assert(f);
    Tex texer;
    Node* diffmin = new Node(FUNC, MINUS);
    if (root->left)
    {
        texer.rule(f, root->left);
        fprintf(f, "И производная $ f_2 = ");
        texer.print_node_in_tex(f, root->left);
        fprintf(f, ":$ \\\\");
        diffmin->left = Diff(root->left, f);
        fprintf(f, "\\[ f_2' = ");
        texer.print_node_in_tex(f, diffmin->left);
        fprintf(f, " \\]");
    }
    if (root->right)
    {
        texer.rule(f, root->right);
        fprintf(f, "И производная $ g_2 = ");
        texer.print_node_in_tex(f, root->right);
        fprintf(f, ":$ \\\\");
        diffmin->right = Diff(root->right, f);
        fprintf(f, "\\[ g_2' = ");
        texer.print_node_in_tex(f, diffmin->right);
        fprintf(f, " \\]");
    }
    fprintf(f, "Промежуточный результат разности: ");
    texer.print_in_tex(f, diffmin);
    return diffmin;
}


Node* Differentiator :: diffmult(Node* root, FILE* f)
{
    assert(root);
    assert(f);
    Tex texer;
    Node* diffprod = new Node(FUNC, PLUS);
    if (root->left && root->right)
    {
        texer.rule(f, root->left);
        fprintf(f, "Следовательно, зная производную $f_3 =");
        texer.print_node_in_tex(f, root->left);
        fprintf(f, "$ получаем:  \\\\");
        diffprod->add_left(FUNC, PROD);
        Node* tmp = diffprod->left;
        tmp->left = Diff(root->left, f);
        tmp->right = copy(root->right);
        fprintf(f, "\\[ f_3' g_3 = ");
        texer.print_node_in_tex(f,diffprod->left);
        fprintf(f, "\\]");

    }
    if (root->right && root->left)
    {
        texer.rule(f, root->right);
        fprintf(f, "Учитывая это, считаем производную $g_3 =");
        texer.print_node_in_tex(f, root->right);
        fprintf(f, ":$ \\\\");
        diffprod->add_right(FUNC, PROD);
        Node* tmp = diffprod->right;
        tmp->left = Diff(root->right, f);
        tmp->right = copy(root->left);
        fprintf(f, "\\[ f_3 g_3' = ");
        texer.print_node_in_tex(f, diffprod->right);
        fprintf(f, "\\]");
    }
    fprintf(f, "Совершенно элементарно выражаем: ");
    texer.print_in_tex(f, diffprod);
    return diffprod;
}


Node* Differentiator :: diffpart(Node *root, FILE* f)
{
    assert(root);
    assert(f);
    Tex texer;
    Node* diffpart = new Node(FUNC, PART);
    if (root->left && root->right)
    {
        texer.rule(f, root->left);
        fprintf(f, "Мы имеет всё, чтобы посчитать производную $f_4' g_4 =");
        texer.print_node_in_tex(f, root->left);
        fprintf(f, "' \\cdot");
        texer.print_node_in_tex(f, root->right);
        fprintf(f, "$: \\\\");
        diffpart->add_left(FUNC, MINUS);
        diffpart->left->add_left(FUNC,PROD);
        diffpart->left->add_right(FUNC, PROD);
        Node* tmp = diffpart->left;
        tmp->left->left = Diff(root->left, f);
        tmp->left->right = copy(root->right);
        tmp->right->left = copy(root->left);
        fprintf(f, "\\[ f_4' g_4 = ");
        texer.print_node_in_tex(f, diffpart->left->left);
        fprintf(f, "\\]");

        texer.rule(f, root->right);
        fprintf(f, "Не составит труда посчитать производную $f_4 g_4' =");
        texer.print_node_in_tex(f, root->right);
        fprintf(f, "' \\cdot");
        texer.print_node_in_tex(f, root->left);
        fprintf(f, "$: \\\\");
        tmp->right->right = Diff(root->right, f);
        diffpart->add_right(FUNC, PROD);
        diffpart->right->left = copy(root->right);
        diffpart->right->right = copy(root->right);
        fprintf(f, "\\[ f_4 g_4' = ");
        texer.print_node_in_tex(f, diffpart->left->right);
        fprintf(f, "\\]");
    }
    texer.print_in_tex(f, diffpart);
    return diffpart;
}


Node* Differentiator :: diffsin(Node *root, FILE* f)
{
    assert(root);
    assert(f);
    Tex texer;
    Node* diffsin = new Node(FUNC, PROD);
    if (root->right)
    {
        texer.rule(f, root->right);
        fprintf(f, "Это знал Беклемишев с рождения, а ты не знаешь до сих пор, производная $ f(x) = ");
        texer.print_node_in_tex(f, root->right);
        fprintf(f, "$: \\\\");
        diffsin->add_right(FUNC, COS);
        diffsin->right->right = copy(root->right);
        diffsin->right->left = NULL;
    }
    fprintf(f, "Выражается, \\[ f'(x) = ");
    diffsin->left = Diff(root->right, f);
    texer.print_node_in_tex(f, diffsin->left);
    fprintf(f, "\\]");

    texer.print_in_tex(f, diffsin);

    return diffsin;
}


Node* Differentiator :: diffcos(Node* root, FILE* f)
{
    assert(root);
    assert(f);
    Tex texer;
    Node* diffcos = new Node(FUNC, PROD);
    if (root->right)
    {
        texer.rule(f, root->right);
        fprintf(f, "Подойди к любому дворнику на Физтехе, и он ответит, что производная $ f(x) = ");
        texer.print_node_in_tex(f, root->right);
        fprintf(f, "$ это: \\\\");
        diffcos->add_right(FUNC, PROD);
        diffcos->right->add_right(FUNC, SIN);
        diffcos->right->right->right = copy(root->right);
        diffcos->right->right->left = NULL;
        diffcos->right->add_left(NUM, -1);

        fprintf(f, "Так, \\[ f'(x) = ");
        diffcos->left = Diff(root->right, f);
        texer.print_node_in_tex(f,diffcos->left);
        fprintf(f, "\\]");

        texer.print_in_tex(f, diffcos);
    }
    return diffcos;
}


Node* Differentiator :: diffln(Node* root, FILE* f)
{
    assert(f);
    assert(root);
    Tex texer;
    Node* diffln = new Node(FUNC, PROD);
    if (root->right)
    {
        texer.rule(f, root->right);
        fprintf(f, "Очевидно, что производная $ f(x) = ");
        texer.print_node_in_tex(f, root->right);
        fprintf(f, "$ это: \\\\");
        diffln->add_right(FUNC, PART);
        diffln->right->right = copy(root->right);
        diffln->right->add_left(NUM, 1);

        fprintf(f, "В общем, \\[ f'(x) = ");
        diffln->left = Diff(root->right, f);
        texer.print_node_in_tex(f, diffln->left);
        fprintf(f, "\\]");

        texer.print_in_tex(f, diffln);
    }
    return diffln;
}


Node* Differentiator :: copy(Node* root)
{
    assert(root);
    Node* copy_root = new Node(root->flag, root->value);
    if (root->right)
    {
        copy_root->right = copy(root->right);
    }
    if (root->left)
    {
        copy_root->left = copy(root->left);
    }
    return copy_root;
}


Node* Differentiator :: VarsDiff(Node* root)
{
    assert(root);
    Node* difvar = NULL;
    switch (root->value)
    {
        case X_FLAG: {
            difvar = new Node(NUM, 1);
            break;
        }
        case Y_FLAG: {
            difvar = new Node(NUM, 1);
            break;
        }
        default:
            printf("Error var\n");
    }
    return difvar;
}


Node* Differentiator :: NumDiff(Node* root)
{
    assert(root);
    Node* difnum = new Node(NUM, 0);
    return difnum;
}
