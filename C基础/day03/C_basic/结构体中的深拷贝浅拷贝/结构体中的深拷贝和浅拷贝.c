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

Teacher* Create()
{
    Teacher *tmp = NULL;
    tmp = (Teacher*)malloc(100);
    if (tmp == NULL)
    {
        return NULL;
    }
    tmp->name - (char*)malloc(100);
    return tmp;
}

void Free(Teacher *t)
{
    if (t == NULL)
        return;
    if (t->name != NULL)
    {
        free(t->name);
    }
}

// �������������ṩ��copy��Ϊ��һ��ǳ����
// ���ṹ���Ա���к���buf��ʱ��û������
// ���ṹ���Ա���к���ָ��ĺ�����������ֻ�����ָ�������copy��ָ��������µ��ڴ�ռ䣬 �����������ڶ�����ڴ�
// ����Ǳ�������ǳ����

int copyObj(Teacher *to, Teacher *from)
{
    //*to = *from;
    memcpy(to, from, sizeof(Teacher));
    to->name = (char *)malloc(100);
    strcpy(to->name, from->name);
}

void main01()
{
    Teacher t1;
    Teacher t2;
    t1.name = (char *)malloc(100);
    t1.age = 10;

    //t2 = t1; // ǳ����
    copyObj(&t2, &t1);

    if (t1.name != NULL)
    {
        free(t1.name);
    }
    if (t2.name != NULL)
    {
        free(t2.name);
    }
}

void main02()
{
    Teacher *p = NULL;
    int i = 0;
    p = p - 1;
    p = p + 1;
    p = p + 2;
    p = p - p;

    i = (int)(&(p->age));
    printf("%d \n", i);
    system("pause");
}