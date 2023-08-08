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



#### 二叉树的中序遍历

* 递归版

```cpp
void InOrder(BiTree T)//中序遍历
{
    if(T!=NULL)
    {
        InOrder(T->lchild);//递归遍历左子树
        cout << T->value << " ";//访问根节点
        InOrder(T->rchild);//递归遍历右子树
    }
}
```

* 非递归版



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



