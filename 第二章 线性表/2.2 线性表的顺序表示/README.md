#### 2.2.1 

> 从顺序表中删除具有最小值的元素（假设唯一）并由函数返回被删元素的值。空出的位置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行。

```cpp
bool Delete_MinElem(SqList &L,ElemType &e)
{
    if(/*Empty(L)==1*/L.length==0)//空表显示出错信息,并退出运行
    {
        cout << "空表,无法删除!" << endl;
        return false;
    }
    
    int min_pos=0;//寻找最小值的位置
    for(int i=1;i<L.length;i++)
        if(L.data[i]<L.data[min_pos])
            min_pos=i;
    
    e=L.data[min_pos];//引用传回最小值
    L.data[min_pos]=L.data[L.length-1];//更改最小位置的值为最后一个元素

    L.length--;//注意length需要减掉
    
    return true;
}

```

#### 2.2.2

> 设计一个高效算法，将顺序表 $L$的所有元素逆置，要求算法的空间复杂度为 $O(1)$.
>
> * 第一种,直接交换第 $i (0\leq i < length/2)$个元素和第 $length-1-i$个元素;
> * 第二种,类似于**双指针**的思想.

```cpp
void ListReverse(SqList &L)
{
    //第一种
    for(int i=0;i<L.length/2;i++)
    {
        //swap(L.data[i],L.data[L.length-1-i]);
        ElemType temp=L.data[i];
        L.data[i]=L.data[L.length-1-i];
        L.data[L.length-1-i]=temp;
    }
    //第二种
    /*
    int l=0,r=L.length-1;
    while(l<r)
    {
        swap(L.data[l],L.data[r]);
        l++,r--;
    }
    */
}
```

#### 2.2.3

>  对长度为 $n$的顺序表 $L$，编写一个时间复杂度为 $O(n)$、空间复杂度为 $O(1)$的算法，该算法删除线性表中所有值为 $x$的数据元素.

* **方法一**: 用 $cnt$记录不为 $x$的元素的个数,扫描时将不等于 $x$的元素移到下标为 $cnt$的位置,并更新 $cnt$的值,扫描结束后修改 $L$的长度( $cnt$).

```cpp
void Delete_Elem(SqList &L,ElemType e)
{
    int cnt=0;

    for(int i=0;i<L.length;i++)
        if(L.data[i]!=e)
            L.data[cnt++]=L.data[i];
    L.length=cnt;
}
```

* **方法二**: 用 $cnt$记录等于 $x$的元素的个数, 扫描时,遇到 $x$更新 $cnt$,反之遇到不等于 $x$的元素应前移 $cnt$位,扫描结束后修改 $L$的长度( $length-cnt$).

```cpp
void Delete_Elem(SqList &L,ElemType e)
{
    int cnt=0;

    for(int i=0;i<L.length;i++)
    {
        if(L.data[i]==e)
            cnt++;
        else L.data[i-cnt]=L.data[i];
    }
    L.length-=cnt;
}
```

#### 2.2.4

>  从**有序顺序表**中删除其值在给定值 $s$与 $t$之间（要求 $s < t$)的所有元素，若 $s$或 $t$不合理或顺序表为空，则显示出错信息并退出运行。

```cpp
//不考虑其有序,参考2.2.3
bool Delete_Elem(SqList &L,ElemType s,ElemType t)
{
    if(/*Empty(L)==1*/L.length==0)//空表显示出错信息,并退出运行
    {
        cout << "空表,无法删除!" << endl;
        return false;
    }
    if(s>=t)
    {
        cout << "左区间应小于右区间" << endl;
        return false;
    }

    int cnt=0;

    for(int i=0;i<L.length;i++)
        if(L.data[i]<s||L.data[i]>t)
            L.data[cnt++]=L.data[i];
    L.length=cnt;

    return true;
}

bool Delete_Elem(SqList &L,ElemType s,ElemType t)
{
    if(/*Empty(L)==1*/L.length==0)//空表显示出错信息,并退出运行
    {
        cout << "空表,无法删除!" << endl;
        return false;
    }
    if(s>=t)
    {
        cout << "左区间应小于右区间" << endl;
        return false;
    }
    int cnt=0;

    for(int i=0;i<L.length;i++)
    {
        if(L.data[i]>=s&&L.data[i]<=t)
            cnt++;
        else L.data[i-cnt]=L.data[i];
    }
    L.length-=cnt;
    return true;
}
```

* **官方做法**:寻找第一个**大于等于** $s$的位置和**大于** $t$的位置,将后面剩余元素移到前面来.

```cpp
bool Delete_Elem(SqList &L,ElemType s,ElemType t)
{
    if(/*Empty(L)==1*/L.length==0)//空表显示出错信息,并退出运行
    {
        cout << "空表,无法删除!" << endl;
        return false;
    }
    if(s>=t)
    {
        cout << "左区间应小于右区间" << endl;
        return false;
    }
    
    int l=0;
    while(l<L.length&&L.data[l]<s)
        l++;
    // if(l>=L.length)
    //     return false;
    
    int r=l;
    while(r<L.length&&L.data[r]<=t)
        r++;
    
    while(r<L.length)
    {
        L.data[l]=L.data[r];
        l++,r++;
    }
    
    L.length=l;
    return true;
}
```

#### 2.2.5

> 从**顺序表**中删除其值在给定值 $s$与 $t$之间（包含 $s$和 $t$，要求 $s < t$)的所有元素，若 $s$或 $t$不合理或顺序表为空，则显示出错信息并退出运行。

```cpp
//可参考2.2.4
bool Delete_Elem(SqList &L,ElemType s,ElemType t)
{
    if(/*Empty(L)==1*/L.length==0)//空表显示出错信息,并退出运行
    {
        cout << "空表,无法删除!" << endl;
        return false;
    }
    if(s>=t)
    {
        cout << "左区间应小于右区间" << endl;
        return false;
    }

    int cnt=0;

    for(int i=0;i<L.length;i++)
        if(L.data[i]<s||L.data[i]>t)
            L.data[cnt++]=L.data[i];
    L.length=cnt;

    return true;
}

bool Delete_Elem(SqList &L,ElemType s,ElemType t)
{
    if(/*Empty(L)==1*/L.length==0)//空表显示出错信息,并退出运行
    {
        cout << "空表,无法删除!" << endl;
        return false;
    }
    if(s>=t)
    {
        cout << "左区间应小于右区间" << endl;
        return false;
    }
    int cnt=0;

    for(int i=0;i<L.length;i++)
    {
        if(L.data[i]>=s&&L.data[i]<=t)
            cnt++;
        else L.data[i-cnt]=L.data[i];
    }
    L.length-=cnt;
    return true;
}
```



