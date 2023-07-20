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

