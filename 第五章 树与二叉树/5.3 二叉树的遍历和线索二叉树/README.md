`visit函数`用来对当前结点的某种操作

```cpp
void visit(BiTNode * p)//访问当前结点的数据
{
    cout << p->value << " ";
}
```

#### 二叉树的前序遍历

* 递归版

```cpp
void PreOrder(BiTree T)//前序遍历
{
    if(T!=NULL)
    {
        cout << T->value << " ";//访问根节点
        PreOrder(T->lchild);//递归遍历左子树
        PreOrder(T->rchild);//递归遍历右子树
    }
}
```

* 非递归版

对于非递归遍历可参考一下递归遍历，在递归遍历中，除去`visit()`函数，三种遍历完全一致，所以**访问路径**也应该一致

![](https://cdn.acwing.com/media/article/image/2023/08/09/85276_53d7490c36-20230809134032.png)

 可以看到三种遍历的**访问路径完全一致**，只是访问结点时机不同，前序遍历在**第一次到结点时**(从`根结点`出发)就进行访问(**第一次**到达该结点)，中序遍历为**第一次回到结点**(从`左子树`返回)进行访问(**第二次**到达该结点)，后序遍历为**第二次回到结点**(从`右子树`返回)进行访问(**第三次**到达该结点)。叶子结点同样对其左右孩子进行访问。

>  访问结点的时机取决于是哪种遍历(前序遍历、中序遍历、后序遍历)
>
>  1)**访问结点 **$P$，并将结点 $P$入栈;
>
>  2)判断结点 $P$的左孩子是否为空，若为空，则取栈顶结点并进行出栈操作，并将栈顶结点的右孩子置为当前的结点 $P$，循环至1);若不为空，则将 $P$的左孩子置为当前的结点 $P$;
>
>  3)直到 $P$为 $NULL$并且栈为空，则遍历结束。

```cpp
//C++中STL的栈
while(p!=NULL||s.empty()==0)//p不空或栈不空
{
    if(p!=NULL)//一路向左
    {
        s.push(p);//当前结点入栈
        p=p->lchild;//左孩子不空,一直向左走
    }
    else//出栈,并转向出栈结点的右子树
    {
        p=s.top();//获取栈顶
        s.pop();//栈顶元素出栈

        p=p->rchild;//向右子树走,p赋值为当前出栈元素的右孩子
    }
}
```

故前序遍历的非递归如下:

```cpp
void PreOrder_Non_Recursive(BiTree T)//前序遍历非递归
{
    stack<BiTNode* > s;//此处为了方便使用c++中的stl

    BiTNode *p=T;

    while(p!=NULL||s.empty()==0)//p不空或栈不空
    {
        if(p!=NULL)//一路向左
        {
            visit(p);// ***访问当前结点***
            s.push(p);//当前结点入栈
            p=p->lchild;//左孩子不空,一直向左走
        }
        else//出栈,并转向出栈结点的右子树
        {
            p=s.top();//获取栈顶
            s.pop();//栈顶元素出栈

            p=p->rchild;//向右子树走,p赋值为当前出栈元素的右孩子
        }
    }
}
```

#### 二叉树的中序遍历

* 递归版

```cpp
void InOrder(BiTree T)//中序遍历
{
    if(T!=NULL)
    {
        InOrder(T->lchild);//递归遍历左子树
        visit(T);//访问根节点
        InOrder(T->rchild);//递归遍历右子树
    }
}
```

* 非递归版

>  1)若其左孩子不为空，则将 $P$入栈并将 $P$的左孩子置为当前的 $P$，然后对当前结点 $P$再进行相同的处理；
>
> 2)若其左孩子为空，则取栈顶元素并进行出栈操作，**访问该栈顶结点**，然后将当前的 $P$置为栈顶结点的右孩子；
>
> 3)直到 $P$为 $NULL$并且栈为空则遍历结束。

```cpp
void InOrder_Non_Recursive(BiTree T)//中序遍历非递归
{
    stack<BiTNode* > s;//此处为了方便使用c++中的stl

    BiTNode *p=T;

    while(p!=NULL||s.empty()==0)//p不空或栈不空
    {
        if(p!=NULL)//一路向左
        {
            s.push(p);//当前结点入栈
            p=p->lchild;//左孩子不空,一直向左走
        }
        else//出栈,并转向出栈结点的右子树
        {
            p=s.top();//获取栈顶
            s.pop();//栈顶元素出栈

            visit(p);// ***访问当前结点***
            p=p->rchild;//向右子树走,p赋值为当前出栈元素的右孩子
        }
    }
}
```

#### 二叉树的后序遍历

* 递归版

```cpp
void PostOrder(BiTree T)//后序遍历
{
    if(T!=NULL)
    {
        PostOrder(T->lchild);//递归遍历左子树
        PostOrder(T->rchild);//递归遍历右子树
        cout << T->value << " ";//访问根结点
    }
}
```

* 非递归版

后序遍历的非递归实现是三种遍历方式中最难的一种。因为在后序遍历中，要保证左孩子和右孩子都已被访问并且左孩子在右孩子前访问才能访问根结点。

**第一种思路**：对于任一结点 $P$，将其入栈，然后沿其左子树一直往下搜索，直到搜索到没有左孩子的结点，此时该结点出现在栈顶，但是此时不能将其出栈并访问， 因此其右孩子还未被访问。所以接下来按照相同的规则对其右子树进行相同的处理，当访问完其右孩子时，该结点又出现在栈顶，此时可以将其出栈并访问。这样就保证了正确的访问顺序。可以看出，在这个过程中，每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。因此需要多**设置一个变量标识该结点是否是第一次出现在栈顶**。

```cpp
typedef struct StackNode{
    BiTNode *bitnode;
    bool isFirst;
}StackNode;

void PostOrder_Non_Recursive1(BiTree T)//后序遍历非递归
{
    stack<StackNode* > s;//此处为了方便使用c++中的stl

    BiTNode *p=T;

    while(p!=NULL||s.empty()==0)//p不空或栈不空
    {
        if(p!=NULL)//一路向左
        {
            StackNode *new_node=(StackNode *)malloc(sizeof(StackNode));
            new_node->bitnode=p;
            new_node->isFirst=true;//标记第一次访问
            
            //s.push(p);//当前结点入栈
            s.push(new_node);

            p=p->lchild;//左孩子不空,一直向左走
        }
        else//出栈,并转向出栈结点的右子树
        {
            StackNode *temp_node=s.top();//获取栈顶
            s.pop();//栈顶元素出栈

            if(temp_node->isFirst==true)//表示是第一次出现在栈顶(从左子树返回)
            {
                temp_node->isFirst=false;
                s.push(temp_node);
                p=temp_node->bitnode->rchild;//向右子树走,p赋值为当前出栈元素的右孩子
            }
            else//第二次出现在栈顶 
            {
                visit(temp_node->bitnode);// ***访问当前结点***
                p=NULL;//结点访问完后,重置p指针
            }
        }
    }
}
```

**第二种思路**：要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点 $P$，先将其入栈。如果 $P$不存在左孩子和右孩子，则可以直接访问它；或者 $P$存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。若非上述两种情况，则将 $P$的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。用**辅助指针**记录最近访问过的结点。

```cpp
void PostOrder_Non_Recursive2(BiTree T)//后序遍历非递归
{
    stack<BiTNode* > s;//此处为了方便使用c++中的stl

    BiTNode *p=T;
    BiTNode *pre=NULL;

    while(p!=NULL||s.empty()==0)//p不空或栈不空
    {
        if(p!=NULL)//一路向左
        {
            s.push(p);//当前结点入栈
            p=p->lchild;//左孩子不空,一直向左走
        }
        else//向右
        {
            p=s.top();//获取栈顶
            if(p->rchild!=NULL&&p->rchild!=pre)//若右子树存在,且未被访问
                p=p->rchild;//转向右
            else//否则,弹出结点并访问
            {
                s.pop();
                visit(p);// ***访问当前结点***
                pre=p;
                p=NULL;//结点访问完,重置p指针
            }
        }
    }
}
```

#### 二叉树的层序遍历

