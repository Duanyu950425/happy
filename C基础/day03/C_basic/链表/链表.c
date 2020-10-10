#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Teacher
{
    char name[64];
    int age;
    struct _Teacher *next;
}Teacher;

void main()
{
    Teacher t1, t2, t3;
    Teacher *p = NULL;
    memset(&t1, 0, sizeof(Teacher));
    memset(&t2, 0, sizeof(Teacher));
    memset(&t3, 0, sizeof(Teacher));
    t1.age = 11;
    t2.age = 22;
    t3.age = 33;
    
    t1.next = &t2;
    t2.next = &t3;
    t3.next = NULL; // 这一句话不要忘记

    p = &t1;
    while (p)
    {
        printf("age:%d \n", p->age);
        p = p->next;
    }

    system("pause");
}