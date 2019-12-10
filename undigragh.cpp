///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//1�����ڽӾ��󴴽���������
//2�����жϸ��������Ƿ���ͨ���Ƿ������·������ʱ�临�Ӷȣ�
//3�����������������֮������м�·�����Լ����Ե�·�����ȣ�·������ָ����·�������бߵ�Ȩֵ֮�ͣ�
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define maxx 9999999 //����������ֵ

typedef struct MyGraph
{
	int type;			//0����ʾ��������1��ʾ������
	int arcnum, vexnum; //ͼ�бߵĸ����Լ��������
	char **vexname;		//��Ŷ������Ķ�ά����
	int **A;			//�ڽӾ���A[i][j]��ʾi�Ŷ�����j�Ŷ���֮��ߵ�Ȩֵ����i,j֮��û�бߣ���A[i][j]ȡֵ�����
} GH;
int menu_select();
int findvex(char *s, GH *G);												//ȷ������s��Ӧ�����
void creatgraph(GH *G);														//���ڽӾ������ʽ����ͼ
void showgraph(GH *G);														//���ڽӱ����ʽ��ʾͼ
void findpath(GH *G, char *start, char *end);								//Ѱ�Ҽ�·��
void allpath(GH *G, int *path, int *visit, int i, int j, int top, int len); //�ݹ�������е�·���������
int iscycle(GH *G);															//�ж�ͼ���Ƿ��л�·���з���1�����򷵻�0
int isconnect(GH *G);														//�ж�ͼ�Ƿ���ͨ���Ƿ���1�����򷵻�0

int menu_select()
{
	char i;
	do
	{
		system("cls");
		printf("1.�������������ڽӾ���\n");
		printf("2.�ж��������Ƿ���ͨ\n");
		printf("3.�ж����������Ƿ��л�·\n");
		printf("4.���������������֮������м�·���Լ�·������\n");
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
				printf("\n��ͼ����ͨ��\n");
			else
				printf("\n��ͼ������ͨ��\n");
			system("pause");
			break;
		case 3:
			showgraph(&G);
			if (iscycle(&G))
				printf("\n��ͼ�а�����·\n");
			else
				printf("\n��ͼ�в�������·\n");
			system("pause");
			break;
		case 4:
			showgraph(&G);
			printf("\n��������ֹ����������:\n");
			scanf("%s%s", c1, c2);
			printf("���д� %s �� %s �ļ�·���Լ�·�����ȣ�\n", c1, c2);
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
		printf("�ļ���ʧ��\n");
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

void allpath(GH *G, int *path, int *visit, int i, int j, int top, int len) //�ݹ�������е�·���������
{
	if (i == j)
	{
		for (int k = 0; k < top; k++)
		{
			printf("%s  ", G->vexname[path[k]]);
		}
		printf("\t·������Ϊ%d\n", len);
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

void findpath(GH *G, char *start, char *end) //Ѱ�Ҽ�·������
{

	int i, j, top = 0, len = 0;
	int path[G->vexnum], visit[G->vexnum] = {0};
	i = findvex(start, G);
	j = findvex(end, G);
	path[top] = i;
	visit[i] = 1;
	allpath(G, path, visit, i, j, top + 1, len);
}

int iscycle(GH *G) //�ж�ͼ���Ƿ��л�·���з���1�����򷵻�0
{
	int visit[G->vexnum] = {0};
	int D[G->vexnum] = {0};
	int stack[G->vexnum], top = -1, index;
	for (int i = 0; i < G->vexnum; i++) //ͳ��ÿ����Ķ�
	{
		for (int j = 0; j < G->vexnum; j++)
		{
			if (G->A[i][j] < maxx)
				D[i]++;
		}
	}
	for (int i = 0; i < G->vexnum; i++)
	{
		if (D[i] <= 1) //�����ж�С�ڵ���1�ĵ���ջ
		{
			top++;
			stack[top] = i;
			visit[i] = 1; //����Ϊ�Ѿ����ʹ���
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
					visit[j] = 1; //����Ϊ�Ѿ����ʹ���
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

int isconnect(GH *G) //�ж�ͼ�Ƿ���ͨ���Ƿ���1�����򷵻�0
{
	//�㷨������һ��dfs����,�����ܱ������е㼴��
	int visit[G->vexnum] = {0};
	int stack[G->vexnum], top = -1;
	int index;
	stack[++top] = 0; //��0�ڵ���ջ
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
