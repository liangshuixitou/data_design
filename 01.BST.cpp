///////////////////////////////////////////////////////////////////////////////////////////
// 题目要求：在BST中做处理
//          1、根据系统随机生成的数据创建BST；
//          2、计算该BST的平均查找长度ASL（等概率，查找成功的）；
//          3、在BST中做删除
//
////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define N 100
typedef struct node
{
	int data;
	struct node *left, *right;
} BST;

BST *createbst(int n);		 //创建BST
BST *insnode(BST *T, int x); //在BST中插入数据点x,并返回根节点指向
BST *delnode(BST *T, int x); //在BST中删除包含x的节点，并返回根节点指向
void showbst(BST *T);		 //显示BST
float comasl(BST *T);		 //计算并返回等概率查找下，该BST的平均查找长度
BST *delbst(BST *T);		 //销毁BST

main()
{
	int i, n, x;
	BST *T = NULL;
	printf("请输入数据规模：\n");
	scanf("%d", &n);
	while (n > 0)
	{
		T = createbst(n); //创建BST
		printf("创建好的BST为：\n");
		showbst(T);													   //显示BST
		printf("\n\n该BST查找成功的平均查找长度=%.2f\n\n", comasl(T)); //计算BST查找成功的ASL
		for (i = 1; T && i <= 4; i++)
		{
			//////////////////////做连续四次的删除，待删除数据随机生成///////////////////////////////////////////////
			x = rand() % 23;
			printf(" \n删除数据%d后，BST为：\n", x);
			T = delnode(T, x); //在BST中做删除
			showbst(T);
			printf("\n\n");
		}
		T = delbst(T); //销毁BST
		printf("请输入数据规模：\n");
		scanf("%d", &n);
	}
	system("pause");
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

BST *delnode(BST *T, int x) //在BST中做删除并返回根节点指向。如果x不存在，给出提示信息“该数据不存在”
{
	BST *p = T, *pa = NULL, *temp; //用于查找该元素的位置，以及该元素的父亲节点位置 ,临时节点记录p的位置
	while (p)
	{
		if (p->data < x)
		{
			pa = p;
			p = p->right;
		}
		else if (p->data > x)
		{
			pa = p;
			p = p->left;
		}
		else
		{
			break;
		}
	}
	if (!p)
	{
		printf("该数据不存在\n");
		return T;
	}
	else
	{
		if (!p->left && !p->right) //没有孩子节点
		{
			if (!pa) //为根节点
			{
				free(p);
				return NULL;
			}
			if (p == pa->left)
				pa->left = NULL;
			else
				pa->right = NULL;
		}
		else if (!p->left || !p->right) //有一个孩子节点
		{
			if (!pa) //为根节点
			{
				if (p->left)
				{
					free(p);
					return p->left;
				}
				else
				{
					free(p);
					return p->right;
				}
			}
			if (p == pa->left)
			{
				if (p->left)
					pa->left = p->left;
				else
					pa->left = p->right;
			}
			else
			{
				if (p->left)
					pa->right = p->left;
				else
					pa->right = p->right;
			}
		}
		else //有两个孩子节点 ,不用单独考虑根节点的情况
		{
			temp = p;
			pa = p;
			p = p->left; //在左子树中找到最大的节点
			while (p->right)
			{
				pa = p;
				p = p->right;
			}
			temp->data = p->data;
			if (p == pa->left)
				pa->left = p->left;
			else
				pa->right = p->left;
			free(p);
		}
		return T;
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

float comasl(BST *T) //计算BST的平均查找长度
{
	if (!T)
		return 0;
	int num = 1, floor = 1; //点的个数,层序遍历,当前层数
	float sum = 0;			//点的总查找长度
	BST *queen[100];
	int top = 0, base = 0, temp_top, i;
	queen[top] = T;
	top++;
	while (base != top)
	{
		temp_top = top;
		for (i = base; i < temp_top; i++)
		{
			if (queen[i]->left)
				queen[top++] = queen[i]->left;
			if (queen[i]->right)
				queen[top++] = queen[i]->right;
			sum += (floor + 0.0);
			num++;
		}
		base = temp_top;
		floor++;
	}
	return sum / (num + 0.0);
}
