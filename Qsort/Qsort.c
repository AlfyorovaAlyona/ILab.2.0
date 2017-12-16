//
// Created by alena on 09.12.17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_MAX 32

int cmp(void* a, void* b);
void Qsort(void* a, int n, int size, int(*cmp)(void*, void*));
int myStrlen(char* a);
int myStrcmp(char* a, char* b);
void Free(char*** a, int N);

int main()
{
    int N, i;
    scanf("%d", &N);
    char** a = (char**) malloc(N * sizeof(char*));
    for(i = 0; i < N; i++)
    {
        a[i] = (char*) malloc(STRING_MAX * sizeof(char));
        scanf("%s", a[i]);
    }

    Qsort(a, N, sizeof(char*), cmp);

    printf("\n");
    for(i = 0; i < N; i++)
    {
        printf("%s\n", a[i]);
    }
    Free(&a, N);
    return 0;
}


void Free(char*** a, int N)
{
    int i;
    for(i = 0; i < N; i++)
    {
        free((*a)[i]);
    }
    free(*a);
    *a = NULL;
}

int myStrlen(char* a)
{
    int i;
    while(a[i] != '\0')
    {
        i++;
    }
    return i;
}


int myStrcmp(char* a, char* b)
{
    int i;
    int lenA = myStrlen(a);
    int lenB = myStrlen(b);
    if(lenA >= lenB)
    {
        for(i = 0; i <= lenB; i++)
        {
            if(a[i] > b[i])
            {
                return 1;
            }
            else if(a[i] < b[i])
            {
                return -1;
            }
        }
    }
    else
    {
        for(i = 0; i <= lenA; i++)
        {
            if(a[i] > b[i])
            {
                return 1;
            }
            else if(a[i] < b[i])
            {
                return -1;
            }
        }
    }
    return 0;
}

int cmp(void* a, void* b)
{

    return myStrcmp(*(char**)a, *(char**)b);
}


void Qsort(void* a, int n, int size, int(*cmp)(void*, void*))
{
    if (n <= 1)
        return;
    void* main = a;   //int* main = &(a[0]);
    void* left = a;
    void* right = a + (n - 1) * size; //int* right = &(a[n - 1]);

    while (left != right)
    {
        if (main == left)
        {
            if (cmp(main, right) > 0)
            {
                void* tmp = (void*) malloc(size); //int tmp = *main;
                memcpy(tmp, main, size);
                memcpy(main, right, size); //*main = *right;
                memcpy(right, tmp, size); //*right = tmp;
                main = right;
                left = left + size;
                free(tmp);
            }
            else
            {
                right = right - size;
            }
        }

        else if (main == right)
        {
            if (cmp(left, main) > 0)
            {
                void* tmp = (void*) malloc(size); //int tmp = *main;
                memcpy(tmp, main, size);
                memcpy(main, left, size); //*main = *left;
                memcpy(left, tmp, size); //*left = tmp;
                main = left;
                right = right - size;
                free(tmp);
            }
            else
            {
                left = left + size;
            }
        }
    }
    Qsort(a, (left - a)/size, size, cmp);
    Qsort(main + size, ((a + (n - 1) * size) - right)/size, size, cmp);
}

