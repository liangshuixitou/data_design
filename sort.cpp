/////////////////////////////////////////////////////////////////////////////////////
// 题目要求：
//        1、设计高效算法实现基数排序，要求空间复杂度O(c)，要求只能用代表0和1的两个桶；

//        2、设计高效非递归算法实现归并排序

//        3、在链式的数据结构中设计高效算法实现冒泡排序，使得链表有序，要求空间复杂度O(c)

//        4、不要修改已给定的公共代码，可以自行增加和定义需要的功能函数，不可调用库函数
//
//////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
typedef struct node
{
	int data;
	struct node *next;
} LI; //基数排序所需的链式结构

void getdata(LI *A, LI *B, int *a, int n);				//获取n个随机数创建两个无序链表和一个数组
void showlist(LI *head);								//显示链表数据
void showarray(int *a, int n);							//显示数组数据
void mergesort(int *a, int n);							//归并排序
void merge(int *t, int *a, int low, int high, int len); //归并
void radixsort(LI *head);								//基数排序
bool is_sorted(LI *head);								//判断当前链表是否有序
void bubblesort(LI *head);								//冒泡排序
void dellist(LI *head);									//销毁链表

main()
{
	int *a, n;
	LI *A, *B;
	A = (LI *)malloc(sizeof(LI));
	B = (LI *)malloc(sizeof(LI));
	A->next = B->next = NULL; //创建两个空的带头链表
	printf("\n请输入数据规模:\n");
	scanf("%d", &n);
	while (n > 0)
	{
		a = (int *)malloc((n + 1) * sizeof(int)); //0号位置不放数据
		getdata(A, B, a, n);					  //获取链表与数组数据
		radixsort(A);							  //基数排序
		mergesort(a, n);						  //归并排序
		bubblesort(B);							  //冒泡排序
		free(a);								  //释放数组空间
		dellist(A);								  //销毁链表
		dellist(B);								  //销毁链表
		printf("\n请输入数据规模:\n");			  //重新输入需要排序的数据规模
		scanf("%d", &n);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getdata(LI *A, LI *B, int *a, int n) //获取n个随机数创建无序链表与数组
{
	LI *p;
	int i, x;
	srand(time(0));
	for (i = 1; i <= n; i++)
	{
		x = rand();
		p = (LI *)malloc(sizeof(LI));
		p->data = x;
		p->next = A->next;
		A->next = p;
		p = (LI *)malloc(sizeof(LI));
		p->data = x;
		p->next = B->next;
		B->next = p;
		a[n - i + 1] = x; //注意数组的有效元素是从a[1]----a[n]
	}
}

void showlist(LI *head) //显示链表内容
{
	int i = 0;
	LI *p = head->next;
	while (p)
	{
		printf("%-6d ", p->data);
		i++;
		if (i % 15 == 0)
			printf("\n");
		p = p->next;
	}
	printf("\n");
}

void showarray(int *a, int n) //显示数组内容
{
	int i, j;
	for (i = 1, j = 0; i <= n; i++)
	{
		printf("%-6d ", a[i]);
		j++;
		if (j % 15 == 0)
			printf("\n");
	}
	printf("\n");
}

void dellist(LI *head) //销毁链表
{
	LI *p, *p2;
	p = head->next;
	head->next = NULL;
	while (p)
	{
		p2 = p->next;
		free(p);
		p = p2;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mergesort(int *a, int n) //归并排序
{
	int *t;
	t = (int *)malloc((n + 1) * sizeof(int)); //辅助数组
	////////////////////////完成该函数////////////////////////////////
	int len = 2; //步长
	int i = 1;   //计数器
	while (len <= n)
	{
		i = 1;
		while (i + len - 1 <= n)
		{
			merge(t, a, i, i + len - 1, len / 2);
			i += len;
		}
		merge(t, a, i, n, len / 2);
		len *= 2;
	}
	merge(t, a, 1, n, len / 2); //处理剩余项
	////////////////////////完成该函数////////////////////////////////
	printf("\n归并排序的结果：\n");
	showarray(a, n);
	free(t);
}

void merge(int *t, int *a, int low, int high, int l) //归并函数
{
	int m = low + l - 1;
	int i = low;
	int j = m + 1;
	int k = low;
	while (i <= m && j <= high)
	{
		if (a[i] < a[j])
		{
			t[k] = a[i];
			i++;
			k++;
		}
		else
		{
			t[k] = a[j];
			j++;
			k++;
		}
	}
	while (i <= m)
	{
		t[k] = a[i];
		i++;
		k++;
	}
	while (j <= high)
	{
		t[k] = a[j];
		j++;
		k++;
	}
	for (int x = low; x <= high; x++)
		a[x] = t[x];
}

void bubblesort(LI *head) //冒泡排序
{
	////////////////////////完成该函数////////////////////////////////
	LI *p1, *p, *p2;					//p1为p的前置节点，p，p2进行比较的两个节点
	if (head->next && head->next->next) //链表的长度大于等于2
	{
		LI *rear;
		int flag;
		while (head->next != rear)
		{
			flag = 0; //检查某一次内部循环中是否出现已经排序好的请况
			p1 = head;
			p = head->next;
			p2 = head->next->next;
			while (p2 && p2 != rear)
			{
				if (p->data > p2->data)
				{
					p->next = p2->next;
					p2->next = p;
					p1->next = p2;
					p = p1->next; //进行更新
					p2 = p->next;
					flag = 1;
				}
				p1 = p1->next; //依次向后移动
				p = p->next;
				p2 = p2->next;
			}
			rear = p; //进行迭代
			if (!flag)
				break; //已经为顺序链表了
		}
	}
	////////////////////////完成该函数////////////////////////////////
	printf("\n冒泡排序的结果：\n");
	showlist(head);
}

void radixsort(LI *head) //基数排序
{
	////////////////////////完成该函数////////////////////////////////
	//仅用两个桶完成排序
	LI *N = (LI *)malloc(sizeof(LI) * 2);
	N[0].next = NULL;
	N[1].next = NULL;
	LI *p = head->next, *q;
	int max = 0;
	int pos; //记录位置
	while (p)
	{
		if (p->data > max)
			max = p->data;
		p = p->next;
	}
	int len = 1; //循环次数
	while (max != 0)
	{
		max /= 2;
		len += 1;
	}
	for (int i = 1; i <= len; i++)
	{
		p = head->next;
		while (p)
		{
			head->next = p->next;
			pos = p->data >> i & 1; //位运算获取第i位的二进制数
			q = N + pos;
			while (q->next)
				q = q->next;
			q->next = p; //放入桶中
			p->next = NULL;
			p = head->next; //迭代
		}
		p = head;
		for (int j = 0; j < 2; j++)
		{
			q = N[j].next;
			while (q)
			{
				N[j].next = q->next;
				while (p->next)
					p = p->next;
				p->next = q; //放入链表的最后一个位置
				q->next = NULL;
				q = N[j].next; //迭代
			}
		}
	}
	free(N);
	////////////////////////完成该函数////////////////////////////////
	printf("\n基数排序的结果：\n");
	showlist(head);
}
