#### 1.2.1

>  一个算法所需时间由下述递归方程表示，试求出该算法的时间复杂度的级别(或阶).
>
> ![](https://cdn.acwing.com/media/article/image/2023/07/25/85276_82e947a22a-20230725111450.png) 
>
> 式中， $n$是问题的规模，为简单起见，设 $n$是 $2$的整数次幂。

$T(n)=2T(\frac{n}{2})+nC$

$=2[2T(\frac{n}{2^2})+\frac{nC}{2}]+nC$

$=2^2T(\frac{n}{2^2})+2nC$

$=2^2[2T(\frac{n}{2^3})+\frac{nC}{2^2}]+2nC$

$=2^3T(\frac{n}{2^3})+3nC$

$=\cdots$

$=2^kT(\frac{n}{2^k})+knC$

令 $\frac{n}{2^k}=1$,即 $n=2^k,k=\log _2 n$

代入原式得: $T(n)=2^k+ \log _2 n \times n C=n+n \log _2 nC=O(n\log _2 n)$

#### 1.2.2

> 分析以下各程序段，求出算法的时间复杂度.
>
> ![](https://cdn.acwing.com/media/article/image/2023/07/25/85276_e470f2682a-20230725114858.jpg)

```cpp
i=1;k=0;
while(i<n-1){
    k=k+10*i;
    i++;
}
```

```cpp
y=0;
while((y+1)*(y+1)<=n)
    	y=y+1;
```

```cpp
for(int i=1;i<=n;i++)
    	for(int j=1;j<=i;j++)
            for(int k=1;k<=j;k++)
                	x++;
```

```cpp
for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
        	a[i][j]=0;
```

时间复杂度分别为 $O(n)$, $O(\sqrt{n})$, $O(n^3)$, $O(nm)$.