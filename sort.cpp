/////////////////////////////////////////////////////////////////////////////////////
// ��ĿҪ��
//        1����Ƹ�Ч�㷨ʵ�ֻ�������Ҫ��ռ临�Ӷ�O(c)��Ҫ��ֻ���ô���0��1������Ͱ��

//        2����Ƹ�Ч�ǵݹ��㷨ʵ�ֹ鲢����

//        3������ʽ�����ݽṹ����Ƹ�Ч�㷨ʵ��ð������ʹ����������Ҫ��ռ临�Ӷ�O(c)

//        4����Ҫ�޸��Ѹ����Ĺ������룬�����������ӺͶ�����Ҫ�Ĺ��ܺ��������ɵ��ÿ⺯��
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
} LI; //���������������ʽ�ṹ

void getdata(LI *A, LI *B, int *a, int n);				//��ȡn������������������������һ������
void showlist(LI *head);								//��ʾ��������
void showarray(int *a, int n);							//��ʾ��������
void mergesort(int *a, int n);							//�鲢����
void merge(int *t, int *a, int low, int high, int len); //�鲢
void radixsort(LI *head);								//��������
bool is_sorted(LI *head);								//�жϵ�ǰ�����Ƿ�����
void bubblesort(LI *head);								//ð������
void dellist(LI *head);									//��������

main()
{
	int *a, n;
	LI *A, *B;
	A = (LI *)malloc(sizeof(LI));
	B = (LI *)malloc(sizeof(LI));
	A->next = B->next = NULL; //���������յĴ�ͷ����
	printf("\n���������ݹ�ģ:\n");
	scanf("%d", &n);
	while (n > 0)
	{
		a = (int *)malloc((n + 1) * sizeof(int)); //0��λ�ò�������
		getdata(A, B, a, n);					  //��ȡ��������������
		radixsort(A);							  //��������
		mergesort(a, n);						  //�鲢����
		bubblesort(B);							  //ð������
		free(a);								  //�ͷ�����ռ�
		dellist(A);								  //��������
		dellist(B);								  //��������
		printf("\n���������ݹ�ģ:\n");			  //����������Ҫ��������ݹ�ģ
		scanf("%d", &n);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getdata(LI *A, LI *B, int *a, int n) //��ȡn�������������������������
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
		a[n - i + 1] = x; //ע���������ЧԪ���Ǵ�a[1]----a[n]
	}
}

void showlist(LI *head) //��ʾ��������
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

void showarray(int *a, int n) //��ʾ��������
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

void dellist(LI *head) //��������
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

void mergesort(int *a, int n) //�鲢����
{
	int *t;
	t = (int *)malloc((n + 1) * sizeof(int)); //��������
	////////////////////////��ɸú���////////////////////////////////
	int len = 2; //����
	int i = 1;   //������
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
	merge(t, a, 1, n, len / 2); //����ʣ����
	////////////////////////��ɸú���////////////////////////////////
	printf("\n�鲢����Ľ����\n");
	showarray(a, n);
	free(t);
}

void merge(int *t, int *a, int low, int high, int l) //�鲢����
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

void bubblesort(LI *head) //ð������
{
	////////////////////////��ɸú���////////////////////////////////
	LI *p1, *p, *p2;					//p1Ϊp��ǰ�ýڵ㣬p��p2���бȽϵ������ڵ�
	if (head->next && head->next->next) //����ĳ��ȴ��ڵ���2
	{
		LI *rear;
		int flag;
		while (head->next != rear)
		{
			flag = 0; //���ĳһ���ڲ�ѭ�����Ƿ�����Ѿ�����õ����
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
					p = p1->next; //���и���
					p2 = p->next;
					flag = 1;
				}
				p1 = p1->next; //��������ƶ�
				p = p->next;
				p2 = p2->next;
			}
			rear = p; //���е���
			if (!flag)
				break; //�Ѿ�Ϊ˳��������
		}
	}
	////////////////////////��ɸú���////////////////////////////////
	printf("\nð������Ľ����\n");
	showlist(head);
}

void radixsort(LI *head) //��������
{
	////////////////////////��ɸú���////////////////////////////////
	//��������Ͱ�������
	LI *N = (LI *)malloc(sizeof(LI) * 2);
	N[0].next = NULL;
	N[1].next = NULL;
	LI *p = head->next, *q;
	int max = 0;
	int pos; //��¼λ��
	while (p)
	{
		if (p->data > max)
			max = p->data;
		p = p->next;
	}
	int len = 1; //ѭ������
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
			pos = p->data >> i & 1; //λ�����ȡ��iλ�Ķ�������
			q = N + pos;
			while (q->next)
				q = q->next;
			q->next = p; //����Ͱ��
			p->next = NULL;
			p = head->next; //����
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
				p->next = q; //������������һ��λ��
				q->next = NULL;
				q = N[j].next; //����
			}
		}
	}
	free(N);
	////////////////////////��ɸú���////////////////////////////////
	printf("\n��������Ľ����\n");
	showlist(head);
}
