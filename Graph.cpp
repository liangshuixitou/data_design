#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct arcnode //邻接表
{
    int weight; //权值
    struct arcnode *next;
    int index; //编号
} AR;
typedef struct MyGraph //图
{
    int type;                //0表示无向图，1表示有向图
    int arc_num, vertex_num; //边和点的数量
    char **vertex_name;      //点的名称
    AR *N;                   //邻接表
    int **A;                 //邻接矩阵
} GH;

int find_vertex(char *s, GH *G) //在邻接表中寻找指定点，返回其编号
{
    int i, M;
    M = G->vertex_num;
    for (i = 0; i < M; i++)
    {
        if (strcmp(s, G->vertex_name[i]) == 0)
            return i;
    }
    printf("read file error\n");
    exit(-1);
}

void create_list(GH *G) //读取文件，创建图的邻接表和邻接矩阵
{
    FILE *fp;
    char c1[4], c2[4];
    AR *p;
    int i, j, k;
    fp = fopen("graph.txt", "rb");
    if (fp == NULL)
    {
        printf("can not open file\n");
        exit(0);
    }
    fscanf(fp, "%d", &k);
    G->arc_num = 0;
    G->type = 0;
    G->vertex_num = k;
    G->A = (int **)malloc(k * sizeof(int *));
    G->vertex_name = (char **)malloc(k * sizeof(char *));
    G->N = (AR *)malloc(k * sizeof(AR));
    for (i = 0; i < k; i++) //创建和初始化邻接表和邻接矩阵
    {
        fscanf(fp, "%s", c1);
        G->vertex_name[i] = (char *)malloc(strlen(c1) * sizeof(char));
        strcpy(G->vertex_name[i], c1);
        G->N[i].next = NULL;
        G->A[i] = (int *)malloc(k * sizeof(int));
        for (j = 0; j < k; j++)
            G->A[i][j] = 0;
    }
    while (fscanf(fp, "%s%s", c1, c2) != EOF)
    {
        G->arc_num++;
        i = find_vertex(c1, G);
        j = find_vertex(c2, G);
        p = (AR *)malloc(sizeof(AR));
        p->index = j;
        p->next = G->N[i].next;
        G->N[i].next = p;
        G->A[i][j] = 1;
        if (!G->type) //无向图
        {
            p = (AR *)malloc(sizeof(AR));
            p->index = i;
            p->next = G->N[j].next;
            G->N[j].next = p;
            G->A[j][i] = 1;
        }
    }
    fclose(fp);
}

void DFS(GH *G, int index, int *visit) //深度优先搜索
{
    AR *p;
    printf("%s ", G->vertex_name[index]);
    visit[index] = 1;
    p = G->N[index].next;
    while (p)
    {
        if (!visit[p->index])
            DFS(G, p->index, visit);
        p = p->next;
    }
}

void DFS_visit(GH *G) //深度优先搜索主调函数
{
    int *visit, i;
    visit = (int *)malloc((G->vertex_num) * sizeof(int));
    for (i = 0; i < G->vertex_num; i++)
        visit[i] = 0;
    for (i = 0; i < G->vertex_num; i++)
    {
        if (!visit[i])
            DFS(G, i, visit);
    }
    free(visit);
}

void BFS(GH *G, int index, int *visit) //广度优先搜索
{
    int *q, front = 0, rear = 0, i;
    AR *p;
    q = (int *)malloc((G->vertex_num) * sizeof(int));
    q[rear] = index;
    visit[index] = 1;
    rear++;
    while (front != rear)
    {
        i = q[front];
        front++;
        printf("%s ", G->vertex_name[i]);
        p = G->N[i].next;
        while (p)
        {
            if (!visit[p->index])
            {
                q[rear] = p->index;
                rear++;
                visit[p->index] = 1;
            }
            p = p->next;
        }
    }
}

void BFS_visit(GH *G) //广度优先搜索主调函数
{
    int *visit, i;
    visit = (int *)malloc((G->vertex_num) * sizeof(int));
    for (i = 0; i < G->vertex_num; i++)
        visit[i] = 0;
    for (i = 0; i < G->vertex_num; i++)
    {
        if (!visit[i])
            BFS(G, i, visit);
    }
    free(visit);
}

void allpath(GH *G, int start, int end, int *path, int *visit, int length) //寻找简单路径
{
    AR *p;
    int i;
    if (start == end)
    {
        for (i = 0; i < length; i++)
            printf("%s ", G->vertex_name[path[i]]);
        printf("\n");
    }
    else
    {
        p = G->N[start].next;
        while (p)
        {
            if (!visit[p->index])
            {
                path[length] = p->index;
                visit[p->index] = 1;
                allpath(G, p->index, end, path, visit, length + 1);
                visit[p->index] = 0;
            }
            p = p->next;
        }
    }
}

void findpath(GH *G, char *start, char *end) //寻找简单路径主调函数
{
    int *visit, *path, i, j;
    visit = (int *)malloc((G->vertex_num) * sizeof(int));
    path = (int *)malloc((G->vertex_num) * sizeof(int));
    for (i = 0; i < G->vertex_num; i++)
        visit[i] = 0;
    i = find_vertex(start, G);
    j = find_vertex(end, G);
    path[0] = i;
    visit[i] = 1;
    allpath(G, i, j, path, visit, 1);
}