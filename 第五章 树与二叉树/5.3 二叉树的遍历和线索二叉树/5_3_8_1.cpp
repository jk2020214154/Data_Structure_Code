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

int ans=0;

void visit(BiTNode * p)//访问当前结点的数据
{
    //cout << p->value << " ";
    if(p->lchild!=NULL&&p->rchild!=NULL)
        ans++;
}

void PreOrder(BiTree T)//前序遍历
{
    if(T!=NULL)
    {
        visit(T);//访问根节点
        PreOrder(T->lchild);//递归遍历左子树
        PreOrder(T->rchild);//递归遍历右子树
    }
}


void InOrder(BiTree T)//中序遍历
{
    if(T!=NULL)
    {
        InOrder(T->lchild);//递归遍历左子树
        visit(T);//访问根节点
        InOrder(T->rchild);//递归遍历右子树
    }
}


void PostOrder(BiTree T)//后序遍历
{
    if(T!=NULL)
    {
        PostOrder(T->lchild);//递归遍历左子树
        PostOrder(T->rchild);//递归遍历右子树
        visit(T);//访问根结点
    }
}

void LevelOrder(BiTree T)//层次遍历
{
    queue<BiTNode *> q;//此处为了方便使用c++中的stl

    q.push(T);//将根结点入队

    while(q.empty()==0)
    {
        BiTNode *p=q.front();//队头结点出队
        q.pop();
        visit(p);//访问队头元素

        if(p->lchild!=NULL)//左子树不空,将左子树根结点入队
            q.push(p->lchild);
        if(p->rchild!=NULL)//右子树不空,将右子树根结点入队
            q.push(p->rchild);
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
    InsertLeftTreeNode(T->lchild->lchild,8);


    ans=0;
    PreOrder(T);

    cout << "(先序)双分支结点个数:" << ans << endl;

    ans=0;
    InOrder(T);

    cout << "(中序)双分支结点个数:" << ans << endl;

    ans=0;
    PostOrder(T);

    cout << "(后序)双分支结点个数:" << ans << endl;
    
    ans=0;
    LevelOrder(T);

    cout << "(层序)双分支结点个数:" << ans << endl;

    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}