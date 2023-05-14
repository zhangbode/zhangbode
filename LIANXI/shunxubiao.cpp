//链式结构
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;


typedef struct Node{
    char data;
    struct Node*next;
}Node,*LinkList;

struct Node*CreateList(){
    Node *head = (struct Node*)malloc(sizeof(Node));
    head->next = NULL;
    Node *p = NULL, *q = NULL;
    p = q = head;
    while (1)
    {
        p = (struct Node *)malloc(sizeof(Node));
        char num;
        cin >> num;
        if (num =='#')
        {
            break;
        }
        
        p->data = num;
        p->next = q->next;//头插法
        q->next = p;
        /* q->next = p;//尾插法
        q = q->next;
        q->next = NULL; */

    }
    return head;
};
struct Node*DeleteNode(LinkList L){
    LinkList p = L->next;
    
}
void PrintList(LinkList L){
    LinkList p = L->next;
    while(p){
        cout << p->data << " ";
        p = p->next;
    }
}
int main()
{
    LinkList L;
    L = CreateList();
    PrintList(L);
    system("pause");
    return 0;
}