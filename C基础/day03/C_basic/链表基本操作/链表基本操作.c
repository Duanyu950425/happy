#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    int data;
    struct _Node *next;
}SLIST;

// ��д����SList_Create����������ͷ���ĵ�������ѭ��������㣻
// ����������е���ֵ�Ӽ������룬��-1��Ϊ���������־�������ͷ����ַ�ɺ���ֵ���ء�
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
    // 1. ����ͷ���
    pHead = (SLIST *)malloc(sizeof(SLIST));
    if (pHead == NULL)
    {
        ret = -1;
        printf("func SList_Create() err: %d", ret);
        return ret;
    }
    pHead->data = 0;
    pHead->next = NULL;

    // 2. �Ӽ����������ݣ�����ҵ����
    printf("\nplease enter the data of node(-1:quit): ");
    scanf("%d", &data);
    
    // 3. ѭ������
    // ��ʼ����ǰ��㣬ָ��ͷ���
    pCurr = pHead;
    while (data != -1)
    {
        pM = (SLIST *)malloc(sizeof(SLIST));
        if (pM == NULL)
        {
            ret = -2;
            printf("func SList_Create() err: %d", ret);
            SList_Destory(pHead); // mallocʧ�ܣ���Ҫ��֮ǰ����������ɾ��
            return ret;
        }
        pM->data = data;
        pM->next = NULL;

        pCurr->next = pM;
        pCurr = pM; // ====> pCur = pCur->next // ����ǰ����λ��ָ���½���㴦

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
        tmp = p->next; // ������һ�����λ��
        free(p); // ɾ����ǰ���
        p = tmp; // ���ָ�����
    }
    return 0;
}

// ���ܣ���ֵΪx�Ľ��ǰ������ֵΪy�Ľ�㣻��ֵΪx�Ľ�㲻���ڣ�����ڱ�β
int SList_NodeInsert(SLIST *pHead, int x, int y)
{
    SLIST *pCur = NULL, *pPre = NULL, *pM = NULL;
    // ����y��ֵmalloc�½ڵ�
    pM = (SLIST *)malloc(sizeof(SLIST));
    if (pM == NULL)
    {
        return -1;
    }
    pM->data = y;
    pM->next = NULL;

    // ׼��pCur��pPre����
    pPre = pHead;
    pCur = pHead->next;

    while (pCur)
    {
        if (pCur->data == x)
        {
            // �������
            break; // break֮��ȥ��ֵ
        }
        pPre = pCur; // ��ǰ��������
        pCur = pCur->next; // �õ�ǰ������
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
        printf("û���ҵ�Ҫɾ���Ľ��\n");
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

    // ��ʼ�����ó���
    p = pHead->next;
    q = pHead->next->next;

    while (q != NULL)
    {
        // 1. ����֮ǰ��q�ĺ�̽�㱣��
        t = q->next;
        // 2. ���ò���
        q->next = p;
        // 3��4�Ǵ�����һ��whileѭ�������ó���
        // 3. ��ǰ��������
        p = q;
        // 4. �����ýڵ����
        q = t;
    }

    // �����ú���ӽڵ���ΪNULL
    pHead->next->next = NULL; // ���ú��ĩ�ڵ�ָ��NULL
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