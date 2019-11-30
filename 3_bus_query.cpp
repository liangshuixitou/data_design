//������·ͼ

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

typedef struct station
{
    char bus_number[20];  //��������
    int index;            //���ڽӱ��еı��
    struct station *next; //��һվ
} ST;

typedef struct BusGragh
{
    int stations_number; //����վ̨������
    ST *N;               //�ڽӱ�洢
    char **st_name;      //�洢��Ӧ��վ̨����
} BG;

typedef struct st
{
    int before;
    int index;
} BFS_N; //BFS������ʱ��������·��

void creatGragh(BG *G);                      //����������·ͼ
int findSt(BG *G, char *);                   //Ѱ�Ҹó�վ�Ƿ������ͼ��
int is_in(BG *G, int i, int j);              //�ж�����վ���Ƿ�֮ǰ�Ѿ�����
void short_way(BG *G, char *st1, char *st2); //Ѱ������վ̨֮�����̳˳�·�ߣ�����վ�����٣�

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
    // cout << "�����������յ㣺" << endl;
    // cin >> st1 >> st2;
    // short_way(G, st1, st2);
    system("pause");
    return 0;
}

void creatGragh(BG *G) //��������
{
    G->stations_number = 0;
    G->st_name = (char **)malloc(sizeof(char *) * 6000);
    G->N = (ST *)malloc(sizeof(ST) * 6000);
    for (int i = 1; i < 6000; i++) //С��6000��վ̨
    {
        G->st_name[i] = (char *)malloc(sizeof(char) * 30);
        G->N[i].next = nullptr;
    }
    char temp_station_name[50];     //��ǰվ̨
    char temp_station_name_pre[50]; //��ǰ������ǰһ��վ̨
    char temp_bus[30];              //��¼ĳһ�еĹ�����Ϣ
    char temp_sy = ',';             //��Ϊ�����Ļ��з���־
    ST *temp_station;
    int flag = 0; //��¼�Ƿ�δ��һ������վ̨
    fstream f;
    f.open("03.�Ͼ�������·.txt", ios::in);
    if (f.fail())
    {
        cout << "������Ϣ�ļ���ʧ��" << endl;
        exit(0);
    }
    while (1)
    {
        flag = 0;
        f >> temp_bus;
        if (f.eof())
            break;
        f.get(temp_sy);
        while (temp_sy == ' ') //�����ո�
            f.get(temp_sy);
        while (1)
        {
            int ch_pos = 0;
            while (temp_sy != ',' && temp_sy != '\n') //��','Ϊֹ
            {
                temp_station_name[ch_pos++] = temp_sy;
                f.get(temp_sy);
            }
            temp_station_name[ch_pos] = '\0';
            int pos = findSt(G, temp_station_name);
            if (!pos) //��վ��δ������
            {
                G->stations_number++;
                strcpy(G->st_name[G->stations_number], temp_station_name);
            }
            if (flag) //�ǵ�һ��վ��
            {
                int i = findSt(G, temp_station_name_pre);
                int j = findSt(G, temp_station_name);
                if (!is_in(G, i, j)) //ԭ��������
                {
                    temp_station = (ST *)malloc(sizeof(ST)); //����ͼ
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
            strcpy(temp_station_name_pre, temp_station_name); //���и���
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
//     //����BFS��������
//     int visit[G->stations_number] = {0};
//     BFS_N temp_s;
//     int top = -1, base = -1;
//     temp_s.before = -1;
//     temp_s.
//     sk[++top] = st_1; //��������
//     while(base!=top)
//     {

//     }
// }