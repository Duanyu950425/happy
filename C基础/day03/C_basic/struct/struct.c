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
        printf("\n��ʦ��ϢΪ:");
        printf("%d %s %s\n", tArray[i].age, tArray[i].name, tArray[i].title);
        printf("\nѧ����ϢΪ:");
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
        printf("�������%d����ʦ������:", i + 1);
        scanf("%d", &pArray[i].age);

        printf("�������%d����ʦ������:", i + 1);
        scanf("%s", pArray[i].name);

        printf("������%d����ʦ��ְ�ƣ�", i + 1);
        scanf("%s", pArray[i].title);

        printf("�����ѧ����Ϣ \n");
        for (j = 0; j < 3; j++)
        {
            printf("������%d��ѧ�������֣�", j + 1);
            scanf("%s", pArray[i].pStuArray[j]);
        }
    }
    printf("����֮ǰ��������\n");
    printTArray(pArray, 3);
    sortArray(pArray, 3);
    printf("����֮�󡣡�����\n");
    printTArray(pArray, 3);
    if (pArray != NULL)
    {
        FreeArray(pArray, 3);
        pArray = NULL;
    }

    system("pause");
    return;
}