//
// Created by alena on 06.03.18.
//

#include <iostream>
#include <cassert>
#include "node.h"

#ifndef __DIFFERENTIATOR__
#define __DIFFERENTIATOR__

struct Differentiator
{
    Node* Diff(Node* root);
    Node* FuncDiff(Node* root);
    Node* diffplus(Node* root);
    Node* diffmult(Node* root);
    Node* diffres(Node* root);
    Node* VarsDiff(Node* root);
    Node* NumDiff(Node* root);
};


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
        tmp->right = root->right;
    }
    if (root->right)
    {
        diffprod->add_right(FUNC, PROD);
        Node* tmp = diffprod->right;
        tmp->left = Diff(root->right);
        tmp->right = root->left;
    }
    return diffprod;
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

#endif //__DIFFERENTIATOR__