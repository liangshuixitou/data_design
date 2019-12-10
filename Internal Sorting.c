#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"math.h"
typedef struct
{
    int data;
    int next;
}LI;

void Mergesort(int *a,int *t,int low,int high,int *move,int *comp);
void Msort(int *a,int *t,int low,int high,int *move,int *comp);
void Merge(int *a,int n);//�鲢����
void insert_sort(int *a,int n);//ֱ�Ӳ�������
void listinssort(int *a,int n);//���������
void BInsertSort(int *a,int n);//�۰��������
void quick_sort(int *a,int n);//��������
void shell(int *a,int n);//ϣ������
void heapsort(int *a,int n);//������
void showdata(int *b,int n);//��ӡ����

main()
{
    int *a;
    int i,n;
    while(1)
    {
        system("cls");
        printf("���������ݹ�ģ��");
        scanf("%d",&n);
        a=(int *)malloc((n+1)*sizeof(int));
        a[0]=0;
        for(i=1;i<=n;i++)
            a[i]=rand()%100;
        printf("\n������Դ���ݣ�\n");
        showdata(a,n);
        Merge(a,n);
        insert_sort(a,n);
        listinssort(a,n);
        BInsertSort(a,n);
        quick_sort(a,n);
        shell(a,n);
        heapsort(a,n);
        system("pause");
    }
}

void showdata(int *b,int n)//��ӡ����
{
    int i;
    for(i=1;i<=n;i++)
        printf("%d ",b[i]);
    printf("\n");    
}

void Merge(int *a,int n)//�鲢����
{
    int i,*b,*t;
    int move=0,comp=0;//�ƶ������ͱȽϴ���
    b=(int *)malloc((n+1)*sizeof(int));
    t=(int *)malloc((n+1)*sizeof(int));//��������
    memcpy(b,a,(n+1)*sizeof(int));
    Mergesort(b,t,1,n,&move,&comp);
    printf("\n�鲢������Ҫ%d�αȽϣ�%d���ƶ�\n",comp,move);
    free(b);
}

void Mergesort(int *a,int *t,int low,int high,int *move,int *comp)
{
    int mid;
    if(low<high)//�ȸ�ǰ�벿�ֺͺ�벿�������ٸ���������
    {
        mid=(low+high)/2;
        Mergesort(a,t,low,mid,move,comp);
        Mergesort(a,t,mid+1,high,move,comp);
        Msort(a,t,low,high,move,comp);
    }
}

void Msort(int *a,int *t,int low,int high,int *move,int *comp)
{
    int i,j,k,m;
    m=(low+high)/2;
    for(i=low,j=m+1,k=low;i<=m&&j<=high;)
    {
        (*comp)++;
        (*move)++;
        if(a[i]>a[j])
        {
            t[k]=a[j];
            j++;
            k++;
        }
        else
        {
            t[k]=a[i];
            i++;
            k++;
        }
        
    }
    while(i<=m)//ǰ�벿��������ʣ��
    {
        (*move)++;
        t[k]=a[i];
        i++;
        k++;
    }
    while(j<=high)//��벿��������ʣ��
    {
        (*move)++;
        t[k]=a[j];
        j++;
        k++;
    }
    for(i=low;i<=high;i++)//�����Ѿ��ź���ĸ�������t��ԭ����a��ֵ
    {
        (*move)++;
        a[i]=t[i];
    }
}

void insert_sort(int *a,int n)//ֱ�Ӳ�������
{
    int i,j,move=0,comp=0,*b;
    b=(int *)malloc((n+1)*sizeof(int));
    memcpy(b,a,(n+1)*sizeof(int));
    for(i=2;i<=n;i++)
    {
        move++;
        b[0]=b[i];//b[0]Ϊ������
        for(j=i-1;;j--)//������һ��С�ڵ���b[0]������ֹͣѭ��
        {
            comp++;
            if(b[j]>b[0])
            {
                move++;
                b[j+1]=b[j];
            }
            else
                break;
        }
        b[j+1]=b[0];
        move++;
    }
    printf("\nֱ�Ӳ���������Ҫ%d�αȽϣ�%d���ƶ�\n",comp,move);
    free(b);
}

void listinssort(int *a,int n)//���������
{
    int i,j,move=0,comp=0;
    int p,p1;
    LI *b=(LI *)malloc((n+1)*sizeof(LI));
    LI t;
    for(i=1;i<=n;i++)
    {
        b[i].data=a[i];
        b[i].next=-1;
    }
    b[0].next=1;
    for(i=2;i<=n;i++)//����̬��������
    {
        p1=0;
        p=b[p1].next;
        while(p!=-1)//�ҵ���һ�����ڵ���b[i]�������ߵ���ǰ��������ĩβֹͣ
        {
            if(b[p].data<b[i].data)
            {
                p1=p;
                p=b[p].next;
            }
            else
                break;
        }
        b[p1].next=i;
        b[i].next=p;
    }
    p=b[0].next;
    for(i=1;i<n;i++)//�ƶ���̬�����Ԫ��ʹ֮��Ϊ��������
    {
        while(p<i)
            p=b[p].next;
        p1=b[p].next;
        if(i!=p)
        {
            move+=3;
            t=b[i];
            b[i]=b[p];
            b[p]=t;
            b[i].next=p;
        }
        p=p1;    
    }
    printf("\n�����������Ҫ%d�αȽϣ�%d���ƶ�\n",comp,move);
    free(b);
}

void BInsertSort(int *a,int n)//�۰��������
{
    int move=0,comp=0;
    int *b,i,j,low,high,mid;
    b=(int *)malloc((n+1)*sizeof(int));
    memcpy(b,a,(n+1)*sizeof(int));
    for(i=2;i<=n;i++)
    {
        b[0]=b[i];//���ü�����
        move++;
        low=1;
        high=i-1;
        while(low<=high)
        {
            comp++;
            mid=(low+high)/2;
            if(b[mid]==b[0])
            {
                low=mid;
                break;
            }
            else if(b[mid]<b[0])
                low=mid+1;
            else
                high=mid-1;    
        }//b[low]Ϊ��һ�����ڵ���b[i]����
        for(j=i-1;j>=low;j--)
        {    
            b[j+1]=b[j];
            move++;
        }
        b[low]=b[0];
        move++;
    }
    printf("\n�۰����������Ҫ%d�αȽϣ�%d���ƶ�\n",comp,move);
    free(b);
}

int pivot(int *a,int low,int high,int *move,int *comp)
{
    a[0]=a[low];
    (*move)++;
    while(low<high)
    {
        while(low<high&&a[high]>=a[0])
        {
            high--;
            (*comp)++;
        }
        a[low]=a[high];
        (*move)++;
        while(low<high&&a[low]<=a[0])
        {
            low++;
            (*comp)++;
        }
        (*move)++;
        a[high]=a[low];
    }
    a[low]=a[0];
    (*move)++;
    return low;
}

void quicksort(int *a,int low,int high,int *move,int *comp)
{
    int pos;
    if(low<high)
    {
        pos=pivot(a,low,high,move,comp);
        quicksort(a,low,pos-1,move,comp);
        quicksort(a,pos+1,high,move,comp);
    }
}

void quick_sort(int *a,int n)//��������
{
    int *b;
    int move=0,comp=0;
    b=(int *)malloc((n+1)*sizeof(int));
    memcpy(b,a,(n+1)*sizeof(int));
    quicksort(b,1,n,&move,&comp);
    printf("\n����������Ҫ%d�αȽϣ�%d���ƶ�\n",comp,move);
    free(b);
}

void shellsort(int *a,int n,int t,int *move,int *comp)
{
    int i,j;
    for(i=t+1;i<=n;i++)
    {
        if(a[i]<a[i-t])
        {
            (*move)++;
            a[0]=a[i];
            for(j=i-t;j>=0;j-=t)
            {
                (*comp)++;
                if(a[0]<a[j])
                {
                    a[j+t]=a[j];
                    (*move)++;
                }
                else 
                    break;
            }
            a[j+t]=a[0];
            (*move)++;
        }
        else
            (*comp)++;
    }
}

void shell(int *a,int n)//ϣ������
{
    int i,j,*b,k,t;
    int move=0,comp=0;
    b=(int *)malloc((n+1)*sizeof(int));
    memcpy(b,a,(n+1)*sizeof(int));
    for(i=1;pow(2,i)<=n;i++);
    i--;
    while(i>=1)
    {
        t=pow(2,i)-1;
        shellsort(b,n,t,&move,&comp);
        i--;
    }
    printf("\nϣ��������Ҫ%d�αȽϣ�%d���ƶ�\n",comp,move);
    free(b);
}

void heapadjust(int *a,int n,int index,int *move,int *comp)
{
    int i,j;
    i=index;
    j=2*i;
    a[0]=a[index];
    (*move)++;
    while(j<=n)
    {
        (*comp)++;
        if(j+1<=n&&a[j+1]>a[j])
        {
            (*comp)++;
            j++;
        }
        if(a[0]<a[j])
        {
            (*move)++;
            a[i]=a[j];
            i=j;
            j=2*i;
        }
        else
            break;
    }
    a[i]=a[0];
    (*move)++;
}

void heapsort(int *a,int n)//������
{
    int i,j,*b,t;
    int move=0,comp=0;
    b=(int *)malloc((n+1)*sizeof(int));
    memcpy(b,a,(n+1)*sizeof(int));
    for(i=n/2;i>=1;i--)
        heapadjust(b,n,i,&move,&comp);
    for(i=1;i<n;i++)
    {
        move+=3;
        t=b[1];
        b[1]=b[n-i+1];
        b[n-i+1]=t;
        heapadjust(b,n-i,1,&move,&comp);
    }
    printf("\n��������Ҫ%d�αȽϣ�%d���ƶ�\n",comp,move);
    free(b);
}