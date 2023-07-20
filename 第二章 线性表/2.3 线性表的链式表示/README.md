#### 2.3.1

> 设计一个递归算法，删除不带头结点的单链表 $L$中所有值为 $x$的结点。

```cpp
LinkList Delete_Same(LinkList L,ElemType e)//以当前结点作为L的开始
{
    LNode *p;
    if(L==NULL)//递归终止条件
        return NULL;
    //cout << L->data << endl;
    if(L->data==e)//当前元素等于e
    {
        p=L;
        L=L->next;
        free(p);
        return Delete_Same(L, e);//L已后移
    }
    else
    {
        L->next=Delete_Same(L->next, e);//将后面修改的结果接在当前位置
        return L;
    }
}
```

#### 2.3.2

> 在带头结点的单链表工中，删除所有值为 $x$的结点，并释放其空间，假设值为 $x$的结点不唯一,试编写算法以实现上述操作.

* **方法一**:从头开始遍历,把值为 $x$的结点删去,即改变其前驱结点的 $next$指针.
```cpp
void Delete_Same(LinkList &L,ElemType e)
{
    LNode *p=L->next,*pre=L;
    LNode *q;//临时变量用来释放

    while(p!=NULL)//从头遍历
    {
        if(p->data==e)
        {
            q=p;//临时存储当前结点
            pre->next=p->next;//将q结点与链表断开
            p=p->next;//p指针后移
            //pre不变
            free(q);
        }
        else
        {
            pre=p;//同步后移
            p=p->next;
        }
    }
}
```

* 方法二:将值不为 $x$的结点**尾插法**插入该链表中,反之,释放空间.

```cpp
void Delete_Same(LinkList &L,ElemType e)
{
    LNode *p=L->next,*r=L;//此处r是尾指针
    LNode *q;//临时变量用来释放

    while(p!=NULL)//从头遍历
    {
        if(p->data==e)//相等释放
        {
            q=p;
            p=p->next;
            free(q);
        }
        else
        {//将其重新链接到链表中
            r->next=p;
            r=p;
            p=p->next;
        }
    }
}
```

#### 2.3.3

> 设 $L$为带头结点的单链表，编写算法实现从尾到头反向输出每个结点的值。

**递归**可实现反向输出

```cpp
void ReversePrint(LNode *p)
{
    if(p==NULL)//终止条件
        return ;
    
    ReversePrint(p->next);
    cout << p->data << " ";
}

ReversePrint(L->next);//调用时使用第一个结点(而不是头结点)
```

#### 2.3.4

> 试编写在带头结点的单链表 $L$中删除一个最小值结点的高效算法（假设最小值结点是唯一的).

```cpp
LinkList Delete_Min_Elem(LinkList L,ElemType &e)
{
    LNode *p=L->next,*pre=L;
    LNode *p_min=L->next;//记录最小值的指针
    LNode *pre_min=L;//记录最小值的前驱指针(方便后续更改)

    while(p!=NULL)
    {
        if(p->data<p_min->data)
        {
            p_min=p;
            pre_min=pre;
        }
        pre=p;
        p=p->next;
    }

    pre_min->next=p_min->next;
    e=p_min->data;
    free(p_min);

    return L;
}
```

#### 2.3.5

> 试编写算法将带头结点的单链表就地逆置，所谓“就地”是指辅助空间复杂度为 $O(1)$.

* **方法一**: 利用**头插法**,从头到尾重新插入到单链表 $L$中.

```cpp
LinkList ReverseList(LinkList L)
{
    LNode *p=L->next;
    LNode *r;//r为p的后继,防止中间处理时断链
    L->next=NULL;//让L与结点断开
    while(p!=NULL)
    {
        r=p->next;//保存p的后继结点
        
        //头插法插入结点
        p->next=L->next;
        L->next=p;

        p=r;//p指针后移
    }

    return L;
}
```

* **方法二**:**指针反指**,使用三个指针 $pre$(当前结点的前驱), $p$(当前结点), $r$(当前结点的后继)记录对应的执行,每次先将 $p$ 和 $r$断开,再将三个指针后移,让当前结点 $p$的 $next$ 指向 $pre$(即`p->next=pre`),当 $r$到达链表的尾部(即`r==NULL`)此时让 $L$指向当前的最后一个结点 $p$.

```cpp
LinkList ReverseList(LinkList L)
{
    LNode *pre;
    LNode *p=L->next;
    LNode *r=p->next;//r为p的后继,防止中间处理时断链
    
    p->next=NULL;//处理第一个结点
    while(r!=NULL)
    {
        pre=p;
        p=r;
        r=r->next;
        p->next=pre;//指针反指

    }

    L->next=p;//处理最后一个结点

    return L;
}

```

两种方法的时间复杂度均为 $O(n)$,空间复杂度均为 $O(1)$.

#### 2.3.6

> 有一个带头结点的单链表 $L$，设计一个算法使其元素递增有序。

* **方法一**:**直接插入排序**,时间复杂度为 $O(n^2)$.

```cpp
void SortList(LinkList &L)
{
    LNode *p=L->next;//p指向第一个结点
    LNode *r=p->next;//r记录p的后继
    LNode *temp,*pre;//temp用于遍历,pre记录前驱
    
    p->next=NULL;//记得断链
    p=r;//从第二个结点开始枚举

    while(p!=NULL)
    {
        //cout << p->data << endl;
        r=p->next;//更新r
        
        temp=L->next;//重头遍历(找到合适的位置)
        pre=L;
        while(temp!=NULL&&temp->data<p->data)
        //跳过小于p的所有结点,在temp(此时temp的值大于p的值)的前面插入p结点
        {
            pre=temp;
            temp=temp->next;
        }
        //前插p结点
        p->next=temp;
        pre->next=p;

        p=r;//p后移
        //PrintList(L);
    }
}
```

* **方法二**:通过`链表->数组->排序->链表`,以空间换取时间,时间复杂度可降低到 $O(nlog_2n)$,此处不过多展示该方法的代码.

#### 2.3.7

> 设在一个带表头结点的单链表中所有元素结点的数据值无序，试编写一个函数，删除表中所有介于给定的两个值（作为函数参数给出)之间的元素的元素（若存在).

```cpp
LinkList Delete_Range_Elem(LinkList L,int l,int r)
{
    LNode *p=L->next,*pre=L;
    while(p!=NULL)
    {
        if(p->data>l&&p->data<r)
        {
            //此处可不用新开一个结点指针,由于pre的next更新后就已知指针p的下一个next
            pre->next=p->next;//前驱结点的next更新
            free(p);//释放
            p=pre->next;//p指针为pre的next
        }
        else
        {
            pre=p;
            p=p->next;           
        }
    }
    return L;
}
```

#### 2.3.8

> 给定两个单链表,编写算法找出两个链表的公共结点。

* **方法一**:设两个单链表分别是 $L_1$, $L_2$,设它们的长度分别是 $len1$, $len2$,在第一个链表上顺序遍历每个结点,每遍历一个结点,在第二个链表上顺序遍历所有结点,若找到两个相同的结点(此处是**地址相同**,而不是 $data$**域相同**),则找到它们的公共结点。时间复杂度为 $O(len1 \times len2)$.

```cpp
void Search_Common_Node(LinkList L1,LinkList L2,LinkList &L)
{
    LNode *p1=L1,*p2=L2;
    
    while(p1!=NULL)
    {
        p2=L2;
        while(p2!=NULL)
        {
            //cout << p1->data << " " << p2->data << endl;
            if(p1==p2)
            {
                L->next=p1;
                return ;
            }
            p2=p2->next;
        }
        p1=p1->next;
        //cout << endl;
    }
}

LinkList L;
InitList(L);
Search_Common_Node(L1, L2,L);
```

* **方法二**:在长的链表上先遍历长度之差个结点之后,再同步遍历两个链表,直到找到相同的结点或者一直到链表结束.时间复杂度为 $O(len1+len2)$(个人认为是 `O(max { len1,len2 })`).

```cpp
int Length(LinkList L)//求表的长度
{
    int len=0;
    LNode *p=L->next;
    while(p!=NULL)
    {
        p=p->next;
        len++;
    }
    return len;
}

void Search_Common_Node(LinkList L1,LinkList L2,LinkList &L)
{
    int len1=Length(L1),len2=Length(L2);
    int delta=abs(len1-len2);//长度差值
    LNode *p1=L1->next,*p2=L2->next;

    for(int i=1;i<=delta;i++)
    {
        if(len1>len2)//p1后移(l1长度大于L2)
            p1=p1->next;
        else//p2后移
            p2=p2->next;
    }

    while(p1!=NULL)//公共长度部分
    {
        if(p1==p2)
        {
            L->next=p1;
            return ;
        }
        p1=p1->next;
        p2=p2->next;
    }
}

LinkList L;
InitList(L);
Search_Common_Node(L1, L2,L);
```

#### 2.3.9

> 给定一个带表头结点的单链表，设 $head$为头指针，结点结构为 $(data, next)$,  $data$为整型元素， $next$为指针，试写出算法:按递增次序输出单链表中各结点的数据元素，并释放结点所占的存储空间（要求:不允许使用数组作为辅助空间).

对链表进行遍历,在每次遍历中找出整个链表的**最小值元素**,输出并释放结点所占空间;再查找次小值元素,输出并释放空间,直至链表为空.时间复杂度为 $O(n^2)$.由于题目限制,时间复杂度无法再降到更低.

```cpp
void Sort_And_Delete(LinkList &L)
{
    while(L->next!=NULL)
    {
        LNode *p=L->next,*pre=L;
        LNode *p_min=L->next;//记录最小值的指针
        LNode *pre_min=L;//记录最小值的前驱指针(方便后续更改)
        ElemType num;

        while(p!=NULL)
        {
            if(p->data<p_min->data)
            {
                p_min=p;
                pre_min=pre;
            }
            pre=p;
            p=p->next;
        }

        pre_min->next=p_min->next;
        num=p_min->data;
        cout << num << " ";
        free(p_min);
    }
    cout << endl;
}
```

此处可借鉴`2.3.4`的查找最小值再释放的函数,如下:

```cpp
void Sort_And_Delete_short(LinkList &L)
{
    while(L->next!=NULL)
    {
        ElemType num;
        Delete_Min_Elem(L, num);//使用2.3.4的函数
        cout << num << " ";
    }
    cout << endl;
}
```

#### 2.3.10

> 将一个带头结点的单链表 $A$分解为两个带头结点的单链表 $A$和 $B$，使得 $A$表中含有原表中序号为**奇数**的元素,而 $B$表中含有原表中序号为**偶数**的元素，且保持其相对顺序不变。

```cpp
void Divide_List(LinkList &L1,LinkList &L2)
{
    int tot=1;

    LNode *p1=L1;
    LNode *p2=L2;
    LNode *p=L1->next;
    p1->next=NULL;//让L1置为空表

    while(p!=NULL)
    {
        if(tot%2==1)//奇数
        {
            p1->next=p;
            p1=p;
        }
        else//偶数
        {
            p2->next=p;
            p2=p;
        }
        p=p->next;
        tot++;
    }
    p1->next=NULL;
    p2->next=NULL;
}
```

#### 2.3.11

> 设 `C={`  $a_1,b_1,a_2,b_2,\cdots,a_n,b_n$ `}`为线性表，采用带头结点的单链表存放，设计一个就地算法，将其拆分为两个线性表，使得  `A={` $a_1,a_2,\cdots,a_n$ `}`, `B={` $b_n,\cdots,b_2,b_1$ `}`.

```cpp
void Divide_TwoList(LinkList L,LinkList &L1,LinkList &L2)
{
    int tot=1;

    LNode *p=L->next;
    LNode *p1=L1;//尾插法
    LNode *temp;//L2头插法,temp临时变量

    while(p!=NULL)
    {
        if(tot%2==1)//尾插法
        {
            p1->next=p;
            p1=p;
            p=p->next;
        }
        else
        {
            temp=p->next;
            p->next=L2->next;
            L2->next=p;
            p=temp;
        }
        tot++;
    }
    p1->next=NULL;//尾插法需置空
}

//可发现计数变量tot可不用
void Divide_TwoList(LinkList L,LinkList &L1,LinkList &L2)
{
    LNode *p=L->next;
    LNode *p1=L1;//尾插法
    LNode *temp;//L2头插法,temp临时变量

    while(p!=NULL)
    {
        p1->next=p;//L1尾插
        p1=p;
        p=p->next;

        temp=p->next;//L2头插
        p->next=L2->next;
        L2->next=p;
        p=temp;
    }
    p1->next=NULL;//尾插法需置空
}
```

