#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct _Teacher
{
    char name[62];
    char c;
    char *title;
    char **pStuArray;
    int age;
} Teacher;



int printTArray(Teacher *tArray, int num)
{

    int i = 0, j = 0;
    for (i = 0; i < num; i++)
    {
        printf("\n老师信息为:");
        printf("%d %s %s\n", tArray[i].age, tArray[i].name, tArray[i].title);
        printf("\n学生信息为:");
        for (j = 0; j < 3; j++)
        {
            printf("%s", tArray[i].pStuArray[j]);
        }
    }
    return 0;
}

int sortArray(Teacher *tArray, int num)
{
    int i, j = 0;
    Teacher tmp;
    for (i = 0; i < num; i++)
    {
        for (j = i + 1; j < num; j++)
        {
            if (tArray[i].age > tArray[j].age)
            {
                tmp = tArray[i];
                tArray[i] = tArray[j];
                tArray[j] = tmp;
            }
        }
    }
    return 0;
}

Teacher* createArray(int num)
{
    int i = 0, j = 0;
    Teacher *tArray = NULL;
    tArray = (Teacher*)malloc(num * sizeof(Teacher));
    if (tArray == NULL)
    {
        return NULL;
    }

    for (i = 0; i < num; i++)
    {
        tArray[i].title = (char*)malloc(100);
    }
    
    for (i = 0; i < num; i++)
    {
        char **ptmp = (char **)malloc((3 + 1) * sizeof(char*));
        for (j = 0; j < 3; j++)
        {
            ptmp[j] = (char*)malloc(100);
        }
        tArray[i].pStuArray = ptmp;
    }
    return tArray;
}
int FreeArray(Teacher *tArray, int num)
{
    int i = 0, j = 0;
	if (tArray == NULL)
	{
		return -1;
	}
    for (i = 0; i < num; i++)
    {
        char **tmp = tArray[i].pStuArray;
        if (tmp == NULL)
        {
            continue;
        }
        for (j = 0; j < 3; j++)
        {
            if (tmp[j] != NULL)
            {
                free(tmp[j]);
            }
        }
        free(tmp);
    }
    for (i = 0; i < 3; i++)
    {
        if (tArray[i].title != NULL)
        {
            free(tArray[i].title);
            tArray[i].title = NULL;
        }
    }
    free(tArray);
    tArray = NULL;
}

void main()
{
    int i = 0, j = 0;
    int ret = 0;

    Teacher *pArray = NULL;

    pArray = createArray(3);
    if (pArray == NULL)
    {
        return;
    }

    for (i = 0; i < 3; i++)
    {
        printf("请输入第%d个老师的年龄:", i + 1);
        scanf("%d", &pArray[i].age);

        printf("请输入第%d个老师的姓名:", i + 1);
        scanf("%s", pArray[i].name);

        printf("请键入第%d个老师的职称：", i + 1);
        scanf("%s", pArray[i].title);

        printf("请键入学生信息 \n");
        for (j = 0; j < 3; j++)
        {
            printf("请键入第%d个学生的名字：", j + 1);
            scanf("%s", pArray[i].pStuArray[j]);
        }
    }
    printf("排序之前。。。。\n");
    printTArray(pArray, 3);
    sortArray(pArray, 3);
    printf("排序之后。。。。\n");
    printTArray(pArray, 3);
    if (pArray != NULL)
    {
        FreeArray(pArray, 3);
        pArray = NULL;
    }

    system("pause");
    return;
}