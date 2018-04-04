//
// Created by alena on 04.04.18.
//

#ifndef DIFFERENTIATOR_PGD_H
#define DIFFERENTIATOR_PGD_H

struct grammar
{
    const char* str;
    int p;

    Node* GetG();
    Node* GetE();
    Node* GetT();
    Node* GetP();
    Node* GetN();
};

#include "PGD.cpp"
#endif //DIFFERENTIATOR_PGD_H
