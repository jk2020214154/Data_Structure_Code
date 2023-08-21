#include<iostream>
#include <limits.h>

using namespace std;

#define MAX_SIZE 110

typedef int ElemType;

typedef struct {                    // MAX_SIZE为已定义常量
    ElemType SqBiTNode[MAX_SIZE];   // 保存二叉树结点值的数组
    int ElemNum;                    // 实际占用的数组元素个数
}SqBiTree;

void InitSqBiTree(SqBiTree &T,int n,ElemType e[])
{
    for(int i=0;i<=n-1;i++)
        T.SqBiTNode[i]=e[i];
    T.ElemNum=n;
}

bool check(SqBiTree T,int id,ElemType minx,ElemType maxx)
{
    if(id>=T.ElemNum||T.SqBiTNode[id]==-1)//越界或者为空结点
        return true;
    if(T.SqBiTNode[id]<=minx||T.SqBiTNode[id]>=maxx)
        return false;
    return check(T,2*id+1,minx,T.SqBiTNode[id])&&check(T, 2*id+2, T.SqBiTNode[id], maxx);
}

bool isValidBST(SqBiTree T)
{
    return check(T,0,INT_MIN,INT_MAX);
}

void PrintTree(SqBiTree T)
{
    for(int i=0;i<T.ElemNum;i++)
        cout << T.SqBiTNode[i] << " ";
    cout << endl;
}


void Test()
{
    SqBiTree T;
    int n;
    ElemType a[MAX_SIZE];

    cin >> n;
    for(int i=0;i<=n-1;i++)
        cin >> a[i];
        
    /*
    10
    40 25 60 -1 30 -1 80 -1 -1 27
    
    11
    40 50 60 -1 30 -1 -1 -1 -1 -1 35
    */
    
    
    InitSqBiTree(T, n, a);


    PrintTree(T);
    if(isValidBST(T)==1)
        cout << "该树是二叉搜索树" << endl;
    else cout << "该树不是二叉搜索树" << endl;

}

int main()
{
    Test();
    return 0;
}