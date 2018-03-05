#include <iostream>

enum FUNC
{
    PLUS = 5,
    MINUS = 6,
    PROD = 7
};


enum FLAG
{
    FUNC = 8,
    NUM = 9
};


struct Node
{
    struct Node* left;
    struct Node* right;
    int flag;
    int value;

    Node(int fl, int val)
    {
        flag = fl;
        value = val;
        left = nullptr;
        right = nullptr;
    }
    Node* add_left(int fl, int val)
    {
        left = new Node(fl, val);
    }
    Node* add_right(int fl, int val)
    {
        right = new Node(fl, val);
    }
    int Calc()
    {
        int res = 0;
        if (flag == FUNC)
        {
            if (value == PLUS)
            {
                res = left->Calc() + right->Calc();
            }
            else if (value == MINUS)
            {
                res = right->Calc() - left->Calc();
            }
            else if (value == PROD)
            {
                res = right->Calc() * left->Calc();
            }
        }
        else if (flag == NUM)
        {
            return value;
        }
        return res;
    }
    ~Node()
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

};


int main()
{
    Node* root;
    root = new Node(FUNC, PLUS);
    root->add_left(NUM, 100);
    root->add_right(NUM, 300);

    int res = root->Calc();

    printf("%d\n", res);

    return 0;
}













