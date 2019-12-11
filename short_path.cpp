#include <stdio.h>
#include <windows.h>
#define maxx 9999999

typedef struct MyGraph
{
    int type;           //0，表示无向网，1表示有向网
    int arcnum, vexnum; //图中边的个数以及顶点个数
    char **vexname;     //存放顶点名的二维数组
    int **A;            //邻接矩阵，A[i][j]表示i号顶点与j号顶点之间边的权值，若i,j之间没有边，则A[i][j]取值无穷大
} GH;

int findvex(char *s, GH *G);                    //确定顶点s对应的序号
void creatgraph(GH *G);                         //以邻接矩阵的形式创建图
void showgraph(GH *G);                          //以邻接表的形式显示图
void dijikstra(GH *G, int n);                   //dijkstra算法输出某个点到所有点的最短路径
void print_path1(GH *G, int before[], int i);   //递归输出路径
void floyd(GH *G);                              //弗洛伊德算法求所有点之间的最短路径
void print_path2(GH *G, int **g, int u, int v); //递归输出路径
int main()
{
    GH *G = (GH *)malloc(sizeof(GH));
    creatgraph(G);
    printf("原图如下:\n");
    showgraph(G);
    printf("Dijikstra算法输出任意两点的最短路径:\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("输出%s到各点的最短路径:\n", G->vexname[i]);
        dijikstra(G, i);
        putchar(10);
    }
    system("pause");
    system("cls");
    printf("原图如下:\n");
    showgraph(G);
    floyd(G);
    system("pause");
    return 0;
}

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
    char filename[] = "graph.txt";
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
        G->A[i][j] = temp_num;
        if (!G->type) //无向图
            G->A[j][i] = temp_num;
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

void dijikstra(GH *G, int n)
{
    int visit[G->vexnum] = {0}; //未被确定的点
    int before[G->vexnum];      //每个点的最短路径中的前驱
    int len[G->vexnum];         //每个点到起始点的距离
    for (int i = 0; i < G->vexnum; i++)
    {
        visit[i] = 0;
        before[i] = -1;
        len[i] = maxx;
    }
    len[n] = 0;
    visit[n] = 1;
    int temp = n, min, min_i; //当前的永久标记
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
        {
            if (!visit[j] && len[j] > len[temp] + G->A[temp][j])
            {
                len[j] = len[temp] + G->A[temp][j];
                before[j] = temp;
            }
        }
        min = maxx;
        min_i = -1;
        for (int k = 0; k < G->vexnum; k++)
        {
            if (len[k] < min && !visit[k])
            {
                min = len[k];
                min_i = k;
            }
        }
        if (min_i == -1)
            break;
        temp = min_i;    //新标记
        visit[temp] = 1; //已经被作为标记了
    }
    for (int i = 0; i < G->vexnum; i++)
    {
        if (len[i] < maxx && i != n)
        {
            printf("%s到%s的最短路径为 ", G->vexname[n], G->vexname[i]);
            print_path1(G, before, i);
            printf("\t其权为%d\n", len[i]);
        }
        else if (len[i] == maxx)
        {
            printf("%s到%s不存在路径", G->vexname[n], G->vexname[i]);
            printf("\t\t其权为max\n");
        }
    }
}

void print_path1(GH *G, int before[], int i)
{
    if (before[i] == -1)
        printf("%s ", G->vexname[i]);
    else
    {
        print_path1(G, before, before[i]);
        printf("%s ", G->vexname[i]);
    }
}

void floyd(GH *G)
{
    int temp_g[G->vexnum][G->vexnum];
    int **temp_d = (int **)malloc(sizeof(int *) * G->vexnum);
    for (int i = 0; i < G->vexnum; i++)
    {
        temp_d[i] = (int *)malloc(sizeof(int) * G->vexnum);
        for (int j = 0; j < G->vexnum; j++)
        {
            temp_g[i][j] = G->A[i][j];
            temp_d[i][j] = j; //记录路径信息
        }
    }

    for (int w = 0; w < G->vexnum; w++)
    {
        for (int u = 0; u < G->vexnum; u++)
        {
            for (int v = 0; v < G->vexnum; v++)
            {
                if (temp_g[u][w] + temp_g[w][v] < temp_g[u][v] && u != v)
                {
                    temp_g[u][v] = temp_g[u][w] + temp_g[w][v];
                    temp_d[u][v] = w; //记录路径
                }
            }
        }
    }
    printf("floyd算法输出任意两点间的最短路径:\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("\n输出%s到各点的最短路径:\n", G->vexname[i]);
        for (int j = 0; j < G->vexnum; j++)
        {
            if (i != j)
            {
                if (temp_g[i][j] < maxx)
                {
                    printf("%s到%s的最短路径为 ", G->vexname[i], G->vexname[j]);
                    printf("%s ", G->vexname[i]);
                    print_path2(G, temp_d, i, j);
                    printf("%s ", G->vexname[j]);
                    printf("\t其权为%d\n", temp_g[i][j]);
                }
                else if (temp_g[i][j] == maxx)
                {
                    printf("%s到%s不存在路径", G->vexname[i], G->vexname[j]);
                    printf("\t\t其权为max\n");
                }
            }
        }
    }
}

void print_path2(GH *G, int **g, int u, int v)
{
    if (g[u][v] == v)
        return;
    else
    {
        print_path2(G, g, u, g[u][v]);
        printf("%s ", G->vexname[g[u][v]]);
        print_path2(G, g, g[u][v], v);
    }
}