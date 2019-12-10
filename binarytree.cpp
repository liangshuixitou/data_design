////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 题目要求：利用二叉链表示二叉树，完成下列操作：
//          1、根据二叉树的中序、先序序列创建二叉树，并返回根节点指针；
//          2、利用递归算法输出根节点到所有叶子节点的路径；
//          3、利用非递归算法输出根节点到所有叶子节点的路径；
//          4、利用递归算法，寻找距离两个指定节点（互相不为对方的祖先）最近的共同祖先，返回该祖先指针；
//          5、按层次分行输出二叉树的节点数据（每层结点单独一行显示），并判断该二叉树是否为完全二叉树
//          6、销毁以指定节点为根节点的子树；
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "windows.h"
#define N 30

typedef struct node
{
	char data;
	struct node *left, *right;
} BT;

typedef struct stack
{
	BT st[10];
	int top;
} ST; //定义一个栈

int menu_select();

BT *createtree(char *in, char *pre, int k);			//根据二叉树的中序和先序序列创建二叉树，k表示字符串in的长度
void showtree(BT *T);								//用括号的形式输出二叉树
void getpath1(BT *T, char string_point[], int top); //递归算法输出根节点到所有叶子节点的路径
void getpath2(BT *T);								//非递归算法输出根节点到所有叶子节点的路径
BT *delsubtree(BT *T, char s);						//找到包含数据为s的节点，并删除以该节点为根的子树，最后返回根节点（因为这个删除也可能会删除整个树）
BT *del(BT *T);										//删除以T节点为根节点的二叉树
BT *getcomances(BT *T, char s1, char s2);			//寻找距离两个指定节点s1和s2（互相不为对方的祖先）最近的共同祖先，返回该祖先指针
int layervisit(BT *T);								//层次遍历二叉树，逐行输出节点数据，并判断该二叉树是否为完全二叉树，如果是，返回1，否则返回0
int search(BT *T, BT *stack[], char s);				//在二叉树中前序遍历然后返回其路径（作为求父节点的子功能函数）

int menu_select()
{
	char i;
	do
	{
		system("cls");
		printf("1.创建二叉树\n");
		printf("2.显示二叉树\n");
		printf("3.输出根节点到所有叶子节点的路径\n");
		printf("4.寻找距离两个节点最近的共同祖先\n");
		printf("5.层次遍历二叉树\n");
		printf("6.销毁以指定节点为根节点的子树\n");
		printf("7.前序非递归销毁整棵树\n");
		printf("0.exit\n");
		printf("Please input index(0-7):");
		i = getchar();
	} while (i < '0' || i > '7');
	return (i - '0');
}

main()
{
	BT *T = NULL, *p = NULL;
	char in[] = "GBEHDFAC", pre[] = "ABGDEHFC"; //已知二叉树的中序和先序序列
	char path[100] = {'\0'};					//递归输出时候的穿传参
	char s;
	int k = strlen(in); //k表示中序序列长度
	for (;;)
	{
		switch (menu_select())
		{
		case 1:
			T = createtree(in, pre, k);
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
				showtree(T);
			printf("\n");
			system("pause");
			break;
		case 3:
			printf("\n递归算法得到根节点到所有叶子节点的路径：\n");
			getpath1(T, path, 0);
			printf("\n非递归算法得到根节点到所有叶子节点的路径：\n");
			getpath2(T);
			system("pause");
			break;
		case 4:
			p = getcomances(T, 'H', 'F');							  //寻找距离H和F节点最近的共同祖先
			printf("\n距离 H 和 F 最近的共同祖先是： %c\n", p->data); //输出找到的祖先节点数据，应该是D
			p = getcomances(T, 'H', 'G');							  //寻找距离H和G节点最近的共同祖先
			printf("\n距离 H 和 G 最近的共同祖先是： %c\n", p->data); //输出找到的祖先节点数据，应该是B
			system("pause");
			break;
		case 5:
			printf("\n二叉树层次遍历结果：\n");
			if (layervisit(T))
				printf("该二叉树是完全二叉树\n");
			else
				printf("该二叉树不是完全二叉树\n");
			system("pause");
			break;
		case 6:
			T = delsubtree(T, 'D'); //删除以D作为根节点的子树
			printf("\n删除以D为根节点的子树后，树变为:\n", s);
			if (!T)
				printf("树为空\n");
			else
			{
				showtree(T); //显示删除后的树
				printf("删除成功！\n");
			}

			system("pause");
			break;
		case 7:
			if (!T)
				printf("树为空\n");
			else
				T = del(T);
			system("pause");
			break;
		case 0:
			printf("GOOD BYE\n");
			system("pause");
			exit(0);
		}
	}
}

BT *createtree(char *in, char *pre, int k) //根据二叉树的中序和先序序列创建二叉树，k表示字符串in的长度
{
	BT *p;
	int i;
	if (k <= 0)
		return NULL;
	else
	{
		p = (BT *)malloc(sizeof(BT));
		p->data = *pre;
		for (i = 0; in[i] != *pre; i++)
			;
		p->left = createtree(in, pre + 1, i);
		p->right = createtree(in + i + 1, pre + i + 1, k - i - 1);
	}
	return p;
}

void showtree(BT *T) //用括号的形式输出二叉树
{
	if (T)
	{
		printf("%c", T->data);
		if (T->left || T->right)
		{
			printf("(");
			showtree(T->left);
			printf(",");
			showtree(T->right);
			printf(")");
		}
	}
}

int layervisit(BT *T) //层次遍历二叉树，逐行输出节点数据，并判断该二叉树是否为完全二叉树，如果是，返回1，否则返回0
{
	BT *temp[20]; //定义指针队列
	BT *p;
	int temp_i[20]; //队列的伴随，作为附属判断当前位置的层数
	int base = 0, top = 0;
	int temp_top = top; //在循环中代替top作为循环的结束
	bool flag = 0;		//判断是否为完全二叉树
	bool perfect = 1;   //是否为完全二叉树
	int i, k = 0;		//计数器
	p = T;
	temp[top] = p;   //将第一位入栈
	temp_i[top] = i; //记录下当前的层数
	top++;
	i++;
	printf("%c\n", p->data);
	while (top != base) //下一层为空
	{
		temp_top = top;
		for (k = base; k < temp_top; k++)
		{
			if (temp[k]->left) //将左端点入栈
			{
				if (flag) //出现空值
					perfect = 0;
				temp[top] = temp[k]->left;
				temp_i[top] = temp_i[base] + 1; //改成前置节点的+1
				top++;
				printf("%c ", temp[k]->left->data);
			}
			else //出现空缺
			{
				printf("  ");
				flag = 1;
			}
			if (temp[k]->right) //将右端点入栈
			{
				if (flag) //出现空值
					perfect = 0;
				temp[top] = temp[k]->right;
				temp_i[top] = temp_i[base] + 1;
				top++;
				printf("%c ", temp[k]->right->data);
			}
			else //出现空缺
			{
				printf(" ");
				flag = 1;
			}
		}
		printf("\n");
		i++;
		base = temp_top; //迭代遍历下一层
	}
	return perfect;
}

void getpath1(BT *T, char string_point[], int top) //递归算法输出根节点到所有叶子节点的路径
{
	if (!T)
		return;
	*(string_point + top) = T->data;
	top++;
	if (!T->left && !T->right) //为叶子节点的时候输出
	{
		for (int i = 0; i < top; i++)
		{
			printf("%c", string_point[i]);
			if (i != top - 1)
				printf("->");
		}
		printf("\n");
	}
	else //非叶子节点
	{
		getpath1(T->left, string_point, top);
		getpath1(T->right, string_point, top);
	}
}

void getpath2(BT *T) //非递归算法输出根节点到所有叶子节点的路径
{
	// BT *stack[20]; //建立一个栈对于节点信息进行存储
	// BT *temp;	  //接受弹出地节点，防止重复路径
	// int flag = 0;  //表示当前节点是否可以走
	// int top = 0;
	// stack[top] = T; //将根节点入栈
	// top++;
	// while (top != 0)
	// {
	// 	if (!T->left && !T->right) //达到叶节点,或者左右两端没有路可以走，对于当前完整路径进行输出,并退栈
	// 	{
	// 		for (int i = 0; i < top; i++)
	// 		{
	// 			printf("%c", stack[i]->data);
	// 			if (i != top - 1)
	// 				printf("->");
	// 		}
	// 		printf("\n");
	// 		temp = stack[top - 1]; //将栈顶元素弹出
	// 		top--;
	// 		T = stack[top - 1]; //设置为栈顶元素
	// 	}
	// 	if (T->left && !(T->left == temp || T->right == temp))
	// 	{
	// 		stack[top] = T->left; //将左节点入栈
	// 		top++;
	// 		T = T->left;
	// 	}
	// 	else if (T->right && T->right != temp)
	// 	{
	// 		stack[top] = T->right; //将右节点入栈
	// 		top++;
	// 		T = T->right;
	// 	}
	// 	else if (T->right == temp || T->left == temp)
	// 	{
	// 		temp = stack[top - 1]; //将栈顶元素弹出
	// 		top--;
	// 		T = stack[top - 1]; //设置为栈顶元素
	// 	}
	// }
	//以上为先序遍历输出路径
	//以下为后序遍历输出路径
	BT *S[20], *p = T, *b;
	int top = -1;
	do
	{
		while (p)
		{
			top++;
			S[top] = p;
			p = p->left;
		}
		b = NULL;
		while (top >= 0)
		{
			p = S[top];
			if (p->right == b)
			{
				top--;
				b = p;
				if (!p->left && !p->right)
				{
					for (int i = 0; i <= top; i++)
					{
						printf("%c->", S[i]->data);
					}
					printf("%c\n", p->data);
				}
			}
			else
			{
				p = p->right;
				break;
			}
		}

	} while (top >= 0);
}

BT *delsubtree(BT *T, char s) //找到包含数据为s的节点，并删除以该节点为根的子树，最后返回根节点（因为这个删除也可能会删除整个树）
{
	BT *stack[10]; //定义一个栈用前序遍历访问每个节点
	BT *temp;
	int top = 0;
	if (T->data == s)
	{
		del(T); //调用删除函数
		return NULL;
	}
	else
	{
		stack[top] = T; //将首位入栈
		top++;
		while (top != 0)
		{
			temp = stack[--top];
			if (temp->right)
			{
				stack[top++] = temp->right;
				if (temp->right->data == s)
				{
					temp->right = NULL;
					del(temp->right); //找到并且删除
					break;
				}
			}
			if (temp->left)
			{
				stack[top++] = temp->left;
				if (temp->left->data == s)
				{
					temp->left = NULL;
					del(temp->left); //找到并且删除
					break;
				}
			}
		}
	}
	return T;
}

BT *del(BT *T) //删除T根节点的函数
{
	// if (T)
	// {
	// 	T->left = del(T->left);
	// 	T->right = del(T->right);
	// }
	// return NULL;

	//以上为递归后序遍历删除二叉树
	//以下为前序遍历删除二叉树
	BT *p = T;
	BT *stack[20];
	int top = -1;
	top++;
	stack[top] = p;
	while (top >= 0)
	{
		p = stack[top];
		top--;
		if (p->right)
		{
			top++;
			stack[top] = p->right;
		}
		if (p->left)
		{
			top++;
			stack[top] = p->left;
		}
		free(p);
		//在前序遍历的操作中，先将当前节点的左右子树全部入栈后，在删除当前节点
	}
	return NULL;
}

BT *getcomances(BT *T, char s1, char s2) //寻找距离两个指定节点s1和s2（互相不为对方的祖先）最近的共同祖先，返回该祖先指针
{
	//具体思想为通过线序遍历得出两个节点的路径栈，将这两个栈从头开始遍历
	//第一个不同的的节点的前一个节点就是两个节点的父亲节点
	// BT *stack1[20]; //路径数组
	// BT *stack2[20]; //路径数组
	// BT *temp;		//临时指针，判断两个路径数组中的值是否相等
	// int top1, top2;
	// top1 = top2 = 0;
	// top1 = search(T, stack1, s1); //分别查找两条路径并用栈存储
	// top2 = search(T, stack2, s2);
	// for (int i = 0; i < top1 && i < top2; i++)
	// {
	// 	if (stack1[i] != stack2[i]) //两个路径开始出现分歧
	// 	{
	// 		//返回前一个必定为共同祖先节点
	// 		return stack1[i - 1];
	// 	}
	// }

	//以上为本人上机写的初始版本，下面为优化版本
	//优化版本
	if (!T)
		return NULL;
	if (T->data == s1 || T->data == s2)
		return T;
	BT *a = getcomances(T->left, s1, s2);
	BT *b = getcomances(T->right, s1, s2);
	if (a && b)
		return T;
	if (a)
		return getcomances(T->left, s1, s2);
	if (b)
		return getcomances(T->right, s1, s2);
}

int search(BT *T, BT *stack[], char s) //在二叉树中寻找一个指定的数据，并将路径存储在栈中
{
	//采用非递归前序遍历的方法,函数返回值判断是否在当前子树找到
	BT *temp = NULL; //接受弹出地节点，防止重复路径
	int flag = 0;	//表示当前节点是否可以走
	int top = 0;
	stack[top] = T; //将根节点入栈
	top++;
	while (top != 0)
	{
		if (T->data == s)
			return top;			   //返回路径长度
		if (!T->left && !T->right) //达到叶节点,或者左右两端没有路可以走，对于当前完整路径进行输出,并退栈
		{
			temp = stack[top - 1]; //将栈顶元素弹出
			top--;
			T = stack[top - 1]; //设置为栈顶元素
		}
		if (T->left && !(T->left == temp || T->right == temp))
		{
			stack[top] = T->left; //将左节点入栈
			top++;
			T = T->left;
		}
		else if (T->right && T->right != temp)
		{
			stack[top] = T->right; //将右节点入栈
			top++;
			T = T->right;
		}
		else if (T->right == temp || T->left == temp)
		{
			temp = stack[top - 1]; //将栈顶元素弹出
			top--;
			T = stack[top - 1]; //设置为栈顶元素
		}
	}
	return 0; //没有找到返回空值
}

//中序遍历
// void InOrderWithoutRecursion1(BTNode *root)
// {
// 	//空树
// 	if (root == NULL)
// 		return;
// 	//树非空
// 	BTNode *p = root;
// 	stack<BTNode *> s;
// 	while (!s.empty() || p)
// 	{
// 		//一直遍历到左子树最下边，边遍历边保存根节点到栈中
// 		while (p)
// 		{
// 			s.push(p);
// 			p = p->lchild;
// 		}
// 		//当p为空时，说明已经到达左子树最下边，这时需要出栈了
// 		if (!s.empty())
// 		{
// 			p = s.top();
// 			s.pop();
// 			cout << setw(4) << p->data;
// 			//进入右子树，开始新的一轮左子树遍历(这是递归的自我实现)
// 			p = p->rchild;
// 		}
// 	}
// }
//中序遍历
// void InOrderWithoutRecursion2(BTNode *root)
// {
// 	//空树
// 	if (root == NULL)
// 		return;
// 	//树非空
// 	BTNode *p = root;
// 	stack<BTNode *> s;
// 	while (!s.empty() || p)
// 	{
// 		if (p)
// 		{
// 			s.push(p);
// 			p = p->lchild;
// 		}
// 		else
// 		{
// 			p = s.top();
// 			s.pop();
// 			cout << setw(4) << p->data;
// 			p = p->rchild;
// 		}
// 	}
// }