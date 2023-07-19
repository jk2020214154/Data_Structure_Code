#include<iostream>
#include <stdlib.h>
using namespace std;

#define InitSize 5

typedef int ElemType;

typedef struct{
    ElemType *data;
    int MaxSize;
    int length;
}SeqList;


void InitList(SeqList &L)//初始化
{
    L.data=(ElemType*)malloc(InitSize*sizeof(ElemType));
    if(L.data==NULL)
        exit(1);
    L.length=0;
    L.MaxSize=InitSize;
}

bool IncreaseSize(SeqList &L,int len)//增加动态数组长度(辅助函数)
{
    ElemType *p=L.data;
    L.data=(ElemType*)malloc((L.MaxSize+len)*sizeof(ElemType));

    if(L.data==NULL)
        return false;
    for(int i=0;i<L.length;i++)
        L.data[i]=p[i];
    
    L.MaxSize=L.MaxSize+len;
    free(p);
    return true;
}

bool ListInsert(SeqList &L,int i,ElemType e)//插入操作
{
    if(i<1||i>L.length+1)
        return false;
    if(L.length>=L.MaxSize)
    {
        bool status=IncreaseSize(L, 10);
        if(status==false)
            return false;
    }

    for(int j=L.length;j>=i;j--)
        L.data[j]=L.data[j-1];
    
    L.data[i-1]=e;
    L.length++;
    return true;
}


bool ListDelete(SeqList &L,int i,ElemType &e)//删除操作
{
    if(i<1||i>L.length)
        return false;
    
    e=L.data[i-1];
    for(int j=i;j<L.length;j++)
        L.data[j-1]=L.data[j];
    L.length--;
    return true;
}


ElemType GetElem(SeqList L,int i)//按位查找
{
    if(i>=1&&i<=L.length)
        return L.data[i-1];
    else return INT_MIN;
}

int LocateElem(SeqList L,ElemType e)//按值查找第一个值为e的位置
{
    for(int i=0;i<L.length;i++)
        if(L.data[i]==e)
            return i+1;
    return -1;
}

int getLength(SeqList L)//获取线性表的长度
{
    return L.length;
}

void PrintList(SeqList L)//打印线性表的数据元素
{
    for(int i=0;i<L.length;i++)
        cout << L.data[i] << " ";
    cout << endl;
}

bool Empty(SeqList L)//判断线性表是否为空
{
    return L.length==0;
}

void DestroyList(SeqList &L)//销毁线性表
{
    free(L.data);
    L.length=0;
}

int a[]={0,11,13,15,17,19};
int b[]={0,2,4,6,8,20};
int c[]={0,1,2,6,10};
int d[]={0,3,8,10,11};

// bool Search_Median(SeqList L1,SeqList L2,int n,ElemType &e)//n为每个线性表的长度
// {
//     if(L1.length==0||L2.length==0||L1.length!=L2.length)
//         return false;
    
//     ElemType *ans=(ElemType *)malloc(2*n*sizeof(ElemType));

//     int i=0,j=0,k=0;

//     while(i<n&&j<n)
//     {
//         if(L1.data[i]<=L2.data[j])
//             ans[k++]=L1.data[i++];
//         else ans[k++]=L2.data[j++];
//     }
//     while(i<n)
//         ans[k++]=L1.data[i++];
//     while(j<n)
//         ans[k++]=L2.data[j++];
    
//     e=ans[n-1];

//     return true;
// }

// bool Search_Median(SeqList L1,SeqList L2,int n,ElemType &e)//n为每个线性表的长度
// {
//     if(L1.length==0||L2.length==0||L1.length!=L2.length)
//         return false;
    
//     ElemType *ans=(ElemType *)malloc(n*sizeof(ElemType));

//     int i=0,j=0,k=0;

//     while(i<n&&j<n&&k<n)
//     {
//         if(L1.data[i]<=L2.data[j])
//             ans[k++]=L1.data[i++];
//         else ans[k++]=L2.data[j++];
//     }
//     while(i<n&&k<n)
//         ans[k++]=L1.data[i++];
//     while(j<n&&k<n)
//         ans[k++]=L2.data[j++];
    
//     e=ans[n-1];

//     return true;
// }

// bool Search_Median(SeqList L1,SeqList L2,int n,ElemType &e)//n为每个线性表的长度
// {
//     if(L1.length==0||L2.length==0||L1.length!=L2.length)
//         return false;
    
//     int i=0,j=0,k=0;

//     while(i<n&&j<n&&k<n)
//     {
//         if(L1.data[i]<=L2.data[j])
//             e=L1.data[i++];
//         else e=L2.data[j++];
//         k++;
//     }
//     while(i<n&&k<n)
//         e=L1.data[i++],k++;
//     while(j<n&&k<n)
//         e=L2.data[j++],k++;
    
//     return true;
// }

bool Search_Median(SeqList L1,SeqList L2,int n,ElemType &e)//n为每个线性表的长度
{
    if(L1.length==0||L2.length==0||L1.length!=L2.length)
        return false;
    
    int l1=0,r1=n-1;//线性表L1的左右边界
    int l2=0,r2=n-1;//线性表L2的左右边界

    while(r1>l1)
    {
        int mid1=(l1+r1)/2;
        int mid2=(l2+r2)/2;
        //cout << l1 << " " << r1 << " " << mid1 << endl;
        //cout << l2 << " " << r2 << " " << mid2 << endl;
        if(L1.data[mid1]==L2.data[mid2])//相等,两者均为中位数
        {
            e=L1.data[mid1];
            return true;
        }
        else if(L1.data[mid1]<L2.data[mid2])//x<y,把小于x和大于y的排除
        {
            if((r1-l1+1)%2==1)//奇数
            {
                l1=mid1;
                r2=mid2;
            }
            else//偶数
            {
                l1=mid1+1;//当前mid不可能成为中位数
                r2=mid2;
            }
        }
        else//x>y,把大于x和小于y的排除
        {
            if((r1-l1+1)%2==1)//奇数
            {
                r1=mid1;
                l2=mid2;
            }
            else//偶数
            {
                r1=mid1;
                l2=mid2+1;//当前mid不可能成为中位数
            }
        }
    }

    e=min(L1.data[l1],L2.data[l2]);
    
    return true;
}

void Test()
{
    int n=5,m=4;
    SeqList L1,L2,L3,L4;
    InitList(L1);
    InitList(L2);
    InitList(L3);
    InitList(L4);

    for(int i=1;i<=n;i++)
    {
        ListInsert(L1, i, a[i]);
        ListInsert(L2, i, b[i]);
    }

    for(int i=1;i<=m;i++)
    {
        ListInsert(L3, i, c[i]);
        ListInsert(L4, i, d[i]);
    }
    
    PrintList(L1);
    PrintList(L2);
    PrintList(L3);
    PrintList(L4);

    ElemType num;

    Search_Median(L1, L2, n, num);
    

    cout << num << endl;
    
    Search_Median(L3, L4, m, num);
    
    cout << num << endl;
    
    DestroyList(L1);
    DestroyList(L2);
    DestroyList(L3);
    DestroyList(L4);
}


int main()
{
    Test();
    return 0;
}