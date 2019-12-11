#include <iostream>
#include <windows.h>
using namespace std;

//在m个元素的数组中找到n个元素的组合

void print_list(int list[], int num[], int m)
{
    for (int i = 0; i < m; i++)
    {
        if (num[i])
        {
            printf("%d", list[i]);
        }
    }
    cout << endl;
}

bool conbination(int num[], int m)
{
    int temp;
    for (int i = 0; i < m - 1; i++)
    {
        if (num[i] && !num[i + 1])
        {
            num[i] = 0;
            num[i + 1] = 1;
            return 0;
        }
    }
    return 1;
}

int main()
{
    int m, n;
    scanf("%d%d", &n, &m);
    int list[m], num[m];
    for (int i = 0; i < n; i++)
        num[i] = 1;
    for (int i = n; i < m; i++)
        num[i] = 0;
    for (int i = 0; i < m; i++)
    {
        list[i] = i + 1;
    }
    while (1)
    {
        print_list(list, num, m);
        if (conbination(num, m))
        {
            break;
        }
    }
    system("pause");
}