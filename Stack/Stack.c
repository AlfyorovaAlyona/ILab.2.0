//
// Created by alena on 10.11.17.
//

#include "stk.h"

#define NoCon
#ifdef NoCon

#define MEOW(Stack) printf("%s &Stack = 0x[%p] %s from file %s (%d)  ", Stack, stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);
#define Print(vav) { printf(#vav); }
#else
#define MEOW(wtf) ;
#endif

void StackPush(pStack stk, int value)
{
    assert(stk);
    assert(stk->count <= SIZE - 1);
    stk->arr[stk->count++] = value;
    assert(stk->count <= SIZE);
}

void StackDump(pStack stk)
{
    MEOW("Stack");
    Print("stk" );
    if (StackOk(stk))
    {
        printf("(OK)\n");
    }
    else
    {
        printf("(ERROR!)\n");
    }
    printf("{\n");
    printf("\tmaxCount = %d\n", SIZE);
    printf("\tcount = %d\n", stk->count);
    printf("\tarr0x[%p]\n", stk->arr);
    for (int i = 0; i <= stk->count - 1; i++)
    {
        printf("\t*[%d] = %d\n", i, stk->arr[i]);
    }
    for(int i = stk->count; i < SIZE; i++)
    {
        printf("\t[%d] = %d //POISON\n", i, stk->arr[i]);
    }

    printf("}\n");
}

bool StackOk(pStack stk)
{
    if(!stk)
        return false;
    return stk->arr && SIZE > 0 && stk->count >=0 && SIZE >= stk->count || !stk->arr && !SIZE && !stk->count;
}