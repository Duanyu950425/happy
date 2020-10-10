# C基础

## 一、 基础知识

### 1. 信息的存储单位

位（Bit）：度量数据的最小单位

字节（Byte）：最常用的基本单位，一个字节有8位

K字节	1K = 1024 byte

M字节	1M = 1024K

G字节	1G = 1024M

T字节	1T = 1024G

### 2. DOS命令行的一些指令

```c++
// 电脑10min后关机
shutdown -s -t 600
// 取消关机
shutdown -a
// 电脑10min后重启
shutdown -r -t 600
// 取消重启
shutdown -a
```

### 3.通过system打开360安全浏览器

右键属性，找到快捷方式的目标，复制

```c++
#include <stdlib.h>

void main()
{
    // 对于快捷方式，必须有""，对于C编译器而言，system中第一层“”属于C，所以需要再加一层引号，此时需要用到转义字符\。对于路径中的\也需要转义，此时编程\\，因此下面的代码变成
    //system("C:\Users\ChouPiTu\AppData\Roaming\secoresdk\360se6\Application\360se.exe");
    system("\"C:\\Users\\ChouPiTu\\AppData\\Roaming\\secoresdk\\360se6\\Application\\360se.exe\"");
}
```

### 4. C编译链接的过程

1.c   <u>编译</u>  1.obj  <u>链接</u>  1.exe

## 二、 内存四区

```c++
char *getStr1()
{
    char *p = "abcd";
    return p;
}

char *getStr2()
{
    char *p = "abcd";
    return p;
}

void main(void)
{
	char *p1 = NULL;
    char *p2 = NULL;
    p1 = getStr1();
    p2 = getStr2();
    
    printf("getStr2():%s...\n", getStr2());
    printf("p1:%d...\n", p1);
    printf("p2:%d...\n", p2);
}
// 此时p1与p2的地址相同。
// 因为C++编译器会自动做优化，如果变量所存内容相同，则会指向同一块内存。
// p的值"abcd"存储在全局区
```

内存四区：栈区， 堆区，全局区，代码区。

变量的本质是内存空间的别名。

指针指向谁就把谁的地址赋给指针。

## 三、 指针

### 1. 指针是一种数据类型

1） 指针也是一种变量，占有内存空间，用来保存内存地址

2） *p操作内存

```c++
void main(void)
{
    int a = 10;
    int *p = NULL;
    int c = 0;
    
    a = 11; // 直接修改变量的值
    
    // *p 放在 = 左边 ，写内存
    p = &a; // 将a的地址赋给p
    *p = 20; // 通过指针间接修改a的值
    
    // *p 放在 = 右边，从p所指内存空间读数据
    c = *p; 
}
```

3） 指针变量和它指向的内存块是两个不同的概念

```c++
// 含义1 给p赋值 p = 0x1111; 只会改变指针变量值，不会改变所指的内容；
// 含义2 给*p赋值 *p = 'a'; 不会改变指针变量的值，只会改变所指的内存块的值
// 含义3  = 左边 *p 表示给内存赋值， = 右边*p表示取值。
// 含义4  = 左边 char *p拷贝字符串
void main()
{
    char buf1[100] = {0};
    char buf2[100] = {0};
    char *p1 = buf1;
    char *p2 = buf2;
    
    strcpy(buf1, "abcdefg");
   
    while(*p != '\0')
    {
        // ++ 和 *优先级相同，但是结合使用时自右向左结合
        *p2++ = *p1++; // 将p1的值赋给p2。*p在左边，写值；*p在右边，读值
    }
}

// 含义5  保证所指的内存块能修改
```

4） 指针是一种数据类型，是指它指向的内存空间的数据类型

#### **步长和sizeof的区别**

```c++
// 含义1： 指针步长（p++）， 根据所指内存空间的数据类型来确定
void main(void)
{
    int a[10]; 
    printf("&a + 1 : %d, a + 1 : %d \n", &a + 1, a + 1);
    // 得到的结果不一样，是因为数据类型不一样。a数组名代表数组首元素的地址，所以+1后直接增加了4； 而&a代表整个数组，所以+1增加了40。
}

// 注意区sizeof!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void main(void)
{
    int a[10];
    printf("sizeof(&a) : %d, sizeof(a) : %d \n", sizeof(&a), sizeof(a));
    // sizeof(&a) = 4, sizeof(a) = 40;
    system("pause");
}
```

### 2. 野指针

#### 1） 一级指针

##### （1） 同函数内的野指针

**指针变量和它所指内存空间变量是两个不同的概念**

###### **野指针避免方法：**

步骤一： 定义指针时，把指针变量赋值成NULL

步骤二： 释放内存时，先判断指针变量是否为NULL

步骤三： 释放内存时，把指针变量重新赋值成NULL

###### a.  模型一

```c++
void main(void)
{
    char buf[100];
    int a = 10;
    int *p; // 分配4个字节的内存
    p = &a; // cpu执行的代码，放在代码区

    *p = 20; // 间接修改a的值
    {
        char *p2 = NULL; // 分配4个字节的内存 栈区也叫临时区
        p2 = (char *)malloc(100);
        // 释放两次内存，如果不写“p2=NULL”，那么在第二次释放的时候就会dump。
        if (p2 != NULL)
        {
            free(p2);// 内存泄漏，只是释放掉了p2指向的内存空间，对p2本身没有影响，p2不是NULL，p2依旧指向那块内存空间
            p2 = NULL; // 这就是避免野指针的办法  ！！！！！！！！！！！！！
        }
        
        if (p2 != NULL)
        {
            free(p2);
        }
    }
    system("pause");
    return;
}
```

###### b. 模型二：不断改变指针的指向

```c++
void main(void)
{
    int i = 0;
    char buf[100];
    char *p = NULL;
    strcpy(buf, "123456789");
    
    p = &buf[0];
    p = &buf[0];
    p = &buf[0];
    p = &buf[0];
    p = &buf[0];
     // 给指针变量赋值，就是不断的改变指针的指向
    for (i = 0; i < strlen(buf); i++)
    {
        p = &buf[i];
    }
    
    system("pause");
}

void main(void)
{
    int i = 0;
    char *p = (char *)malloc(100);
    strcpy(p, "123456789");
    
    p = p + 2;
    *p = 'a';
    free(p); // 报错，C规定，释放内存必须要拿到内存的首地址去释放，所以这里的p变成了野指针
}

// ----------------> 解决办法： 引入辅助指针变量
void main()
{
    int i = 0; 
    char *pHead, *p;
    pHead = p = (char*)malloc(100);
    strcpy(p, "123456789");
    p = p + 2;
    *p = 'a';
    free(pHead);
}
```

##### （2） 不同函数内的野指针模型

```c++
// 方法一： return 返回实参的值  √√√√√√√√
char *getMem(int count)
{
    char *tmp = NULL;
    tmp = (char*)malloc(count * sizeof(char));
    return tmp;
}

// 错误示范：想要通过传参的方式修改实参，但这里无法修改实参的值。这里是在给形参p赋值
// 形参和实参是两个不同的概念
void getMem3(int count, char *p)
{
    char *tmp = NULL;
    tmp = (char*)malloc(count * sizeof(char));
    p = tmp; // 在这个场景下，是给形参赋值，而不是给实参赋值
}

// 方法二： 间接赋值，修改实参的值   √√√√√√√√√√√√
void getMem4(int count, char **p/*_out_ 二级指针做输出*/)
{
    char *tmp = NULL;
    tmp = (char*)malloc(count * sizeof(char));
    *p = tmp;
}

int FreeMem(char *p)
{
    if (p == NULL)
    {
        return -1;
    }
    if (p != NULL)
    {
        free(p);
        p = NULL; // 这里无法修改实参
    }
    return 0;
}

int FreeMem2(char **p)
{
    char *tmp = NULL;
    if (p == NULL)
    {
        return -1;
    }
    tmp = *p;
    if (tmp != NULL)
    {
        free(tmp);// 释放实参和形参指向的内存空间
    }
    *p = NULL;
    return 0;
}

void main()
{
    char *p = NULL;
    p = getMem(10);
    
	getMem4(10, &p); // 这里通过取地址，来修改实参的值

    FreeMem(p);
    FreeMem(p); // 这里会dump掉
    
    // 解决办法
    FreeMem2(&p);
    FreeMem2(&p);
}
```

![野指针](../野指针.png)

### 3. 通过p/p++来改变变量的值是指针存在的最大的意义

```c++
void getFileLen(int *p) // p是形参
{
    *p = 100;
}
void main()
{
    int a = 10; // a是实参
    getFileLen(&a); // &a 建立关联
    printf("函数调用后a的值 : %d \n", a);
    system("pause");
}
```

#### 1） 间接赋值的三个条件：

- 定义一个变量（实参），定义一个变量（形参）
- 建立关联：把实参取地址传给形参
- 形参间接地修改了实参的值

1. 例子：画内存四区

```c++
int main()
{
    char buf[20] = "aaaa";
    char buf2[] = "bbbb";
    
    char *p1 = "111111";
    
    char *p2 = malloc(100);
    strcpy(p2, "3333");
}
```

![内存四区](../内存四区.png)

#### 2） 用n级指针去修改n-1级指针的值

##### a. 二级指针概念

```c++
// 二级指针 -----》  首先是个数组，只不过每个元素都是指针而已。
// 多维数组名的本质 ------》 指向数组的指针
char *myArray[4]; // 指针数组

void main()
{
    char *myArray[5] = { "bbbb", "aaaa", "cccc", "1111", "aaaa" };
    sizeof(myArray);
    printf("sizeof(myArray) : %d \n", sizeof(myArray)); // 20, 4(指针内存大小)*5(二维数组维度)
    // 以下两个式子等价。求数组元素个数
    printf("num : %d \n", sizeof(myArray) / sizeof(*myArray)); 
    printf("num : %d \n", sizeof(myArray) / sizeof(myArray[0]));
}

// 二维数组内存分配 
void main()
{
    char **newStr = (char **)malloc(100 * sizeof(char *)); // char* newStr[100] 指针数组
    char **newStr = (char **)malloc(100 * sizeof(char)); // char newStr[100] 字符数组
}
```

##### b. 二级指针分配内存与释放内存函数封装

```c++
char **getMem(int num)
{
    int i = 0;
    char **pp = (char **)malloc(num * sizeof(char*));
    if (pp == NULL)
    {
        return NULL; // 假设分配失败，则return，但是在return之前没有释放内存，则会产生内存泄漏。
    }
    for (i = 0; i < num; i++)
    {
        pp[i] = (char*)malloc(100);
        if (pp[i] == NULL)
        {
            return NULL;
        }
    }
    return pp;
}
int FreeMem(char **pp, int num)
{
    int i = 0;
    if (pp == NULL)
    {
        return -1;
    }
    for (i = 0; i < num; i++)
    {
        free(pp[i]);
    }
    free(pp);
    return 0;
}

// 第二种方法：通过传地址给指针分配内存，以及在释放内存时，将指针置为NULL
int GetMem02(char ***myp, int numArray)
{
    int ret = 0;
    int i = 0;
    char **tmp = NULL;
    if (myp == NULL)
    {
        ret = -1;
        return ret;
    }
    tmp = (char**)malloc(numArray * sizeof(char*));
    if (tmp == NULL)
    {
        ret = -2;
        return ret;
    }
    for (i = 0; i < numArray; i++)
    {
        tmp[i] = (char*)malloc(100);
        if (tmp[i] == NULL)
        {
            ret = -2;
            return ret;
        }
    }
    *myp = tmp;
    return ret;
}
int FreeMem02(char ***myp, int numArray)
{
    int ret = 0;
    int i = 0;
    char **tmp = NULL;
    if (myp == NULL)
    {
        ret = -1;
        return ret;
    }
    tmp = *myp;
    for (i = 0; i < numArray; i++)
    {
        if (tmp[i] != NULL)
        {
            free(tmp[i]);
        }
    }
    free(tmp); // 到这里，将实参与形参共同指向的内存空间释放
    *myp = NULL;
    return ret;
}
void main()
{
    int ret = 0, i = 0;
    int numArray = 10;
    char **pp = NULL;
    
    // 第一种方法: 分配内存与释放内存
    pp = getMem(numArray); // 分配内存
    if (pp == NULL) // 分配内存失败
    {
        return;
    }
    
    FreeMem(pp, numArray); // 释放内存
    
    // 第二种方法: 分配内存与释放内存
    GetMem02(&pp, numArray);
    if(pp == NULL)
    {
        return;
    }
    FreeMem02(&pp, numArray);
}
```

对付一个入口多个出口的办法（既有多个return）：

- 在每次return前，都调用释放函数（太慢，复杂，不推荐）
- **使用goto（推荐！！！！！！！！！！！！！！）**

```c++
void main()
{
    int ret = 0, i = 0;
    int numArray = 10;
    char **pp = NULL;
    char **pp2 = NULL;
    pp = getMem(numArray); // 分配内存
    if (pp == NULL) // 分配内存失败
    {
        //return;
        ret = -1;
        printf(" func getMem() err : %d \n", ret);
        goto End;
    }
    pp2 = getMem(numArray);
    if (pp2 == NULL)
    {
        //return;
        ret = -2;
        printf(" func getMem() err : %d \n", ret);
        goto End;
    }
End:    
    if (pp != NULL) // 判断一把，避免野指针
    {
        FreeMem(pp, numArray); // 释放内存
    }
	if (pp2 != NULL)    
    {
        FreeMem(pp2, numArray);
    }
}
```

##### c. 二级指针内存模型

```c++
void main()
{
    int i = 0;
    // 指针数组 
    char *p1[] = {"123", "456", "789"}; // 第一种内存模型
    
    // 二维数组
    char p2[3][4] = {"123", "456", "789"}; // 第二种内存模型
    
    // 手工二维数组
    char **p3 = (char *)malloc(3 * sizeof(char*)); // 第三种内存模型
    for (i = 0; i <3; i++)
    {
        p3[i] = (char *)malloc(10 * sizeof(char)); // char buf[10];
    }
}
```

![二级指针内存模型图](../二级指针内存模型图.png)

##### d. 第一种内存模型与第三种内存模型的区别

​	**第一种内存模型**，如图所示，数组中的每一个值都是一个指针，指向对应全局区中的内存的值。全局区中内存的值不能被修改。

​	**第三种内存模型**，如图所示，数组中的每一个值在堆区中重新开辟了一块内存。指向堆中开辟的内存。这里的值可以被改变。

​	第一种内存模型和第三种内存模型其实是一样的，只是数组分配在堆上还是临时区上。

​	因此在进行二级指针**排序**时，对于第一种内存模型而言，只能修改指针的指向，而不能修改内存中的值；对于第三种内存模型而言，即能修改指针指向，又能修改内存中的值。

```c++
char** getMem(int num) // 简单的分配内存
{
    int i = 0;
    char **temp = (char*)malloc(num*sizeof(char*));
    for (i = 0; i < num; i++)
    {
        temp[i] = (char*)malloc(100);
    }
    return temp;
}

void sortArray(char **myArray, int count) // 修改指针指向的排序。适用于第一种和第三种内存模型
{
    int i = 0, j =0;
    char *temp = NULL;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (strcmp(myArray[i], myArray[j]) > 0)
            {
                temp = myArray[i];
                myArray[i] = myArray[j];
                myArray[j] = temp;
            }
        }
    }
}

void sortArray02(char **myArray, int count) // 修改内存中的值，适用于第三种内存模型
{
    int i = 0, j =0;
    char temp[100] = {0};
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (strcmp(myArray[i], myArray[j]) > 0)
            {
                strcpy(temp, myArray[i]);
                strcpy(myArray[i], myArray[j]);
                strcpy(myArray[j], temp); // 交换的是buf的内容
            }
        }
    }
}
void printfArray(char **myArray, int count)
{
    int i = 0, j = 0;
    for (i = 0; myArray[i] != NULL; i++)
    {
        printf("%s \n", myArray[i]);
    }
}
void main()
{
    char **myArray = NULL;
    myArray = getMem(3);
    strcpy(myArray[0], "bbbb");
    strcpy(myArray[1], "aaaa");
    strcpy(myArray[2], "cccc");

    //sortArray(myArray, 3);
    sortArray02(myArray, 3);

    printfArray(myArray, 3);

    system("pause");
    return;
}
```

​	如果在分配内存的时候**不想告知大小**，那就在二级指针最后加个0，分配内存时多加一位。

```c++
char** getMem(int num) // 简单的分配内存
{
    int i = 0;
    char **temp = (char*)malloc((num + 1)*sizeof(char*));
    for (i = 0; i < num; i++)
    {
        temp[i] = (char*)malloc(100);
    }
    temp[num] = '\0';
    temp[num] = NULL;
    temp[num] = 0; // 这三种方法均可以
    return temp;
}
void sortArray02(char **myArray) // 修改内存中的值，适用于第三种内存模型
{
    int i = 0, j =0;
    char temp[100] = {0};
    for (i = 0; myArray[i] != NULL; i++)
    {
        for (j = 0; myArray[j] != NULL; j++)
        {
            if (strcmp(myArray[i], myArray[j]) > 0)
            {
                strcpy(temp, myArray[i]);
                strcpy(myArray[i], myArray[j]);
                strcpy(myArray[j], temp); // 交换的是buf的内容
            }
        }
    }
}
void printfArray(char **myArray)
{
    int i = 0, j = 0;
    for (i = 0; i < count; i++)
    {
        printf("%s \n", myArray[i]);
    }
}
void main()
{
    char **myArray = NULL;
    myArray = getMem(3);
    strcpy(myArray[0], "bbbb");
    strcpy(myArray[1], "aaaa");
    strcpy(myArray[2], "cccc");

    //sortArray(myArray);
    sortArray02(myArray);

    printfArray(myArray);

    system("pause");
    return;
}
```



### 4. 理解指针必须和内存四区概念相结合

1） 主调函数 被调函数

​	a） 主调函数可把堆区、栈区、全局数据内存地址传给被调函数

​	b） 被调用函数只能返回堆区、全局数据

​	c） 内存分配方式

​	d） 指针做函数参数，是有输入和输出特性的。

```c++
void copy_str(*from /*in*/, *to /*in*/);
```

2） 为什么int a[10]中a是个常量，C++编译器禁止a++？

```c++
{
    int a[10];
    int *p = a;
    p++;
    
    a++; // XXXX 不允许这样做。
    // C++编译器要拿着a去析构内存，为了避免把a的指向改变，所以设置为常量。
}
```

### 5. 应用指针必须和函数调用相结合（指针做函数参数）

### 6. 数组指针

#### 1） 数组指针的定义

```c++
void main()
{
    {
        // 定义了一个数组类型
        typedef int MyArrayType[5]; // int
        // 定义了一个 数组类型的指针
        MyArrayType *pArray = NULL;
    }
    {
        // 这是定义了一个类型，定义了一个指针类型，定义了一个指向数组的指针类型
        // 数组指针
        typedef int (*MyArrayType)[5];
        MyArrayType myPoint; 
    }
    // 直接定义数组指针
    int (*myArrayPoint)[5]; // 告诉编译器，开辟四个字节内存
}
```

#### 2）数组指针的本质

​	**二维数组的本质就是一个数组指针。**

```c++
void main()
{
    int a[3][5];
    int c[5];
    int b[10]; // b代表数组首元素的地址， &b代表整个数组的地址， &b+1相当于指针后移4*10个单位
    
    // 多维数组a代表什么？
    printf("a: %d, a+1: %d \n", a, a+1);
    // 输出a: 14547044, a+1: 14547064 
    // 4*5， 则a的本质是一个数组指针，指向低维数组的指针，步长为一维的维数。
}

void main()
{
    int a[3][5];
    int i = 0, j = 0;
    (a + i); // 相当于整个第i行的数组地址 // 二级指针
    *(a+i); // 第i行的首地址 // 一维数组
    *(a+i)+j; // 相当于第i行第j列元素的地址
    *(*(a+i)+j) // 相当于第i行第j列元素的值
}
```

```c++
// C++编译器需要知道步长
int printArray(char buf[10][30]);
int printArray(char buf[][30]);
int printArray(char (*buf)[30]); // ()和[]的优先级相等，但结合方向是自左向右。所以这是一个数组指针
```

#### 3） 指针数组

```c++
// 指针数组做参数的技术推演过程
void printfArray(char *p[3]);
void printfArray(char *p[]);
void printfArray(char **p);

void main()
{
    char *p1[3] = { "123", "456", "789" };
}
```

**多维数组做韩束参数退化原因：**

​	本质是因为程序员眼中的二维内存，在物理内存上是线型存储，所以说是真。

## 四、 字符串

### 1. 对字符数组初始化

```c++
void main()
{
    // 指定长度，超过初始化的长度后面自动补0
    char buf1[100] = {'a', 'b', 'c', 'd'};
    
    // 不指定长度
    char buf2[] = {'a', 'b', 'c', 'd'}; // 乱码，因为没有指定结束字符
    char buf3[] = {'a', 'b', 'c', 'd', '\0'};
    
    // 通过字符串初始化字符数组，并且追加\0
    char buf4[] = "abcdefg";
}
```

### 2. 操作数组的方法

```c++
void main()
{
    int i = 0;
    char *p = NULL;
    
    char buf4[] = "abcd";
    for (i = 0; i < strlen(buf4); i++)
    {
        printf("%c", buf4[i]); // buf[]
    }
    printf("\n");
    
    p = buf4;
    for (i = 0; i < strlen(buf4); i++)
    {
        printf("%c", *(p+i)); // *p 间接赋值
    }
    printf("\n");
    
    // [] 和 * 的本质是什么？
    // *p 是程序员手工的（显式的）利用间接赋值
    // []是c/c++编译器帮我们做了一个*p操作，内部操作：buf4[i] ====> buf4[0+i] ====> *(buf4+i)
}
```

### 3. 字符串做函数参数

```c++
void copy_str1(*form, *to)
{
    if (; *from != '\0'; from++, to++)
    {
        *to = *from;
    }
    *to = '\0';
}

void copy_str2(*form, *to)
{
    while (*from != '\0')
    {
        *to = *from;
        from++;
        to++;
    }
    *to = '\0';
}

void copy_str3(*form, *to)
{
    while (*from != '\0')
    {
        *to++ = *from++;
    }
    *to = '\0';
}

void copy_str4_1(*from, *to)
{
	while((*to = *from) != '\0')
    {
        from++;
        to++;
    }
}

void copy_str4_2(*from, *to)
{
	while((*to++ = *from++) != '\0')
    {
        ;
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!最经典的算法！！！！！！！！！！！！！！！！
void copy_str5(*from, *to)
{
	while((*to++ = *from++))
    {
        ;
    }
}

void  main()
{
	char *p = "abcdefg";
 	char p2[100];
    copy_str4_1(p, p2);
}
```

## 五、 结构体

**构体即自定义数据类型，本质：固定大小内存块的别名。**

### 1. 结构体的深拷贝浅拷贝

**编译器的浅拷贝：**

1） 编译器给我们提供的copy行为是一个浅拷贝
2） 当结构体成员域中含有buf的时候没有问题
3） 当结构体成员域中含有指针的时候，编译器只会进行指针变量的copy。指针变量所指的内存空间， 编译器不会在多分配内存

```c++
// 结构体是捆绑分配，捆绑释放
typedef struct _Teacher
{
    char *name;
    int age;
} Teacher; // struct只是定义了一个数据类型，并没有分配内存

Teacher* Create()
{
    Teacher* tmp = NULL;
    tmp = (Teacher*)malloc(100);
    if (tmp == NULL)
        return;
    tmp->name = (char*)malloc(100);
}

void Free(Teacher* t)
{
    if (t == NULL)
        return;
    if (t->name != NULL)
    {
        free(t->name);
    }
}

void copyObj(Teacher* to, Teacher* from)
{
    //*to = *from;
    memcpy(to, from, sizeof(Teacher)); // 在这里将整个结构体拷贝
    to->name = (char*)malloc(100);
    strcpy(to->name, from->name);
}

void main()
{
    Teacher t1;
    Teacher t2;
    t1.name = (char *)malloc(100);
    t1.age = 10;
    
    // t2 = t1;// 浅拷贝
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
```

### 2. 结构体内成员偏移地址

1. ->与.操作都是取址操作，并没有操作内存
2. p=NULL时，相当于把p这一块内存映射到0开始的这一块内存空间。所以**里面成员的偏移量刚好是每一个成员相对于成员域的大小**。

```c++
typedef struct _Teacher
{
    char* name; //4
    int age2; //4
    char buf[32]; //32
    int age;
} Teacher;

void main()
{
    Teacher *p = NULL; // 这里的p为NULL
    int i = 0;
    p = p - 1;
    p = p + 1;
    p = p + 2;
    p = p - p;

    i = (int)(&(p->age)); // 相当于 i = (int)&(((Teacher*)0)->age)
                          // 将p这一块内存映射到0开始的这一块内存空间
    printf("%d \n", i);  // 此时打印出来的i刚好是40
    system("pause");
}
```

### 3. 结构体二级指针

```c++
typedef struct _Teacher
{
    char* name;
    int age2;
    char buf[32];
    int age;
} Teacher;

// 方法1： 为结构体分配内存
Teacher *getTeacher()
{
    Teacher *tmp = (Teacher *)malloc(sizeof(Teacher));
    tmp->age = 10;
    return tmp;
}

int FreeTeacher(Teacher *p)
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

// 方法2： 为结构体分配内存
int getTeacher2(Teacher **p)
{
    Teacher *tmp = (Teacher *)malloc(sizeof(Teacher));
    tmp->age = 10;
    *p = tmp;
    return 0;
}

int FreeMem2(Teacher **p)
{
    int ret = 0;
    Teacher *tmp = NULL;
    if (p == NULL)
    {
        ret = -1;
        return ret;
    }
    tmp = *p;
    free(tmp);
    *p = NULL;
    return ret;
}

void main()
{
    Teacher *pT1 = NULL;
    pT1 = getTeacher(); 
    FreeTeacher(pT1);
    pT1 = NULL;// 方法1

    Teacher *p2 = NULL;
    getTeacher2(&p2); // 方法2
	
    FreeMem(&p2);
    system("pause");
}
```

### 4. 结构体中套结构体

```c++
typedef struct _Student
{
    char name[64];
    int age;
}Student;

typedef struct _Teacher
{
    char name[64];
    int age;
    char *p1;
    char **p2;
    Student s1; // 在分配内存的时候，将Student的整块内存拷贝过来
    Student *ps1;
}Teacher;

void main()
{
    Student s1;
    Teacher t1;
    t1.age = 30;
    t1.si.age = 20;
    
    // error
    t1.ps1->age = 20 // 没有给ps1分配内存
    
    // 结构体中套一个指针
    t1.ps1 = &s1; // 这里，为结构体中的指针分配内存
    t1.ps1->age = 10;   
}
```



## 六、 文件操作

### 1. C语言读写api

#### 1） api的种类

fopen() 文件的打开

| 方式  | 含义                                  |
| ----- | ------------------------------------- |
| "r"   | 打开，只读                            |
| "w"   | 打开，文件指针指到头，只写            |
| "a"   | 打开，指向文件尾，在已存在文件中追加  |
| "rb"  | 打开一个二进制文件，只读              |
| "wb"  | 打开一个二进制文件，只写              |
| "ab"  | 打开一个二进制文件，进行追加          |
| "r+"  | 以读/写方式打开一个已存在的文件       |
| "w+"  | 以读/写方式建立一个新的文本文件       |
| "a+"  | 以读/写方式打开一个文本文件进行追加   |
| "rb+" | 以读/写方式打开一个二进制文件         |
| "wb+" | 以读/写方式建立一个新的二进制文件     |
| "ab+" | 以读/写方式打开一个二进制文件进行追加 |

##### a. 文件读写api

- fgetc fputc  按照字符读写文件（读写配置文件）

- fread fwrite  按照块读写文件（大数据块迁移）

- 按照格式化进行读写文件

##### b. 文件控制api

- 文件是否结束
- 文件指针的定位、跳转

##### c. api项目

## 七、 动态库

动态库中的.lib：是对.dll的资源描述。描述.dll中有哪些函数，以及具体的函数入口。

.dll加载到工程中：通过vs2017工具加载的。链接器 -> 输入 -> .lib文件

### 1. 动态库导出和导入函数的匹配

- 导出

```c++
__declspec(dllexport) int cltSocketDestory2(void **handle)
```

- 导入

```c++
__declspec(dllimport) int cltSocketDestory2(void **handle)
```

### 2. 动态库调用方式

#### 1） 显示调用

​	通过定义工程属性，链接器 -> 输入 -> 导入.lib，利用编译器显示调用动态库

#### 2） 隐式调用

#### 3） 动态库分配的内存需要动态库去释放

​	**如果在动态库中分配的内存，需要动态库提供释放内存的接口去释放内存。**

## 八、 链表

### 1. 链表定义及静态链表

- 建立的时候，指针指向谁，就把谁的地址赋给指针
- 辅助指针变量的引入

缺陷：

- 只能在一个函数内调用。分配的内存在栈区。

```c++
typedef struct _Teacher
{
    char name[64];
    int age;
    struct _Teacher *next;
}Teacher;

void main()
{
    Teacher t1, t2, t3;
    Teacher *p = NULL; // 辅助指针变量
    memset(&t1, 0, sizeof(Teacher)); // 对结构体清零
    memset(&t2, 0, sizeof(Teacher)); 
    memset(&t3, 0, sizeof(Teacher)); 
    
    t1.age = 11;
    t2.age = 22;
    t3.age = 33;
    
    // 构建链表
    t1.next = &t2; // 指针指向谁，就把谁的地址赋给指针
    t2.next = &t3;
    t3.next = NULL; // 结束标志。因为上面已经memset了，所以这一句可加可不加
    
    p = &t1;
    
    // 打印链表
    while (p)
    {
        printf("%d \n", p->age);
        p = p->next;
    }
}
```

### 2. 链表基本操作

```c++
typedef struct _Node
{
    int data;
    struct _Node *next;
}SLIST;

int SList_Create(SLIST **mypHead)
{
    int ret = 0;
    SLIST *pHead = NULL, *pNew = NULL, *pCur = NULL;
    
    // 1. 创建头结点
    pHead = (SLIST*)malloc(sizeof(SLIST));
    if (pHead == NULL)
    {
        ret = -1;
        printf("func SList_Create() err: %d", ret);
        return ret;
    }
    pHead->data = 0;
    pHead->next = NULL;
    
    // 2. 从键盘输入数据，创建业务结点
    printf("\nplease enter the data of node(-1:quit): ");
    scanf("%d", &data);
    
    // 3. 循环创建
    // 初始化当前结点，指向头结点
    pCur = pHead;
    while (data != -1)
    {
        pNew = (SLIST*)malloc(sizeof(SLIST));
        if (pNew == NULL)
        {
            ret = -2;
            printf("func SList_Create() err: %d", ret);
            SList_Destory(pHead); // malloc失败，需要将之前创建的链表删除
            return ret;
        }
        pNew->data = data;
        pNew->next = NULL;
        
        pCur->next = pNew;
        pCur = pNew; // 将当前指针移至添加的最新的结点上
        
        printf("\nplease enter the data of node(-1:quit): ");
        scanf("%d", &data);
    }
    *mypHead = pHead;
    return ret;
}

int SList_Print(SLIST *pHead)
{
    int ret = 0;
    SLIST *pCur = NULL;
    if (pHead == NULL)
    {
        ret = -1;
        printf("func SList_Print() err: %d", ret);
        return ret;
    }
    pCur = pHead->next;
    printf("\nBegin ");
    while (pCur)
    {
        printf("%d ", pCur->data);
        pCur = pCur->next;
    }
    printf("\nEnd ");
    return ret;
}

// 功能：在值为x的结点前，插入值为y的结点；若值为x的结点不存在，则插在表尾
int SList_NodeInsert(SLIST *pHead, int x, int y)
{
    int ret = 0;
    SLIST *pPre = NULL, *pCur = NULL, pNew = NULL;
    // 根据y的值malloc新节点
    pNew = (SLIST*)malloc(sizeof(SLIST));
    if (pNew == NULL)
    {
        ret = -1;
        printf("func SList_NodeInsert() err: %d, (pNew == NULL)", ret);
        return ret;
    }
    pNew->data = y;
    pNew->next = NULL;
    
    // 准备pCur和pPre的环境
    pPre = pHead;
    pCur = pHead->next
    while(pCur)
    {
        if (pCur->data == x)
        {
            break;
        }
        pPre = pCur;
        pCur = pCur->next;
    }
    pNew->next = pCur; // 现将单向链表后面的链表接上，否则就找不到了
    pPre->next = pNew;
    return ret;
}

int SList_NodeDel(SLIST *pHead, int x)
{
    int ret = 0;
    SLIST *pPre = NULL, pCur = NULL;
    if (pHead == NULL)
    {
        ret = -1;
        printf("func SList_NodeDel() err: %d, (pHead == NULL)", ret);
        return ret;
    }
    pPre = pHead;
    pCur = pHead->next;
    
    while (pCur)
    {
        if (pCur->data == x)
        {
            break;
        }
        pPre = pCur;
        pCur = pCur->next;
    }
    if (pCur == NULL)
    {
        printf("没有找到要删除的结点\n");
        return 0;
    }
    pPre->next = pCur->next;
    free(pCur);
    return ret;
}

int SList_Destroy(SLIST *pHead)
{
    int ret = 0;
    SLIST *pCur = NULL, pNext = NULL;
    if (pHead == NULL)
    {
        ret = -1;
        printf("func SList_Destroy() err: %d, (pHead == NULL)", ret);
        return ret;
    }
    pCur = pHead;
    while (pCur)
    {
        pNext = pCur->next;
        free(pCur);
        pCur = pNext;
    }
    return ret;
}

int SList_Resve(SLIST *pHead)
{
    int ret = 0;
    SLIST *pCur = NULL, *pPre = NULL, *pNext = NULL;
    if (pHead == NULL)
    {
        ret = -1;
        printf("func SList_Resve() err: %d, (pHead == NULL)", ret);
        return ret;
    }
    
    // 如果没有结点 或 只有一个结点
    if (pHead->next == NULL || pHead->Next->next == NULL)
    {
        ret = -2;
        printf("只有一个结点或没有结点");
        return ret;
    }
    
    // 初始化逆置场景
    pPre = pHead->next;
    pCur = pHead->next->next;
    while(pCur != NULL)
    {
        // 逆置之前把pCur的后继结点保存
        pNext = pCur->next;
        // 逆置操作
        pCur->next = pPre;
        
        // 后面两步的目的：为下次循环打造场景
        // 将前一节点后移
        pPre = pCur;
        // 将当前节点后移
        pCur = pNext;
    }
    pHead->next->next = NULL;// 逆置后的末节点指向NULL
    pHead->next = pCur;
    return ret;
}

void main()
{
    int ret = 0; // 错误检查
    SLIST *pHead = NULL;
    
    // 创建链表
    ret = SList_Create(&pHead);
    if (ret != 0)
    {
        printf("func SList_Create() err: %d", ret);
        return;
    }
    SList_Print(pHead);
    
    // 插入结点
    SList_NodeInsert(pHead, 20, 19);
    if (ret != 0)
    {
        printf("func SList_NodeInsert() err: %d", ret);
        return;
    }
    
    // 删除结点
    SList_NodeDel(pHead, 20);
    if (ret != 0)
    {
        printf("func SList_NodeDel() err: %d", ret);
        return;
    }
    
    // 逆置操作
    ret = SList_Resve(pHead);
    if (ret != 0)
    {
        printf("func SList_Resve() err: %d", ret);
        return;
    }
    SList_Print(pHead);
    
    // 销毁链表
    SList_Destory(pHead);
    if (ret != 0)
    {
        printf("func SList_Destory() err: %d", ret);
        return;
    }
    system("pause");
}
```

# C++与C的关系