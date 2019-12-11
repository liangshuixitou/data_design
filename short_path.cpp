#include <stdio.h>
#include <windows.h>
#define maxx 9999999

typedef struct MyGraph
{
    int type;           //0����ʾ��������1��ʾ������
    int arcnum, vexnum; //ͼ�бߵĸ����Լ��������
    char **vexname;     //��Ŷ������Ķ�ά����
    int **A;            //�ڽӾ���A[i][j]��ʾi�Ŷ�����j�Ŷ���֮��ߵ�Ȩֵ����i,j֮��û�бߣ���A[i][j]ȡֵ�����
} GH;

int findvex(char *s, GH *G);                    //ȷ������s��Ӧ�����
void creatgraph(GH *G);                         //���ڽӾ������ʽ����ͼ
void showgraph(GH *G);                          //���ڽӱ����ʽ��ʾͼ
void dijikstra(GH *G, int n);                   //dijkstra�㷨���ĳ���㵽���е�����·��
void print_path1(GH *G, int before[], int i);   //�ݹ����·��
void floyd(GH *G);                              //���������㷨�����е�֮������·��
void print_path2(GH *G, int **g, int u, int v); //�ݹ����·��
int main()
{
    GH *G = (GH *)malloc(sizeof(GH));
    creatgraph(G);
    printf("ԭͼ����:\n");
    showgraph(G);
    printf("Dijikstra�㷨���������������·��:\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("���%s����������·��:\n", G->vexname[i]);
        dijikstra(G, i);
        putchar(10);
    }
    system("pause");
    system("cls");
    printf("ԭͼ����:\n");
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
        G->A[i][j] = temp_num;
        if (!G->type) //����ͼ
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
    int visit[G->vexnum] = {0}; //δ��ȷ���ĵ�
    int before[G->vexnum];      //ÿ��������·���е�ǰ��
    int len[G->vexnum];         //ÿ���㵽��ʼ��ľ���
    for (int i = 0; i < G->vexnum; i++)
    {
        visit[i] = 0;
        before[i] = -1;
        len[i] = maxx;
    }
    len[n] = 0;
    visit[n] = 1;
    int temp = n, min, min_i; //��ǰ�����ñ��
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
        temp = min_i;    //�±��
        visit[temp] = 1; //�Ѿ�����Ϊ�����
    }
    for (int i = 0; i < G->vexnum; i++)
    {
        if (len[i] < maxx && i != n)
        {
            printf("%s��%s�����·��Ϊ ", G->vexname[n], G->vexname[i]);
            print_path1(G, before, i);
            printf("\t��ȨΪ%d\n", len[i]);
        }
        else if (len[i] == maxx)
        {
            printf("%s��%s������·��", G->vexname[n], G->vexname[i]);
            printf("\t\t��ȨΪmax\n");
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
            temp_d[i][j] = j; //��¼·����Ϣ
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
                    temp_d[u][v] = w; //��¼·��
                }
            }
        }
    }
    printf("floyd�㷨����������������·��:\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("\n���%s����������·��:\n", G->vexname[i]);
        for (int j = 0; j < G->vexnum; j++)
        {
            if (i != j)
            {
                if (temp_g[i][j] < maxx)
                {
                    printf("%s��%s�����·��Ϊ ", G->vexname[i], G->vexname[j]);
                    printf("%s ", G->vexname[i]);
                    print_path2(G, temp_d, i, j);
                    printf("%s ", G->vexname[j]);
                    printf("\t��ȨΪ%d\n", temp_g[i][j]);
                }
                else if (temp_g[i][j] == maxx)
                {
                    printf("%s��%s������·��", G->vexname[i], G->vexname[j]);
                    printf("\t\t��ȨΪmax\n");
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