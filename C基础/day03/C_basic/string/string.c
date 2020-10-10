#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int subStringNum(char *str, char* substr, int *count)
{
    char *p = str;
    int nCount = 0;
    do
    {
        p = strstr(p, substr);
        if (p == NULL)
        {
            break;
        }
        else
        {
            nCount++;
            p = p + strlen(substr);
        }
    } while (*p != '\0');
    *count = nCount;
    printf("nCount : %d \n", nCount);
    return 0;
}

void main01()
{
    char *p = "abcd1111abcd2222abcd3333";
    char *sub = "abcd";
    int count = 0;
    int ret = subStringNum(p, sub, &count);

    system("pause");
    return;
}

void trimSpace01(const char* inbuf, char * outbuf)
{
    int i = 0, j = strlen(inbuf) - 1; 
    while (*inbuf != '\0' && isspace(inbuf[i]))
    {
        i++;
    }
    while (isspace(inbuf[j]) && j > 0)
    {
        j--;
    }
    strncpy(outbuf, inbuf + i, j - i + 1);
    //strncpy(outbuf, inbuf[i], j - i + 1); // 有错，数组元素和数组元素地址的区别
}

void main02()
{
    char buf[] = "    abcdefgdddd      ";
    char buf2[100] = { 0 };
    trimSpace(buf, buf2);
    printf("%s \n", buf2);
    system("pause");
    return;
}

void main03()
{
    char p[] = "abcdef";
    char *p1 = p;
    char *p2 = p + strlen(p) - 1;
    char c;

    while (p1 < p2)
    {
        c = *p1;
        *p1 = *p2;
        *p2 = c;
        ++p1;
        --p2;
    }
    printf("%s \n", p);
    system("pause");
}

int trimSpace(char *inbuf, char *outbuf)
{
    int ret = 0;
    int i = 0, j = strlen(inbuf) - 1;
    while (*inbuf != '\0' && isspace(inbuf[i]))
    {
        i++;
    }
    while (j > 0 && isspace(inbuf[j]))
    {
        j--;
    }
    strncpy(outbuf, inbuf + i, j - i + 1);
    return ret;
}

int getKeybyValue(char *pKeyValude, char *pKey, char *pValue)
{
    int ret = 0;
    char *p = NULL;
    if (pKeyValude == NULL || pKey == NULL || pValue == NULL)
    {
        ret = -1;
        printf("func getKeybyValue() err : %d 查找没有关键字pKey \n", ret);
        return ret;
    }
    p = strstr(pKeyValude, pKey);
    if (p == NULL)
    {
        ret = -1;
        printf("func getKeybyValue() err : %d 查找没有关键字pKey \n", ret);
        return ret;
    }
    p = p + strlen(pKey);
    p = strstr(p, "=");
    if (p == NULL)
    {
        ret = -2;
        printf("func getKeybyValue() err : %d 查找没有关键字= \n", ret);
        return ret;
    }
    p = p + 1;
    ret = trimSpace(p, pValue);
    if (ret != 0)
    {
        printf("func trimSpace() err : %d \n", ret);
        return ret;
    }
    return ret;
}

void main()
{
    int ret = 0;
    char buf[] = "key    =    abcdef ";
    char Key[] = "key";
    char Value[1024] = { 0 };
    ret = getKeybyValue(buf, Key, Value);
    if (ret != 0)
    {
        printf("func getKeybyValue() err : %d \n", ret);
        return ret;
    }
    printf("%s \n", Value);
    system("pause");
    return 0; 
}