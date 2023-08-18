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

void InThread(ThreadTree T)//中序线索化
{
    if(T!=NULL)
    {
        InThread(T->lchild);//递归遍历左子树
        visit(T);//访问根节点
        InThread(T->rchild);//递归遍历右子树
    }
}

void CreateInThread(ThreadTree T)
{
    pre=NULL;//pre初始为NULL
    if(T!=NULL)//非空二叉树才能线索化
    {
        InThread(T);//中序线索化二叉树
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

void InOrder(ThreadTree T)//中序遍历
{
    if(T!=NULL)
    {
        if(T->ltag==0)
            InOrder(T->lchild);//递归遍历左子树
        Print(T);//访问根节点
        if(T->rtag==0)
            InOrder(T->rchild);//递归遍历右子树
    }
}


//找到以p为根的子树中,第一个被中序遍历的结点
ThreadNode* Firstnode(ThreadNode *p)
{
    //循环找到最左下结点(不一定是叶节点)
    while(p->ltag==0)
        p=p->lchild;
    return p;
}

//在中序线索二叉树中找到结点p的后继结点
ThreadNode* Nextnode(ThreadNode *p)
{
    if(p->rtag==0)//右子树中最左下结点
        return Firstnode(p->rchild);
    else return p->rchild;//rtag==1直接返回后继线索
}


void Inorder(ThreadNode* T)//利用线索二叉树实现中序遍历
{
    for(ThreadNode *p=Firstnode(T);p!=NULL;p=Nextnode(p))
        cout << p->value << " ";
}

//找到以p为根的子树中,最后一个被中序遍历的结点
ThreadNode* Lastnode(ThreadNode *p)
{
    //循环找到最右下结点(不一定是叶节点)
    while(p->rtag==0)
        p=p->rchild;
    return p;
}

//在中序线索二叉树中找到结点p的前驱结点
ThreadNode* Prenode(ThreadNode *p)
{
    if(p->ltag==0)//左子树中最右下结点
        return Lastnode(p->lchild);
    else return p->lchild;//ltag==1直接返回前驱线索
}

void RevInorder(ThreadNode* T)//利用线索二叉树实现逆向中序遍历
{
    for(ThreadNode *p=Lastnode(T);p!=NULL;p=Prenode(p))
        cout << p->value << " ";
}

ThreadNode * Get_PostPre_By_InOrder(ThreadNode * p)
{
    if(p==NULL)
        return NULL;
    if(p->rtag==0)//有右孩子,则右孩子是它的前驱
        return p->rchild;
    else if(p->ltag==0)//只有左孩子,则右孩子是它的前驱
        return p->lchild;
    
    while(p!=NULL&&p->ltag==1)//p的最近的<祖先的左孩子>
        p=p->lchild;
    
    if(p!=NULL)
        return p->lchild;
    else return NULL;
}


void Test()
{
    ThreadTree T;
    InitTree(T);
    InsertLeftTreeNode(T, 2);
    InsertRightTreeNode(T, 3);
    InsertLeftTreeNode(T->lchild, 4);
    InsertRightTreeNode(T->lchild, 5);
    InsertRightTreeNode(T->rchild, 6);
    InsertLeftTreeNode(T->rchild->rchild, 7);
    InsertRightTreeNode(T->rchild->rchild, 8);

    
    CreateInThread(T); 
    //InOrder(T);

    ThreadNode *p=Get_PostPre_By_InOrder(T);
    p=Get_PostPre_By_InOrder(T->lchild);
    p=Get_PostPre_By_InOrder(T->rchild);
    p=Get_PostPre_By_InOrder(T->lchild->lchild);
    p=Get_PostPre_By_InOrder(T->lchild->rchild);
    p=Get_PostPre_By_InOrder(T->rchild->rchild);
    p=Get_PostPre_By_InOrder(T->rchild->rchild->lchild);
    //p=Get_PostPre_By_InOrder(T->rchild->rchild->rchild);
    
    
    /*
    中序:
    4 2 5 1 3 7 6 8
    后序:
    4 5 2 7 8 6 3 1
    */
    

    if(p==NULL)
        cout << "不存在" << endl;
    else cout << p->value << endl;
    
    ReleaseTree(T);

}

int main()
{
    Test();
    return 0;
}