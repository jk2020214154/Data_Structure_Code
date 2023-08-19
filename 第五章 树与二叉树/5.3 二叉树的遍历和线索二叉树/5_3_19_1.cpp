#include<iostream>
#include<stack>
#include<queue>

using namespace std;

#define MaxSize 110

typedef int ElemType;

typedef struct BiTNode{
    ElemType weight;//结点中的顺序元素
    struct BiTNode *lchild,*rchild;    
    //struct BiTNode *parent;
}BiTNode,*BiTree;

void InitTree(BiTree &T)
{
    T=NULL;//初始化可将根节点置空，空树
    T=(BiTree)malloc(sizeof(BiTree));

    T->weight=0;
    T->lchild=NULL;
    T->rchild=NULL;
}

bool InsertLeftTreeNode(BiTNode *&T,ElemType e)
{
    BiTNode *p=(BiTNode *)malloc(sizeof(BiTNode));
    if(p==NULL)
        return false;
    p->weight=e;
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
    p->weight=e;
    p->lchild=NULL;
    p->rchild=NULL;
    T->rchild=p;
    return true;    
}

void ReleaseTree(BiTree t)//释放二叉树空间
{ 
  	if(t!=NULL){
    	ReleaseTree(t->lchild);
    	ReleaseTree(t->rchild);
    	free(t);
  	}
}

int wpl_res=0;

void Wpl_PreOrder(BiTree T,int depth)
{
    if(T!=NULL)
    {
        if(T->lchild==NULL&&T->rchild==NULL)//叶子结点
            wpl_res+=(depth-1)*T->weight;//注意是路径,不是深度

        if(T->lchild!=NULL)
            Wpl_PreOrder(T->lchild, depth+1);
        if(T->rchild!=NULL)
            Wpl_PreOrder(T->rchild, depth+1);
    }
    
}

int Calc_Wpl(BiTree T)
{
    wpl_res=0;
    Wpl_PreOrder(T,1);
    return wpl_res;
}


void Test()
{
    BiTree T;
    InitTree(T);
    InsertLeftTreeNode(T, 0);
    InsertRightTreeNode(T, 9);
    InsertLeftTreeNode(T->lchild, 0);
    InsertRightTreeNode(T->lchild, 5);
    InsertLeftTreeNode(T->lchild->lchild, 0);
    InsertRightTreeNode(T->lchild->lchild, 2);
    InsertLeftTreeNode(T->lchild->lchild->lchild, 1);
    InsertRightTreeNode(T->lchild->lchild->lchild, 2);


    cout << Calc_Wpl(T) << endl;

    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}