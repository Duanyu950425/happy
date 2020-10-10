#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socketclientdll.h"
#include "itcastlog.h"

void main01()
{
    ITCAST_LOG(__FILE__, __LINE__, LogLevel[0], 0, "00000");
    ITCAST_LOG(__FILE__, __LINE__, LogLevel[1], 1, "11111");
    ITCAST_LOG(__FILE__, __LINE__, LogLevel[2], 2, "22222");
    ITCAST_LOG(__FILE__, __LINE__, LogLevel[3], 3, "33333");
    ITCAST_LOG(__FILE__, __LINE__, LogLevel[4], 4, "44444");
    system("pause");
}

void main02()
{
    int ret = 0;
    int i = 0;
    void *handle = NULL;
    unsigned char buf[1024];
    int buflen = 10;

    unsigned char out[1024] = { 0 };
    int outlen = 0;

    strcpy(buf, "aaaaadafdfhaklejwofl;dfnjdf;adlfjafjoiweahoriyw");

    //客户端初始化 获取handle上下
    ret = cltSocketInit(&handle /*out*/);
    if (ret != 0)
    {
        printf("func cltSocketInit() err: %d \n", ret);
        return;
    }

    ////客户端发报文
    //int cltSocketSend(void *handle /*in*/, unsigned char *buf /*in*/, int buflen /*in*/);
    ret = cltSocketSend(handle, buf, buflen);
    if (ret != 0)
    {
        printf("func cltSocketSend() err: %d \n", ret);
        return;
    }

    ////客户端收报文
    //int cltSocketRev(void *handle /*in*/, unsigned char *buf /*in*/, int *buflen /*in out*/);
    ret = cltSocketRev(handle, out, &outlen);
    if (ret != 0)
    {
        printf("func cltSocketRev() err: %d \n", ret);
        return;
    }
    printf("out: %s \n", out);

    ////客户端释放资源
    //int cltSocketDestory(void *handle/*in*/);
    ret = cltSocketDestory(handle);
    if (ret != 0)
    {
        printf("func cltSocketDestory() err: %d \n", ret);
        return;
    }

    system("pause");
}

void main()
{
    int ret = 0;
    int i = 0;
    void *handle = NULL;
    unsigned char buf[1024];
    int buflen = 10;

    unsigned char *out = NULL;
    int outlen = 0;

    strcpy(buf, "aaaaadafdfhaklejwofl;dfnjdf;adlfjafjoiweahoriyw");

    //客户端初始化 获取handle上下
    ret = cltSocketInit2(&handle /*out*/);
    if (ret != 0)
    {
        printf("func cltSocketInit2() err: %d \n", ret);
        return;
    }

    ////客户端发报文
    //int cltSocketSend(void *handle /*in*/, unsigned char *buf /*in*/, int buflen /*in*/);
    ret = cltSocketSend2(handle, buf, buflen);
    if (ret != 0)
    {
        printf("func cltSocketSend2() err: %d \n", ret);
        return;
    }

    ////客户端收报文
    //int cltSocketRev(void *handle /*in*/, unsigned char *buf /*in*/, int *buflen /*in out*/);
    ret = cltSocketRev2(handle, &out, &outlen);
    if (ret != 0)
    {
        printf("func cltSocketRev2() err: %d \n", ret);
        return;
    }
    printf("out: %s \n", out);

    ret = cltSocketRev2_Free(&out);
    if (ret != 0)
    {
        printf("func cltSocketRev2_Free() err: %d \n", ret);
        return;
    }

    ////客户端释放资源
    //int cltSocketDestory(void *handle/*in*/);
    ret = cltSocketDestory2(&handle);
    if (ret != 0)
    {
        printf("func cltSocketDestory2() err: %d \n", ret);
        return;
    }

    system("pause");
}