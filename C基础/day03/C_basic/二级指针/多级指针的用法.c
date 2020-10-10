#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **getMem(int num)
{
    int i = 0;
    char **pp = (char **)malloc(num * sizeof(char*));
    if (pp == NULL)
    {
        return NULL; // 假设分配失败，则return，但是在return之前没有释放内存，则会产生内存泄漏。
    }
    for (i = 0; i < num; i++)
    {
        pp[i] = (char*)malloc(100);
        if (pp[i] == NULL)
        {
            return NULL;
        }
    }
    return pp;
}

int FreeMem(char **pp, int num)
{
    int i = 0;
    if (pp == NULL)
    {
        return -1;
    }
    for (i = 0; i < num; i++)
    {
        free(pp[i]);
    }
    free(pp);
    return 0;
}

// 方法2：
int getMem02(char ***pp, int num)
{
    int ret = 0;
    int i = 0;
    char **tmp = NULL;
    if (pp == NULL)
    {
        ret = -1;
        return ret;
    }
    tmp = (char**)malloc(num * sizeof(char*));
    if (tmp == NULL)
    {
        ret = -2;
        return ret;
    }
    for (i = 0; i < num; i++)
    {
        tmp[i] = (char*)malloc(100);
        if (tmp[i] == NULL)
        {
            ret = -3;
            return ret;
        }
    }
    *pp = tmp;
    return ret;
}

int FreeMem02(char ***pp, int num)
{
    int ret = 0;
    int i = 0;
    char **tmp = NULL;
    if (pp == NULL)
    {
        ret = -1;
        return ret;
    }
    tmp = *pp;
    for (i = 0; i < num; i++)
    {
        if (tmp[i] != NULL)
        {
            free(tmp[i]);
        }
    }
    free(tmp);
    *pp = NULL;
    return ret;
}
void main()
{
    int ret = 0, i = 0;
    int numArray = 10;
    char **pp = NULL;
    //pp = getMem(numArray); // 分配内存
    pp = getMem02(&pp, numArray); // 分配内存
    if (pp == NULL) // 分配内存失败
    {
        return;
    }

    //FreeMem(pp, numArray); // 释放内存
    FreeMem02(pp, numArray); // 释放内存

    system("pause");
}