#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 把谁的地址传过来，就间接的修改谁的值
// 函数调用的时候
// 用1级指针形参去间接修改0级指针参数的值
int getLen(int *p)
{
    *p = 30;
}

void main01()
{
    int a = 0;
    int *p = NULL;

    // 直接修改a的值
    a = 10;
    printf("a: %d\n", a);

    p = &a;
    *p = 20; // *p（p是a的地址， p是实参的地址）间接的修改了a实参的值
    printf("a: %d\n", a);

    getLen(&a);
    printf("a: %d\n", a);

    system("pause");
    return;
}

int getMem(char **p2)
{
    *p2 = 200;
    return 0;
}

void main02()
{
    char *p = NULL; // 定义一个变量通常是实参
    char **p2 = NULL; // 定义一个变量通常是形参
    // 不断地给指针变量赋值，相当于不断地改变指针的指向
    // 改变指针的指向不要紧，但是不能随便对指针指向的内存空间进行操作
    p = 0x01;
    p = 2;
    p = 3;// 这是在修改p的门牌号

    // 现在间接地去修改p的值
    p2 = &p; // 建立关联 p取地址传给另外一个变量
    *p2 = 100; // 通过*p(p是谁的地址)就间接的修改谁的值
    printf("p: %d\n", p);

    getMem(&p);
    printf("p: %d\n", p);

    system("pause");
    return;
}