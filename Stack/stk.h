//
// Created by alena on 10.11.17.
//
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#ifndef STACK2_STK_H
#define STACK2_STK_H

#define SIZE 10

typedef struct Stack
{
    unsigned int count;
    int arr[SIZE];
} Stack, *pStack;

void StackPush(pStack stk, int value);
void StackDump(pStack stk);
bool StackOk(pStack stk);

#endif //STACK2_STK_H
