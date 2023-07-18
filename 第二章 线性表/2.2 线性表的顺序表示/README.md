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

#### 2.2.6

>  从**有序顺序表**中删除所有其值重复的元素，使表中所有元素的值均不同。

```cpp
bool Delete_Same(SqList &L)
{
    if(L.length==0)
        return false;
    int cnt=0;

    for(int i=0;i<L.length;i++)
    {
        int j=i;
        while(j<L.length&&L.data[j]==L.data[i])
            j++;
        L.data[cnt++]=L.data[i];
        i=j-1;
    }

    L.length=cnt;

    return true;
}
```

* **官方做法**

```cpp
bool Delete_Same(SqList &L)
{
	if(L.length==0) return false;
	int i,j; //i存储第一个不相同的元素，j为工作指针 
	for(i=0,j=1;j<L.length;j++)
	    if(L.data[i]!=L.data[j]) //查找下一个与上个元素值不同的元素 
	       L.data[++i]=L.data[j];  //找到后就将元素前移 
	L.length = i+1; //因为i是从0开始的 
	return true;
}

//自我做法
bool Delete_Same(SqList &L)
{
	if(L.length==0) return false;
	
    int cnt=0;

    L.data[cnt++]=L.data[0];

    for(int i=1;i<L.length;i++)//注意i从1开始枚举
        if(L.data[i]!=L.data[cnt-1])//注意是cnt-1(和官方有部分差异)
        {
            L.data[cnt++]=L.data[i];
            //PrintList(L);
        }
    L.length=cnt;

	return true;
}
```

* **扩展**:假设数均为正数,且将**有序表**改为**无序表**,使用`散列表`(类似于**标记数组**),保证时间复杂度为 $O(n)$;若存在负数,标记数组设为有**偏移量**的标记数组即可

```cpp
#define MaxNumSize 1000010

bool Delete_Same(SqList &L)
{
    if(L.length==0)
        return false;
    int vis[MaxNumSize]={0};
    int cnt=0;

    for(int i=0;i<L.length;i++)
        if(vis[L.data[i]]==0)
        {
            vis[L.data[i]]=1;
            L.data[cnt++]=L.data[i];
        }
    L.length=cnt;

    return true;
}
```

#### 2.2.7

>  将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表。

```cpp
bool MergeList(SeqList A,SeqList B,SeqList &C)
{
    if(A.length+B.length>C.MaxSize)
        return false;
    
    int i=0,j=0,cnt=0;

    while(i<A.length&&j<B.length)
    {
        if(A.data[i]<=B.data[j])
            C.data[cnt++]=A.data[i++];
        else C.data[cnt++]=B.data[j++];
    }

    while(i<A.length)
        C.data[cnt++]=A.data[i++];
    
    while(j<B.length)
        C.data[cnt++]=B.data[j++];
    
    C.length=A.length+B.length;

    return true;
}
```

#### 2.2.8

>  已知在一维数组 $A[m+n]$中依次存放两个线性表( $a_1,a_2,a_3,\cdots,a_m$)和( $b_1, b_2,b_3,\cdots,b_n$)。试编写一个函数，将数组中两个顺序表的位置互换，即将( $b_1,b_2,b_3,\cdots,b_n$)放在( $a_1,a_2,a_3,\cdots,a_m$)的前面。
