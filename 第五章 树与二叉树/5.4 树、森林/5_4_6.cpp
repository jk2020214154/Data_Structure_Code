#include <cstdlib>
#include<iostream>

using namespace std;

#define MAX_TREE_SIZE 100
typedef char ElemType;

typedef struct CSNode
{
    ElemType data;
    struct CSNode *firstchild,*nextsibling;//第一个孩子和右兄弟节点
    //类似于二叉树中左孩子(第一个孩子),右孩子(右兄弟节点)
}CSNode,*CSTree;

void Init_Tree(CSTree &t)//使用先序遍历初始化
{
    ElemType e;
    cin >> e;
    if(e=='#')
        t=NULL;
    else
    {
        t=(CSNode *)malloc(sizeof(CSNode));
        t->data=e;
        Init_Tree(t->firstchild);
        Init_Tree(t->nextsibling);
    }
}

void InOrder(CSTree t)
{
    if(t!=NULL)
    {
        InOrder(t->firstchild);
        cout << t->data << " ";
        InOrder(t->nextsibling);
    }
}

void Init_Tree_By_LevelOrder(CSTree &t,ElemType e[],int degree[],int n)
{
    CSTree *temp=new CSTree[MAX_TREE_SIZE];

    for(int i=0;i<=n-1;i++)//初始化赋值和置空
    {
        temp[i] = new CSNode;//一定记得初始化
        temp[i]->data=e[i];
        temp[i]->firstchild=temp[i]->nextsibling=NULL;
    }

    int pos=0;
    for(int i=0;i<=n-1;i++)//遍历至第i个结点
    {
        if(degree[i]>0)//如果有孩子
        {
            temp[i]->firstchild=temp[++pos];//第一个孩子赋给孩子指针
            for(int j=2;j<=degree[i];j++)
            {
                temp[pos]->nextsibling=temp[pos+1];//其余孩子处理:后一个赋给前一个的兄弟指针
                pos++;
            }
        }
    }
    t=temp[0];
    //delete []temp;
}

void Test()
{
    CSTree cs;

    ElemType data[MAX_TREE_SIZE];
    int degree[MAX_TREE_SIZE];
    int n;
    cin >> data;
    
    cin >> n;
    for(int i=0;i<=n-1;i++)
        cin >> degree[i];
        
/*
ABCDE
5
2 2 0 0 0

RABCDEFGHK
10
3 2 0 1 0 0 3 0 0 0
    
ABCDEFG
7
3 2 0 1 0 0 0
*/

    Init_Tree_By_LevelOrder(cs, data, degree, n);


    InOrder(cs);
}

int main()
{
    Test();
    return 0;
}