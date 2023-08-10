#include<iostream>
#include<stack>
#include<queue>

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

void ReleaseTree(BiTree t)//释放二叉树空间
{ 
  	if(t!=NULL){
    	ReleaseTree(t->lchild);
    	ReleaseTree(t->rchild);
    	free(t);
  	}
}

BiTNode *p;//p指向目标结点
BiTNode *pre=NULL;//指向当前结点的前驱
BiTNode *final=NULL;//用于记录最终结果

void visit(BiTNode * q)//访问当前结点的数据
{
    if(p==q)
        final=pre;
    else pre=q;
}

void InOrder_Find_Pre(BiTree T)//中序遍历
{
    if(T!=NULL)
    {
        InOrder_Find_Pre(T->lchild);//递归遍历左子树
        visit(T);//访问根节点
        InOrder_Find_Pre(T->rchild);//递归遍历右子树
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
    InsertRightTreeNode(T->lchild->lchild, 7);
    p=T->rchild->lchild;
    
    InOrder_Find_Pre(T);

    if(final!=NULL)
        cout << "中序前驱的值:" << final->value << endl;

    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}