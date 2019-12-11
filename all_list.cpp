#include <iostream>
#include <vector>
using namespace std;

//递归实现全排列的算法
// void swap(int &a, int &b)
// {
//     int temp = a;
//     a = b;
//     b = temp;
// }
// void perm(int list[], int low, int high)
// {
//     if (low == high)
//     { //当low==high时,此时list就是其中一个排列,输出list
//         for (int i = 0; i <= low; i++)
//             cout << list[i];
//         cout << endl;
//     }
//     else
//     {
//         for (int i = low; i <= high; i++)
//         { //每个元素与第一个元素交换
//             swap(list[i], list[low]);
//             perm(list, low + 1, high); //交换后,得到子序列,用函数perm得到子序列的全排列
//             swap(list[i], list[low]);  //最后,将元素交换回来,复原,然后交换另一个元素
//         }
//     }
// }

//非递归实现全排列的算法

bool check(int n, vector<int> &a) //n表示需要检查的数字，site表示n所在位置
{
    for (int i = 0; i < a.size(); i++)
    {
        if (a.at(i) == n)
            return 0;
    }
    return 1;
}

void perm(int n)
{
    vector<int> q; //初始时候分配20个元素，并且赋予零值
    int k = 0;     //记录空栈数目
    int num = 0;   //记录全面排列的数目
    int temp = 1;  //临时接受弹出栈的int数值
    q.push_back(1);
    while (k < n)
    {
        temp++;
        if (q.size() == n)
        {
            for (vector<int>::iterator i = q.begin(); i != q.end(); ++i)
            {
                cout << *i << " ";
            }
            cout << endl;
            q.pop_back();
            temp = q.back(); //弹出最后一个元素
            q.pop_back();
            temp++;
        }
        if (temp > n)
        {
            temp = q.back(); //整个回溯过程
            q.pop_back();
        }
        else if (temp <= n && check(temp, q))
        {
            q.push_back(temp);
            temp = 0;
        }
        if (q.size() == 0)
        {
            k++;
        }
    }
}

main()
{
    int n;
    scanf("%d", &n);
    perm(n);
    system("pause");
}