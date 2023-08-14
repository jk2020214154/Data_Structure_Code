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

```cpp
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
```

#### 由遍历序列构造二叉树

* 由二叉树的`先序序列`和**中序序列**可以唯一确定一棵二叉树.
* 由二叉树的`后序序列`和**中序序列**可以唯一确定一棵二叉树.
* 由二叉树的`层序序列`和**中序序列**可以唯一确定一棵二叉树.

前序、后序、层序序列的两两组合**无法唯一确定**一棵二叉树

#### 线索二叉树

核心

```cpp
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
```

* 前序线索化

```cpp
void PreThread(ThreadTree T)//前序线索化
{
    if(T!=NULL)
    {
        visit(T);//访问根节点
        if(T->ltag==0)
            PreThread(T->lchild);//递归遍历左子树
        if(T->rtag==0) //注意王道此处未加,实际应加上
            PreThread(T->rchild);//递归遍历右子树
    }
}

void CreatePreThread(ThreadTree T)
{
    pre=NULL;//pre初始为NULL
    if(T!=NULL)//非空二叉树才能线索化
    {
        PreThread(T);//前序线索化二叉树
        if(pre->rchild==NULL)//处理遍历的最后一个结点(此处if可省略)
            pre->rtag=1;
    }
}
```

* 中序线索化

```cpp
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
```

* 后序线索化

```cpp
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
```

#### 在线索二叉树中找前驱后继

* 中序线索二叉树找**中序后继**并实现中序遍历

>  1.若 $p\to rtag=1$,则 $next=p \to rchild$(有后继线索);
>
> 2.若 $p \to rtag=0$,则 $next=p$的**右子树中最左下结点**.

```cpp
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
```

* 中序线索二叉树找**中序前驱**并实现逆向中序遍历

>  1.若 $p\to ltag=1$,则 $pre=p \to lchild$(有前驱线索);
>
> 2.若 $p \to ltag=0$,则 $pre=p$的**左子树中最右下结点**.

```cpp
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
```

* 先序线索二叉树找先序后继

>  1.若 $p \to rtag=1$,则 $next=p \to rchild$(有后继线索);
>
> 2.若 $p \to rtag=0$,则:
>
> 当 $p$有左孩子,则先序后继为**左孩子**;当 $p$没有左孩子,则先序后继为**右孩子**.

```cpp
//在先序线索二叉树中找到结点p的后继结点
ThreadNode* Nextnode(ThreadNode *p)
{
    if(p->rtag==0)
    {
        if(p->lchild!=NULL&&p->ltag==0)
            return p->lchild;
        else if(p->rchild!=NULL&&p->rtag==0)
            return p->rchild;
        else return NULL;
    }
    else return p->rchild;//rtag==1直接返回后继线索
}


void Preorder(ThreadNode* T)//利用线索二叉树实现先序遍历
{
    for(ThreadNode *p=T;p!=NULL;p=Nextnode(p))
        cout << p->value << " ";
}
```

* 先序线索二叉树找先序前驱(**无法实现**,`无指向父结点的指针`的条件下,由于左右子树中的结点只能是根的后继,不可能是前驱)

基于**三叉链表**可实现先序前驱的查找

> 1.如果能找到 $p$的父结点,且 $p$是左孩子,此时 $p$的父结点是 $p$的前驱;
>
> 2.如果能找到 $p$的父结点,且 $p$是右孩子,其左兄弟为空,此时 $p$的父结点是 $p$的前驱;
>
> 3.如果能找到 $p$的父结点,且 $p$是右孩子,其左兄弟非空,此时 $p$的前驱为**左兄弟子树中最后一个被先序遍历的结点**;
>
> 4.如果 $p$是根结点,则 $p$无先序前驱.

* 后序线索二叉树找后序前驱

>  1.若 $p \to ltag=1$,则 $pre=p \to lchild$;
>
> 2.若 $p \to ltag=0$,则:
>
> 当 $p$有右孩子,则后序前驱为右孩子;当 $p$没有右孩子,则后序前驱为左孩子.

```cpp
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
```

* 后序线索二叉树找后序后继(**无法实现**,`无指向父结点的指针`的条件下,左右子树中的结点只可能是根的前驱,不可能是后继)

基于**三叉链表**可实现后序后继的查找

>  1.如果能找到 $p$的父结点,且 $p$是右孩子,此时 $p$的父结点是 $p$的后继;
>
> 2.如果能找到 $p$的父结点,且 $p$是左孩子,其右兄弟为空,此时 $p$的父结点是 $p$的后继;
>
> 3.如果能找到 $p$的父结点,且 $p$是左孩子,其右兄弟非空,此时 $p$的前驱为**右兄弟子树中第一个被后序遍历的结点**;
>
> 4.如果 $p$是根结点,则 $p$无后序后继.

![](https://cdn.acwing.com/media/article/image/2023/08/10/85276_9cc495f437-20230810225250.png) 

![](https://cdn.acwing.com/media/article/image/2023/08/10/85276_bf2f95ad37-20230810225351.png) 

>  前序为 $A,B,C$,后序为 $C,B,A$的二叉树共有().
>
> A. $1$棵
>
> B. $2$棵
>
> C. $3$棵
>
> D. $\color{Red}{4棵}$

当树的结点较少时,可通过枚举的方式进行判断.

前序为 $A,B,C$的二叉树有 $5$种结果(符合**卡特兰数** $\frac{C_{2n}^{n}}{n+1}$)

![](https://cdn.acwing.com/media/article/image/2023/08/12/85276_74a3bf7839-20230812213011.png) 

* 在第一个二叉树中,后序遍历为 $BCA$,不满足要求;
* 在第二个二叉树中,后序遍历为 $CBA$,满足要求;
* 在第三个二叉树中,后序遍历为 $CBA$,满足要求;
* 在第四个二叉树中,后序遍历为 $CBA$,满足要求;
* 在第五个二叉树中,后序遍历为 $CBA$,满足要求;

共有 $4$个满足条件的二叉树

>  **扩展**:一棵非空二叉树的先序遍历序列与后序遍历序列**正好相反**,则二叉树一定满足
>
>  * 只有一个叶结点;
>
>  * 高度等于结点数;
>
>  * 每个结点的左子树`或者`右子树为空.
>
>  若先序遍历序列与后序遍历序列**正好相同**,则只有可能为`只有根节点`



>  一棵二叉树的前序遍历序列为 $1234567$,它的中序遍历序列可能是()
>
> A. $3124567$
>
> B. $\color{Red}{1234567}$
>
> C. $4135627$
>
> D. $1463572$

> **方法**:
>
> * 硬算，把每个答案都代入一遍，如果出现矛盾的话，结果不正确。
> * 转化成入栈出栈问题。
>
> 1.一棵二叉树的前序遍历结果，就是`前序遍历`时候元素**入栈顺序**。
>
> 2.一颗二叉树的中序、后序遍历的结果，就是`中序遍历`、`后序遍历`遍历时候**元素出栈顺序**。

* 在选项 $A$中,当第一个元素 $3$出栈时, $1,2$已在栈中,而当第二个元素 $1$出栈,而栈顶元素是 $2$,不满足条件;
* 在选项 $B$中,依次入栈一个元素,出栈一个元素,满足条件;
* 在选项 $C$中,当第一个元素 $4$出栈时, $1,2,3$已在栈中,而当第二个元素 $1$出栈,而栈顶元素是 $3$,不满足条件;
* 在选项 $D$中, $1$入栈出栈,第二个元素 $4$出栈时, $2,3$已在栈中,第三个元素 $6$出栈时, $2,3,5$已在栈中第四个元素 $3$出栈时,栈顶元素是 $5$,不满足条件.

>  已知一棵二叉树的后序序列为 $DABEC$,中序序列为 $DEBAC$,则先序序列为().
>
> A. $ACBED$
>
> B. $DECAB$
>
> C. $DEABC$
>
> D. $\color{Red}{CEDBA}$

后序遍历是`左右根`的顺序,故从后序序列的最右端开始

* 从后序的倒数第一个元素 $C$开始,在中序遍历中, $DEBA$在 $C$的左子树, $C$的右子树为空;

* 从后序的倒数第二个元素 $E$,在中序遍历中, $D$在 $E$的左子树, $BA$在 $E$的右子树;(由于 $D$已安排好,故 $D$不再考虑)
* 从后序的倒数第三个元素 $B$,在中序遍历中, $B$的左子树为空, $A$在 $B$的右子树(由于 $A$已安排好,故 $A$不再考虑).

![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_19d658c139-20230813170817.png) 

故前序序列为 $CEDBA$

>  已知一棵二叉树的先序遍历结果为 $ABCDEF$,中序遍历为 $CBAEDF$,则后序遍历的结果为()
>
> A. $\color{Red}{CBEFDA}$
>
> B. $FEDCBA$
>
> C. $CBEDFA$
>
> D. 不确定

先序遍历是`根左右`的顺序,故从先序序列的最左端开始

* 从先序的第一个元素 $A$开始,在中序遍历中, $CB$在 $A$的左子树, $EDF$在 $A$的右子树;
* 从先序的第二个元素 $B$开始,在中序遍历中, $C$在 $B$的左子树, $B$的右子树为空;(由于 $C$已安排好,故 $C$不再考虑)
* 从先序的第四个元素 $D$开始,在中序遍历中, $E$在 $D$的左子树, $F$在 $D$的右子树(由于 $E,F$已安排好,故 $E,F$不再考虑).

![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_d3ad93e139-20230813172134.png) 

故后序序列为 $CBEFDA$

>   已知一棵二叉树的层序遍历结果为 $ABCDEF$,中序遍历为 $BADCFE$,则后序遍历的结果为()
>
> A. $ACBEDF$
>
> B. $\color{Red}{ABCDEF}$
>
> C. $BDFECA$
>
> D. $FCEDBA$

层序遍历和先序遍历类似,也是从头开始

* 从层序的第一个元素 $A$开始,在中序遍历中, $B$在 $A$的左子树, $DCFE$在 $A$的右子树(由于 $B$已安排好,故 $B$不再考虑);

* 从层序的第三个元素 $C$开始,在中序遍历中, $D$在 $C$的左子树, $FE$在 $C$的右子树;(由于 $D$已安排好,故 $D$不再考虑);

* 从层序的第五个元素 $E$开始,在中序遍历中, $F$在 $E$的左子树, $E$的右子树为空(由于 $F$已安排好,故 $F$不再考虑).

![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_52c4ac2b39-20230813173219.png) 

故先序序列为 $ABCDEF$

>  **2009统考真题**：给定二叉树如图所示。设 $N$代表二叉树的根， $L$代表根结点的左子树， $R$代表根结点的右子树。若遍历后的结点序列是 $3175624$,则其遍历方式是().
>
> ![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_f91d0a9539-20230813173654.png)
>
> A. $LRN$
>
> B. $NRL$
>
> C. $RLN$
>
> D. $\color{Red}{RNL}$

* 选项 $A$, 按照`左右根`(后序遍历),后序序列为 $4675231$,不满足题中序列 $\color{Green}{3175624}$;
* 选项 $B$,按照`根右左`,序列为 $1325764$,不满足题中序列 $\color{Green}{3175624}$;
* 选项 $C$,按照`右左根`,序列为 $3765421$,不满足题中序列 $\color{Green}{3175624}$;
* 选项 $D$,按照`右根左`,序列为 $3175624$,满足题中序列 $\color{Green}{3175624}$;

>  **2011统考真题**：若一棵二叉树的前序遍历序列和后序遍历序列分别为 $1,2,3,4$和 $4,3,2,1$,则该二又树的中序遍历序列不会是().
>
> A. $1,2,3,4$
>
> B. $2,3,4,1$
>
> C. $\color{Red}{3,2,4,1}$
>
> D. $4,3,2,1$

可先将中序遍历和前序(或后序)遍历**构成**一棵二叉树,再用对应的后序(或前序)去**验证**二叉树是否满足要求.

下图是根据前序和中序分别构造的二叉树

![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_23a87afb39-20230813180638.png) 

* 选项 $A$,用后序遍历去验证满足条件;
* 选项 $B$,用后序遍历去验证满足条件;
* 选项 $C$,后序序列为 $3,4,2,1$,不满足条件;
* 选项 $D$,用后序遍历去验证满足条件;

此题另可发现先序遍历序列与后序遍历序列**正好相反**,此时必然满足只有一个叶节点,故 $C$不满足条件.

>  **2012统考真题**：若一棵二叉树的前序遍历序列为 $a,e,b,d,c$,后序遍历序列为 $b,c,d,e,a$,则根结点的孩子结点( $\color{Red}{A}$).
>
> A. 只有 $e$
>
> B. 有 $e,b$
>
> C. 有 $e,c$
>
> D. 无法确定

**结论**:前序序列和后序序列不能唯一确定一棵二叉树,但可以确定二叉树中结点的祖先关系:当两个结点的前序序列为 $XY$,后序序列为 $YX$,则 $X$为 $Y$的祖先。

故 前序序列 $a,e$和后序序列 $e,a$,可得 $a$是 $e$的祖先, $e$是 $a$的孩子结点;同理前序序列 $d,c$和后序序列 $c,d$,可得 $d$是 $c$的祖先;而前序序列 $e,b,d,c$和后序序列 $b,c,d,e$中,  $e$是 $b,c,d$的祖先.

综上, $e$是根结点 $a$的孩子结点.

>  **2015统考真题**：先序序列为 $a,b,c,d$的不同二叉树的个数是()
>
> A. $13$
>
> B. $\color{Red}{14}$
>
> C. $15$
>
> D. $16$

根据二叉树前序遍历和中序遍历的递归算法中递归工作栈的状态变化得出：前序序列和中序序列的关系相当于以**前序序列**为`入栈次序`，以**中序序列**为`出栈次序`。因为前序序列和中序序列可以唯一地确定一棵二叉树，所以题意相当于`以序列a,b,c,d为入栈次序，则出栈序列的个数为`,对于 $n$个不同元素进 栈，出栈序列的个数为 $\frac{C_{2n}^{n}}{n+1}$(**卡特兰数**),故结果为 $\frac{C_{8}^{4}}{5}=\frac{8\times 7\times 6\times 5}{5\times 4\times 3\times 2}=14$

>  **2017统考真题**：某二叉树的树形如右图所示，其后序序列为 $e,a,c,b,d,g,f$,树中与结点 $a$同层的结点是()
>
> ![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_1126b55739-20230813183448.png) 
>
> A. $c$
>
> B. $\color{Red}{d}$
>
> C. $f$
>
> D. $g$

* 由后序遍历(**左右根**)和图知:根结点为 $f$,左子树有 $3$个结点 $e,a,c$,右子树有 $3$个结点 $b,d,g$;
* 同理, $f$的左子树的根结点为 $c$, $c$的右子树的根结点为 $a$, $a$的左子树的根结点为 $e$;
* 同理, $f$的右子树的根结点为 $g$, $g$的左子树的根结点为 $d$, $d$的右子树的根结点为 $b$.

![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_f9844dfe39-20230813184118.png) 

由图知,树中与结点 $a$同层的结点是 $d$

>  **2022统考真题**：若结点 $p$与 $q$在二叉树 $T$的中序遍历序列中相邻，且 $p$在 $q$之前，则下列 $p$与 $q$的关系中，不可能的是( $\color{Red}{B}$)
>
> Ⅰ. $q$是 $p$的双亲
>
> Ⅱ. $q$是 $p$的右孩子
>
> Ⅲ. $q$是 $p$的右兄弟
>
> Ⅳ. $q$是 $p$的双亲的双亲
>
> A. 仅 Ⅰ
>
> B. 仅 Ⅲ
>
> C. 仅 Ⅱ、 Ⅲ
>
> D. 仅 Ⅱ、 Ⅳ

![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_04445eb839-20230813184608.png) 

* 图 $1$中, $q$是 $p$的双亲,中序序列为`{p,q}`,满足条件,Ⅰ可能;
* 图 $2$中, $q$是 $p$的右孩子,中序序列为`{p,q}`,满足条件,Ⅱ可能;
* 图 $3$中, $q$是 $p$的右兄弟,一定先访问 $p$,再访问 $F$,最后访问 $q$,即 $p$和 $q$不可能相邻出现,不满足条件,Ⅲ不可能;
* 图 $4$中, $q$是 $p$的双亲的双亲,中序序列为`{x,p,q}`,满足条件,Ⅳ可能;

#### 5.3.1 & 5.3.2

> 若某非空二叉树的先序序列和后序序列**正好相反**，则该二叉树的形态是什么?
>
> 若某非空二叉树的先序序列和后序序列**正好相同**，则该二叉树的形态是什么?

可参考前文的**扩展**:一棵非空二叉树的先序遍历序列与后序遍历序列**正好相反**,则二叉树一定满足

* 只有一个叶结点;

* 高度等于结点数;

* 每个结点的左子树`或者`右子树为空.

若先序遍历序列与后序遍历序列**正好相同**,则只有可能为`只有根节点`

> * **相反**
> 
> ![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_44dca88b39-20230813193240.png) 
> * **相同**
> 
> ![](https://cdn.acwing.com/media/article/image/2023/08/13/85276_84b0330f39-20230813193517.png)

#### 5.3.3

>  编写后序遍历二叉树的非递归算法。

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

#### 5.3.4

>  试给出二叉树的自下而上、从右到左的层次遍历算法。

用正常的**层次遍历算法**，唯一区别就是变为逆向输出，很容易联想到**栈**，可以将输出语句改为压栈语句，等层次遍历完之后再输出栈元素，即为结果。

```cpp
void visit(BiTNode * p)//访问当前结点的数据
{
    cout << p->value << " ";
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

void Reverse_LevelOrder(BiTree T)
{
    queue<BiTNode *> q;//此处为了方便使用c++中的stl
    stack<BiTNode *> sta;

    q.push(T);//将根结点入队

    while(q.empty()==0)
    {
        BiTNode *p=q.front();//队头结点出队

        sta.push(p);//入栈
        q.pop();

        if(p->lchild!=NULL)//左子树不空,将左子树根结点入队
            q.push(p->lchild);
        if(p->rchild!=NULL)//右子树不空,将右子树根结点入队
            q.push(p->rchild);
    }

    while(sta.size()>0)
    {
        BiTNode *p=sta.top();
        visit(p);//访问栈顶元素
        sta.pop();
    }
}
```

#### 5.3.5

>  假设二叉树采用二叉链表存储结构，设计一个非递归算法求二叉树的高度。

* 递归做法(非题目要求)

```cpp
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
```

* 非递归做法

```cpp
int treeDepth(BiTree T)
{
    if(T==NULL)
        return 0;
    
    int maxdepth=0;

    queue<node> q;//此处为了方便使用c++中的stl

    q.push({T,1});//将根结点入队

    while(q.empty()==0)
    {
        node temp=q.front();//队头结点出队
        q.pop();
        
        maxdepth=max(maxdepth,temp.depth);//更新值
        maxdepth=temp.depth;//由于是层序遍历,必然深度越大的,后访问,故可直接更新

        if(temp.p->lchild!=NULL)//左子树不空,将左子树根结点入队
            q.push({temp.p->lchild,temp.depth+1});
        if(temp.p->rchild!=NULL)//右子树不空,将右子树根结点入队
            q.push({temp.p->rchild,temp.depth+1});
    }

    return maxdepth;
}
```

#### 5.3.6

>  设一棵二叉树中各结点的值互不相同，其先序遍历序列和中序遍历序列分别存于两个一维数组 $A[ 1 \cdots n]$和 $B[1 \cdots n]$中，试编写算法建立该二叉树的二叉链表。

根据二叉树的先序遍历序列和中序遍历序列可以创建一棵唯一的二叉树。先序遍历的第一个结点，是二叉树的根节点，在中序遍历找到根结点后，可以知道根节点的左右子树的结点和左右子树的结点数(用 $left \underline{} size$和 $right \underline{} size$表示），然后递归分别建立其左右子树，依次扫描二叉树先序序列，然后在中序序列中找到该结点从而确定该结点下的左右子树，直到左右子树的结点数为 $0$时( $left \underline{} size=0$和 $right \underline{} size=0$)，二叉树建立完毕。

```cpp
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

ElemType pre_list[MaxSize];
ElemType in_list[MaxSize];

BiTree T=CreateBiTree_by_Pre_and_In(pre_list, in_list, 1, n, 1, n);
```

#### 5.3.7

>  二叉树按二叉链表形式存储，写一个判别给定二叉树是否是完全二叉树的算法。

采用层次遍历。只有一下两种情况出现时，一棵树才不是完全二叉树

- 一个节点的左子树为空，右子树非空
- 在 $n$层遇到过非空节点，然后在 $n+1$层又遇到了非空节点

```cpp
bool isCompleteTree(BiTree T)
{
    if(T==NULL)
        return true;
    queue<BiTNode *> q;//此处为了方便使用c++中的stl

    q.push(T);//将根结点入队

    bool flag=false;//用来标记是否遇到空
    while(q.empty()==0)
    {
        int cnt=q.size();//当前层的个数

        while(cnt--)
        {
            BiTNode *p=q.front();//队头结点出队
            q.pop();
        
            if(p->lchild==NULL&&p->rchild!=NULL)//左子树空，右子树不空
                return false;

            if(flag==true&&(p->lchild!=NULL||p->rchild!=NULL))//曾经遇到过空，又遇到了非空
                return false;
            
            if(p->lchild==NULL||p->rchild==NULL)//遇到空,更新flag
                flag=true;

            if(p->lchild!=NULL)//左子树不空,将左子树根结点入队
                q.push(p->lchild);
            if(p->rchild!=NULL)//右子树不空,将右子树根结点入队
                q.push(p->rchild);
        }
    }    
    return true;
}
```

#### 5.3.8

>  假设二叉树采用二叉链表存储结构存储，试设计一个算法，计算一棵给定二叉树的所有双分支结点个数。

**方法一**:通过 $4$种遍历方式,访问根节点时判断是否左右子树都存在

```cpp
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
```

**方法二**:通过递归式**计算双分支结点个数** $F(p)$

* 当结点 $p$为 $NULL$时, $F(p)=0$;
* 当结点 $p$为**双分支结点**时(左右节点都不为空), $F(p)=F(p\to lchild)+F(p \to rchild)+1$;
* 反之(即结点 $p$为**单分支结点**或**叶子结点**), $F(p)=F(p\to lchild)+F(p \to rchild)$.

```cpp
int Calc_Double_Brach(BiTree T)
{
    if(T==NULL)//结点为空
        return 0;
    else if(T->lchild!=NULL&&T->rchild!=NULL)//当前是双分支结点
        return Calc_Double_Brach(T->lchild)+Calc_Double_Brach(T->rchild)+1;
    else return Calc_Double_Brach(T->lchild)+Calc_Double_Brach(T->rchild);//叶子结点或单分子结点
}
```

#### 5.3.9

>  设树 $B$是一棵采用链式结构存储的二叉树，编写一个把树 $B$中所有结点的左、右子树进行交换的函数。

采用递归算法实现交换二叉树的左、右子树,首先交换**左孩子**的左、右子树,再交换**右孩子**的左、右子树,最后交换当前根结点的左、右孩子,当结点为空时递归结束

```cpp
void Swap_Left_Right_Tree(BiTree T)
{
    if(T!=NULL)
    {
        Swap_Left_Right_Tree(T->lchild);//处理左孩子
        Swap_Left_Right_Tree(T->rchild);//处理右孩子

        //处理当前根结点
        BiTNode *temp=T->lchild;
        T->lchild=T->rchild;
        T->rchild=temp;
    }
}
```

#### 5.3.10

>  假设二叉树采用二叉链存储结构存储，设计一个算法，求先序遍历序列中第 $k$ (  $1 \leq k \leq $二叉树中结点个数)个结点的值。

用全局变量 $cnt$记录当前访问的个数,当先序遍历访问到第 $k$个结点时,输出它的值.

```cpp
void visit(BiTNode * p)//访问当前结点的数据
{
    cout << p->value << " ";
}

int cnt=0;
void PreOrder(BiTree T,int k)//前序遍历
{
    if(T!=NULL)
    {
        cnt++;//个数+1
        if(cnt==k)//当到达第 k个元素访问
        {
            visit(T);//访问根节点
            return ;
        }
        PreOrder(T->lchild,k);//递归遍历左子树
        PreOrder(T->rchild,k);//递归遍历右子树
    }
}
```

#### 5.3.11

>  已知二叉树以二叉链表存储，编写算法完成:对于树中每个元素值为 $x$的结点，删去以它为根的子树，并释放相应的空间.

```cpp
void ReleaseTree(BiTree t)//释放二叉树空间
{ 
  	if(t!=NULL){
    	ReleaseTree(t->lchild);
    	ReleaseTree(t->rchild);
    	free(t);
  	}
}

void Delete_X(BiTree &T,ElemType e)
{
    if(T==NULL)
        return ;
    
    if(T->value==e)//若T的value为想要删除的元素,则进行删除
    {
        ReleaseTree(T);//删除包括根节点
        T=NULL;//手动赋值为NULL
    }
    
    if(T!=NULL)
    {
        Delete_X(T->lchild, e);
        Delete_X(T->rchild, e);
    }
}
```

#### 5.3.12

>  在二叉树中查找值为 $x$的结点，试编写算法（用 $C$语言）打印值为 $x$的结点的所有祖先，假设值为 $x$的结点不多于一个。

* **递归版**

```cpp
void visit(BiTNode * p)//访问当前结点的数据
{
    cout << p->value << " ";
}

int Search_Ancestor(BiTree T,ElemType e)
{
    if(T==NULL)//空结点返回
        return 0;
    if(T->value==e)
        return 1;
    
    if(Search_Ancestor(T->lchild, e)==1||Search_Ancestor(T->rchild, e)==1)//左子树或右子树找到
    {
        visit(T);
        return 1;
    }
    else return 0;
}
```

* **非递归版**

采用非递归后序遍历,最后访问根节点,访问到值为 $x$的结点时,栈中所有元素均为该结点的祖先,依次出栈即可

```cpp
typedef struct StackNode{
    BiTNode *bitnode;
    bool isFirst;
}StackNode;

void Search_Ancestor(BiTree T,ElemType e)
{
    if(T==NULL)//空结点返回
        return ;
    stack<StackNode* > sta;//此处为了方便使用c++中的stl

    BiTNode *p=T;

    while(p!=NULL||sta.empty()==0)//p不空或栈不空
    {
        if(p!=NULL)//一路向左
        {
            StackNode *new_node=(StackNode *)malloc(sizeof(StackNode));
            new_node->bitnode=p;
            new_node->isFirst=true;//标记第一次访问
            
            //s.push(p);//当前结点入栈
            sta.push(new_node);

            p=p->lchild;//左孩子不空,一直向左走
        }
        else//出栈,并转向出栈结点的右子树
        {
            StackNode *temp_node=sta.top();//获取栈顶
            sta.pop();//栈顶元素出栈

            if(temp_node->isFirst==true)//表示是第一次出现在栈顶(从左子树返回)
            {
                temp_node->isFirst=false;
                sta.push(temp_node);
                p=temp_node->bitnode->rchild;//向右子树走,p赋值为当前出栈元素的右孩子
            }
            else//第二次出现在栈顶 
            {
                p=NULL;//结点访问完后,重置p指针
            }
        }

        if(p!=NULL&&p->value==e)
        {
            while(sta.size()>0)
            {
                StackNode *temp_node=sta.top();//获取栈顶
                visit(temp_node->bitnode);
                sta.pop();//栈顶元素出栈                
            }
            return ;
        }
    }
}
```

#### 5.3.13

>  设一棵二叉树的结点结构为( $LLINK,INFO,RLINK$)， $ROOT $为指向该二叉树根结点的指针， $p$和 $q$分别为指向该二叉树中任意两个结点的指针，试编写算法`ANCESTOR(ROOT,p,q,r)`，找到 $p$和 $q$的最近公共祖先结点 $r$.

