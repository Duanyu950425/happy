#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *fp = NULL;
    char a[100] = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    char buf[100] = { 0 };
    char *p = NULL;

    //char *fname = "c:\\1.txt";
    char *fname = "d:/1.txt"; // ͳһ������������windows�º�Linux����һ����
        
    fp = fopen(fname, "r+"); // �����ļ��Ƿ���ڣ��½��ļ�
                             // r ֻ���� r+ ��д
    if (NULL == fp)
    {
        printf("func open() err : \n");
    }

    //fputs(a, fp);
    while (!feof(fp))
    {
        p = fgets(buf, 100, fp);
        printf("%s \n", buf);
        printf("%s \n", p);
    }

    if (fp != NULL)
    {
        fclose(fp);
    }

    system("pause");
    return;
}