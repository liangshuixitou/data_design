//���˿��Ƽ���24��

#include <windows.h>
#include <math.h>
#include <iostream>
using namespace std;

float cal_s(float a, float b, int flag); //����flag��ֵ���м���
void prt(float a, float b, float c, float d, int i, int j, int k);
int perm(float num_f[]); //ȫ���еݹ�
bool check(int stack[], int temp, int top);
void prt_symbol(int i);

int all_1_flag = 0; //ȫ�Ӻ�
int all_3_flag = 0; //ȫ�˺�

//������git
int main()
{
    float num_f[4];
    cin >> num_f[0] >> num_f[1] >> num_f[2] >> num_f[3];
    while (1)
    {
        if (!perm(num_f))
            cout << -1;
        cin >> num_f[0] >> num_f[1] >> num_f[2] >> num_f[3];
    }
    system("pause");
    return 0;
}

float cal_s(float a, float b, int flag) //����flag��ֵ���м���
{
    switch (flag)
    {
    case 0:
        return a + b;
    case 1:
        return a - b;
    case 2:
        return a * b;
    case 3:
        return a / b;
    default:
        return -1;
    }
}
void prt_symbol(int i)
{
    switch (i)
    {
    case 0:
        cout << "+";
        break;
    case 1:
        cout << "-";
        break;
    case 2:
        cout << "*";
        break;
    case 3:
        cout << "/";
        break;
    }
}
void prt_1(float a, float b, float c, float d, int i, int j, int k)
{
    if (j < 2 && k >= 2)
        cout << "(";
    if (i < 2 && j >= 2)
        cout << "(";
    cout << a;
    prt_symbol(i);
    cout << b;
    if (i < 2 && j >= 2)
        cout << ")";
    prt_symbol(j);
    cout << c;
    if (j < 2 && k >= 2)
        cout << ")";
    prt_symbol(k);
    cout << d << " = 24" << endl;
}
void prt_2(float a, float b, float c, float d, int i, int j, int k)
{
    if (i < 2 && j >= 2)
        cout << "(";
    cout << a;
    prt_symbol(i);
    cout << b;
    if (i < 2 && j >= 2)
        cout << ")";
    prt_symbol(j);
    if ((k < 2 && j >= 2) || j == 1)
        cout << "(";
    cout << c;
    prt_symbol(k);
    cout << d;
    if ((k < 2 && j >= 2) || j == 1)
        cout << ")";
    cout << " = 24" << endl;
}
int Cal(float a, float b, float c, float d) //�����Ƿ���Թ���24��
{
    float temp_r1, temp_r2, temp_r3;
    int F = 0;
    for (int i = 0; i < 4; i++)
    {
        temp_r1 = cal_s(a, b, i);
        for (int j = 0; j < 4; j++)
        {
            temp_r2 = cal_s(temp_r1, c, j);
            for (int k = 0; k < 4; k++)
            {
                temp_r3 = cal_s(temp_r2, d, k);
                if (fabs(temp_r3 - 24) < 0.01)
                {
                    prt_1(a, b, c, d, i, j, k); //�������
                    F = 1;                      //�ҵ���������ʽ
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        temp_r1 = cal_s(a, b, i);
        for (int k = 0; k < 4; k++)
        {
            temp_r2 = cal_s(c, d, k);
            for (int j = 0; j < 4; j++) //�м�������
            {
                temp_r3 = cal_s(temp_r1, temp_r2, j);
                if (fabs(temp_r3 - 24) < 0.01)
                {
                    prt_2(a, b, c, d, i, j, k); //�������
                    F = 1;                      //�ҵ���������ʽ
                }
            }
        }
    }
    return F; //��ٽ���
}
bool check(int stack[], int temp, int top)
{
    for (int i = 0; i < top; i++)
    {
        if (stack[i] == temp)
            return false;
    }
    return true;
}
int perm(float num_f[]) //ȫ���еݹ�
{
    int f = 0; //�жϵ�ǰ�Ƿ��ҵ����������ı��ʽ
    int temp = 0;
    int k = 0; //��¼��ջ����
    int stack[4];
    int top = 0;
    stack[top] = temp;
    top++;
    while (k < 4)
    {
        temp++;
        if (top == 4)
        {
            if (Cal(num_f[stack[0]], num_f[stack[1]], num_f[stack[2]], num_f[stack[3]]) == 1)
                f = 1; //�ҵ�
            // cout << num_f[stack[0]] << num_f[stack[1]] << num_f[stack[2]] << num_f[stack[3]] << endl;
            top--;
            top--;
            temp = stack[top];
            temp++;
        }
        if (temp >= 4)
        {
            top--;
            temp = stack[top];
        }
        else if (check(stack, temp, top))
        {
            stack[top] = temp;
            top++;
            temp = -1;
        }
        if (top == 0)
            k++;
    }
    return f;
}