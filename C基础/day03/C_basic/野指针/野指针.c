#include <stdio.h>
#include <stdlib.h>

void main01(void)
{
    char buf[100];
    int a = 10;
    int *p; // ����4���ֽڵ��ڴ�
    p = &a; // cpuִ�еĴ��룬���ڴ�����

    *p = 20; // ����޸�a��ֵ
    {
        char *p2 = NULL; // ����4���ֽڵ��ڴ� ս��Ҳ����ʱȥ
        p2 = (char *)malloc(100);
        if (p2 != NULL)
        {
            free(p2);// �ڴ�й©��ֻ���ͷŵ���p2ָ����ڴ�ռ䣬��p2����û��Ӱ�죬p2����NULL
        }
    }
    system("pause");
    return;
}

char *getMem(int count)
{
    char *tmp = NULL;
    tmp = (char*)malloc(count * sizeof(char));
    return tmp;
}

int FreeMen(char *p)
{
    if (p == NULL)
    {
        return -1;
    }
    if (p != NULL)
    {
        free(p);
        p = NULL;
    }
    return 0;
}

void main()
{
    char *p = NULL;
    p = getMem(10);


    FreeMen(p);
    FreeMen(p);
}