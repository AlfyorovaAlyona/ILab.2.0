//
// Created by alena on 06.03.18.
//

#include <iostream>
#include <cassert>

#ifndef __NODE__
#define __NODE__

enum FUNC
{
    PLUS = 5,
    MINUS = 6,
    PROD = 7
};

enum FLAG
{
    FUNC = 8,
    NUM = 9,
    VARS = 10
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

    Node(int fl, int val);
    Node *add_left(int fl, int val);
    Node *add_right(int fl, int val) ;
    ~Node();
};

Node :: Node(int fl, int val)
{
    flag = fl;
    value = val;
    left = nullptr;
    right = nullptr;
}

Node* Node :: add_left(int fl, int val)
{
    left = new Node(fl, val);
}

Node* Node :: add_right(int fl, int val)
{
    right = new Node(fl, val);
}

Node :: ~Node()
{
    if (left)
    {
        delete left;
        left = nullptr;
    }
    if (right)
    {
        delete right;
        right = nullptr;
    }
}

#endif //__NODE__








