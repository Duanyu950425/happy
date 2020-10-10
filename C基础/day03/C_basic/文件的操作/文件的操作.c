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
    char *fname = "d:/1.txt"; // 统一用这个，这个在windows下和Linux下是一样的
        
    fp = fopen(fname, "r+"); // 不管文件是否存在，新建文件
                             // r 只读； r+ 读写
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