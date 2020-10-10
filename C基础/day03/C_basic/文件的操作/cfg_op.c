#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetCfgItem(char *pFileName, char *pKey, char *pValue, int *pValueLen);
int WriteCfgItem(char *pFileName, char *pItemName, char *pItemValue, int *pItemValueLen);

// ʵ������
// ���ļ�
// �����еķ�ʽ ѭ�����ļ�
// ����ÿһ�У���ƥ��Key�ؼ��֣��ڽ���valueֵ����ȡ
// ��ȡvalueֵ��Ҫ 1. ȥ��ǰ��ո�  1��ָ�����Ӧ��

#define  LineMaxLen 2048
#define KeyMaxLen 64

int GetCfgItem(char *pFileName, char *pKey, char *pValue, int *pValueLen)
{
    int rv = 0;
    FILE *fp = NULL;
    char lineBuf[LineMaxLen];
    char *pTemp = NULL, *pBegin = NULL, *pEnd = NULL;

    if (pFileName == NULL || pKey == NULL || pValue == NULL || pValueLen == NULL)
    {
        rv = -1;
        printf("GetCfgItem() err. param err \n");
        goto End;
    }

    fp = fopen(pFileName, "r");
    if (fp == NULL)
    {
        rv = -2;
        printf("fopen() err. \n");
        goto End;
    }

    while (!feof(fp))
    {
        memset(lineBuf, 0, sizeof(lineBuf));
        pTemp = fgets(lineBuf, LineMaxLen, fp);
        if (pTemp == NULL)
        {
            break;
        }

        pTemp = strchr(pKey, '=');
        if (pTemp == NULL)
        {
            continue;
        }

        pTemp = strstr(lineBuf, pKey);
        if (pTemp == NULL)
        {
            continue;
        }

        pTemp = strchr(lineBuf, '=');
        if (pTemp == NULL)
        {
            continue;
        }
        pTemp = pTemp + 1;

        while (1)
        {
            if (*pTemp == ' ')
            {
                pTemp++;
            }
            else
            {
                pBegin = pTemp;
                if (*pBegin == '\n')
                {
                    printf("������: %s û������value \n", pKey);
                    goto End;
                }
                break;
            }
        }
        while (1)
        {
            if ((*pTemp == ' ' || *pTemp == '\n'))
            {
                break;
            }
            else
            {
                pTemp++;
            }
        }
        pEnd = pTemp;

        *pValueLen = pEnd - pBegin;
        memcpy(pValue, pBegin, pEnd - pBegin);
        break;
    }
End:
    if (fp != NULL)
    {
        fclose(fp);
    }
    return rv;
}

// ʵ������
// ѭ����ÿһ�У� ���key�������Ƿ���� �������޸Ķ�Ӧvalueֵ
// �������ڣ����ļ�ĩβ������key = value"
// �ѵ㣺����޸��ļ����е�ֵ

int SetCfgItem(char *pFileName, char *pKey, char *pValue, int pValueLen)
{
    int rv = 0, iTag = 0, length = 0;
    FILE *fp = NULL;
    char lineBuf[LineMaxLen];
    char *pTemp = NULL, *pBegin = NULL, *pEnd = NULL;
    char filebuf[1024 * 8] = { 0 };

    if (pFileName == NULL || pKey == NULL || pValue == NULL)
    {
        rv = -1;
        printf("SetCfgItem() err. param err \n");
        goto End;
    }

    fp = fopen(pFileName, "r+");
    if (fp == NULL)
    {
        rv = -2;
        printf("fopen() err. \n");
        //goto End;
    }

    if (fp == NULL)
    {
        fp = fopen(pFileName, "w+t");
        if (fp == NULL)
        {
            rv = -3;
            printf("fopen() err. \n");
            goto End;
        }
    }

    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    if (length > 8 * 1024)
    {
        rv = -3;
        printf("�ļ�����1024*8��unsported");
        goto End;
    }

    while (!feof(fp))
    {
        memset(lineBuf, 0, sizeof(lineBuf));
        pTemp = fgets(lineBuf, LineMaxLen, fp);
        if (pTemp == NULL)
        {
            break;
        }

        pTemp = strstr(lineBuf, pKey);
        if (pTemp == NULL)
        {
            strcat(filebuf, lineBuf);
            continue;
        }
        else
        {
            sprintf(lineBuf, "%s = %s\n", pKey, pValue);
            strcat(filebuf, lineBuf);
            iTag = 1;
        }
    }

    if (iTag == 0)
    {
        fprintf(fp, "%s = %s\n", pKey, pValue);
    }
    else
    {
        if (fp != NULL)
        {
            fclose(fp);
            fp = NULL;
        }
        fp = fopen(pFileName, "w+t");
        if (fp == NULL)
        {
            rv = -4;
            printf("fopen() err. \n");
            goto End;
        }
        fputs(filebuf, fp);
    }
End:
    if (fp != NULL)
    {
        fclose(fp);
    }
    return rv;
}