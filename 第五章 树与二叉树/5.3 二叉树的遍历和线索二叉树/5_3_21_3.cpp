#include<iostream>
#include <limits.h>
#include<vector>

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

bool InOrder(SqBiTree T,int id,ElemType &prev)
{
    if(id>=T.ElemNum||T.SqBiTNode[id]==-1)//越界或者为空结点
        return true;
    if(InOrder(T, 2*id+1, prev)==false)
    //此处不能写成return InOrder(T, 2*id+1, prev);
    //当是true的时候需看右孩子
        return false;
    if(T.SqBiTNode[id]<prev)
        return false;
    prev=T.SqBiTNode[id];
    return InOrder(T, 2*id+2, prev);
}

bool isValidBST(SqBiTree T)
{
    ElemType prev=0;
    return InOrder(T, 0, prev);
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