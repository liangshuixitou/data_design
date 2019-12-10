///////////////////////////////////////////////////////////////////////////////////////////
// 题目要求：随机生成n个整数（可能会有重复元素），请利用BST设计高效算法，按降序有序的
//          顺序输出所有大于等于k的数据
//          1、自行设计BST的数据结构，自行设计需要的其余的功能函数，不要修改main函数
//          2、数据规模n以及k均从键盘输入
//          3、随机生成的数据，数值不要超过100，方便调试和观察结果，不要以此为条件设计算法
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

BST *createbst(int n);		 //创建BST
BST *insnode(BST *T, int x); //在BST中插入数据点x,并返回根节点指向
void showbst(BST *T);		 //显示BST
void output(int n, int k);   //在n个随机数中，利用BST，按降序有序的顺序输出所有大于等于k的数据
BST *delbst(BST *T);		 //销毁BST

main()
{
	int n, k;
	printf("请输入数据规模n以及需要查找的有序序列的最小值k:\n");
	scanf("%d%d", &n, &k);
	while (n > 0 && k > 0)
	{
		+printf("所有大于等于%d的数据有:\n", k);
		output(n, k);
		printf("请输入数据规模n以及需要查找的有序序列的最大值k:\n");
		scanf("%d%d", &n, &k);
	}
	system("pause");
	return 0;
}

void output(int n, int k)
{
	BST *T;
	BST *stack[n], *p;
	int top = -1;		   //先输出右边节点然后输出中间，最后输出左边，变种的中序遍历
	int flag = 0, max = 0; //判断最大的数是否输出
	T = createbst(n);
	printf("根据数据规模n创建好的BST为\n");
	showbst(T);
	putchar(10);
	p = T;
	if (!p)
		printf("BST创建失败\n");
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
				max = p->data; //记录下最大值
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
		printf("序列中最大值为:%d\n", max);
	else
		printf("为找到序列\n");
	T = delbst(T);
}

BST *createbst(int n)
{
	int i, x;
	BST *T = NULL;
	for (i = 0; i < n; i++)
	{
		x = rand() % 23; //随机生成的数据均小于23，方便调试，这个可以自行调整
		T = insnode(T, x);
	}
	return T;
}

BST *delbst(BST *T) //销毁BST
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
void showbst(BST *T) //显示BST
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

BST *insnode(BST *T, int x) //在BST中做插入，并返回根节点指向
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
