////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ĿҪ�����ö�������ʾ��������������в�����
//          1�����ݶ������������������д����������������ظ��ڵ�ָ�룻
//          2�����õݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          3�����÷ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·����
//          4�����õݹ��㷨��Ѱ�Ҿ�������ָ���ڵ㣨���಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ�룻
//          5������η�������������Ľڵ����ݣ�ÿ���㵥��һ����ʾ�������жϸö������Ƿ�Ϊ��ȫ������
//          6��������ָ���ڵ�Ϊ���ڵ��������
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
} ST; //����һ��ջ

int menu_select();

BT *createtree(char *in, char *pre, int k);			//���ݶ�������������������д�����������k��ʾ�ַ���in�ĳ���
void showtree(BT *T);								//�����ŵ���ʽ���������
void getpath1(BT *T, char string_point[], int top); //�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
void getpath2(BT *T);								//�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
BT *delsubtree(BT *T, char s);						//�ҵ���������Ϊs�Ľڵ㣬��ɾ���Ըýڵ�Ϊ������������󷵻ظ��ڵ㣨��Ϊ���ɾ��Ҳ���ܻ�ɾ����������
BT *del(BT *T);										//ɾ����T�ڵ�Ϊ���ڵ�Ķ�����
BT *getcomances(BT *T, char s1, char s2);			//Ѱ�Ҿ�������ָ���ڵ�s1��s2�����಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ��
int layervisit(BT *T);								//��α�������������������ڵ����ݣ����жϸö������Ƿ�Ϊ��ȫ������������ǣ�����1�����򷵻�0
int search(BT *T, BT *stack[], char s);				//�ڶ�������ǰ�����Ȼ�󷵻���·������Ϊ�󸸽ڵ���ӹ��ܺ�����

int menu_select()
{
	char i;
	do
	{
		system("cls");
		printf("1.����������\n");
		printf("2.��ʾ������\n");
		printf("3.������ڵ㵽����Ҷ�ӽڵ��·��\n");
		printf("4.Ѱ�Ҿ��������ڵ�����Ĺ�ͬ����\n");
		printf("5.��α���������\n");
		printf("6.������ָ���ڵ�Ϊ���ڵ������\n");
		printf("7.ǰ��ǵݹ�����������\n");
		printf("0.exit\n");
		printf("Please input index(0-7):");
		i = getchar();
	} while (i < '0' || i > '7');
	return (i - '0');
}

main()
{
	BT *T = NULL, *p = NULL;
	char in[] = "GBEHDFAC", pre[] = "ABGDEHFC"; //��֪���������������������
	char path[100] = {'\0'};					//�ݹ����ʱ��Ĵ�����
	char s;
	int k = strlen(in); //k��ʾ�������г���
	for (;;)
	{
		switch (menu_select())
		{
		case 1:
			T = createtree(in, pre, k);
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
				showtree(T);
			printf("\n");
			system("pause");
			break;
		case 3:
			printf("\n�ݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath1(T, path, 0);
			printf("\n�ǵݹ��㷨�õ����ڵ㵽����Ҷ�ӽڵ��·����\n");
			getpath2(T);
			system("pause");
			break;
		case 4:
			p = getcomances(T, 'H', 'F');							  //Ѱ�Ҿ���H��F�ڵ�����Ĺ�ͬ����
			printf("\n���� H �� F ����Ĺ�ͬ�����ǣ� %c\n", p->data); //����ҵ������Ƚڵ����ݣ�Ӧ����D
			p = getcomances(T, 'H', 'G');							  //Ѱ�Ҿ���H��G�ڵ�����Ĺ�ͬ����
			printf("\n���� H �� G ����Ĺ�ͬ�����ǣ� %c\n", p->data); //����ҵ������Ƚڵ����ݣ�Ӧ����B
			system("pause");
			break;
		case 5:
			printf("\n��������α��������\n");
			if (layervisit(T))
				printf("�ö���������ȫ������\n");
			else
				printf("�ö�����������ȫ������\n");
			system("pause");
			break;
		case 6:
			T = delsubtree(T, 'D'); //ɾ����D��Ϊ���ڵ������
			printf("\nɾ����DΪ���ڵ������������Ϊ:\n", s);
			if (!T)
				printf("��Ϊ��\n");
			else
			{
				showtree(T); //��ʾɾ�������
				printf("ɾ���ɹ���\n");
			}

			system("pause");
			break;
		case 7:
			if (!T)
				printf("��Ϊ��\n");
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

BT *createtree(char *in, char *pre, int k) //���ݶ�������������������д�����������k��ʾ�ַ���in�ĳ���
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

void showtree(BT *T) //�����ŵ���ʽ���������
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

int layervisit(BT *T) //��α�������������������ڵ����ݣ����жϸö������Ƿ�Ϊ��ȫ������������ǣ�����1�����򷵻�0
{
	BT *temp[20]; //����ָ�����
	BT *p;
	int temp_i[20]; //���еİ��棬��Ϊ�����жϵ�ǰλ�õĲ���
	int base = 0, top = 0;
	int temp_top = top; //��ѭ���д���top��Ϊѭ���Ľ���
	bool flag = 0;		//�ж��Ƿ�Ϊ��ȫ������
	bool perfect = 1;   //�Ƿ�Ϊ��ȫ������
	int i, k = 0;		//������
	p = T;
	temp[top] = p;   //����һλ��ջ
	temp_i[top] = i; //��¼�µ�ǰ�Ĳ���
	top++;
	i++;
	printf("%c\n", p->data);
	while (top != base) //��һ��Ϊ��
	{
		temp_top = top;
		for (k = base; k < temp_top; k++)
		{
			if (temp[k]->left) //����˵���ջ
			{
				if (flag) //���ֿ�ֵ
					perfect = 0;
				temp[top] = temp[k]->left;
				temp_i[top] = temp_i[base] + 1; //�ĳ�ǰ�ýڵ��+1
				top++;
				printf("%c ", temp[k]->left->data);
			}
			else //���ֿ�ȱ
			{
				printf("  ");
				flag = 1;
			}
			if (temp[k]->right) //���Ҷ˵���ջ
			{
				if (flag) //���ֿ�ֵ
					perfect = 0;
				temp[top] = temp[k]->right;
				temp_i[top] = temp_i[base] + 1;
				top++;
				printf("%c ", temp[k]->right->data);
			}
			else //���ֿ�ȱ
			{
				printf(" ");
				flag = 1;
			}
		}
		printf("\n");
		i++;
		base = temp_top; //����������һ��
	}
	return perfect;
}

void getpath1(BT *T, char string_point[], int top) //�ݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
{
	if (!T)
		return;
	*(string_point + top) = T->data;
	top++;
	if (!T->left && !T->right) //ΪҶ�ӽڵ��ʱ�����
	{
		for (int i = 0; i < top; i++)
		{
			printf("%c", string_point[i]);
			if (i != top - 1)
				printf("->");
		}
		printf("\n");
	}
	else //��Ҷ�ӽڵ�
	{
		getpath1(T->left, string_point, top);
		getpath1(T->right, string_point, top);
	}
}

void getpath2(BT *T) //�ǵݹ��㷨������ڵ㵽����Ҷ�ӽڵ��·��
{
	// BT *stack[20]; //����һ��ջ���ڽڵ���Ϣ���д洢
	// BT *temp;	  //���ܵ����ؽڵ㣬��ֹ�ظ�·��
	// int flag = 0;  //��ʾ��ǰ�ڵ��Ƿ������
	// int top = 0;
	// stack[top] = T; //�����ڵ���ջ
	// top++;
	// while (top != 0)
	// {
	// 	if (!T->left && !T->right) //�ﵽҶ�ڵ�,������������û��·�����ߣ����ڵ�ǰ����·���������,����ջ
	// 	{
	// 		for (int i = 0; i < top; i++)
	// 		{
	// 			printf("%c", stack[i]->data);
	// 			if (i != top - 1)
	// 				printf("->");
	// 		}
	// 		printf("\n");
	// 		temp = stack[top - 1]; //��ջ��Ԫ�ص���
	// 		top--;
	// 		T = stack[top - 1]; //����Ϊջ��Ԫ��
	// 	}
	// 	if (T->left && !(T->left == temp || T->right == temp))
	// 	{
	// 		stack[top] = T->left; //����ڵ���ջ
	// 		top++;
	// 		T = T->left;
	// 	}
	// 	else if (T->right && T->right != temp)
	// 	{
	// 		stack[top] = T->right; //���ҽڵ���ջ
	// 		top++;
	// 		T = T->right;
	// 	}
	// 	else if (T->right == temp || T->left == temp)
	// 	{
	// 		temp = stack[top - 1]; //��ջ��Ԫ�ص���
	// 		top--;
	// 		T = stack[top - 1]; //����Ϊջ��Ԫ��
	// 	}
	// }
	//����Ϊ����������·��
	//����Ϊ����������·��
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

BT *delsubtree(BT *T, char s) //�ҵ���������Ϊs�Ľڵ㣬��ɾ���Ըýڵ�Ϊ������������󷵻ظ��ڵ㣨��Ϊ���ɾ��Ҳ���ܻ�ɾ����������
{
	BT *stack[10]; //����һ��ջ��ǰ���������ÿ���ڵ�
	BT *temp;
	int top = 0;
	if (T->data == s)
	{
		del(T); //����ɾ������
		return NULL;
	}
	else
	{
		stack[top] = T; //����λ��ջ
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
					del(temp->right); //�ҵ�����ɾ��
					break;
				}
			}
			if (temp->left)
			{
				stack[top++] = temp->left;
				if (temp->left->data == s)
				{
					temp->left = NULL;
					del(temp->left); //�ҵ�����ɾ��
					break;
				}
			}
		}
	}
	return T;
}

BT *del(BT *T) //ɾ��T���ڵ�ĺ���
{
	// if (T)
	// {
	// 	T->left = del(T->left);
	// 	T->right = del(T->right);
	// }
	// return NULL;

	//����Ϊ�ݹ�������ɾ��������
	//����Ϊǰ�����ɾ��������
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
		//��ǰ������Ĳ����У��Ƚ���ǰ�ڵ����������ȫ����ջ����ɾ����ǰ�ڵ�
	}
	return NULL;
}

BT *getcomances(BT *T, char s1, char s2) //Ѱ�Ҿ�������ָ���ڵ�s1��s2�����಻Ϊ�Է������ȣ�����Ĺ�ͬ���ȣ����ظ�����ָ��
{
	//����˼��Ϊͨ����������ó������ڵ��·��ջ����������ջ��ͷ��ʼ����
	//��һ����ͬ�ĵĽڵ��ǰһ���ڵ���������ڵ�ĸ��׽ڵ�
	// BT *stack1[20]; //·������
	// BT *stack2[20]; //·������
	// BT *temp;		//��ʱָ�룬�ж�����·�������е�ֵ�Ƿ����
	// int top1, top2;
	// top1 = top2 = 0;
	// top1 = search(T, stack1, s1); //�ֱ��������·������ջ�洢
	// top2 = search(T, stack2, s2);
	// for (int i = 0; i < top1 && i < top2; i++)
	// {
	// 	if (stack1[i] != stack2[i]) //����·����ʼ���ַ���
	// 	{
	// 		//����ǰһ���ض�Ϊ��ͬ���Ƚڵ�
	// 		return stack1[i - 1];
	// 	}
	// }

	//����Ϊ�����ϻ�д�ĳ�ʼ�汾������Ϊ�Ż��汾
	//�Ż��汾
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

int search(BT *T, BT *stack[], char s) //�ڶ�������Ѱ��һ��ָ�������ݣ�����·���洢��ջ��
{
	//���÷ǵݹ�ǰ������ķ���,��������ֵ�ж��Ƿ��ڵ�ǰ�����ҵ�
	BT *temp = NULL; //���ܵ����ؽڵ㣬��ֹ�ظ�·��
	int flag = 0;	//��ʾ��ǰ�ڵ��Ƿ������
	int top = 0;
	stack[top] = T; //�����ڵ���ջ
	top++;
	while (top != 0)
	{
		if (T->data == s)
			return top;			   //����·������
		if (!T->left && !T->right) //�ﵽҶ�ڵ�,������������û��·�����ߣ����ڵ�ǰ����·���������,����ջ
		{
			temp = stack[top - 1]; //��ջ��Ԫ�ص���
			top--;
			T = stack[top - 1]; //����Ϊջ��Ԫ��
		}
		if (T->left && !(T->left == temp || T->right == temp))
		{
			stack[top] = T->left; //����ڵ���ջ
			top++;
			T = T->left;
		}
		else if (T->right && T->right != temp)
		{
			stack[top] = T->right; //���ҽڵ���ջ
			top++;
			T = T->right;
		}
		else if (T->right == temp || T->left == temp)
		{
			temp = stack[top - 1]; //��ջ��Ԫ�ص���
			top--;
			T = stack[top - 1]; //����Ϊջ��Ԫ��
		}
	}
	return 0; //û���ҵ����ؿ�ֵ
}

//�������
// void InOrderWithoutRecursion1(BTNode *root)
// {
// 	//����
// 	if (root == NULL)
// 		return;
// 	//���ǿ�
// 	BTNode *p = root;
// 	stack<BTNode *> s;
// 	while (!s.empty() || p)
// 	{
// 		//һֱ���������������±ߣ��߱����߱�����ڵ㵽ջ��
// 		while (p)
// 		{
// 			s.push(p);
// 			p = p->lchild;
// 		}
// 		//��pΪ��ʱ��˵���Ѿ��������������±ߣ���ʱ��Ҫ��ջ��
// 		if (!s.empty())
// 		{
// 			p = s.top();
// 			s.pop();
// 			cout << setw(4) << p->data;
// 			//��������������ʼ�µ�һ������������(���ǵݹ������ʵ��)
// 			p = p->rchild;
// 		}
// 	}
// }
//�������
// void InOrderWithoutRecursion2(BTNode *root)
// {
// 	//����
// 	if (root == NULL)
// 		return;
// 	//���ǿ�
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