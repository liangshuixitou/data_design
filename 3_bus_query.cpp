//公交线路图

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

typedef struct station
{
    char bus_number[20];  //公交车号
    int index;            //在邻接表中的编号
    struct station *next; //下一站
} ST;

typedef struct BusGragh
{
    int stations_number; //公交站台的数量
    ST *N;               //邻接表存储
    char **st_name;      //存储对应的站台名字
} BG;

typedef struct st
{
    int before;
    int index;
} BFS_N; //BFS遍历的时候便于输出路径

void creatGragh(BG *G);                      //创建公交线路图
int findSt(BG *G, char *);                   //寻找该车站是否存在于图中
int is_in(BG *G, int i, int j);              //判断两个站点是否之前已经相连
void short_way(BG *G, char *st1, char *st2); //寻找两个站台之间的最短乘车路线（经过站点最少）

int main()
{
    BG *G = (BG *)malloc(sizeof(BG));
    char st1[50];
    char st2[50];
    ST *p;
    creatGragh(G);
    for (int i = 1; i <= 5126; i++)
    {
        cout << G->st_name[i] << "----";
        p = G->N[i].next;
        while (p)
        {
            cout << G->st_name[p->index] << "(" << p->bus_number << ")";
            p = p->next;
        }
        cout << endl;
    }
    // cout << "请输入起点和终点：" << endl;
    // cin >> st1 >> st2;
    // short_way(G, st1, st2);
    system("pause");
    return 0;
}

void creatGragh(BG *G) //创建函数
{
    G->stations_number = 0;
    G->st_name = (char **)malloc(sizeof(char *) * 6000);
    G->N = (ST *)malloc(sizeof(ST) * 6000);
    for (int i = 1; i < 6000; i++) //小于6000个站台
    {
        G->st_name[i] = (char *)malloc(sizeof(char) * 30);
        G->N[i].next = nullptr;
    }
    char temp_station_name[50];     //当前站台
    char temp_station_name_pre[50]; //当前公交的前一个站台
    char temp_bus[30];              //记录某一行的公交信息
    char temp_sy = ',';             //作为结束的换行符标志
    ST *temp_station;
    int flag = 0; //记录是否未第一个公交站台
    fstream f;
    f.open("03.南京公交线路.txt", ios::in);
    if (f.fail())
    {
        cout << "公交信息文件打开失败" << endl;
        exit(0);
    }
    while (1)
    {
        flag = 0;
        f >> temp_bus;
        if (f.eof())
            break;
        f.get(temp_sy);
        while (temp_sy == ' ') //跳过空格
            f.get(temp_sy);
        while (1)
        {
            int ch_pos = 0;
            while (temp_sy != ',' && temp_sy != '\n') //到','为止
            {
                temp_station_name[ch_pos++] = temp_sy;
                f.get(temp_sy);
            }
            temp_station_name[ch_pos] = '\0';
            int pos = findSt(G, temp_station_name);
            if (!pos) //该站并未被创建
            {
                G->stations_number++;
                strcpy(G->st_name[G->stations_number], temp_station_name);
            }
            if (flag) //非第一个站点
            {
                int i = findSt(G, temp_station_name_pre);
                int j = findSt(G, temp_station_name);
                if (!is_in(G, i, j)) //原本不存在
                {
                    temp_station = (ST *)malloc(sizeof(ST)); //无向图
                    temp_station->index = j;
                    temp_station->next = G->N[i].next;
                    G->N[i].next = temp_station;
                    strcpy(temp_station->bus_number, temp_bus);

                    temp_station = (ST *)malloc(sizeof(ST));
                    temp_station->index = i;
                    temp_station->next = G->N[j].next;
                    G->N[j].next = temp_station;
                    strcpy(temp_station->bus_number, temp_bus);
                }
            }
            flag = 1;
            strcpy(temp_station_name_pre, temp_station_name); //进行更替
            if (temp_sy == '\n')
                break;
            else
                f.get(temp_sy);
        }
        // cout << endl;
    }
}

int findSt(BG *G, char *name)
{
    for (int i = 1; i <= G->stations_number; i++)
    {
        if (strcmp(G->st_name[i], name) == 0)
            return i;
    }
    return 0;
}

int is_in(BG *G, int i, int j)
{
    ST *p;
    p = G->N[i].next;
    while (p)
    {
        if (p->index == j)
            return 1;
        p = p->next;
    }
    return 0;
}

// void short_way(BG *G, char *st1, char *st2)
// {
//     int st_1 = findSt(G, st1);
//     int st_2 = findSt(G, st2);
//     //采用BFS遍历即可
//     int visit[G->stations_number] = {0};
//     BFS_N temp_s;
//     int top = -1, base = -1;
//     temp_s.before = -1;
//     temp_s.
//     sk[++top] = st_1; //将起点入队
//     while(base!=top)
//     {

//     }
// }