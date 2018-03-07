//
// Created by alena on 06.03.18.
//

#include <iostream>
#include <cassert>

#ifndef __NODE__
#define __NODE__

enum FLAG
{
    FUNC = 8,
    NUM = 9,
    VARS = 10
};

enum FUNC
{
    PLUS = 5,
    MINUS = 6,
    PROD = 7
};

enum VARS
{
    X_FLAG = 11,
    Y_FLAG = 12,
};

struct Node {
    struct Node *left;
    struct Node *right;
    int flag;
    int value;

    Node(int fl, int val); //constructor
    Node* add_left(int fl, int val);
    Node* add_right(int fl, int val);
    void PRINT();
    void print();
    void dot();
    void print_in_dot(FILE* f);
    ~Node(); //distructor
};
#include "node.cpp"
#endif //__NODE__







