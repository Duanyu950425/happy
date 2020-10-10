#include <stdio.h>
#include <stdlib.h>

void main01(void)
{
    char buf[100];
    int a = 10;
    int *p; // 分配4个字节的内存
    p = &a; // cpu执行的代码，放在代码区

    *p = 20; // 间接修改a的值
    {
        char *p2 = NULL; // 分配4个字节的内存 战区也叫临时去
        p2 = (char *)malloc(100);
        if (p2 != NULL)
        {
            free(p2);// 内存泄漏，只是释放掉了p2指向的内存空间，对p2本身没有影响，p2不是NULL
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