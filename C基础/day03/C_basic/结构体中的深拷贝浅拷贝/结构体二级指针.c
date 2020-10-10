#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Teacher
{
    char* name;
    int age2;
    char buf[32];
    int age;
} Teacher;

Teacher *getTeacher()
{
    Teacher *tmp = (Teacher *)malloc(sizeof(Teacher));
    tmp->age = 10;
    return tmp;
}

int getTeacher2(Teacher **p)
{
    Teacher *tmp = (Teacher *)malloc(sizeof(Teacher));
    tmp->age = 10;
    *p = tmp;
    return 0;
}

int PrintTeacher(Teacher *p)
{
    printf("p.age: %d", p->age);
}

int FreeTeacher(Teacher **p)
{
    int ret = 0;
    Teacher *tmp = NULL;
    if (p == NULL)
    {
        ret = -1;
        return ret;
    }
    tmp = *p;
    free(tmp); // 释放实参和形参所指向的内存空间
    *p = NULL; // 把实参，通过间接赋值成NULL
    return ret;
}

int FreeTeacher01(Teacher *p)
{
    int ret = 0;
    Teacher *tmp = NULL;
    if (p == NULL)
    {
        ret = -1;
        return ret;
    }
    tmp = p;
    free(tmp);
}

void main()
{
    Teacher *p2 = NULL;

    Teacher *pT1 = NULL;
    pT1 = getTeacher();
    PrintTeacher(pT1);
    FreeTeacher01(pT1);
    pT1 = NULL;
    
    /*getTeacher2(&p2);
    PrintTeacher(p2);

    FreeTeacher(&p2);*/

    system("pause");
}