#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getMem2(char ***p3)
{
    int i = 0;
    //*p3 = "bbb";
    char **tmp = (char**)malloc(10 * sizeof(char**));
    if (tmp == NULL)
    {
        return -1;
    }
    memset(tmp, 0, 10 * sizeof(char*));
    for (i = 0; i < 3; i++)
    {
        tmp[i] = (char*)malloc(100);
    }
    *p3 = tmp;
    return 0;
}

void main06()
{
    char **p2 = NULL;
    char ***p3 = NULL;
    // ֱ���޸�p2��ֵ
    p2 = 1;
    p2 = 2;
    printf("p2: %d\n", p2);

    p3 = &p2;
    *p3 = "aaa";// p2ȡ��ַ����p3 ͨ��*p3(p2�ĵ�ַ)ȥ��ӵ��޸���p2��ֵ
    printf("p2: %s\n", p2);

    getMem2(&p2);
    printf("p2: %s\n", p2);

    system("pause");
}

int getMem7(char ********p)
{
    *p = "aaa";
}

void main11()
{
    char *******p7 = NULL; // p7����4���ֽ�
    p7 = 1;
    p7 = 3;

    {
        char ********p8 = NULL;
        p8 = &p7;
        *p8 = "ccc";
        printf("p7: %s\n", p7);
    }

    getMem7(&p7);
    printf("p7: %s\n", p7);
    system("pause");
}