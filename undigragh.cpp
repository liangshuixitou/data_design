///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：
//1、用邻接矩阵创建无向网；
//2、请判断该无向网是否连通，是否包含回路（分析时间复杂度）
//3、输出任意两个顶点之间的所有简单路径，以及各自的路径长度（路径长度指的是路径中所有边的权值之和）
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define maxx 9999999 //定义的无穷大值

typedef struct MyGraph
{
	int type;			//0，表示无向网，1表示有向网
	int arcnum, vexnum; //图中边的个数以及顶点个数
	char **vexname;		//存放顶点名的二维数组
	int **A;			//邻接矩阵，A[i][j]表示i号顶点与j号顶点之间边的权值，若i,j之间没有边，则A[i][j]取值无穷大
} GH;
int menu_select();
int findvex(char *s, GH *G);												//确定顶点s对应的序号
void creatgraph(GH *G);														//以邻接矩阵的形式创建图
void showgraph(GH *G);														//以邻接表的形式显示图
void findpath(GH *G, char *start, char *end);								//寻找简单路径
void allpath(GH *G, int *path, int *visit, int i, int j, int top, int len); //递归查找所有的路径并且输出
int iscycle(GH *G);															//判断图中是否有回路，有返回1，否则返回0
int isconnect(GH *G);														//判断图是否连通，是返回1，否则返回0

int menu_select()
{
	char i;
	do
	{
		system("cls");
		printf("1.创建无向网（邻接矩阵）\n");
		printf("2.判断无向网是否连通\n");
		printf("3.判断无向网中是否有回路\n");
		printf("4.输出任意两个顶点之间的所有简单路径以及路径长度\n");
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
			if (isconnect(&G))
				printf("\n该图是连通的\n");
			else
				printf("\n该图不是连通的\n");
			system("pause");
			break;
		case 3:
			showgraph(&G);
			if (iscycle(&G))
				printf("\n该图中包含回路\n");
			else
				printf("\n该图中不包含回路\n");
			system("pause");
			break;
		case 4:
			showgraph(&G);
			printf("\n请输入起止两个顶点名:\n");
			scanf("%s%s", c1, c2);
			printf("所有从 %s 到 %s 的简单路径以及路径长度：\n", c1, c2);
			findpath(&G, c1, c2);
			system("pause");
			break;
		case 0:
			printf("GOOD BYE\n");
			system("pause");
			exit(0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int findvex(char *s, GH *G)
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
	char filename[] = "graph2.txt";
	FILE *fp = fopen(filename, "r");
	char temp_name1[5], temp_name2[5];
	int i, j, temp_num;
	if (!fp)
	{
		printf("文件打开失败\n");
		exit(0);
	}
	fscanf(fp, "%d", &G->vexnum);
	G->type = 0;
	G->arcnum = 0;
	G->A = (int **)malloc(sizeof(int *) * G->vexnum);
	G->vexname = (char **)malloc(sizeof(char *) * G->vexnum);
	for (i = 0; i < G->vexnum; i++)
	{
		fscanf(fp, "%s", temp_name1);
		G->vexname[i] = (char *)malloc(sizeof(char) * (strlen(temp_name1) + 1));
		strcpy(G->vexname[i], temp_name1);
		G->A[i] = (int *)malloc(sizeof(int) * G->vexnum);
		for (j = 0; j < G->vexnum; j++)
			G->A[i][j] = maxx;
	}
	while (fscanf(fp, "%s%s%d", temp_name1, temp_name2, &temp_num) != EOF)
	{
		G->arcnum++;
		i = findvex(temp_name1, G);
		j = findvex(temp_name2, G);
		G->A[i][j] = G->A[j][i] = temp_num;
	}
	fclose(fp);
}

void showgraph(GH *G)
{
	int i, j;
	for (i = 0; i < G->vexnum; i++)
	{
		printf("\n%s", G->vexname[i]);
		for (j = 0; j < G->vexnum; j++)
		{
			if (G->A[i][j] < maxx)
				printf("--%s(%d) ", G->vexname[j], G->A[i][j]);
		}
	}
	printf("\n");
}

void allpath(GH *G, int *path, int *visit, int i, int j, int top, int len) //递归查找所有的路径并且输出
{
	if (i == j)
	{
		for (int k = 0; k < top; k++)
		{
			printf("%s  ", G->vexname[path[k]]);
		}
		printf("\t路径长度为%d\n", len);
	}
	else
	{
		for (int k = 0; k < G->vexnum; k++)
		{
			if (!visit[k] && G->A[i][k] < maxx)
			{
				visit[k] = 1;
				path[top] = k;
				allpath(G, path, visit, k, j, top + 1, len + G->A[i][k]);
				visit[k] = 0;
			}
		}
	}
}

void findpath(GH *G, char *start, char *end) //寻找简单路径函数
{

	int i, j, top = 0, len = 0;
	int path[G->vexnum], visit[G->vexnum] = {0};
	i = findvex(start, G);
	j = findvex(end, G);
	path[top] = i;
	visit[i] = 1;
	allpath(G, path, visit, i, j, top + 1, len);
}

int iscycle(GH *G) //判断图中是否有回路，有返回1，否则返回0
{
	int visit[G->vexnum] = {0};
	int D[G->vexnum] = {0};
	int stack[G->vexnum], top = -1, index;
	for (int i = 0; i < G->vexnum; i++) //统计每个点的度
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			if (G->A[i][j] < maxx)
				D[i]++;
		}
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		if (D[i] <= 1) //将所有度小于等于1的点入栈
		{
			top++;
			stack[top] = i;
			visit[i] = 1; //设置为已经访问过了
		}
	}
	while (top >= 0)
	{
		index = stack[top];
		top--;
		for (int j = 0; j < G->vexnum; j++)
		{
			if (G->A[index][j] < maxx && !visit[j])
			{
				D[j]--;
				if (D[j] == 1)
				{
					top++;
					stack[top] = j;
					visit[j] = 1; //设置为已经访问过了
				}
			}
		}
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		if (!visit[i])
			return 1;
	}
	return 0;
}

int isconnect(GH *G) //判断图是否连通，是返回1，否则返回0
{
	//算法分析，一次dfs即可,若是能遍历所有点即可
	int visit[G->vexnum] = {0};
	int stack[G->vexnum], top = -1;
	int index;
	stack[++top] = 0; //将0节点入栈
	while (top >= 0)
	{
		index = stack[top];
		top--;
		for (int i = 0; i < G->vexnum; i++)
		{
			if (!visit[i] && G->A[index][i] < maxx)
			{
				top++;
				stack[top] = i;
				visit[i] = 1;
			}
		}
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		if (!visit[i])
			return 0;
	}
	return 1;
}
