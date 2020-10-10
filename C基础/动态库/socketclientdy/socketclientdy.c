#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itcastlog.h"

typedef struct _SCK_HANDLE
{
    char version[16];
    char serverip[16];
    int serverport;
    unsigned char *buf;
    int buflen;
}SCK_HANDLE;

//客户端初始化 获取handle上下
__declspec (dllexport) int cltSocketInit(void **handle /*out*/)
{
    int ret = 0;
    SCK_HANDLE *sh = NULL;
    sh = (SCK_HANDLE *)malloc(sizeof(SCK_HANDLE));
    if (sh == NULL)
    {
        ret = -1;
        ITCAST_LOG(__FILE__, __LINE__, LogLevel[4], ret, "func cltSocketInit() err: %d, malloc err.....", ret);
        return ret;
    }
    memset(sh, 0, sizeof(SCK_HANDLE));
    strcpy(sh->serverip, "192.168.0.128");
    sh->serverport = 88;
    *handle = sh;
    return 0;
}

//客户端发报文
__declspec (dllexport) int cltSocketSend(void *handle /*in*/, unsigned char *buf /*in*/, int buflen /*in*/)
{
    int ret = 0;
    SCK_HANDLE *sh = NULL;
    if (handle == NULL || buf == NULL)
    {
        ret = -1;
        ITCAST_LOG(__FILE__, __LINE__, LogLevel[4], ret, "func cltSocketSend() err: %d, (handle == NULL || buf == NULL)", ret);
        return ret;
    }
    sh = (SCK_HANDLE *)handle;
    sh->buf = (char*)malloc(buflen);
    if (sh->buf == NULL)
    {
        ret = -2;
        ITCAST_LOG(__FILE__, __LINE__, LogLevel[4], ret, "func cltSocketSend() err: %d, (buflen: %d)", ret, buflen);
        return ret;
    }
    memcpy(sh->buf, buf, buflen);
    sh->buflen = buflen;
    return 0;
}

//客户端收报文
__declspec (dllexport) int cltSocketRev(void *handle /*in*/, unsigned char *buf /*in*/, int *buflen /*in out*/)
{
    int ret = 0;
    SCK_HANDLE *sh = NULL;
    if (handle == NULL || buf == NULL || buflen == NULL)
    {
        ret = -1;
        ITCAST_LOG(__FILE__, __LINE__, LogLevel[4], ret, "func cltSocketRev() err: %d, (handle == NULL || buf == NULL)", ret);
        return ret;
    }
    sh = (SCK_HANDLE *)handle;
    memcpy(buf, sh->buf, sh->buflen);
    *buflen = sh->buflen;

    if (sh->buflen != NULL)
    {
        free(sh->buf);
        sh->buf = NULL;
        sh->buflen = 0;
    }

    return ret;
}

//客户端释放资源
__declspec (dllexport) int cltSocketDestory(void *handle/*in*/)
{
    int ret = 0;
    SCK_HANDLE *sh = NULL;
    if (handle == NULL)
    {
        ret = -1;
        ITCAST_LOG(__FILE__, __LINE__, LogLevel[4], ret, "func cltSocketDestory() err: %d, (handle == NULL)", ret);
        return ret;
    }
    sh = (SCK_HANDLE *)handle;
    if (sh->buf != NULL)
    {
        free(sh->buf);
        sh->buf = NULL;
        sh->buflen = 0;
    }
    free(sh);
    return ret;
}


// --------------------第二套api接口-----Begin----------------------//
__declspec(dllexport) int cltSocketInit2(void **handle)
{
    return cltSocketInit(handle);
}

//客户端发报文
__declspec(dllexport) int cltSocketSend2(void *handle, unsigned char *buf, int buflen)
{
    return cltSocketSend(handle, buf, buflen);
}

//客户端收报文
__declspec(dllexport) int cltSocketRev2(void *handle, unsigned char **buf, int *buflen)
{
    int ret = 0;
    SCK_HANDLE *sh = NULL;
    if (handle == NULL || buf == NULL || buflen == NULL)
    {
        ret = -1;
        ITCAST_LOG(__FILE__, __LINE__, LogLevel[4], ret, "func cltSocketRev2() err: %d, (handle == NULL || buf == NULL)", ret);
        return ret;
    }
    sh = (SCK_HANDLE *)handle;

    *buf = (char*)malloc(sh->buflen);
    memcpy(*buf, sh->buf, sh->buflen);
    *buflen = sh->buflen;

    return ret;
}

__declspec(dllexport) int cltSocketRev2_Free(unsigned char **buf)
{
    if (buf == NULL)
    {
        return -1;
    }
    free(*buf);
    *buf = NULL;
    return 0;
}
//客户端释放资源

__declspec(dllexport) int cltSocketDestory2(void **handle)
{
    int ret = 0;
    SCK_HANDLE *sh = NULL;
    if (handle == NULL)
    {
        ret = -1;
        ITCAST_LOG(__FILE__, __LINE__, LogLevel[4], ret, "func cltSocketDestory() err: %d, (handle == NULL)", ret);
        return ret;
    }
    sh = (SCK_HANDLE *)*handle;
    if (sh->buf != NULL)
    {
        free(sh->buf);
        sh->buf = NULL;
        sh->buflen = 0;
    }
    free(sh);
    *handle = NULL; // 把实参置成NULL
    return ret;
}
// --------------------第二套api接口-----End----------------------//


// 啦啦啦林锐锋修改
// happy every day