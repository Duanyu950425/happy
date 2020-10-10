#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getValue(int *p)
{
    *p = 200;
}

void main01(void)
{
    int a = 10;
    int *p = NULL;

    // 直接修改a的值
    a = 20;

    // 间接修改a的值
    p = &a;
    *p = 100;
    printf("间接修改a的值：%d \n", a);

    getValue(&a);
    printf("间接修改a的值：%d \n", a);
    
    system("pause");
    return;
}

void main02()
{
    // 指定长度，超过初始化的长度后面自动补0
    char buf1[100] = { 'a', 'b', 'c', 'd' };
    printf("%s \n", buf1);

    // 不指定长度
    char buf2[] = { 'a', 'b', 'c', 'd' };
    char buf3[] = { 'a', 'b', 'c', 'd', '\0' };
    printf("%s \n", buf2);
    printf("%s \n", buf3);

    // 通过字符串初始化字符数组，并且追加\0
    char buf4[] = "abcdefg";
    printf("%s \n", buf4);

    system("pause");
    return;
}

void main()
{
    int i = 0;
    char *p = NULL;

    char buf4[] = "abcd";
    for (i = 0; i < strlen(buf4); i++)
    {
        printf("%c", buf4[i]);
    }
    printf("\n");

    p = buf4;
    for (i = 0; i < strlen(buf4); i++)
    {
        printf("%c", *(p + i));
    }
    printf("\n");
    system("pause");
    return;
}