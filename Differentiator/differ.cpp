//
// Created by alena on 06.03.18.
//

Node* Differentiator :: Diff(Node* root)
{
    assert(root);
    Node* diffroot = nullptr;
    switch(root->flag)
    {
        case FUNC:
            diffroot = FuncDiff(root);
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


Node* Differentiator :: FuncDiff(Node* root)
{
    Node* difun = nullptr;
    switch(root->value)
    {
        case PLUS:
            difun = diffplus(root);
            break;

        case MINUS:
            difun = diffres(root);
            break;

        case PROD:
            difun = diffmult(root);
            break;

        default:
            printf("Error function\n");
    }
    return difun;
}


Node* Differentiator :: diffplus(Node* root)
{
    Node* diffsum = new Node(FUNC, PLUS);
    if (root->left)
    {
        diffsum->left = Diff(root->left);
    }
    if (root->right)
    {
        diffsum->right = Diff(root->right);
    }
    return diffsum;
}


Node* Differentiator :: diffres(Node* root)
{
    Node* diffmin = new Node(FUNC, MINUS);
    if (root->left)
    {
        diffmin->left = Diff(root->left);
    }
    if (root->right)
    {
        diffmin->right = Diff(root->right);
    }
    return diffmin;
}


Node* Differentiator :: diffmult(Node* root)
{
    Node* diffprod = new Node(FUNC, PLUS);
    if (root->left)
    {
        diffprod->add_left(FUNC, PROD);
        Node* tmp = diffprod->left;
        tmp->left = Diff(root->left);
        tmp->right = copy(root->right);
    }
    if (root->right)
    {
        diffprod->add_right(FUNC, PROD);
        Node* tmp = diffprod->right;
        tmp->left = Diff(root->right);
        tmp->right = copy(root->left);
    }
    return diffprod;
}


Node* Differentiator :: copy(Node* root)
{
    Node* copy_root = new Node(root->flag, root->value);
    copy_root = root;
    return copy_root;
}


Node* Differentiator :: VarsDiff(Node* root)
{
    Node* difvar = nullptr;
    switch(root->value)
    {
        case X_FLAG:
            difvar = new Node(NUM, 1);
            break;
        case Y_FLAG:
            difvar = new Node(NUM, 1);
            break;
        default:
            printf("Wrong var\n");
    }
    return difvar;
}


Node* Differentiator :: NumDiff(Node* root)
{
    Node* difnum = new Node(NUM, 0);
    return difnum;
}
