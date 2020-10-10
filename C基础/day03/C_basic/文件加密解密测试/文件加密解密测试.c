#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"

// 完成文件加密的操作

int FileSymEnc(char *fileName1, char *fileName2)
{
    int ret = 0;
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    unsigned char plain[4096];
    int plainlen = 0;
    int writelen = 0;

    fp1 = fopen(fileName1, "rb");
    if (fp1 == NULL)
    {
        ret = -1;
        goto End;
    }

    fp2 = fopen(fileName1, "wb");
    if (fp2 == NULL)
    {
        ret = -2;
        goto End;
    }

    while (!feof(fp1))
    {
        plainlen = fread(plain, 1, 4096, fp1);
        if (feof(fp1))
        {
            break;
        }
        writelen = fwrite(plain, 1, plainlen, fp2);
        if (writelen != plainlen) // 如果长度不相等，说明写文件发生了io错误
        {
            ret = -3;
            printf("写新文件失败\n");
            goto End;
        }
    }

    writelen = fwrite(plain, 1, plainlen, fp2);
    if (writelen != plainlen) // 如果长度不相等，说明写文件发生了io错误
    {
        ret = -3;
        printf("写新文件失败\n");
        goto End;
    }
End:
    if (fp1 != NULL) fclose(fp1);
    if (fp2 != NULL) fclose(fp2);
    return 0;
}

void main()
{
    int ret = 0;
    char *file1 = "d:/1.txt";
    char *file2 = "d:/222.txt";

    ret = FileSymEnc(file1, file2);
    if (ret != 0)
    {
        return;
    }
}