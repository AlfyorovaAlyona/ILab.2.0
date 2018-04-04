//
// Created by alena on 25.03.18.
//

#ifndef DIFFERENTIATOR_TEXOUTPUT_H
#define DIFFERENTIATOR_TEXOUTPUT_H

struct Tex
{
    void printpreambula(FILE* f);
    void print_in_tex(FILE* f, Node* root);
    void print_node_in_tex(FILE* f, Node* root);
    void func_tex(FILE* f, Node* root);
    void vars_tex(FILE* f, Node* root);
    void num_tex(FILE* f, Node* root);
    void rule(FILE* f, Node* root);
};
#include "TexOutput.cpp"
#endif //DIFFERENTIATOR_TEXOUTPUT_H
