#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    int data;
    struct _Node *next;
}SLIST;

// 编写函数SList_Create，建立带有头结点的单向链表。循环创建结点；
// 结点数据域中的数值从键盘输入，以-1作为输入结束标志。链表的头结点地址由函数值返回。
int SList_Create(SLIST **mypHead);
int SList_Print(SLIST *pHead);
int SList_NodeInsert(SLIST *pHead, int x, int y);
int SList_NodeDel(SLIST *pHead, int x);
int SList_Destory(SLIST *pHead);
int SList_Resve(SLIST *pHead);

int SList_Create(SLIST **mypHead)
{
    SLIST *pHead = NULL, *pM = NULL, *pCurr = NULL;
    int data = 0, ret = 0;
    // 1. 创建头结点
    pHead = (SLIST *)malloc(sizeof(SLIST));
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
    pCurr = pHead;
    while (data != -1)
    {
        pM = (SLIST *)malloc(sizeof(SLIST));
        if (pM == NULL)
        {
            ret = -2;
            printf("func SList_Create() err: %d", ret);
            SList_Destory(pHead); // malloc失败，需要将之前创建的链表删除
            return ret;
        }
        pM->data = data;
        pM->next = NULL;

        pCurr->next = pM;
        pCurr = pM; // ====> pCur = pCur->next // 将当前结点的位置指向新建结点处

        printf("\nplease enter the data of node(-1:quit): ");
        scanf("%d", &data);
    }
    *mypHead = pHead;
    return ret;
}

int SList_Print(SLIST *pHead)
{
    SLIST *p = NULL;
    if (pHead == NULL)
    {
        return -1;
    }
    p = pHead->next;
    printf("\nBegin ");
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\nEnd ");
    return 0;
}

int SList_Destory(SLIST *pHead)
{
    SLIST *p = NULL, *tmp = NULL;
    if (pHead == NULL)
    {
        return -1;
    }
    p = pHead;
    while (p)
    {
        tmp = p->next; // 缓存下一个结点位置
        free(p); // 删除当前结点
        p = tmp; // 结点指针后移
    }
    return 0;
}

// 功能：在值为x的结点前，插入值为y的结点；若值为x的结点不存在，则插在表尾
int SList_NodeInsert(SLIST *pHead, int x, int y)
{
    SLIST *pCur = NULL, *pPre = NULL, *pM = NULL;
    // 根据y的值malloc新节点
    pM = (SLIST *)malloc(sizeof(SLIST));
    if (pM == NULL)
    {
        return -1;
    }
    pM->data = y;
    pM->next = NULL;

    // 准备pCur和pPre环境
    pPre = pHead;
    pCur = pHead->next;

    while (pCur)
    {
        if (pCur->data == x)
        {
            // 插入操作
            break; // break之后去赋值
        }
        pPre = pCur; // 让前驱结点后移
        pCur = pCur->next; // 让当前结点后移
    }
    pM->next = pCur;
    pPre->next = pM;
    return 0;
}

int SList_NodeDel(SLIST *pHead, int x)
{
    SLIST *pCur = NULL, *pPre = NULL;
    if (pHead == NULL)
    {
        return -1;
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
    return 0;
}

int SList_Resve(SLIST *pHead)
{
    int ret = 0;
    SLIST *p = NULL, *q = NULL, *t = NULL;
    if (pHead == NULL)
    {
        ret = -1;
        printf("func SList_Resve() err: %d, (pHead == NULL)", ret);
        return ret;
    }

    if (pHead->next == NULL || pHead->next->next == NULL)
    {
        ret = -2;
        printf("");
        return ret;
    }

    // 初始化逆置场景
    p = pHead->next;
    q = pHead->next->next;

    while (q != NULL)
    {
        // 1. 逆置之前把q的后继结点保存
        t = q->next;
        // 2. 逆置操作
        q->next = p;
        // 3和4是打造下一次while循环的逆置场景
        // 3. 让前驱结点后移
        p = q;
        // 4. 让逆置节点后移
        q = t;
    }

    // 让逆置后的子节点置为NULL
    pHead->next->next = NULL; // 逆置后的末节点指向NULL
    pHead->next = p;
    return ret;
}

void main()
{
    int ret = 0;
    SLIST *pHead = NULL;
    ret = SList_Create(&pHead);
    if (ret != 0)
    {
        printf("func SList_Create() err: %d", ret);
        return;
    }
    SList_Print(pHead);

    SList_NodeInsert(pHead, 20, 19);
    if (ret != 0)
    {
        printf("func SList_NodeInsert() err: %d", ret);
        return;
    }
    SList_Print(pHead);

    SList_NodeDel(pHead, 20);
    if (ret != 0)
    {
        printf("func SList_NodeDel() err: %d", ret);
        return;
    }
    SList_Print(pHead);

    ret = SList_Resve(pHead);
    if (ret != 0)
    {
        printf("func SList_Resve() err: %d", ret);
        return;
    }
    SList_Print(pHead);

    SList_Destory(pHead);
    if (ret != 0)
    {
        printf("func SList_Destory() err: %d", ret);
        return;
    }
    system("pause");
}