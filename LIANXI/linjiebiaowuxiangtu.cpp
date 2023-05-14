#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

const int MVnum =100;//最大顶点数
//边结点
typedef struct ArcNode{
    int adjvex;//该边所指向的结点位置
    struct ArcNode*nextarc;//指向下一条边的指针 
}ArcNdoe;
//表头结点
typedef struct VNode{
    char data;//表头数据
    struct ArcNode*firstarc;//指向第一条依附该顶点的边的指针
}VNode;

typedef VNode AdjList[MVnum];
//邻接表
typedef struct ALGraph{
    AdjList vertices;
    int vexnum,arcnum;//当前顶点数和边数
}ALGraph;

int LocateVex(ALGraph G, char v)
{
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data == v)
			return i;
}
 
//算法6.2采用邻接表表示法创建无向图
int CreateUDG(ALGraph &G)
{
	cout<<"请输入总顶点数，总边数"<<endl;
	cin>>G.vexnum>>G.arcnum;
 
	cout<<"依次输入顶点的信息："<<endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
 
	cout<<"开始构造邻接表："<<endl;
	char v1, v2; 
	int i, j;
	ArcNode *p1 = NULL, *p2 = NULL;
	for (int k = 0; k < G.arcnum; k++)
	{
		cout<<"输入一条边依附的顶点："<<endl;
		cin>>v1>>v2;
		i = LocateVex(G, v1); j = LocateVex(G, v2);
 
		p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p1;
 
 
		p2 = new ArcNode;
		p2->adjvex = i;
		p2->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = p2;
	}
	return 0;
}
//补.遍历
int PrintVex(ALGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		cout<<"vertices["<<i<<"]="<<G.vertices[i].data<<"->";
		ArcNode *p = G.vertices[i].firstarc;
		while (p != NULL)
		{
			cout<<p->adjvex<<" ";
			p = p->nextarc;
		}
		cout << endl;
	}
	return 0;
}
int main()
{
	ALGraph G;
	CreateUDG(G);
	PrintVex(G);
	system("pause");
	return 0;
}