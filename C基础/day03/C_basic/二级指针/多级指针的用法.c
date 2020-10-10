#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **getMem(int num)
{
    int i = 0;
    char **pp = (char **)malloc(num * sizeof(char*));
    if (pp == NULL)
    {
        return NULL; // �������ʧ�ܣ���return��������return֮ǰû���ͷ��ڴ棬�������ڴ�й©��
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

// ����2��
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
    //pp = getMem(numArray); // �����ڴ�
    pp = getMem02(&pp, numArray); // �����ڴ�
    if (pp == NULL) // �����ڴ�ʧ��
    {
        return;
    }

    //FreeMem(pp, numArray); // �ͷ��ڴ�
    FreeMem02(pp, numArray); // �ͷ��ڴ�

    system("pause");
}