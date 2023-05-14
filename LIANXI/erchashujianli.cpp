#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef struct BiTNode
{
    char data;//数据域
    struct BiTNode *Lchild, *Rchild;//左右孩子指针
} BiTNode, *BiTree;

BiTree CreateTree()
{
    char data;//存放数据
    char temp;//吸收输入的空格

    scanf("%c", &data);//输入数据
    temp = getchar();//吸收空格

    if(data=='#')//#表示叶子节点为空返回
    {
        return NULL;
    }
    else
    {
        BiTNode *T = (struct BiTNode *)malloc(sizeof(BiTNode));//分配空间
        T->data = data;
        T->Lchild = CreateTree();
        T->Rchild = CreateTree();
        return T;
    }
}

void xianxubianli(BiTree T)
{
    if (T==NULL)
    {
        return;
    }
    printf("%c ", T->data);
    xianxubianli(T->Lchild);
    xianxubianli(T->Rchild);
}
void zhongxubianli(BiTree T)
{
    if (T==NULL)
    {
        return;
    }
    zhongxubianli(T->Lchild);
    printf("%c ", T->data);
    zhongxubianli(T->Rchild);
}
void houxubianli(BiTree T)
{
    if(T==NULL)
    {
        return;
    }
    houxubianli(T->Lchild);
    houxubianli(T->Rchild);
    printf("%c ", T->data);
}
int Deepth(BiTree T)//求二叉树深度
{
    int m, n;
    if (T==NULL)
    {
        return 0;
    }
    else
    {
        m = Deepth(T->Lchild);
        n = Deepth(T->Rchild);
        return (m > n) ? (m + 1) : (n + 1);
    }
}
int jiedianshu(BiTree T)//二叉树结点数
{
    if (T==NULL)
    {
        return 0;
    }
    else
    {
        return jiedianshu(T->Lchild) + jiedianshu(T->Rchild) + 1;
    }
}
//非递归实现二叉树先、中、后续建立及遍历(函数部分)
/*
 
*/



int main()
{
    BiTree T;
    T = CreateTree();
    xianxubianli(T);
    cout << endl;
    zhongxubianli(T);
    cout << endl;
    houxubianli(T);
    int n = Deepth(T);
    printf("\n%d", n);
    int x = jiedianshu(T);
    printf("\n%d", x);
    system("pause");
    return 0;
}
