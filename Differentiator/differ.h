//
// Created by alena on 06.03.18.
//

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
    Node* copy(Node* root);
};
#include "differ.cpp"
#endif //__DIFFERENTIATOR__