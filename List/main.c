#include "list.h"
#include <stdio.h>

const int N = 3;

int main()
{
    List* lst = create_list();

    int i;
    for(i = 0; i < N; i++)
    {
        int tmp = 0;
        scanf("%d", &tmp);
        push_back(lst, tmp);
    }

    printf("PrintList: ");
    print_list(lst);

    dumpList(lst);

    if (Find(lst, 6))
    {
        printf("Find: There is an element 6\n");
    }
    else
    {
        printf("Find: There is no 6\n");
    }

    delete_list(lst);

    return 0;
}

