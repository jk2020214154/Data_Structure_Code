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

int Calc_Double_Brach(BiTree T)
{
    if(T==NULL)//结点为空
        return 0;
    else if(T->lchild!=NULL&&T->rchild!=NULL)//当前是双分支结点
        return Calc_Double_Brach(T->lchild)+Calc_Double_Brach(T->rchild)+1;
    else return Calc_Double_Brach(T->lchild)+Calc_Double_Brach(T->rchild);//叶子结点或单分子结点
}


void Test()
{
    BiTree T;
    InitTree(T);
    InsertLeftTreeNode(T, 2);
    InsertRightTreeNode(T, 3);
    InsertLeftTreeNode(T->lchild, 4);
    //InsertRightTreeNode(T->lchild, 5);
    //InsertLeftTreeNode(T->rchild, 6);
    InsertRightTreeNode(T->rchild, 7);
    InsertLeftTreeNode(T->lchild->lchild,8);

    cout << "双分支结点个数:" << Calc_Double_Brach(T) << endl;


    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}