补充一下关于邻接矩阵和邻接表的`FirstNeighbor(G,x)`和`NextNeighbor(G,x,y)`的函数实现(方便遍历边).此处是以下标为 $1$开始.

* **邻接矩阵**

```cpp
int FirstNeighbor(MGraph G,int x)
{
    if(x>=1&&x<=G.vexnum)
    {
        for(int i=1;i<=G.vexnum;i++)
            if(G.Edge[x][i]!=inf&&G.Edge[x][i]!=0)
                return i;
    }
    return -1;
}

int NextNeighbor(MGraph G,int x,int y)
{
    if(x>=1&&x<=G.vexnum&&y>=1&&y<=G.vexnum)
    {
        for(int i=y+1;i<=G.vexnum;i++)
            if(G.Edge[x][i]!=inf&&G.Edge[x][i]!=0)
                return i;
    }
    return -1;
}

```

* **邻接表**

```cpp
int FirstNeighbor(ALGraph G,int x)
{
    if(x>=1&&x<=G.vexnum)
    {
        if(G.vertices[x].first!=NULL)
            return G.vertices[x].first->adjvex;
    }
    return -1;
}

int NextNeighbor(ALGraph G,int x,int y)
{
    ArcNode *temp=G.vertices[x].first;

    while(temp!=NULL)
    {
        if(temp->adjvex==y)
            break;
        temp=temp->next;
    }

    if(temp==NULL||temp->next==NULL)
        return -1;
    else return temp->next->adjvex;
}
```

#### 广度优先搜索

**基本思想**：首先访问起始顶点 $v$,接着从 $v$出发,依次访问 $v$的各个未访问过的邻接顶点 $w_1,w_2,\cdots,w_i$,然后依次访问 $w_1,w_2,\cdots,w_i$的所有未被访问过的邻接顶点;再从这些访问过的顶点出发,访问它们所有未被访问过的邻接顶点,直至图中所有顶点都被访问过为止.若此时图中尚有顶点未被访问,则另选图中一个未曾被访问的顶点作为始点,重复上述过程,直至图中所有顶点都被访问到为止.常通过**队列**和**标记数组**来进行实现.

![](https://cdn.acwing.com/media/article/image/2023/09/11/85276_3430fe7a50-20230911173946.png) 

假设以 $7$出发(假设按递增顺序访问邻接顶点),故广度优先搜索序列为 $\color{Red}{7,3,6,8,2,4,1,5}$;(调用使用 $1$次 $BFS$函数)

假设以 $1$出发(访问邻接顶点同上),故广度优先搜索序列为 $\color{Green}{1,5,2,3,6,4,7,8}$(调用使用 $4$次 $BFS$函数,分别在 $1,2,3,4$各自调用)

代码如下(以**邻接矩阵**为例)：

```cpp
bool visited[MaxVertexNum];

void visit(MGraph G,int pos)
{
    cout << G.Vex[pos] << " ";
}

void BFS(MGraph G,int start)
{
    queue<int> q;//此处为了方便,使用C++的stl中的队列

    //将起点放入队列中,并标记为true
    q.push(start);
    visited[start]=true;

    while(q.size()>0)
    {
        int temp=q.front();
        visit(G,temp);//访问该结点
        q.pop();//弹出队列

        for(int j=FirstNeighbor(G, temp);j!=-1;j=NextNeighbor(G, temp, j))
        {
            if(visited[j]==false)//当前邻接顶点未访问,放入队列并标记
            {
                q.push(j);
                visited[j]=true;
            }
        }
    }
    cout << endl << "--------" << endl;//观察使用 BFS次数
}

void BFSTraverse(MGraph G)
{
    for(int i=1;i<=G.vexnum;i++)
        visited[i]=false;
    
    for(int i=1;i<=G.vexnum;i++)
        if(visited[i]==false)
            BFS(G,i);
}
```

##### BFS算法的性能分析

>  无论是邻接表还是邻接矩阵的存储方式, $BFS$算法都需要借助一个**辅助队列** $Q$, $n$个顶点均需入队一次,在最坏情况下,空间复杂度为 $O(\left| {V} \right|)$.
>
> 采用**邻接表**存储方式时,每个顶点只需搜索一次(或入队一次),故时间复杂度为 $O(\left| V \right|)$,在搜索任意一个顶点的邻接点时,每条边至少访问一次,故时间复杂度为 $O(\left| E \right|)$,算法总的时间复杂度为 $O(\left| V \right| + \left| E \right|)$;采用邻接矩阵存储方式时,查找每个顶点的邻接点所需的时间为 $O(\left| V \right|)$,故算法总的时间复杂度为 $O(\left| V \right| ^2)$.

##### 广度优先搜索树

在广度遍历的过程中,可得到一棵遍历树,称为广度优先生成树.同一个图的**邻接矩阵**存储表示是唯一的,故其广度优先生成树也是`唯一`的,但由于**邻接表**存储表示不唯一,故其广度优先生成树也是`不唯一`的.

![](https://cdn.acwing.com/media/article/image/2023/09/11/85276_b0c133d750-20230911193801.png) 

对**非连通图**的广度优先遍历,可得到**广度优先森林**

#### 深度优先搜索

**基本思想**：首先访问图中某一起始顶点 $v$,然后由 $v$出发,访问与其相邻且未被访问的任意一个顶点 $w_1$,再访问与 $w_1$邻接且未被访问的任意一个顶点 $w_2$, $\cdots \cdots$重复上述过程.当不能再继续向下访问时,依次退回到最近被访问的顶点,若它还有邻接顶点未被访问过,则从该点开始继续上述搜索过程,直至图中所有顶点均为访问过为止.

![](https://cdn.acwing.com/media/article/image/2023/09/11/85276_3430fe7a50-20230911173946.png)

仍以该图做例子,假设以 $7$出发(假设按递增顺序访问邻接顶点),故深度优先搜索序列为 $\color{Red}{7,3,6,2,1,5,8,4}$.

代码如下(以**邻接矩阵**为例)：

```cpp
bool visited[MaxVertexNum];

void visit(MGraph G,int pos)
{
    cout << G.Vex[pos] << " ";
}

void DFS(MGraph G,int start)
{
    visit(G,start);//访问该点,并标记
    visited[start]=true;
    for(int j=FirstNeighbor(G, start);j!=-1;j=NextNeighbor(G, start, j))//访问其未被访问的邻接顶点
        if(visited[j]==false)
            DFS(G,j);
}

void DFSTraverse(MGraph G)
{
    for(int i=1;i<=G.vexnum;i++)
        visited[i]=false;
    
    for(int i=1;i<=G.vexnum;i++)
        if(visited[i]==false)
        {
            DFS(G,i);
            cout << endl << "--------" << endl;//观察使用 DFS次数
        }
}
```

##### DFS算法的性能分析

>  $DFS$算法是一个递归算法,需要借助一个递归工作栈,故空间复杂度为 $O(\left| V \right|)$.
>
> 遍历图的过程实质是对每个顶点查找其邻接点的过程,其耗费的时间取决于所用的存储结构.以**邻接矩阵**表示时,查找每个顶点的邻接点的时间为 $O(\left| V \right|)$,故总的时间复杂度为 $O(\left| V \right|)^2$;以邻接表表示时,查找所有顶点的邻接点所需的时间为 $O(\left| E \right|)$,访问顶点所需的时间为 $O(\left| V \right|)$,总的时间复杂度为 $O(\left| V \right| + \left| E \right)$.

##### 深度优先搜索树



#### 图的遍历和连通性



