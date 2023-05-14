#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef struct Node
{
    struct Node *pro;//指针域指向前结点
    char data;
    struct Node *next;//指针域指向后结点
} ListNode, *LinkList;

struct CreateNode(Node *Head)
{
    Head = (struct Node *)malloc(sizeof(Node));
}
