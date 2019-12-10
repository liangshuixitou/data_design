///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ��
//1�����ڽӱ�������ͼ��
//2����Ƶݹ��㷨Ѱ������ͨ��ָ���ڵ�ļ򵥻�·
//3������㷨�жϴӶ���u������v�Ƿ����·��������ʱ�临�Ӷȣ�
//4������㷨�������ж������ȣ�����ʱ�临�Ӷȣ�
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct arcnode
{
	int index; //�ڽӵ����
	struct arcnode *next;
} AR;

typedef struct MyGraph
{
	int type;			//0����ʾ����ͼ��1��ʾ����ͼ
	int arcnum, vexnum; //ͼ�бߵĸ����Լ��������
	char **vexname;		//��Ŷ������Ķ�ά����
	AR *N;				//����ڽӱ�ͷ��������
} GH;

int findvex(char *s, GH *G);									 //ȷ������s��Ӧ�����
void creatgraph(GH *G);											 //���ڽӱ����ʽ����ͼ
void showgraph(GH *G);											 //���ڽӱ����ʽ��ʾͼ
void findpath(GH *G, char *start);								 //Ѱ�����о�������start�ļ�·��
void allpath(GH *G, int *stack, int *visit, int top, int index); //��Ϊ���溯���ĸ�����)
int ispath(GH *G, char *start, char *end);						 //�жϴӶ���start������end�Ƿ����·�������ڷ���1�����򷵻�0
void indegree(GH *G);											 //���㲢��ʾ���ͼ��ÿ����������
int menu_select();

int menu_select()
{
	char i;
	do
	{
		system("cls");
		printf("1.��������ͼ���ڽӱ�\n");
		printf("2.������о���ָ������ļ򵥻�·\n");
		printf("3.�ж���������֮���Ƿ����·��\n");
		printf("4.������ж�������\n");
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
			printf("�����붥����:\n");
			scanf("%s", c1);
			printf("���о���%s�ļ򵥻�·��:\n", c1);
			findpath(&G, c1);
			system("pause");
			break;
		case 3:
			showgraph(&G);
			printf("��������ֹ����������:\n");
			scanf("%s%s", c1, c2);
			if (ispath(&G, c1, c2))
				printf("�Ӷ���%s������%s����·��\n", c1, c2);
			else
				printf("�Ӷ���%s������%s������·��\n", c1, c2);
			system("pause");
			break;
		case 4:
			showgraph(&G);
			printf("\nͼ�����ж�������:\n");
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

int findvex(char *s, GH *G) //���ݶ�����ȷ���ö���ı��
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
	char temp_name1[5]; //���ڱߵ��ڵ����֡�������ʱ�洢
	char temp_name2[5];
	AR *temp_node;
	FILE *fp = fopen(filename, "r");
	int i, j;
	if (!fp)
	{
		printf("�ļ��򿪴���\n");
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
		temp_node->next = G->N[i].next; //�����ڽӱ��ͬһ�ڵ���ڽӵ��Ⱥ�������
		G->N[i].next = temp_node;
		if (!G->type) //����ͼ
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

void findpath(GH *G, char *start) //Ѱ�����о�������start�ļ򵥻�·
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
	if (index == stack[0] && top != 1) //�ҵ���·�������,�ҷ�ֹ��һ�εݹ��ʱ�����
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
				stack[top] = p->index; //ע�⵽top��û�м�1���������滻
				visit[p->index] = 1;
				allpath(G, stack, visit, top + 1, p->index); //�ݹ麯��
				visit[p->index] = 0;						 //�����޷��ظ�����
			}
			p = p->next;
		}
	}
}

void indegree(GH *G) //���㲢��ʾ���ͼ��ÿ����������
{
	int *innum = (int *)malloc(sizeof(int) * G->vexnum); //ͳ��ÿ��������
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
	printf("���нڵ���������\n");
	for (i = 0; i < G->vexnum; i++)
	{
		printf("%s", G->vexname[i]);
		printf("%4d\n", innum[i]);
	}
	free(innum);
}

int ispath(GH *G, char *start, char *end) //�жϴӶ���start������end�Ƿ����·�������ڷ���1�����򷵻�0
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
			return 1; //��ջ��Ϊ���ʣ������ҵ�һ��·����ֱ�ӷ���1
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
	return 0; //δ���ҵ�·��
}
