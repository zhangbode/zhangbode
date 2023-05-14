#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
}ListNode, * LinkList;

struct Node* CreateList();//建立单链表
void PrintList(LinkList L);//遍历输出链表
struct Node* InsertNode(LinkList L);//指定节点插入数据


struct Node* CreateList()
{
	int num;
	ListNode* head = (struct Node*)malloc(sizeof(Node));
	head->next = NULL;
	ListNode* p = NULL, * q = NULL;
	p = q = head;
	while (true)
	{
		p = (struct Node*)malloc(sizeof(Node));
		scanf("%d", &num);
		p->data = num;
		if (num == -1)
		{
			break;
		}
		/*p->next = q->next;
		q->next = p;*/
		q->next = p;
		q = q->next;
		q->next = NULL;
	}
	return head;
}
void PrintList(LinkList L)
{
	LinkList p = L->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
struct Node* InsertNode(LinkList L)
{
	int n = 1, num, i = 2;
	ListNode* p = L->next;
	printf("请输入插入结点的位置：");
	scanf("%d", &n);
	if (n==1)
	{
		ListNode* head = (struct Node*)malloc(sizeof(Node));
		head->next = NULL;
		printf("请输入插入的数据：");
		scanf("%d", &num);
		head->data = num;
		head->next = p;
		L->next = head;
		return L;
	}
	else
	{
		p = p->next;
		while (p)
		{
			if (i==n)
			{
				ListNode* q = (struct Node*)malloc(sizeof(Node));
				printf("已找到结点，请输入插入的值：");
				scanf("%d", &num);
				q->data = num;
				q->next = p->next;
				q->next = p;
				return L;
			}
			i++;
			p = p->next;
			if (p->next==NULL && i<n)
			{
				printf("未找到该结点。\n");
			}
		}
	}
}
int main()
{
	LinkList L;
	L = CreateList();
	PrintList(L);
	L = InsertNode(L);
	PrintList(L);
	system("pause");
	return 0;
}