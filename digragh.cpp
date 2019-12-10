///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//1、用邻接表创建有向图；
//2、设计递归算法寻找所有通过指定节点的简单回路
//3、设计算法判断从顶点u到顶点v是否存在路径（分析时间复杂度）
//4、设计算法计算所有顶点的入度（分析时间复杂度）
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct arcnode
{
	int index; //邻接点序号
	struct arcnode *next;
} AR;

typedef struct MyGraph
{
	int type;			//0，表示无向图，1表示有向图
	int arcnum, vexnum; //图中边的个数以及顶点个数
	char **vexname;		//存放顶点名的二维数组
	AR *N;				//存放邻接表头结点的数组
} GH;

int findvex(char *s, GH *G);									 //确定顶点s对应的序号
void creatgraph(GH *G);											 //以邻接表的形式创建图
void showgraph(GH *G);											 //以邻接表的形式显示图
void findpath(GH *G, char *start);								 //寻找所有经过顶点start的简单路径
void allpath(GH *G, int *stack, int *visit, int top, int index); //作为上面函数的副函数)
int ispath(GH *G, char *start, char *end);						 //判断从顶点start到顶点end是否存在路径，存在返回1，否则返回0
void indegree(GH *G);											 //计算并显示输出图中每个顶点的入度
int menu_select();

int menu_select()
{
	char i;
	do
	{
		system("cls");
		printf("1.创建有向图（邻接表）\n");
		printf("2.输出所有经过指定顶点的简单回路\n");
		printf("3.判断两个顶点之间是否存在路径\n");
		printf("4.输出所有顶点的入度\n");
		printf("0.exit\n");
		printf("Please input index(0-4):");
		i = getchar();
	} while (i < '0' || i > '4');
	return (i - '0');
}

main()
{
	GH G;
	char c1[20], c2[20];
	for (;;)
	{
		switch (menu_select())
		{
		case 1:
			creatgraph(&G);
			showgraph(&G);
			system("pause");
			break;
		case 2:
			showgraph(&G);
			printf("请输入顶点名:\n");
			scanf("%s", c1);
			printf("所有经过%s的简单回路有:\n", c1);
			findpath(&G, c1);
			system("pause");
			break;
		case 3:
			showgraph(&G);
			printf("请输入起止两个顶点名:\n");
			scanf("%s%s", c1, c2);
			if (ispath(&G, c1, c2))
				printf("从顶点%s到顶点%s存在路径\n", c1, c2);
			else
				printf("从顶点%s到顶点%s不存在路径\n", c1, c2);
			system("pause");
			break;
		case 4:
			showgraph(&G);
			printf("\n图中所有顶点的入度:\n");
			indegree(&G);
			system("pause");
			break;
		case 0:
			printf("GOOD BYE\n");
			system("pause");
			exit(0);
		}
	}
}

int findvex(char *s, GH *G) //根据顶点名确定该顶点的编号
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (strcmp(s, G->vexname[i]) == 0)
			return i;
	}
	printf("read file erro\n");
	exit(-1);
}

void creatgraph(GH *G)
{
	char filename[] = "graph1.txt";
	char temp_name1[5]; //对于边的邻点名字——的临时存储
	char temp_name2[5];
	AR *temp_node;
	FILE *fp = fopen(filename, "r");
	int i, j;
	if (!fp)
	{
		printf("文件打开错误\n");
		exit(0);
	}
	fscanf(fp, "%d", &G->vexnum);
	G->arcnum = 0;
	G->type = 1;
	G->vexname = (char **)malloc(G->vexnum * sizeof(char *));
	G->N = (AR *)malloc(sizeof(AR) * G->vexnum);
	for (i = 0; i < G->vexnum; i++)
	{
		fscanf(fp, "%s", temp_name1);
		G->vexname[i] = (char *)malloc(sizeof(char) * (strlen(temp_name1) + 1));
		strcpy(G->vexname[i], temp_name1);
		G->N[i].next = NULL;
		G->N[i].index = i;
	}
	while (fscanf(fp, "%s%s", temp_name1, temp_name2) != EOF)
	{
		G->arcnum++;
		i = findvex(temp_name1, G);
		j = findvex(temp_name2, G);
		temp_node = (AR *)malloc(sizeof(AR));
		temp_node->index = j;
		temp_node->next = G->N[i].next; //由于邻接表的同一节点的邻接点先后并无区别
		G->N[i].next = temp_node;
		if (!G->type) //无向图
		{
			temp_node = (AR *)malloc(sizeof(AR));
			temp_node->index = i;
			temp_node->next = G->N[j].next;
			G->N[j].next = temp_node;
		}
	}
	fclose(fp);
}

void showgraph(GH *G)
{
	int i;
	AR *p;
	for (i = 0; i < G->vexnum; i++)
	{
		printf("\n%s ", G->vexname[i]);
		p = G->N[i].next;
		while (p)
		{
			printf("--%s ", G->vexname[p->index]);
			p = p->next;
		}
	}
	printf("\n");
}

void findpath(GH *G, char *start) //寻找所有经过顶点start的简单回路
{
	int stack[G->vexnum], visit[G->vexnum];
	int top = 0, index, i;
	i = findvex(start, G);
	index = G->N[i].index;
	stack[top] = index;
	for (i = 0; i < G->vexnum; i++)
		visit[i] = 0;
	allpath(G, stack, visit, top + 1, index);
}
void allpath(GH *G, int *stack, int *visit, int top, int index)
{
	AR *p;
	int temp_index, i;
	if (index == stack[0] && top != 1) //找到回路方可输出,且防止第一次递归的时候输出
	{
		for (i = 0; i < top; i++)
		{
			printf("%s  ", G->vexname[stack[i]]);
		}
		printf("\n");
	}
	else
	{
		p = G->N[index].next;
		while (p)
		{
			if (!visit[p->index])
			{
				stack[top] = p->index; //注意到top并没有加1，类似于替换
				visit[p->index] = 1;
				allpath(G, stack, visit, top + 1, p->index); //递归函数
				visit[p->index] = 0;						 //避免无法重复访问
			}
			p = p->next;
		}
	}
}

void indegree(GH *G) //计算并显示输出图中每个顶点的入度
{
	int *innum = (int *)malloc(sizeof(int) * G->vexnum); //统计每个点的入度
	int i;
	AR *p;
	for (i = 0; i < G->vexnum; i++)
	{
		innum[i] = 0;
	}
	for (i = 0; i < G->vexnum; i++)
	{
		p = G->N[i].next;
		while (p)
		{
			innum[p->index]++;
			p = p->next;
		}
	}
	printf("所有节点的入度如下\n");
	for (i = 0; i < G->vexnum; i++)
	{
		printf("%s", G->vexname[i]);
		printf("%4d\n", innum[i]);
	}
	free(innum);
}

int ispath(GH *G, char *start, char *end) //判断从顶点start到顶点end是否存在路径，存在返回1，否则返回0
{
	int path[G->vexnum];
	int top = -1;
	int visit[G->vexnum];
	int i, j;
	AR *p;
	for (i = 0; i < G->vexnum; i++)
		visit[i] = 0;
	i = findvex(start, G);
	j = findvex(end, G);
	top++;
	path[top] = i;
	visit[i] = 1;
	while (top >= 0)
	{
		if (G->N[path[top]].index == j)
			return 1; //弹栈即为访问，若是找到一条路径则直接返回1
		p = G->N[path[top]].next;
		top--;
		while (p)
		{
			if (!visit[p->index])
			{
				visit[p->index] = 1;
				top++;
				path[top] = p->index;
			}
			p = p->next;
		}
	}
	return 0; //未能找到路径
}
