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

    // ֱ���޸�a��ֵ
    a = 20;

    // ����޸�a��ֵ
    p = &a;
    *p = 100;
    printf("����޸�a��ֵ��%d \n", a);

    getValue(&a);
    printf("����޸�a��ֵ��%d \n", a);
    
    system("pause");
    return;
}

void main02()
{
    // ָ�����ȣ�������ʼ���ĳ��Ⱥ����Զ���0
    char buf1[100] = { 'a', 'b', 'c', 'd' };
    printf("%s \n", buf1);

    // ��ָ������
    char buf2[] = { 'a', 'b', 'c', 'd' };
    char buf3[] = { 'a', 'b', 'c', 'd', '\0' };
    printf("%s \n", buf2);
    printf("%s \n", buf3);

    // ͨ���ַ�����ʼ���ַ����飬����׷��\0
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