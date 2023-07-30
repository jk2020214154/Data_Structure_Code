#### 数组的存储结构

* **一维数组**

设一维数组为 $a[0,\cdots,n-1]$(即有 $n$个元素,下标从 $0$到 $n-1$),类型为 $ElemType$(长度为 $L$), $a_i$的存放地址为 $LOC(a_i)=LOC(a_0)+L\times i$ ,此处 $0 \le i \le n-1$;

如果询问是第 $j$个元素(从 $1$到 $n$,注意和**下标**的差别,与下标相差 $1$),此时第 $j$个元素的存放地址为 $LOC(a_{j-1})=LOC(a_0)+L\times (j-1)$,此处 $1\le j \le n$

* **二维数组**

>  **行优先**(内存地址中一行一行的放,平常使用较多)
>
>  设二维数组为 $b[0,\cdots,n-1][0,\cdots,m-1]$(即有 $n\times m$个元素,行下标从 $0$到 $n-1$,列下标从 $0$到 $m-1$),类型为 $ElemType$(长度为 $L$), $a_{i,j}$的存放地址为 $LOC(a_{i,j})=LOC(a_{0,0})+(i \times m + j) \times L$,偏移量是 $\color{Red}{i\times m +j}$(说明前面有 $i$行,每行有 $m$个,当前行的第 $j$个)
>
>  ![](https://cdn.acwing.com/media/article/image/2023/07/30/85276_f0eaebb92e-20230730113325.png) 


>  **列优先**(内存地址中一列一列的放)
>
>  设二维数组为 $b[0,\cdots,n-1][0,\cdots,m-1]$(即有 $n\times m$个元素,行下标从 $0$到 $n-1$,列下标从 $0$到 $m-1$),类型为 $ElemType$(长度为 $L$), $a_{i,j}$的存放地址为 $LOC(a_{i,j})=LOC(a_{0,0})+(j \times n + i) \times L$,偏移量是 $\color{Red}{j\times n +i}$(说明前面有 $j$列,每列有 $n$个,当前列的第 $i$个)
>
>  ![](https://cdn.acwing.com/media/article/image/2023/07/30/85276_fd66cb642e-20230730113341.png) 

**计算公式**:  $\color{Orange}{LOC(a_{i,j})=LOC(第一个元素)+(a_{i,j}前面的元素个数)*每个元素所占用字节}$



#### 特殊矩阵的压缩存储

##### 对称矩阵



##### 三角矩阵



##### 三对角矩阵



##### 稀疏矩阵

设矩阵元素个数为 $m$ ,非零元素的个数为 $n$,其中非零元素极少,即 $n \ll m$,称为稀疏矩阵.只存储`非零元素`进行空间压缩

![](https://cdn.acwing.com/media/article/image/2023/07/30/85276_75e5dcba2e-20230730121758.png) 

* **三元组(行标,列标,值)**——顺序存储

![](https://cdn.acwing.com/media/article/image/2023/07/30/85276_8c76e5552e-20230730122111.png) 

* **十字链表**——链式存储

>  $i,j,value$分别代表非零元素所在的行号、列号和相应的元素值； $down$和 $right$分别称为向下指针和向右指针,分别用来链接同列中和同行中的下一个非零元素结点。
>
>  ![](https://cdn.acwing.com/media/article/image/2023/07/30/85276_a60435b42e-20230730122155.png) 

![](https://cdn.acwing.com/media/article/image/2023/07/30/85276_af3ca5662e-20230730125756.png) 