#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��˭�ĵ�ַ���������ͼ�ӵ��޸�˭��ֵ
// �������õ�ʱ��
// ��1��ָ���β�ȥ����޸�0��ָ�������ֵ
int getLen(int *p)
{
    *p = 30;
}

void main01()
{
    int a = 0;
    int *p = NULL;

    // ֱ���޸�a��ֵ
    a = 10;
    printf("a: %d\n", a);

    p = &a;
    *p = 20; // *p��p��a�ĵ�ַ�� p��ʵ�εĵ�ַ����ӵ��޸���aʵ�ε�ֵ
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
    char *p = NULL; // ����һ������ͨ����ʵ��
    char **p2 = NULL; // ����һ������ͨ�����β�
    // ���ϵظ�ָ�������ֵ���൱�ڲ��ϵظı�ָ���ָ��
    // �ı�ָ���ָ��Ҫ�������ǲ�������ָ��ָ����ڴ�ռ���в���
    p = 0x01;
    p = 2;
    p = 3;// �������޸�p�����ƺ�

    // ���ڼ�ӵ�ȥ�޸�p��ֵ
    p2 = &p; // �������� pȡ��ַ��������һ������
    *p2 = 100; // ͨ��*p(p��˭�ĵ�ַ)�ͼ�ӵ��޸�˭��ֵ
    printf("p: %d\n", p);

    getMem(&p);
    printf("p: %d\n", p);

    system("pause");
    return;
}