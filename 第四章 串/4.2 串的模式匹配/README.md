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

