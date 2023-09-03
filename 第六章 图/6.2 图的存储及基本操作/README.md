#### 邻接矩阵法

结点数为 $n$的图 $G=(V,E)$的邻接矩阵 $A$是 $n\times n$的,将 $G$的顶点编号为 $v_1,v_2,\cdots,v_n$,则

![](https://cdn.acwing.com/media/article/image/2023/09/03/85276_8b125b254a-20230903163954.png) 

对于**带权图**,若顶点 $v_i$和 $v_j$之间有边相连,则邻接矩阵中对应项存放着该边**对应的权值**;若顶点 $v_i$和 $v_j$不相连,则通常用 $\infty$来代表着两个顶点间不存在边,则

![](https://cdn.acwing.com/media/article/image/2023/09/03/85276_5182ad994a-20230903164532.png) 

图的邻接矩阵存储结构如下:

```cpp
#define MaxVertexNum 100//顶点数目的最大值
#define inf (INT_MAX)//无穷大

typedef char VertexType;//顶点的数据类型
typedef int EdgeType;//带权图中边上权值的数据类型

typedef struct{
    VertexType Vex[MaxVertexNum];//顶点表
    EdgeType Edge[MaxVertexNum][MaxVertexNum];//邻接矩阵,边表
    int vernum,arcnum;//图的当前顶点数,图的边数/弧数
}MGraph;
```

![](https://cdn.acwing.com/media/article/image/2023/09/03/85276_808b7fa44a-20230903164713.png) 

* **无向图**的邻接矩阵一定是一个**对称矩阵**(并且唯一),对规模特大的邻接矩阵可采用**压缩存储**(只存储上(或下)三角矩阵的元素);
* 对于**无向图**,邻接矩阵的第 $i$**行**(或第 $i$**列**)非零元素(或非 $\infty$元素)的个数是**顶点 $i$的度** $TD(v_i)$
* 对于**有向图**,邻接矩阵的第 $i$**行**非零元素(或非 $\infty$元素)的个数是**顶点 $i$的出度** $OD(v_i)$;第 $i$**列**非零元素(或非 $\infty$元素)的个数是**顶点 $i$的入度** $ID(v_i)$.
* 用邻接矩阵存储图,可容易确定图中**任意两个顶点之间是否有边相连**.要确定图中有多少条边,必须按行、按列对每个元素进行检测,所花费的时间代价很大.
* **稠密图**适合使用邻接矩阵的存储表示,空间复杂度为 $O( \left| V \right|  ^{2} )$.
* 设图 $G$的邻接矩阵为 $A$,则 $A^{n}$的元素 $A^{n}[i][j]$等于由顶点 $i$到顶点 $j$的长度为 $n$的**路径的数目**.

#### 邻接表法



#### 十字链表(用于有向图)



#### 邻接多重表(用于无向图)



#### 图的基本操作

