#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int spitString(const char *buf1, char c, char buf[10][30], int *num)
{
    int ret = 0;
    if (buf1 == NULL || num == NULL)
    {
        ret = -1;
        printf("传入参数有误 err : %d \n", ret);
        return ret;
    }
    char *p = NULL; 
    char *pTmp = NULL;
    int ncount = 0;

    p = buf1;
    pTmp = buf1;
    do
    {
        p = strchr(p, c);
        if (p == NULL)
        {
            break;
        }
        else
        {
            strncpy(buf[ncount], pTmp, p - pTmp);
            buf[ncount][p - pTmp] = '\0';
            ncount++;
            pTmp = p = p + 2;
        }
    } while (*p != '\0');
    *num = ncount;
    return ret;
}

void main01()
{
    char buf[] = "abcdeg, acccd, eeee, aaaa, e3eeeee, sssss,";
    char c = ',';
    char buf2[10][30];
    int num = 0;
    int ret = spitString(buf, c, buf2, &num);
    if (ret != 0)
    {
        printf("func spitString() err : %d \n", ret);
        return ret;
    }
    for (int i = 0; i < num; i++)
    {
        printf("%s\n", buf2[i]);
    }
    system("pause");
    return;
}

void main02(void)
{
    int a[10];
    printf("&a : %d, a : %d \n", &a, a);
    printf("&a + 1 : %d, a + 1 : %d \n", &a + 1, a + 1);
    // 得到的结果不一样，是因为数据类型不一样。a数组名代表数组首元素的地址，所以+1后直接增加了4； 而&a代表整个数组，所以+1增加了40。
    system("pause");
}

void main03(void)
{
    int a[10];
    //printf("&a : %d, a : %d \n", &a, a);
    printf("sizeof(&a) : %d, sizeof(a) : %d \n", sizeof(&a), sizeof(a));
    // 得到的结果不一样，是因为数据类型不一样。a数组名代表数组首元素的地址，所以+1后直接增加了4； 而&a代表整个数组，所以+1增加了40。
    system("pause");
}

void main04(void)
{
    char *myArray[5] = { "bbbb", "aaaa", "cccc", "1111", "aaaa" };
    sizeof(myArray);
    printf("sizeof(myArray) : %d \n", sizeof(myArray));
    printf("num : %d \n", sizeof(myArray) / sizeof(*myArray));
    system("pause");
}

void main05()
{
    int a[3][5];
    int c[5];
    int b[10]; // b代表数组首元素的地址， &b代表整个数组的地址， &b+1相当于指针后移4*10个单位

    // 多维数组a代表什么？
    printf("a: %d, a+1: %d \n", a, a + 1);
    // 输出
    system("pause");
}

void main06()
{
    char *p1[] = { "123", "456", "789" };
    //char (*p2)[4] = { "123", "456", "789" };
    system("pause");
}

char **getMem(int num)
{
    int i = 0;
    char **temp = (char **)malloc(num * sizeof(char*));
    for (i = 0; i < num; i++)
    {
        temp[i] = (char*)malloc(100);
    }
    return temp;
}

void sortArray(char **myArray, int count)
{
    int i = 0, j = 0;
    char *tmp;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (strcmp(myArray[i], myArray[j]) > 0)
            {
                tmp = myArray[i];
                myArray[i] = myArray[j];
                myArray[j] = tmp;
            }
        }
    }
}

void sortArray02(char **myArray, int count)
{
    int i = 0, j = 0;
    char tmp[100];
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (strcmp(myArray[i], myArray[j]) > 0)
            {
                strcpy(tmp, myArray[i]);
                strcpy(myArray[i], myArray[j]);
                strcpy(myArray[j], tmp); // 交换的是buf的内容
            }
        }
    }
}

void printfArray(char **myArray, int count)
{
    int i = 0, j = 0;
    for (i = 0; i < count; i++)
    {
        printf("%s \n", myArray[i]);
    }
}

void main07()
{
    char **myArray = NULL;
    myArray = getMem(3);

    strcpy(myArray[0], "bbbb");
    strcpy(myArray[1], "aaaa");
    strcpy(myArray[2], "cccc");

    //sortArray(myArray, 3);
    sortArray02(myArray, 3);

    printfArray(myArray, 3);

    system("pause");
    return;
}

char** getMem01(int num) // 简单的分配内存
{
    int i = 0;
    char **temp = (char*)malloc((num + 1) * sizeof(char*));
    for (i = 0; i < num; i++)
    {
        temp[i] = (char*)malloc(100);
    }
    temp[num] = '\0';
    //temp[num] = NULL;
    //temp[num] = 0; // 这三种方法均可以
    return temp;
}
void sortArray03(char **myArray) // 修改内存中的值，适用于第三种内存模型
{
    int i = 0, j = 0;
    char temp[100] = { 0 };
    for (i = 0; myArray[i] != NULL; i++)
    {
        for (j = 0; myArray[j] != NULL; j++)
        {
            if (strcmp(myArray[i], myArray[j]) > 0)
            {
                strcpy(temp, myArray[i]);
                strcpy(myArray[i], myArray[j]);
                strcpy(myArray[j], temp); // 交换的是buf的内容
            }
        }
    }
}
void printfArray02(char **myArray)
{
    int i = 0, j = 0;
    for (i = 0; myArray[i] != NULL; i++)
    {
        printf("%s \n", myArray[i]);
    }
}
void main08()
{
    char **myArray = NULL;
    myArray = getMem01(3);
    strcpy(myArray[0], "bbbb");
    strcpy(myArray[1], "aaaa");
    strcpy(myArray[2], "cccc");

    //sortArray(myArray);
    sortArray03(myArray);

    printfArray02(myArray);

    system("pause");
    return;
}

char **getArray3(char **myp1, int num1, char(*myp2)[30], int num2, int *num3)
{
    int i = 0, j = 0;
    int tmpNum3 = 0;
    char **tmpp3 = NULL;
    if (myp1 == NULL || myp2 == NULL || num3 == NULL)
    {
        return NULL;
    }
    tmpNum3 = num1 + num2;

    tmpp3 = (char**)malloc(tmpNum3 * sizeof(char*));
    if (tmpp3 == NULL)
    {
        return NULL;
    }
    for (i = 0; i < num1; i++)
    {
        tmpp3[i] = (char*)malloc(strlen(myp1[i]) + 1);
        if (tmpp3[i] == NULL)
        {
            return NULL;
        }
        strcpy(tmpp3[i], myp1[i]);
    }

    for (j = 0; j < num2; j++, i++)
    {
        tmpp3[i] = (char *)malloc(strlen(myp2[i]) + 1);
        if (tmpp3[i] == NULL)
        {
            return NULL;
        }
        strcpy(tmpp3[i], myp2[j]);
    }

    for (i = 0; i < tmpNum3; i++)
    {
        for (j = i + 1; j < tmpNum3; j++)
        {
            if (tmpp3[i] > tmpp3[j])
            {
                char *tmp = tmpp3[i];
                tmpp3[i] = tmpp3[j];
                tmpp3[j] = tmp;
            }
        }
    }

    *num3 = tmpNum3;
    return tmpp3;
}

int getArray3_free(char **p3, int num3)
{
    int i = 0;
    if (p3 == NULL)
    {
        return -1;
    }
    for (i = 0; i < num3; i++)
    {
        if (p3[i] != NULL)
        {
            free(p3[i]);
        }
    }
    free(p3);

    return 0;
}

char** getArray4(char **p1, int num1, char (*p2)[30], int num2, int *num3)
{
    int i = 0, j = 0;
    char *tmp = NULL;
    char **pTemp = NULL;
    if (p1 == NULL || p2 == NULL || num3 == NULL)
    {
        return NULL;
    }
    int tmpNum3 = num1 + num2;
    pTemp = (char **)malloc((tmpNum3 + 1) * sizeof(char*));
    if (pTemp == NULL)
    {
        return NULL;
    }
    for (i = 0; i < num1; i++)
    {
        pTemp[i] = (char*)malloc(strlen(p1[i]) + 1);
        if (pTemp == NULL)
        {
            return NULL;
        }
        strcpy(pTemp[i], p1[i]);
    }

    for (j = 0; j < num2; j++, i++)
    {
        pTemp[i] = (char*)malloc(strlen(p2[j]) + 1);
        if (pTemp[i] == NULL)
        {
            return NULL;
        }
        strcpy(pTemp[i], p2[j]);
    }

    for (i = 0; i < tmpNum3; i++)
    {
        for (j = i + 1; j < tmpNum3; j++)
        {
            if (pTemp[i] < pTemp[j])
            {
                tmp = pTemp[i];
                pTemp[i] = pTemp[j];
                pTemp[j] = tmp;
            }
        }
    }

    *num3 = tmpNum3;
    return pTemp;
}

int getArray4_free(char **pTemp, int num)
{
    int i = 0;
    if (pTemp == NULL)
    {
        return -1;
    }
    for (i = 0; i < num; i++)
    {
        if (pTemp[i] != NULL)
        {
            free(pTemp[i]);
        }
    }
    free(pTemp);
    return 0;
}
void main()
{
    int i = 0;
    int num3 = 0;
    char *p1[] = { "22222", "111111", "333333" };
    char p2[3][30] = { "aaaaaaaa", "bbbbbb", "cccccc" };
    char **p3 = NULL;

    //p3 = getArray3(p1, 3, p2, 4, &num3);
    p3 = getArray4(p1, 3, p2, 3, &num3);
    if (p3 == NULL)
    {
        return;
    }
    for (i = 0; i < num3; i++)
    {
        printf("%s \n", p3[i]);
    }

    //getArray3_free(p3, num3);
    getArray4_free(p3, num3);
    system("pause");
}