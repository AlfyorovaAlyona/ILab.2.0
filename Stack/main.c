#include "stk.h"

int main()
{
    Stack stk;
    StackPush(&stk, 10);
    StackPush(&stk, 20);
    StackPush(&stk, 30);
    StackDump(&stk);
    return 0;
}