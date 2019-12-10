///////////////////////////////////////////////////////////////////////////////////////////
// ��ĿҪ����BST��������
//          1������ϵͳ������ɵ����ݴ���BST��
//          2�������BST��ƽ�����ҳ���ASL���ȸ��ʣ����ҳɹ��ģ���
//          3����BST����ɾ��
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

BST *createbst(int n);		 //����BST
BST *insnode(BST *T, int x); //��BST�в������ݵ�x,�����ظ��ڵ�ָ��
BST *delnode(BST *T, int x); //��BST��ɾ������x�Ľڵ㣬�����ظ��ڵ�ָ��
void showbst(BST *T);		 //��ʾBST
float comasl(BST *T);		 //���㲢���صȸ��ʲ����£���BST��ƽ�����ҳ���
BST *delbst(BST *T);		 //����BST

main()
{
	int i, n, x;
	BST *T = NULL;
	printf("���������ݹ�ģ��\n");
	scanf("%d", &n);
	while (n > 0)
	{
		T = createbst(n); //����BST
		printf("�����õ�BSTΪ��\n");
		showbst(T);													   //��ʾBST
		printf("\n\n��BST���ҳɹ���ƽ�����ҳ���=%.2f\n\n", comasl(T)); //����BST���ҳɹ���ASL
		for (i = 1; T && i <= 4; i++)
		{
			//////////////////////�������Ĵε�ɾ������ɾ�������������///////////////////////////////////////////////
			x = rand() % 23;
			printf(" \nɾ������%d��BSTΪ��\n", x);
			T = delnode(T, x); //��BST����ɾ��
			showbst(T);
			printf("\n\n");
		}
		T = delbst(T); //����BST
		printf("���������ݹ�ģ��\n");
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

BST *delnode(BST *T, int x) //��BST����ɾ�������ظ��ڵ�ָ�����x�����ڣ�������ʾ��Ϣ�������ݲ����ڡ�
{
	BST *p = T, *pa = NULL, *temp; //���ڲ��Ҹ�Ԫ�ص�λ�ã��Լ���Ԫ�صĸ��׽ڵ�λ�� ,��ʱ�ڵ��¼p��λ��
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
		printf("�����ݲ�����\n");
		return T;
	}
	else
	{
		if (!p->left && !p->right) //û�к��ӽڵ�
		{
			if (!pa) //Ϊ���ڵ�
			{
				free(p);
				return NULL;
			}
			if (p == pa->left)
				pa->left = NULL;
			else
				pa->right = NULL;
		}
		else if (!p->left || !p->right) //��һ�����ӽڵ�
		{
			if (!pa) //Ϊ���ڵ�
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
		else //���������ӽڵ� ,���õ������Ǹ��ڵ�����
		{
			temp = p;
			pa = p;
			p = p->left; //�����������ҵ����Ľڵ�
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

float comasl(BST *T) //����BST��ƽ�����ҳ���
{
	if (!T)
		return 0;
	int num = 1, floor = 1; //��ĸ���,�������,��ǰ����
	float sum = 0;			//����ܲ��ҳ���
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
