#include <iostream>
#include <vector>
using namespace std;

//�ݹ�ʵ��ȫ���е��㷨
// void swap(int &a, int &b)
// {
//     int temp = a;
//     a = b;
//     b = temp;
// }
// void perm(int list[], int low, int high)
// {
//     if (low == high)
//     { //��low==highʱ,��ʱlist��������һ������,���list
//         for (int i = 0; i <= low; i++)
//             cout << list[i];
//         cout << endl;
//     }
//     else
//     {
//         for (int i = low; i <= high; i++)
//         { //ÿ��Ԫ�����һ��Ԫ�ؽ���
//             swap(list[i], list[low]);
//             perm(list, low + 1, high); //������,�õ�������,�ú���perm�õ������е�ȫ����
//             swap(list[i], list[low]);  //���,��Ԫ�ؽ�������,��ԭ,Ȼ�󽻻���һ��Ԫ��
//         }
//     }
// }

//�ǵݹ�ʵ��ȫ���е��㷨

bool check(int n, vector<int> &a) //n��ʾ��Ҫ�������֣�site��ʾn����λ��
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
    vector<int> q; //��ʼʱ�����20��Ԫ�أ����Ҹ�����ֵ
    int k = 0;     //��¼��ջ��Ŀ
    int num = 0;   //��¼ȫ�����е���Ŀ
    int temp = 1;  //��ʱ���ܵ���ջ��int��ֵ
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
            temp = q.back(); //�������һ��Ԫ��
            q.pop_back();
            temp++;
        }
        if (temp > n)
        {
            temp = q.back(); //�������ݹ���
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