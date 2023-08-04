#include<iostream>

using namespace std;

#define MaxSize 110

typedef int ElemType;

typedef struct BiTNode{
    ElemType value;//结点中的顺序元素
    struct BiTNode *lchild,*rchild;    
    //struct BiTNode *parent;
}BiTNode,*BiTree;

void InitTree(BiTree &T)
{
    T=NULL;//初始化可将根节点置空，空树
    T=(BiTree)malloc(sizeof(BiTree));

    T->value=1;
    T->lchild=NULL;
    T->rchild=NULL;
}

bool InsertLeftTreeNode(BiTNode *&T,ElemType e)
{
    BiTNode *p=(BiTNode *)malloc(sizeof(BiTNode));
    if(p==NULL)
        return false;
    p->value=e;
    p->lchild=NULL;
    p->rchild=NULL;
    T->lchild=p;
    return true;
}

bool InsertRightTreeNode(BiTNode *&T,ElemType e)
{
    BiTNode *p=(BiTNode *)malloc(sizeof(BiTNode));
    if(p==NULL)
        return false;
    p->value=e;
    p->lchild=NULL;
    p->rchild=NULL;
    T->rchild=p;
    return true;    
}


void PreOrder(BiTree T)//前序遍历
{
    if(T!=NULL)
    {
        cout << T->value << " ";
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}


void InOrder(BiTree T)//中序遍历
{
    if(T!=NULL)
    {
        InOrder(T->lchild);
        cout << T->value << " ";
        InOrder(T->rchild);
    }
}


void PostOrder(BiTree T)//后序遍历
{
    if(T!=NULL)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        cout << T->value << " ";
    }
}

int treeDepth(BiTree T)
{
    if(T==NULL)
        return 0;
    else
    {
        int l=treeDepth(T->lchild);
        int r=treeDepth(T->rchild);
        return l>r?l+1:r+1;
    }
}


void Test()
{
    BiTree T;
    InitTree(T);
    InsertLeftTreeNode(T, 2);
    InsertRightTreeNode(T, 3);
    InsertLeftTreeNode(T->lchild, 4);
    InsertRightTreeNode(T->lchild, 5);
    InsertLeftTreeNode(T->rchild, 6);
    InsertRightTreeNode(T->rchild, 7);

    cout << "前序遍历结果:";
    PreOrder(T);

    cout << endl << "中序遍历结果:";
    InOrder(T);

    cout << endl << "后序遍历结果:";
    PostOrder(T);

    cout << endl << "二叉树的深度:" << treeDepth(T) << endl;

}

int main()
{
    Test();
    return 0;
}