#include<iostream>
#include<stack>
#include<queue>

using namespace std;

#define MaxSize 110

typedef int ElemType;

typedef struct ThreadNode{
    ElemType value;//结点中的顺序元素
    struct ThreadNode *lchild,*rchild;    
    int ltag,rtag;//左右线索标志

    //struct ThreadNode *parent;
}ThreadNode,*ThreadTree;

void InitTree(ThreadTree &T)
{
    T=NULL;//初始化可将根节点置空，空树
    T=(ThreadTree)malloc(sizeof(ThreadTree));
    T->value=1;
    T->lchild=NULL;
    T->rchild=NULL;
    T->ltag=0,T->rtag=0;
}

bool InsertLeftTreeNode(ThreadNode *&T,ElemType e)
{
    ThreadNode *p=(ThreadNode *)malloc(sizeof(ThreadNode));
    if(p==NULL)
        return false;
    p->value=e;
    p->lchild=NULL;
    p->rchild=NULL;
    p->ltag=0,p->rtag=0;
    T->lchild=p;
    return true;
}

bool InsertRightTreeNode(ThreadNode *&T,ElemType e)
{
    ThreadNode *p=(ThreadNode *)malloc(sizeof(ThreadNode));
    if(p==NULL)
        return false;
    p->value=e;
    p->lchild=NULL;
    p->rchild=NULL;
    p->ltag=0,p->rtag=0;
    T->rchild=p;
    return true;    
}

void ReleaseTree(ThreadTree t)//释放二叉树空间
{ 
  	if(t!=NULL){
        if(t->ltag==0)
    	    ReleaseTree(t->lchild);
        if(t->rtag==0)
            ReleaseTree(t->rchild);
    	free(t);
  	}
}

ThreadNode *pre=NULL;//指向当前访问结点的前驱

void visit(ThreadNode *q)//访问当前结点的数据
{
    if(q->lchild==NULL)//左子树为空建立前驱线索
    {
        q->lchild=pre;
        q->ltag=1;
    }
    if(pre!=NULL&&pre->rchild==NULL)//建立前驱结点的后继结点
    {
        pre->rchild=q;
        pre->rtag=1;
    }
    pre=q;
}

void PostThread(ThreadTree T)//后序线索化
{
    if(T!=NULL)
    {
        PostThread(T->lchild);//递归遍历左子树
        PostThread(T->rchild);//递归遍历右子树
        visit(T);//访问根节点
    }
}

void CreatePostThread(ThreadTree T)
{
    pre=NULL;//pre初始为NULL
    if(T!=NULL)//非空二叉树才能线索化
    {
        PostThread(T);//后序线索化二叉树
        if(pre->rchild==NULL)//处理遍历的最后一个结点(此处if可省略)
            pre->rtag=1;
    }
}


void Print(ThreadNode *q)
{
    if(q!=NULL)
    {
        cout << "value: " << q->value << " ltag: " << q->ltag << " rtag: " << q->rtag << endl;
        if(q->lchild!=NULL)
            cout << q->lchild->value;
        else cout << "NULL";
        if(q->rchild!=NULL)
            cout << " " << q->rchild->value << endl;
        else cout << " NULL" << endl;
    }
}

void PostOrder(ThreadTree T)//后序遍历
{
    if(T!=NULL)
    {
        if(T->ltag==0)
            PostOrder(T->lchild);//递归遍历左子树
        if(T->rtag==0)
            PostOrder(T->rchild);//递归遍历右子树
        Print(T);//访问根结点
    }
}


//在后序线索二叉树中找到结点p的后继结点
ThreadNode* Prenode(ThreadNode *p)
{
    if(p->ltag==0)
    {
        if(p->rchild!=NULL&&p->rtag==0)
            return p->rchild;
        else if(p->lchild!=NULL&&p->ltag==0)
            return p->lchild;
        else return NULL;
    }
    else return p->lchild;//ltag==1直接返回前驱线索
}

void RevInorder(ThreadNode* T)//利用线索二叉树实现逆向后序遍历
{
    for(ThreadNode *p=T;p!=NULL;p=Prenode(p))
        cout << p->value << " ";
}

void Test()
{
    ThreadTree T;
    InitTree(T);
    InsertLeftTreeNode(T, 2);
    InsertRightTreeNode(T, 3);
    InsertLeftTreeNode(T->lchild, 4);
    InsertRightTreeNode(T->lchild, 5);
    InsertLeftTreeNode(T->rchild, 6);
    InsertRightTreeNode(T->lchild->lchild, 7);
    
    CreatePostThread(T);

    PostOrder(T);

    cout << "逆向中序遍历:";
    RevInorder(T);
    
    
    ReleaseTree(T);

}

int main()
{
    Test();
    return 0;
}