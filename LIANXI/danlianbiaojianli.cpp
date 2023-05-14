#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;//数据域
    struct Node *next;//指针域
} Node, *LinkList;

struct Node*CreateList()//建立单链表
{
    LinkList Head;//头结点
    Head = (struct Node *)malloc(sizeof(Node));
    Head->next = NULL;
    Node *p, *q;
    p = q = Head;//指针结点，储存数据时结点移动
    int num;
    while (1)
    {
        p = (struct Node *)malloc(sizeof(Node));
        scanf("%d", &num);
        p->data = num;
        if(num==-1)//当输入-1时跳出循环，
        {
            break;
        }
       // p->next = q->next;//头插法
       // q->next = p;
        q->next = p;//尾插法
        q = q->next;
        q->next = NULL;
    }

    return Head;
};
void PrintList(LinkList L)//遍历输出单链表
{
    Node *p = L->next;//头结点为空，跳过头结点
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
void Clear(LinkList L)//释放链表结点
{
    Node *p = L->next;
    Node *q = NULL;
    while (p)
    {
        q = p;//p作为前置指针，q作为后置指针
        p = q->next;//将p指针移动到下一个结点
        free(q);//释放q结点所占空间
    }
    L->next = NULL;//将头结点next指向NULL，若不指向空遍历输出会进入死循环
    printf("链表空间已释放！");
}

int main()
{
    LinkList L;
    L = CreateList();//建立单链表
    PrintList(L);//遍历输出链表
    Clear(L);//清除结点，释放空间
    system("pause");
    return 0;
}