#### 树的存储结构

* 双亲表示法

采用**一组连续空间**来存储每个结点,同时在**每个结点中增设一个伪指针**,指示其**双亲结点在数组中的位置**.根结点的下标为0,其伪指针域为-1.

![](https://cdn.acwing.com/media/article/image/2023/08/28/85276_9f4aefbf45-20230828150030.png) 

```cpp
#define MAX_TREE_SIZE 100
typedef int ElemType;

typedef struct{//树的结点定义
    ElemType data;//数据元素
    int parent;//双亲位置域
}PTNode;

typedef struct{
    PTNode nodes[MAX_TREE_SIZE];//双亲表示
    int size;//结点个数
}PTree;
```

查指定结点的**双亲**很方便,查指定结点的**孩子**不方便(只能**从头遍历**)

* 孩子表示法

将每个结点的孩子结点都用单链表链接起来形成一个线性结构,此时 $n$个结点就有 $n$个孩子链表(**叶子结点**的孩子链表为**空表**)

![](https://cdn.acwing.com/media/article/image/2023/08/28/85276_47ed668e45-20230828154818.png) 

```cpp
#define MAX_TREE_SIZE 100
typedef char ElemType;

struct ChildNode
{//链表中每个结点的定义
    //链表中每个结点存储的不是数据本身,而是数据在数组中存储的位置下标
    int child;//孩子结点在数组中的位置
    struct ChildNode *next;//下一个孩子
};

typedef struct
{//树中每个结点的定义
    ElemType data;
    ChildNode *firstchild;//孩子链表头指针
}CHNode;

typedef struct
{
    CHNode nodes[MAX_TREE_SIZE];
    int size;
}CTree;
```

孩子表示法这种存储方式**寻找子女的操作非常直接**,而**寻找双亲**的操作需要遍历 $n$个结点中孩子链表指针域所指向的 $n$个孩子链表.

* 孩子兄弟表示法(**使用较多**)

孩子兄弟表示法又称**二叉树表示法**,即以**二叉链表**作为树的存储结构.孩子兄弟表示法使每个结点包括三部分内容：结点值、**指向结点第一个孩子结点的指针**、**指向结点下一个兄弟结点的指针**（沿此域可以找到结点的所有兄弟结点）。

![](https://cdn.acwing.com/media/article/image/2023/08/28/85276_b120991f45-20230828155113.png) 

```cpp
#define MAX_TREE_SIZE 100
typedef char ElemType;

typedef struct CSNode
{
    ElemType data;
    struct CSNode *firstchild,*nextsibling;//第一个孩子和右兄弟节点
    //类似于二叉树中左孩子(第一个孩子),右孩子(右兄弟节点)
}CSNode,*CSTree;
```

孩子兄弟存储表示法比较灵活,其最大的**优点**是可以方便的**实现树转换为二叉树**的操作,易于**查找结点的孩子**等;**缺点**是从当前结点**查找其双亲结点**比较麻烦.

若为每一个结点增设一个 $parent$域指向其父结点,则查找结点的父结点也很方便.

通过孩子兄弟表示法,任意一棵普通树都可以相应转化为一棵二叉树,也就是说,任意一棵普通树都有唯一一颗二叉树与之对应.

#### 树的遍历



#### 森林的遍历





#### 5.4.1



#### 5.4.2



#### 5.4.3



#### 5.4.4

