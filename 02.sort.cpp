///////////////////////////////////////////////////////////////////////////////////////////
// ��ĿҪ���������n�����������ܻ����ظ�Ԫ�أ���������BST��Ƹ�Ч�㷨�������������
//          ˳��������д��ڵ���k������
//          1���������BST�����ݽṹ�����������Ҫ������Ĺ��ܺ�������Ҫ�޸�main����
//          2�����ݹ�ģn�Լ�k���Ӽ�������
//          3��������ɵ����ݣ���ֵ��Ҫ����100��������Ժ͹۲�������Ҫ�Դ�Ϊ��������㷨
//
////////////////////////////////////////////////////////////////////////////////////////////
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct node
{
	int data;
	struct node *left, *right;
} BST;

BST *createbst(int n);		 //����BST
BST *insnode(BST *T, int x); //��BST�в������ݵ�x,�����ظ��ڵ�ָ��
void showbst(BST *T);		 //��ʾBST
void output(int n, int k);   //��n��������У�����BST�������������˳��������д��ڵ���k������
BST *delbst(BST *T);		 //����BST

main()
{
	int n, k;
	printf("���������ݹ�ģn�Լ���Ҫ���ҵ��������е���Сֵk:\n");
	scanf("%d%d", &n, &k);
	while (n > 0 && k > 0)
	{
		+printf("���д��ڵ���%d��������:\n", k);
		output(n, k);
		printf("���������ݹ�ģn�Լ���Ҫ���ҵ��������е����ֵk:\n");
		scanf("%d%d", &n, &k);
	}
	system("pause");
	return 0;
}

void output(int n, int k)
{
	BST *T;
	BST *stack[n], *p;
	int top = -1;		   //������ұ߽ڵ�Ȼ������м䣬��������ߣ����ֵ��������
	int flag = 0, max = 0; //�ж��������Ƿ����
	T = createbst(n);
	printf("�������ݹ�ģn�����õ�BSTΪ\n");
	showbst(T);
	putchar(10);
	p = T;
	if (!p)
		printf("BST����ʧ��\n");
	while (top >= 0 || p)
	{
		while (p)
		{
			top++;
			stack[top] = p;
			p = p->right;
		}
		p = stack[top];
		top--;
		if (p->data >= k)
		{
			if (!flag)
			{
				max = p->data; //��¼�����ֵ
				flag = 1;
			}
			printf("%4d", p->data);
		}
		else
			break;
		p = p->left;
	}
	putchar(10);
	if (flag)
		printf("���������ֵΪ:%d\n", max);
	else
		printf("Ϊ�ҵ�����\n");
	T = delbst(T);
}

BST *createbst(int n)
{
	int i, x;
	BST *T = NULL;
	for (i = 0; i < n; i++)
	{
		x = rand() % 23; //������ɵ����ݾ�С��23��������ԣ�����������е���
		T = insnode(T, x);
	}
	return T;
}

BST *delbst(BST *T) //����BST
{
	if (!T)
		return NULL;
	else
	{
		T->left = delbst(T->left);
		T->right = delbst(T->right);
		free(T);
		return NULL;
	}
}
void showbst(BST *T) //��ʾBST
{
	if (T)
	{
		printf("%d", T->data);
		if (T->left || T->right)
		{
			printf("(");
			showbst(T->left);
			printf(",");
			showbst(T->right);
			printf(")");
		}
	}
}

BST *insnode(BST *T, int x) //��BST�������룬�����ظ��ڵ�ָ��
{
	if (!T)
	{
		T = (BST *)malloc(sizeof(BST));
		T->data = x;
		T->left = T->right = NULL;
		return T;
	}
	else
	{
		if (T->data < x)
		{
			T->right = insnode(T->right, x);
		}
		else if (T->data > x)
		{
			T->left = insnode(T->left, x);
		}
		return T;
	}
}
