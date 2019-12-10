////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ĿҪ�����ú���-�ֵܷ���ʾ����������в�����
//
//          1�������ŵ���ʽ��ʾ����A(B(E,F),C,D(G(H,I,J)))
//          2�����õݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          3�����÷ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          4���������ĸ߶ȣ�
//          5��ͳ������Ҷ�ӽڵ��������
//          6����α��������������������εĽڵ㣬���������Ŀ�ȣ��������ڵ�Ĳ����ʵ�ʰ����Ľڵ��������Ŀ�ȣ�
//          7�����õݹ��㷨Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ�
//          8������һ�������һģһ�������������ظ������ĸ��ڵ�ָ��
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
TR *createtree(char *pre, int *k); //���������������У������ո񣩴�����������*k��ʾ��ǰ���������еĵ�*k��λ�ã���λ����
								   //����ǿո��򷵻�һ����ָ�룬�����һ��ȷ�����ַ����򴴽�һ���ڵ㣬�ýڵ�����Ϊ
								   //pre[*k]��Ȼ���(*k)++,�ݹ�Ĵ����ýڵ�ĺ��ӷ�֧��Ȼ���(*k)++,�ٵݹ�Ĵ��������ֵܷ�֧��
								   //��󷵻ظýڵ�ָ�롣��ע���ڸù����в�Ҫ��paָ�븳ֵ����

void showtree(TR *T);					 //�����ŵ���ʽ�����
void getpath1(TR *T, char *path, int n); //��Ƶݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
void getpath2(TR *T);					 //��Ʒǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
int heighttree(TR *T);					 ///���㲢�������ĸ߶�
int leaftree(TR *T);					 //���㲢��������Ҷ�ӽڵ������
int layervisit(TR *T);					 //���������������εĽڵ�,���������Ŀ��
void getpa(TR *T);						 //Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ㣬���ڵ��paָ��NULL
void showpa(TR *T);						 //��ʾÿ���ڵ㼰�丸�ڵ�
TR *copytree(TR *T);					 //����һ�������һģһ�������������ظ��Ƶ����ĸ��ڵ�ָ��
TR *deltree(TR *T);						 //������

int menu_select()
{
	char i;
	do
	{
		system("cls");
		printf("1.��������-�ֵܶ�����\n");
		printf("2.��ʾ��\n");
		printf("3.������ڵ㵽����Ҷ�ӽڵ��·��\n");
		printf("4.���ĸ߶Ⱥ�Ҷ�ӽڵ�����\n");
		printf("5.��α�����\n");
		printf("6.��ȡpaָ��\n");
		printf("7.������\n");
		printf("0.exit\n");
		printf("Please input index(0-7):");
		i = getchar();
	} while (i < '0' || i > '7');
	return (i - '0');
}

main()
{
	char pre[] = "ABE F  C DGH I J     "; //��֪������������(�ո��Ӧ��ָ��)
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
			T = createtree(pre, &k); //������
			if (T)
				printf("�����ɹ�\n");
			else
				printf("�������ɹ�\n");
			system("pause");
			break;
		case 2:
			if (!T)
				printf("���ǿ���\n");
			else
				showtree(T); //��ʾ��
			printf("\n");
			system("pause");
			break;
		case 3:
			printf("\n�ݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath1(T, path, n); //�ݹ��㷨��·��
			printf("\n�ǵݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath2(T); //�ǵݹ��㷨��·��
			system("pause");
			break;
		case 4:
			printf("\n���ĸ߶� = %d ,���а��� %d ƬҶ��\n", heighttree(T), leaftree(T)); //ͳ�����ĸ߶Ⱥ�Ҷ�ӽڵ�����
			system("pause");
			break;
		case 5:
			printf("\n���Ĳ�α��������\n");
			k = layervisit(T); //������ʾ������εĽڵ㣬���������Ŀ��
			printf("\n���Ŀ��Ϊ��%d\n", k);
			system("pause");
			break;
		case 6:
			getpa(T); //��ÿ���ڵ��paָ�븳ֵ
			printf("\n���Ľڵ㼰���Ӧ���ڵ�:\n");
			showpa(T); //��ʾ�������нڵ㼰���Ӧ���ڵ�
			system("pause");
			break;
		case 7:
			R = copytree(T); //����һ��������ΪT����һģһ�����������������ĸ��ڵ�ָ�򷵻ظ�ֵ��R
			T = deltree(T);  //����ԭ��
			printf("\n���Ƶ�����\n");
			showtree(R); //��ʾ���Ƶ���R
			printf("\n");
			R = deltree(R); //���ٸ��Ƶ���
			system("pause");
			break;
		case 0:
			printf("GOOD BYE\n");
			system("pause");
			exit(0);
		}
	}
}

TR *createtree(char *pre, int *k) //���������������д���������
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

void showtree(TR *T) //�����ŵ���ʽ���������
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

void getpath1(TR *T, char *path, int n) //�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
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

void getpath2(TR *T) //�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
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

int heighttree(TR *T) ///���㲢�������ĸ߶�
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
int leaftree(TR *T) //���㲢��������Ҷ�ӽڵ������
{
	if (!T)
		return 0;
	int sum;
	sum = leaftree(T->fir) + leaftree(T->sib);
	if (!T->fir)
		sum += 1;
	return sum;
}
int layervisit(TR *T) //����������ĸ�����Σ����������Ŀ��
{
	int len = 1, i;
	TR *t[15], *p = T; //����
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
			while (p) //�������ֵ����
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

void getpa(TR *T) //Ϊÿ���ڵ��paָ�븳ֵ��ָ��ýڵ�ĸ��ڵ㣬���ڵ��paָ��NULL
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

void showpa(TR *T) //��ʾÿ���ڵ㼰�丸�ڵ�
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

TR *copytree(TR *T) //������
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

TR *deltree(TR *T) //������
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
