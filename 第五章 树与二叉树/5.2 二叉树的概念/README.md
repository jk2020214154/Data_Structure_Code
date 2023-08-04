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

#### 二叉树的性质

