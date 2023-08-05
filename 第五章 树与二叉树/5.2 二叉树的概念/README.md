#### 二叉树的顺序存储

```cpp
#define MaxSize 110

typedef int ElemType;

struct TreeNode{
    ElemType value;//结点中的顺序元素
    bool isEmpty;//结点是否为空
};

TreeNode t[MaxSize];
```

#### 二叉树的链式存储

```cpp
#define MaxSize 110

typedef int ElemType;

typedef struct BiTNode{
    ElemType value;//结点中的顺序元素
    struct BiTNode *lchild,*rchild;    
}BiTNode,*BiTree;
```

若要快速找到父结点,可使用**三叉链表**,即增加父结点指针域

```cpp
typedef struct BiTNode{
    ElemType value;//结点中的顺序元素
    struct BiTNode *lchild,*rchild;    
    struct BiTNode *parent;
}BiTNode,*BiTree;
```

在 $n$个结点的二叉链表中,每个结点提供两个指针域,共 $2n$个,其中含有 $n+1$个空指针域(在 $n$个结点的树中有 $n-1$条边,每条边共享一个指针域),此处空指针域会在**线索链表**中使用.

#### 二叉树的基本术语

* 二叉树与度为 $2$的有序树的区别:

> 度为 $2$的树至少有 $3$个结点,而二叉树可以是空树.
>
> 度为 $2$的有序树的孩子的左右次序是根据相对另一个孩子而言,若某个结点只有一个孩子,则这个孩子就无须区分其左右次序,而二叉树无论其孩子树是否为 $2$,均需确定其左右次序,即二叉树的结点次序不是相对另一个结点而言,而是确定的.

* **满二叉树**: 一棵高度为 $h$,且含有 $2^h-1$个结点的二叉树.满二叉树的叶节点都集中在二叉树的最后一层(第 $h$层),并且除叶结点之外的每个结点度数均为 $2$.(它是特殊的**完全二叉树**)
* **完全二叉树**:当且仅当其每个结点都与高度为 $h$的满二叉树中编号为 $1\sim n$的结点一一对应时，称为完全二叉树.

![](https://cdn.acwing.com/media/article/image/2023/08/05/85276_bffa492933-20230805131154.png) 
