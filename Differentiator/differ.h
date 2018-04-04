//
// Created by alena on 06.03.18.
//

#ifndef __DIFFERENTIATOR__
#define __DIFFERENTIATOR__

struct Differentiator
{
    Node* Diff(Node* root, FILE* f);
    Node* FuncDiff(Node* root, FILE* f);
    Node* diffplus(Node* root, FILE* f);
    Node* diffmult(Node* root, FILE* f);
    Node* diffres(Node* root, FILE* f);
    Node* diffpart(Node* root, FILE* f);
    Node* diffsin(Node* root, FILE* f);
    Node* diffcos(Node* root, FILE* f);
    Node* diffln(Node* root, FILE* f);
    Node* VarsDiff(Node* root);
    Node* NumDiff(Node* root);
    Node* copy(Node* root);
};
#include "differ.cpp"
#endif //__DIFFERENTIATOR__