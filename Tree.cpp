////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//题目要求：利用孩子-兄弟法表示树，完成下列操作：
//
//          1、以括号的形式显示树；A(B(E,F),C,D(G(H,I,J)))
//          2、利用递归算法输出根节点到所有叶子节点的路径；
//          3、利用非递归算法输出根节点到所有叶子节点的路径；
//          4、计算树的高度；
//          5、统计树中叶子节点的数量；
//          6、层次遍历树，逐行输出各个层次的节点，并计算树的宽度（包含最多节点的层次所实际包含的节点数即树的宽度）
//          7、利用递归算法为每个节点的pa指针赋值，指向该节点的父节点
//          8、复制一个与该树一模一样的树，并返回复制树的根节点指针
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define N 30

typedef struct node
{
	char data;
	struct node *fir, *sib;
	struct node *pa;
} TR;

int menu_select();
TR *createtree(char *pre, int *k); //根据树的先序序列（包含空格）创建二叉树，*k表示当前先序序列中的第*k个位置，该位置上
								   //如果是空格，则返回一个空指针，如果是一个确定的字符，则创建一个节点，该节点数据为
								   //pre[*k]，然后对(*k)++,递归的创建该节点的孩子分支，然后对(*k)++,再递归的创建它的兄弟分支，
								   //最后返回该节点指针。（注意在该过程中不要对pa指针赋值。）

void showtree(TR *T);					 //用括号的形式输出树
void getpath1(TR *T, char *path, int n); //设计递归算法输出根节点到所有叶子节点的路径
void getpath2(TR *T);					 //设计非递归算法输出根节点到所有叶子节点的路径
int heighttree(TR *T);					 ///计算并返回树的高度
int leaftree(TR *T);					 //计算并返回树的叶子节点的数量
int layervisit(TR *T);					 //逐行输出树各个层次的节点,并返回树的宽度
void getpa(TR *T);						 //为每个节点的pa指针赋值，指向该节点的父节点，根节点的pa指向NULL
void showpa(TR *T);						 //显示每个节点及其父节点
TR *copytree(TR *T);					 //复制一个与该树一模一样的树，并返回复制的树的根节点指向
TR *deltree(TR *T);						 //销毁树

int menu_select()
{
	char i;
	do
	{
		system("cls");
		printf("1.创建孩子-兄弟二叉树\n");
		printf("2.显示树\n");
		printf("3.输出根节点到所有叶子节点的路径\n");
		printf("4.树的高度和叶子节点数量\n");
		printf("5.层次遍历树\n");
		printf("6.获取pa指针\n");
		printf("7.复制树\n");
		printf("0.exit\n");
		printf("Please input index(0-7):");
		i = getchar();
	} while (i < '0' || i > '7');
	return (i - '0');
}

main()
{
	char pre[] = "ABE F  C DGH I J     "; //已知树的先序序列(空格对应空指向)
	TR *T = NULL, *R = NULL;
	char path[150] = {"\0"};
	int n = 0;
	int k;
	for (;;)
	{
		switch (menu_select())
		{
		case 1:
			k = 0;
			T = createtree(pre, &k); //创建树
			if (T)
				printf("创建成功\n");
			else
				printf("创建不成功\n");
			system("pause");
			break;
		case 2:
			if (!T)
				printf("树是空树\n");
			else
				showtree(T); //显示树
			printf("\n");
			system("pause");
			break;
		case 3:
			printf("\n递归算法得到根节点到所有叶子节点的路径：\n");
			getpath1(T, path, n); //递归算法找路径
			printf("\n非递归算法得到根节点到所有叶子节点的路径：\n");
			getpath2(T); //非递归算法找路径
			system("pause");
			break;
		case 4:
			printf("\n树的高度 = %d ,树中包含 %d 片叶子\n", heighttree(T), leaftree(T)); //统计数的高度和叶子节点数量
			system("pause");
			break;
		case 5:
			printf("\n树的层次遍历结果：\n");
			k = layervisit(T); //逐行显示各个层次的节点，并返回树的宽度
			printf("\n树的宽度为：%d\n", k);
			system("pause");
			break;
		case 6:
			getpa(T); //给每个节点的pa指针赋值
			printf("\n树的节点及其对应父节点:\n");
			showpa(T); //显示树的所有节点及其对应父节点
			system("pause");
			break;
		case 7:
			R = copytree(T); //复制一个与根结点为T的树一模一样的树，将复制树的根节点指向返回赋值给R
			T = deltree(T);  //销毁原树
			printf("\n复制的树：\n");
			showtree(R); //显示复制的树R
			printf("\n");
			R = deltree(R); //销毁复制的树
			system("pause");
			break;
		case 0:
			printf("GOOD BYE\n");
			system("pause");
			exit(0);
		}
	}
}

TR *createtree(char *pre, int *k) //根据树的先序序列创建二叉树
{
	TR *p;
	if (pre[*k] == ' ')
	{
		(*k)++;
		return NULL;
	}
	else
	{
		p = (TR *)malloc(sizeof(TR));
		p->data = pre[*k];
		(*k)++;
		p->fir = createtree(pre, k);
		p->sib = createtree(pre, k);
		return p;
	}
}

void showtree(TR *T) //用括号的形式输出二叉树
{
	printf("%c", T->data);
	if (T->fir)
	{
		printf("(");
		showtree(T->fir);
		printf(")");
	}
	if (T->sib)
	{
		printf(",");
		showtree(T->sib);
	}
}

void getpath1(TR *T, char *path, int n) //递归算法输出根节点到所有叶子节点的路径
{
	int i;
	if (!T)
		return;
	else
		path[n] = T->data;
	if (T->fir)
	{
		getpath1(T->fir, path, n + 1);
	}
	else
	{
		for (i = 0; i < n + 1; i++)
			printf("%4c", path[i]);
		printf("\n");
	}
	if (T->sib)
	{
		getpath1(T->sib, path, n);
	}
}

void getpath2(TR *T) //非递归算法输出根节点到所有叶子节点的路径
{
	TR *t[15], *p = T;
	int top = -1;
	int i = 0;
	while (top >= 0 || p)
	{
		while (p)
		{
			top++;
			t[top] = p;
			p = p->fir;
		}
		p = t[top];
		top--;
		if (!p->fir)
		{
			for (i = 0; i <= top; i++)
				printf("%4c", t[i]->data);
			printf("%4c", p->data);
			printf("\n");
		}
		p = p->sib;
	}
}

int heighttree(TR *T) ///计算并返回树的高度
{
	if (!T)
		return 0;
	int child, brother;
	child = heighttree(T->fir) + 1;
	brother = heighttree(T->sib);
	if (child >= brother)
		return child;
	else
		return brother;
}
int leaftree(TR *T) //计算并返回树的叶子节点的数量
{
	if (!T)
		return 0;
	int sum;
	sum = leaftree(T->fir) + leaftree(T->sib);
	if (!T->fir)
		sum += 1;
	return sum;
}
int layervisit(TR *T) //逐行输出树的各个层次，并返回树的宽度
{
	int len = 1, i;
	TR *t[15], *p = T; //队列
	int base, top, temp_top;
	base = top = -1;
	base++;
	top++;
	t[top] = T;
	printf("%c\n", T->data);
	while (top != base - 1)
	{
		temp_top = top;
		for (i = base; i <= temp_top; i++)
		{
			p = t[i];
			p = p->fir;
			while (p) //将所有兄弟入队
			{
				printf("%-4c", p->data);
				top++;
				t[top] = p;
				p = p->sib;
			}
		}
		printf("\n");
		base = temp_top + 1;
		len = (top - base + 1 > len) ? top - base + 1 : len;
	}
	return len;
}

void getpa(TR *T) //为每个节点的pa指针赋值，指向该节点的父节点，根节点的pa指向NULL
{
	TR *t[15], *p = T;
	int top = -1;
	while (top >= 0 || p)
	{
		while (p)
		{
			top++;
			t[top] = p;
			p = p->fir;
		}
		p = t[top];
		top--;
		if (top != -1)
			p->pa = t[top];
		p = p->sib;
	}
	T->pa = NULL;
}

void showpa(TR *T) //显示每个节点及其父节点
{
	if (T)
	{
		if (T->pa)
			printf("%c---%c\n", T->data, T->pa->data);
		else
			printf("%c---NULL\n", T->data);
		showpa(T->fir);
		showpa(T->sib);
	}
}

TR *copytree(TR *T) //复制树
{
	if (!T)
		return NULL;
	else
	{
		TR *p = (TR *)malloc(sizeof(TR));
		p->data = T->data;
		p->fir = copytree(T->fir);
		p->sib = copytree(T->sib);
		return p;
	}
}

TR *deltree(TR *T) //销毁树
{
	if (T)
	{
		T->fir = deltree(T->fir);
		T->sib = deltree(T->sib);
		free(T);
		return NULL;
	}
	else
		return NULL;
}
