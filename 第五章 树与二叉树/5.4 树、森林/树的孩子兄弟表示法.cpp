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


void Test()
{
    CSTree cs;
    Init_Tree(cs);
    /*
    RAD#E##B#CFG#H#K#####
    */

    InOrder(cs);
}

int main()
{
    Test();
    return 0;
}