#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Student
{
    char name[64];
    int age;
}Student;

// 自定义数据结构定义 本质：固定大小内存块的别名，
typedef struct _Teacher
{
    char name[64];
    int age;
    char *p1;
    char **p2;
    Student s1;
    Student *ps1;
}Teacher;

// 自定义数据类型，本质：固定大小内存块的别名
typedef struct _AdvTeacher
{
    char name[64];
    int age;
    struct _AdvTeacher *pAdvTeacher;
    struct _AdvTeacher myAdvTeacher;
}AdvTeacher;

void main()
{
    AdvTeacher adv;
    system("pause");
}