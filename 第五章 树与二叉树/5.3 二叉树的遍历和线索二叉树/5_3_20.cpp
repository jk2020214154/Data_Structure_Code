#include<iostream>
#include<stack>
#include<queue>
#include<cstring>

using namespace std;

#define MaxSize 110

typedef char ElemType;

typedef struct BiTNode{
    ElemType data[10];//结点中的顺序元素
    struct BiTNode *left,*right;    
    //struct BiTNode *parent;
}BTree;

void InitTree(BTree * &T)
{
    T=NULL;//初始化可将根节点置空，空树
    T=(BTree*)malloc(sizeof(BTree));

    strcpy(T->data,"*");
    //strcpy(T->data,"+");
    T->left=NULL;
    T->right=NULL;
}

bool InsertLeftTreeNode(BTree *&T, const char *e)
{
    BTree *p = (BTree *)malloc(sizeof(BTree));
    if (p == NULL)
        return false;
    strcpy(p->data, e);
    p->left = NULL;
    p->right = NULL;
    T->left = p;
    return true;
}

bool InsertRightTreeNode(BTree *&T, const char *e)
{
    BTree *p = (BTree *)malloc(sizeof(BTree));
    if (p == NULL)
        return false;
    strcpy(p->data, e);
    p->left = NULL;
    p->right = NULL;
    T->right = p;
    return true;
}

void ReleaseTree(BTree * t)//释放二叉树空间
{ 
  	if(t!=NULL){
    	ReleaseTree(t->left);
    	ReleaseTree(t->right);
    	free(t);
  	}
}


void visit(BTree *p)//访问当前结点的数据
{
    printf(" %s ",p->data);
}

void InOrder(BTree *T,int depth)//中序遍历
{
    if(T==NULL)
        return ;
    if(T->left!=NULL||T->right)
    {
        if(depth>1)
            cout << "(";
        InOrder(T->left,depth+1);//递归遍历左子树
        visit(T);//访问根节点
        InOrder(T->right,depth+1);//递归遍历右子树
        if(depth>1)
            cout << ")";
    }
    else visit(T);
}



void Test()
{
    BTree * T;
    InitTree(T);
    
    InsertLeftTreeNode(T, "+");
    InsertRightTreeNode(T, "*");
    InsertLeftTreeNode(T->left, "a");
    InsertRightTreeNode(T->left, "b");
    InsertLeftTreeNode(T->right, "c");
    InsertRightTreeNode(T->right, "-");
    InsertRightTreeNode(T->right->right, "d");
    
    
    // InsertLeftTreeNode(T, "*");
    // InsertLeftTreeNode(T->left, "a");
    // InsertRightTreeNode(T->left, "b");
    // InsertRightTreeNode(T, "-");
    // InsertRightTreeNode(T->right, "-");
    // InsertLeftTreeNode(T->right->right, "c");
    // InsertRightTreeNode(T->right->right, "d");


    InOrder(T,1);


    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}