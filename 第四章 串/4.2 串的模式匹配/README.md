 $n$为主串长度, $m$为模式串长度,求`模式匹配`(**子串或模式串**在**主串**中的位置)

#### 朴素模式匹配算法

时间复杂度为 $O(nm)$

```cpp
int StrIndex(SString Str1,SString Str2)//定位操作
{
    int pos1=1,pos2=1;//分别指向Str1和Str2的第一个元素
    while(pos1<=Str1.length&&pos2<=Str2.length)
    {
        if(Str1.ch[pos1]==Str2.ch[pos2])
            pos1++,pos2++;
        else pos1=pos1-pos2+2,pos2=1;
    }
    if(pos2>Str2.length)
        return pos1-Str2.length;
    else return 0;
}
```

#### KMP算法

时间复杂度为 $O(m+n)$,求 $next$数组时间复杂度为 $O(m)$,模式匹配过程最坏时间复杂度为 $O(n)$.

```cpp
int StrIndex_KMP(SString Str1,SString Str2,int next[])//定位操作
{
    int i=1,j=1;//分别指向Str1和Str2的第一个元素
    while(i<=Str1.length&&j<=Str2.length)
    {
        if(j==0||Str1.ch[i]==Str2.ch[j])//j==0时也需要
            i++,j++;
        else j=next[j];
    }
    if(j>Str2.length)
        return i-Str2.length;
    else return 0;
}
```

#### 计算next数组

**手算**思想: $next[1]$填 $0$; $next[2]$填 $1$;其他的 $next$,在不匹配的位置前,划一根分界线,模式串一步一步往后退,直到分界线之前`能对上`,或模式串完全跨过分界线为止.此时 $j$指向哪, $next$数组值就是多少.

```cpp
//教材写法
void get_next(SString Str,int next[])
{
    int i=1,j=0;
    next[1]=0;

    while(i<Str.length)
    {
        if(j==0||Str.ch[i]==Str.ch[j])
            i++,j++,next[i]=j;
        else j=next[j];//往前找
    }
}
```

#### 计算nextval数组

**手算**思想: 先求 $next$数组,再由 $next$数组求 $nextval$数组.当 $s[next[j]]==s[j]$,则 $nextval[j]=nextval[next[j]]$;反之, $nextval[j]=next[j]$.

```cpp
void get_next_val(SString Str,int next[],int nextval[])//可通过next数组直接求
{
    nextval[1]=0;
    for(int j=2;j<=Str.length;j++)
    {
        if(Str.ch[next[j]]==Str.ch[j])
            nextval[j]=nextval[next[j]];
        else nextval[j]=next[j];
    }
}

//教材写法
void get_next_val(SString Str,int nextval[])
{
    int i=1,j=0;
    nextval[1]=0;

    while(i<Str.length)
    {
        if(j==0||Str.ch[i]==Str.ch[j])
        {
            i++,j++;
            if(Str.ch[i]!=Str.ch[j])
                nextval[i]=j;
            else nextval[i]=nextval[j];

        }
        else j=nextval[j];//往前找
    }
}
```

关于计算 $next$和 $nextval$可参考上面的**手算**思想

>  已知串 $S='aaab'$，其 $next$数组值为().
>
> A. $\color{Red}{0123}$
>
> B. $0112$
>
> C. $0231$
>
> D. $1211$ 

![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_d6d810ae30-20230801191338.png) 

 ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_cb6511a130-20230801191353.png)

> **教材做法**
>
> ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_2c04e36a30-20230801194706.png) 

>  串 $'ababaaababaa'$的 $next$数组值为().
>
> A. $012345678999$
>
> B. $012121111212$
>
> C. $\color{Red}{011234223456}$
>
> D. $012301232234$
>
>  串 $'ababaaababaa'$的 $next$数组为().
>
> A. $-1,0,1,2,3,4,5,6,7,8,8,8$
>
> B. $-1,0,1,0,1,0,0,0,0,1,0,1$
>
> C. $\color{Red}{-1,0,0,1,2,3,1,1,2,3,4,5}$
>
> D. $-1,0,1,2,-1,0,1,2,1,1,2,3$
>
>  串 $'ababaaababaa'$的 $nextval$数组为().
>
> A. $0,1,0,1,1,2,0,1,0,1,0,2$
>
> B. $0,1,0,1,1,4,1,1,0,1,0,2$
>
> C. $\color{Red}{0,1,0,1,0,4,2,1,0,1,0,4}$
>
> D. $0,1,1,1,0,2,1,1,0,1,0,4$

![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_cac4361130-20230801215137.png) 

* 求 $next$数组

> ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_6137d44330-20230801215514.png) 
> 
> ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_7af1bc5030-20230801222647.png) 
>
>  ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_29e3448830-20230801214919.png)
>
>  ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_332e348030-20230801215002.png)
>
> ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_3dbb38c530-20230801215038.png)  
>
> 当求**位序**的 $next$数组,过程如上;当求**下标**的 $next$数组,无非在位序的 $next$数组基础上每个数 $-1$即可.

* 求 $nextval$数组

![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_53ca442930-20230801215054.png) 

>  **教材做法**(忽略水印)
>
> ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_d20f07ea30-20230801195014.png) 
>
> - - -
>
> ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_e3a0649030-20230801195133.png) 



>  **2015统考真题**：已知字符串 $S$为 $' abaabaabacacaabaabcc'$，模式串 $t$为 $'abaabc'$.采用 $KMP$算法进行匹配，第一次出现“失配”( $s[i] \neq s[j]$)时， $i=j=5$，则下次开始匹配时， $i$和 $j$的值分别是().
>
> A. $i=1,j=0$
>
> B. $i=5,j=0$
>
> C. $\color{Red}{i=5,j=2}$
>
> D. $i=6,j=2$

![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_96949dc230-20230801222548.png) 

![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_ab144eea30-20230801222608.png) 

![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_b8885d6d30-20230801222731.png) 

注意题目中 $i=j=5$时失配,可发现是下标法(对应编号是 $6$),由表知 $i$不变, $j$变成对应的 $next$数组值,故 $i=5$, $j=2$

>  **2019统考真题**：设主串 $T='abaabaabcabaabc'$，模式串 $s = 'abaabc'$，采用 $KMP$算法进行模式匹配，到匹配成功时为止，在匹配过程中进行的单个字符间的比较次数是().
>
> A. $9$
>
> B. $\color{Red}{10}$
>
> C. $12$
>
> D. $15$

![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_96949dc230-20230801222548.png)

模式串同上题的一样.

![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_592ab7d030-20230801224007.png) 

下划线处表示比较的次数,共 $6+4=10$次.

#### 4.2.1

>  在字符串模式匹配的 $KMP$算法中，求模式的 $nex$t数组值的定义如下:
>
>  ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_675beac730-20230801224741.png)
>  
>  1)当 $j=1$时,为什么要取 $next [1]=0$?
>  
>  2)为什么要取 `max{k}`， $k$最大是多少?
>  
>  3)其他情况是什么情况，为什么取 $next[j]=1$?

1)当模式串中的第一个字符和主串的当前字符比较**不相等**时，$next[1]=0$，表示模式串应该右移一位，主串当前指针也要后移一位，再和模式串中的第一字符进行比较;

2)当主串的第 $i$个字符与模式串的第 $j$个字符失配时，主串 $i$不回溯，则假定模式串的第 $k$个字符与主串的第 $i$个字符比较， $k$值应满足条件 $1 < k < j$且 $'p_1 \cdots p_{k-1}'='p_{j-k+1} \cdots p_{j-1}'$，即 $k$为模式串的下次比较位置。 $k$值可能有多个，为了不使向右移动丢失可能的匹配，右移距离应该取最小，由于 $j-k$表示右移的距离，所以取 `max{k}`。

3)除上面两种情况外，发生失配时，主串指针 $i$不回溯，在最坏情况下，模式串从第 $1$个字符开始与主串的第 $i$个字符比较。

#### 4.2.2

>  设有字符串 $S= 'aabaabaabaac'$， $P='aabaac'$.
>
> 1)求出 $P$的 $next$数组.
>
> 2)若 $S$作主串， $P$作模式串，试给出 $KMP$算法的匹配过程。
