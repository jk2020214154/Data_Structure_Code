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

void ReleaseTree(BiTree t)//释放二叉树空间
{ 
  	if(t!=NULL){
    	ReleaseTree(t->lchild);
    	ReleaseTree(t->rchild);
    	free(t);
  	}
}

void visit(BiTNode * p)//访问当前结点的数据
{
    cout << p->value << " ";
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


BiTree CreateBiTree_by_Pre_and_In(ElemType a[],ElemType b[],int la,int ra,int lb,int rb)
{
    BiTNode *root=(BiTNode *)malloc(sizeof(BiTNode));

    root->value=a[la];//当前先序第一个元素

    int pos=lb;

    while(b[pos]!=a[la])//找到当前段中序遍历等于当前先序的第一个元素
        pos++;
    
    int left_size=pos-lb;//左子树长度
    int right_size=rb-pos;//右子树长度

    if(left_size>0)//建立左子树
        root->lchild=CreateBiTree_by_Pre_and_In(a, b, la+1, la+left_size, lb,lb+left_size-1);
    else root->lchild=NULL;//左子树为空

    if(right_size>0)
        root->rchild=CreateBiTree_by_Pre_and_In(a, b, ra-right_size+1, ra, rb-right_size+1, rb);
    else root->rchild=NULL;

    return root;
}


void Test()
{
    int n;
    ElemType pre_list[MaxSize];
    ElemType in_list[MaxSize];
    cin >> n;

    for(int i=1;i<=n;i++)
        cin >> pre_list[i];
    
    for(int i=1;i<=n;i++)
        cin >> in_list[i];

    /*
    9
    1 2 4 5 8 3 6 9 7
    4 2 8 5 1 6 9 3 7
    
    后序: 4 8 5 2 9 6 7 3 1
    */
    

    BiTree T=CreateBiTree_by_Pre_and_In(pre_list, in_list, 1, n, 1, n);

    
    cout << "前序遍历结果:";
    PreOrder(T);

    cout << endl << "中序遍历结果:";
    InOrder(T);

    cout << endl << "后序遍历结果:";
    PostOrder(T);

    ReleaseTree(T);
}

int main()
{
    Test();
    return 0;
}