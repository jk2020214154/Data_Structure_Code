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

**手算**思想: $next[1]$填 $0$;$next[2]$填 $1$;其他的 $next$,在不匹配的位置前,划一根分界线,模式串一步一步往后退,直到分界线之前`能对上`,或模式串完全跨过分界线为止.此时 $j$指向哪, $next$数组值就是多少.

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

**手算**思想: 先求 $next$数组,再由 $next$数组求 $nextval$数组

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



>  **教材做法**
>
> ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_d20f07ea30-20230801195014.png) 
>
> - - -
>
> ![](https://cdn.acwing.com/media/article/image/2023/08/01/85276_e3a0649030-20230801195133.png) 