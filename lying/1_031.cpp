#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#define NULL 0
#define LEN sizeof(struct Node)
// 能够实现先将单个多项式中指数相同的项合并起来，再将两个多项式进行加减
// 而且支持乱序输入，最后按一定的格式降幂输出结果
typedef struct Node
{
    int zhishu; // 存储指数
    int xishu;  // 存储系数
    struct Node *next;
} Node, *LinkList;
void printdxs(Node *head)
{
    // 按标准输出多项式
    int j = 0;
    struct Node *p1;
    p1 = head;
    if (head != NULL)
    {
        do
        {
            if (p1 == head && p1->xishu != 0) // 说明式第一个数
            {
                if (p1->zhishu == 0)
                {
                    printf("%d", p1->xishu);
                    j++;
                }
                else
                {
                    printf("%dX^%d", p1->xishu, p1->zhishu);
                    j++;
                }
            }
            else // 后续单项式判断系数正负输出
            {
                if (p1->zhishu == 0)
                {
                    if (p1->xishu > 0)
                    {
                        printf("+%d", p1->xishu);
                        j++;
                    }
                    else
                    {
                        if (p1->xishu < 0)
                        {
                            printf("%d", p1->xishu);
                            j++;
                        }
                    }
                }
                else
                {
                    if (p1->xishu > 0)
                    {
                        printf("+%dX^%d", p1->xishu, p1->zhishu);
                        j++;
                    }
                    else
                    {
                        if (p1->xishu < 0)
                        {
                            printf("%dX^%d", p1->xishu, p1->zhishu);
                            j++;
                        }
                    }
                }
            }
            p1 = p1->next;
        } while (p1 != NULL);
    }
    if (j == 0) // 格式输出
    {
        printf("0");
    }
}
Node *clean(Node *a)
{
    // 通过遍历来使相同指数的两项合并
    struct Node *p1, *p2, *p3;
    // 相当于已经传了链表的参数到函数中，开始遍历
    p1 = p2 = p3 = a; // 都先指向头
    p2 = p3->next;    // 让p2指向下一个结点
    while (1)         // 当指针没有指向链表的最后
    {
        while (p1->next != NULL)
        {
            if (p2->zhishu == p3->zhishu)

            {
                p3->xishu = p3->xishu + p2->xishu;
                p1->next = p2->next; // 删除p2所指的结点
                free(p2);
                p2 = p1->next;
            }
            else
            {
                p1 = p2;
                p2 = p1->next;
            }
        }
        if (p3->next == NULL)
            break;
        p3 = p3->next; // 查询完一遍后，所有相同系数的放在了一个节点
        p1 = p3;
        p2 = p3->next; // p2继续在下一个结点工作
    }
    return a;
};
Node *create(int n) // 实现链表的组建
{
    struct Node *head, *p1, *p2;
    int i = 1; // 计数器
    head = p1 = p2 = (struct Node *)malloc(LEN);
    p2->next = NULL;
    while (i <= n) // 当没有完成多项式的全部输入时
    {
        if (n == 0) // 当多项式为零项
        {
            printf("error!");
            break;
        }
        p1 = (struct Node *)malloc(LEN); // 开辟一个新空间
        printf("Please enter the %dth polynomial coefficient:", i);
        scanf_s("%d", &p1->xishu);

        printf("Please enter the %dth polynomial exponent:", i);
        scanf_s("%d", &p1->zhishu);
        i++;
        p2->next = p1;
        p2 = p1;
    }
    p2->next = NULL;
    p1 = head->next; // 将p1指向head的下一个结点
    p1 = clean(p1);
    printdxs(p1);

    return (head);
};
Node *paixu(struct Node *head)
{
    // 实现降幂排序
    struct Node *p1, *p2, *p3; //
    int flag;
    p1 = head->next;
    p2 = p1->next;
    p3 = p1;
    while (p1->next != NULL) // 选择排序，按照指数实现降幂排序
    {
        while (p2 != NULL)
        {
            if (p2->zhishu > p3->zhishu)
                p3 = p2;
            p2 = p2->next;
        }
        // 当走完一轮后找到当前最大的指数，开始交换
        flag = p3->zhishu;
        p3->zhishu = p1->zhishu;
        p1->zhishu = flag;
        flag = p3->xishu;
        p3->xishu = p1->xishu;
        p1->xishu = flag;
        p1 = p1->next;
        p2 = p1->next;
        p3 = p1;
    }
    return head;
}
Node *jiajian(Node *a, Node *b, int m, int d) //
{
    // 实现加减法
    Node *a1, *b1, *b2;
    b1 = b;
    b2 = b->next;
    a1 = a->next;
    if (d == 2) // 为第二个多项式系数赋值为负，达到减法的功能
    {
        while (b2 != NULL)
        {
            b2->xishu = -b2->xishu;
            b2 = b2->next;
        }
        b2 = b->next;
    }
    while (a1 != NULL)
    {
        while (b2 != NULL)
        {
            if (b2->zhishu == a1->zhishu) // 指数相等
            {
                a1->xishu = a1->xishu + b2->xishu; // 之后将第二个链表中的该节点删除
                b1->next = b2->next;
                free(b2);
                b2 = b1->next;
            }
            else
            {
                b1 = b2;
                b2 = b2->next; // 往后走
            }
        }
        a1 = a1->next;
        b1 = b;
        b2 = b->next;
    }
    // 当遍历完第一个链表的结点后，查看第二个链表中是否还有剩余的结点，将剩余结点插入到A链表中
    b1 = b->next;      // 让指针指向头部
    while (b1 != NULL) // 当链表不为空
    {
        b2 = b1->next;
        b1->next = a->next;
        a->next = b1;
        b1 = b2;
    }
    printf("The calculation result is:\n");
    printdxs(a->next);
    a = paixu(a);
    printf("\nThe sorted results are:\n");
    printdxs(a->next);
    return a;
};
void txt(Node *head)
{

    int j = 0;
    struct Node *p1;
    p1 = head->next;
    head = head->next;
    FILE *fp;
    fopen_s(&fp, "polynomial.txt", "a");
    if (head != NULL)
    {
        do
        {
            if (p1 == head && p1->xishu != 0) // 说明式第一个数
            {
                if (p1->zhishu == 0)
                {
                    fprintf(fp, "%d", p1->xishu);
                    j++;
                }
                else
                {
                    fprintf(fp, "%dX^%d", p1->xishu, p1->zhishu);
                    j++;
                }
            }
            else
            {
                if (p1->zhishu == 0)
                {
                    if (p1->xishu > 0)
                    {
                        fprintf(fp, "+%d", p1->xishu);
                        j++;
                    }
                    else
                    {
                        if (p1->xishu < 0)
                        {
                            fprintf(fp, "%d", p1->xishu);
                            j++;
                        }
                    }
                }
                else
                {
                    if (p1->xishu > 0)
                    {
                        fprintf(fp, "+%dX^%d", p1->xishu, p1->zhishu);
                        j++;
                    }
                    else
                    {
                        if (p1->xishu < 0)
                        {
                            fprintf(fp, "%dX^%d", p1->xishu, p1->zhishu);
                            j++;
                        }
                    }
                }
            }
            p1 = p1->next;
        } while (p1 != NULL);
    }
    if (j == 0) // 格式输出
    {
        fprintf(fp, "0");
    }
    fprintf(fp, "\n");
    fclose(fp);
}
int main()
{

    int m, n, i; // 初始化链表结点的总数
    printf("To clear the original data in the file, please enter: (1 for YES, 2 for NO)\n");
    scanf_s("%d", &i);
    if (i == 1)
    {
        FILE *fp;
        fopen_s(&fp, "polynomial.txt", "w");
        fclose(fp);
    }
    printf("Please enter how many terms the first polynomial consists of:\n");
    scanf_s("%d", &m);
    printf("Please enter how many terms the second polynomial consists of:\n");
    scanf_s("%d", &n);
    Node *a, *b, *c; // 建立两个多项式链表
    printf("Please enter the information of the first polynomial:\n");
    a = (Node *)create(m);
    txt(a);
    printf("\nPlease enter the information of the second polynomial:\n");
    b = (Node *)create(n);
    txt(b);
    int d;
    printf("\nPlease enter the operation you want to perform: (1 for addition, 2 for subtraction)\n");
    scanf_s("%d", &d);
    c = (Node *)jiajian(a, b, n, d);
    txt(c);
    printf("\nIf you want to know the contents of the existing file, please enter:(1 for YES,0 for NO)\n");
    scanf_s("%d", &i);
    if (i == 1)
    {
        FILE *fp;
        fopen_s(&fp, "polynomial.txt", "w");
        fclose(fp);
    }
    return 0;
}